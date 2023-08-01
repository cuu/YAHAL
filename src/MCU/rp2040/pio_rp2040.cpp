/*
 * pio_rp2040.cpp
 *
 *  Created on: 25.12.2022
 *      Author: andreas
 */

#include <cassert>
#include "pio_rp2040.h"

using namespace _PIO0_;
using namespace _PIO1_;

// The two PIO instances
pio_rp2040 pio_rp2040::pio0(PIO0, 0);
pio_rp2040 pio_rp2040::pio1(PIO1, 1);

function<void()> pio_rp2040::_handler_pio0[12] = { nullptr };
function<void()> pio_rp2040::_handler_pio1[12] = { nullptr };

void SM_regs::init() {
    // Initialize SM registers with reset values;
    SM_CLKDIV                 = 0;
    SM_CLKDIV.INT             = 1;
    SM_EXECCTRL               = 0;
    SM_EXECCTRL.WRAP_TOP      = 0x1f;
    SM_SHIFTCTRL              = 0;
    SM_SHIFTCTRL.OUT_SHIFTDIR = 1;
    SM_SHIFTCTRL.IN_SHIFTDIR  = 1;
    SM_PINCTRL                = 0;
    SM_PINCTRL.SET_COUNT      = 5;
}

void SM::setRegister(out_dest_t reg, uint32_t val,
                     uint8_t offset, uint8_t size) {
    // Store current configuration
    bool en = isEnabled();
    disable();
    uint8_t out_base  = regs.SM_PINCTRL.OUT_BASE;
    uint8_t out_count = regs.SM_PINCTRL.OUT_COUNT;
    // Configure bits to write
    regs.SM_PINCTRL.OUT_BASE  = offset;
    regs.SM_PINCTRL.OUT_COUNT = size;
    // Empty the TX Fifo
    while(pio.FLEVEL & (0xf << (sm_index << 3))) {
        execute( op_PULL(0, 0) );
    }
    // Write value to TX Fifo first.
    // Then pull it and write it to destination.
    writeTxFifo(val);
    execute( op_PULL(0, 0)      );
    execute( op_OUT (0, reg, 0) );
    // Restore original state
    regs.SM_PINCTRL.OUT_BASE  = out_base;
    regs.SM_PINCTRL.OUT_COUNT = out_count;
    if (en) enable();
}

void SM::setClock(uint32_t hz) {
    regs.SM_CLKDIV.INT = 125000000 / hz;
    uint64_t frac = ((125000000 % hz) << 8);
    frac /= hz;
    regs.SM_CLKDIV.FRAC = frac;
}

void SM::attachIrq(function<void()> handler) {
    if (pio_index)
        pio_rp2040::_handler_pio1[sm_index + 8] = handler;
    else
        pio_rp2040::_handler_pio0[sm_index + 8] = handler;
}

void SM::enableIrq() {
    pio_set.IRQ0_INTE = 1 << (sm_index + 8);
}

void SM::disableIrq() {
    pio_clr.IRQ0_INTE = 1 << (sm_index + 8);
}

void SM::attachTXNFULLIrq(function<void()> handler) {
    if (pio_index)
        pio_rp2040::_handler_pio1[sm_index + 4] = handler;
    else
        pio_rp2040::_handler_pio0[sm_index + 4] = handler;
}

void SM::enableTXNFULLIrq() {
    pio_set.IRQ0_INTE = 1 << (sm_index + 4);
}

void SM::disableTXNFULLIrq() {
    pio_clr.IRQ0_INTE = 1 << (sm_index + 4);
}

void SM::attachRXNEMPTYIrq(function<void()> handler) {
    if (pio_index)
        pio_rp2040::_handler_pio1[sm_index + 0] = handler;
    else
        pio_rp2040::_handler_pio0[sm_index + 0] = handler;
}

void SM::enableRXNEMPTYIrq() {
    pio_set.IRQ0_INTE = 1 << (sm_index);
}

void SM::disableRXNEMPTYIrq() {
    pio_clr.IRQ0_INTE = 1 << (sm_index);
}

pio_rp2040::pio_rp2040(PIO0_t & pio, uint8_t pio_index)
: _pio(pio),
  _pio_xor(*(PIO0_t *)((uint8_t *)&pio + 0x1000)),
  _pio_set(*(PIO0_t *)((uint8_t *)&pio + 0x2000)),
  _pio_clr(*(PIO0_t *)((uint8_t *)&pio + 0x3000)),
  _pio_index(pio_index),
  _next_free_addr(0) {
    // Set base address of SM register banks
    _sm_regbanks = (SM_regs *)&pio.SM0_CLKDIV;
    // Disable and restart all state machines
    _pio.CTRL.SM_ENABLE  = 0x0;
    _pio.CTRL.SM_RESTART = 0xf;
    // Erase instruction memory
    for(int i=0; i < 32; ++i) {
        _pio.INSTR_MEM[i] = 0;
    }
    // Initially all state machines are not in use
    for(int i=0; i < 4; ++i) {
        _in_use[i] = false;
    }
    // Enable PIO interrupts in NVIC
    NVIC_EnableIRQ(PIO0_IRQ_0_IRQn);
    NVIC_EnableIRQ(PIO1_IRQ_0_IRQn);
}

pio_rp2040::~pio_rp2040() {
    // Disable all state machines
    _pio.CTRL.SM_ENABLE  = 0x0;
}

SM* pio_rp2040::loadProgram(const pio_program & prgm) {
    // Find a free state machine
    uint8_t sm_index=0;
    for(sm_index=0; sm_index < 4; ++sm_index) {
        if (!_in_use[sm_index]) break;
    }
    assert(sm_index < 4);
    // Set 'used' marker
    _in_use[sm_index] = true;
    // Check program origin
    uint8_t load_at_addr = 0;
    if (prgm.origin == -1) {
        // Reloctable program
        load_at_addr = _next_free_addr;
    } else {
        // Absolute origin
        assert(prgm.origin >= _next_free_addr);
        load_at_addr = prgm.origin;
    }
    // Check program size
    assert((load_at_addr + prgm.length) <= 32);
    // Load the PIO program
    for(int i=0; i < prgm.length; i++) {
        uint16_t inst = prgm.instructions[i];
        // Relocate JMP instruction if needed
        if (is_JMP(inst) && (prgm.origin == -1)) {
            inst += load_at_addr;
        }
        _pio.INSTR_MEM[i + load_at_addr] = inst;
    }
    // Generate a state machine and initialize it
    SM* sm = new SM(_pio, _pio_set, _pio_clr, _pio_index, sm_index,
                    load_at_addr, _sm_regbanks[sm_index]);
    // Set the initial PC
    sm->setRegister(out_dest_t::PC, load_at_addr);
    // Update the next free addr
    _next_free_addr += load_at_addr + prgm.length;
    // Return the state machine in charge
    return sm;
}

extern "C" {
    void PIO0_IRQ_0_Handler(void) {
        uint32_t status = PIO0.IRQ0_INTS;
        while (uint8_t pos = __builtin_ffs(status)) {
            status ^= 1 << --pos;
            if (pos > 7) {
                PIO0.IRQ = 1 << (pos - 8);
            }
            if (pio_rp2040::_handler_pio0[pos])
                pio_rp2040::_handler_pio0[pos]();
        }
    }

    void PIO1_IRQ_0_Handler(void) {
        uint32_t status = PIO1.IRQ0_INTS;
        while (uint8_t pos = __builtin_ffs(status)) {
            status ^= 1 << --pos;
            if (pos > 7) {
                PIO1.IRQ = 1 << (pos - 8);
            }
            if (pio_rp2040::_handler_pio1[pos])
                pio_rp2040::_handler_pio1[pos]();
        }
    }
}
