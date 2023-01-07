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

pio_rp2040 pio_rp2040::pio0(PIO0);
pio_rp2040 pio_rp2040::pio1(PIO1);

pio_rp2040::pio_rp2040(PIO0_t & pio)
: _pio(pio),
  _pio_xor(*(PIO0_t *)((uint8_t *)&pio + 0x1000)),
  _pio_set(*(PIO0_t *)((uint8_t *)&pio + 0x2000)),
  _pio_clr(*(PIO0_t *)((uint8_t *)&pio + 0x3000)),
  _next_free_addr(0) {
    // Set base address of SM register banks
    _sm_regbanks = (SM_regs *)&pio.SM0_CLKDIV;
    // Disable all state machines, just in case..
    _pio.CTRL.SM_ENABLE  = 0x0;
    // Restart all state machines
    _pio.CTRL.SM_RESTART = 0xf;
    // Erase instruction memory
    for(int i=0; i < 32; ++i) {
        _pio.INSTR_MEM[i] = 0;
    }
}

pio_rp2040::~pio_rp2040() {
    // Disable all state machines, just in case..
    _pio.CTRL.SM_ENABLE  = 0x0;
    _pio.CTRL.SM_ENABLE  = 0x0;
}

SM pio_rp2040::loadProgram(const pio_program & prgm) {
    // Find a free state machine
    uint8_t sm_index=0;
    for(sm_index=0; sm_index < 4; ++sm_index) {
        if (!(_pio.CTRL.SM_ENABLE & (1 << sm_index)))
            break;
    }
    assert(sm_index < 4);
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
        if (is_JMP(inst)) {
            inst += load_at_addr;
        }
        _pio.INSTR_MEM[i + load_at_addr] = inst;
    }
    // Generate a state machine and initialize it
    SM sm(_pio, _pio_set, _pio_clr, sm_index,
          load_at_addr, _sm_regbanks[sm_index]);
    // Set the initial PC
    sm.setRegister(out_dest_t::PC, load_at_addr);
    // Update the next free addr
    _next_free_addr += load_at_addr + prgm.length;
    // Return the state machine in charge
    return sm;
}

