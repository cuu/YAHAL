// ---------------------------------------------
//           This file is part of
//      _  _   __    _   _    __    __
//     ( \/ ) /__\  ( )_( )  /__\  (  )
//      \  / /(__)\  ) _ (  /(__)\  )(__
//      (__)(__)(__)(_) (_)(__)(__)(____)
//
//     Yet Another HW Abstraction Library
//      Copyright (C) Andreas Terstegge
//      BSD Licensed (see file LICENSE)
//
// ---------------------------------------------

#include <array>
#include <cassert>
#include <cstdlib>

#include "multicore_rp2040.h"
#include "task.h"
#include "RP2040.h"
using namespace _SIO_;
using namespace _PPB_;
using namespace _PSM_;

#pragma GCC push_options
#pragma GCC optimize("O0")

// Static members
std::function<void(void)> multicore_rp2040::_f;

void multicore_rp2040::fifo_push_blocking(uint32_t val) {
    while(SIO.FIFO_ST.RDY != 1) ;
    SIO.FIFO_WR = val;
    __SEV();
}

uint32_t multicore_rp2040::fifo_pop_blocking() {
    while(SIO.FIFO_ST.VLD != 1) ;
    return SIO.FIFO_RD;
}

uint32_t multicore_rp2040::fifo_drain() {
    uint32_t val {0};
    while(SIO.FIFO_ST.VLD) val = SIO.FIFO_RD;
    return val;
}

void multicore_rp2040::start_on_core1(
            std::function<void(void)> func,
            uint8_t * stack,
            uint32_t * vec_table) {
    // Store the method to execute
    _f = func;
    // When no stack if given, use SCRATCH_Y
    if (stack == nullptr) {
        extern uint32_t __StackYTop;
        stack = (uint8_t *)&__StackYTop;
    }
    // When no vector table is given, use the current one
    if (vec_table == nullptr) {
        vec_table = (uint32_t *)PPB.VTOR.value;
    }
    // Set up the command array
    std::array<uint32_t, 6> cmd_sequence = {
            0, 0, 1,
            (uint32_t)vec_table,
            (uint32_t)stack,
            (uint32_t)_run
    };

    uint32_t seq = 0;
    // Start the communication with core 1, using a
    // simple state machine, which will transfer all
    // necessary information to run the code
    do {
        uint32_t cmd = cmd_sequence[seq];
        // Always drain the READ FIFO (from core 1) before sending a 0
        if (!cmd) {
            fifo_drain();
            // Execute a SEV as core 1 may be waiting for FIFO space via WFE
            __SEV();
        }
        fifo_push_blocking(cmd);
        uint32_t response = fifo_pop_blocking();
        // Move to next state on correct response
        // (echo-d value), otherwise start over
        seq = (cmd == response) ? seq + 1 : 0;
    } while (seq < cmd_sequence.size());
}

//void __attribute__ ((naked)) task_trampoline() {
//    asm("pop {r0-r7}");
//    asm("mov r12, r4");
//    asm("mov lr,  r5");
//    asm("bx  r6     ");
//}
//
//void multicore_rp2040::start_on_core1(const task & t) {
//    //assert(!t.isLinkedIn());
//    start_on_core1(task_trampoline, t.getSavedSP()+sizeof(callee_saved_registers));
//}

void multicore_rp2040::reset_core1() {
    task::sleep_ms(10);
    // Reset core 1
    PSM_SET.FRCE_OFF.proc1 = 1;
    // Wait until reset has been performed
    while (!PSM.FRCE_OFF.proc1) ;
    // Bring core 1 back out of reset.
    PSM_CLR.FRCE_OFF.proc1 = 1;
    // Wait for core 1 to send us a 0 via the FIFO
    uint32_t value = fifo_pop_blocking();
    // check the pushed value
    assert(value == 0);
    (void) value; // silence warning
    task::sleep_ms(10);
}

// Helper method
void multicore_rp2040::_run() {
    _f();
    exit(0);
}

#pragma GCC pop_options
