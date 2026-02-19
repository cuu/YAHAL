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
//
// Low-level task implementation for RP2350/Cortex M33
//
#ifndef _TASK_RP2350_H_

#include <cstdint>
#include "task.h"

//////////////////
// System call API
//////////////////
#define sys_call(code)  asm volatile ("svc %0":: "I" (code));

#define SYS_START_SCHEDULER     0
#define SYS_YIELD               1

//////////////////////////////////////////
// The following structure defines a stack
// frame without floating-point data. Such
// a frame is set up for every Task before
// it is started.
//////////////////////////////////////////

struct callee_saved_registers {

    // The following 10 registers have to be saved by
    // the context switching handler (callee-saved registers)

    uint32_t exc_return;    // the LR value inside the handler
    uint32_t ctrl;          // the CONTROL register
    uint32_t r4;            // register R4 ...
    uint32_t r5;            // .
    uint32_t r6;            // .
    uint32_t r7;            // . ...to ...
    uint32_t r8;            // .
    uint32_t r9;            // .
    uint32_t r10;           // .
    uint32_t r11;           // register R11
};

struct caller_saved_registers {

    // The following 8 registers are automatically
    // saved when handling an exception (caller-saved registers)

    task *      r0;     // register R0 (the 'this' pointer in C++ calls)
    uint32_t    r1;     // .
    uint32_t    r2;     // . ...to ...
    uint32_t    r3;     // register R3
    uint32_t    r12;    // register R12
    uint32_t    lr;     // register R14 (=LR)
    void        (*pc)();// register R15 (=PC)
    uint32_t    psr;    // PSR
};

struct Stack_Frame {
    callee_saved_registers  cesr;
    caller_saved_registers  crsr;
};

#endif // _TASK_RP2350_H_
