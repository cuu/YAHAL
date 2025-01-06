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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpmf-conversions"

#include "RP2350.h"

#include "task.h"
#include "task_idle.h"
#include "system_rp2350.h"
#include "yahal_config.h"
#include <cassert>

using namespace _PPB_;

//////////////////
// System call API
//////////////////
#define sys_call(code)  asm volatile ("svc %0":: "I" (code));

#define SYS_START_SCHEDULER     0
#define SYS_YIELD               1

// Global vars
//////////////
task_idle idle_task;

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

void task::_setup_stack(bool priv) {
    assert(_stack_size > sizeof(Stack_Frame));

    _stack_ptr = _stack_base +
                (_stack_size - sizeof(Stack_Frame));

    auto *frame = (Stack_Frame *)_stack_ptr;
    frame->crsr.psr         = 0x01000000;   // Set the Thumb-Bit
    frame->crsr.pc          = (void (*)(void))(&task::_run);
    frame->crsr.r0          = this;         // Set the 'this'-pointer
    frame->cesr.exc_return  = EXC_RETURN_THREAD_PSP_NOFP;
    frame->cesr.ctrl        = CONTROL_SPSEL_PSP |
                              (priv ? CONTROL_PRIV : CONTROL_NOT_PRIV);
}

void task::_context_switch() {
    // Trigger a PendSV interrupt
    PPB.ICSR.PENDSVSET = 1;
}

uint64_t task::millis() {
    uint32_t lo = _TIMER0_::TIMER0.TIMELR;
    uint32_t hi = _TIMER0_::TIMER0.TIMEHR;
    return (((uint64_t)hi << 32l) | lo) / timer_ticks_per_us / 1000;
}

void task::start_scheduler() {
    sys_call(SYS_START_SCHEDULER);
}

void task::yield() {
    sys_call(SYS_YIELD);
}

void task::cpu_sleep() {
    __WFE();
}

void task::enterCritical() {
    NVIC_DisableIRQ(PendSV_IRQn);
//    __disable_irq();
    __DSB();
    __ISB();
}

void task::leaveCritical() {
    NVIC_EnableIRQ(PendSV_IRQn);
//    __enable_irq();
    __ISB();
}

bool task::isPrivileged() const {
    uint32_t ctrl;
    if (_run_ptr == this) {
        ctrl = __get_CONTROL();
    } else {
        ctrl = ((Stack_Frame *)_stack_ptr)->cesr.ctrl;
    }
    return (ctrl & CONTROL_nPRIV_Msk) == 0;
}

bool task::isUsingFloat() const {
    uint32_t ctrl;
    if (_run_ptr == this) {
        ctrl = __get_CONTROL();
    } else {
        ctrl = ((Stack_Frame *)_stack_ptr)->cesr.ctrl;
    }
    return ctrl & CONTROL_FPCA_Msk;
}

////////////////
// IRQ handlers
////////////////

extern "C" {

void SysTick_Handler(void) __attribute__((weak));
void SysTick_Handler(void) {
    task::_tick_handler();
}

uint8_t * switch_context(uint8_t * last_sp) {
    task::_setStackPtr(last_sp);
#ifdef CHECK_STACK_OVERFLOW
    assert((last_sp - task::_getStackBase()) > 10);
#endif
    task::_switchToNext();
    return task::_getStackPtr();
}

void PendSV_Handler(void) __attribute__((naked));
void PendSV_Handler(void) {

    asm volatile(
    "       mrs         r0, psp             @ \n"
    "       tst         lr, #0x10           @ \n"
    "       it          eq                  @ \n"
    "       vstmdbeq    r0!, {s16-s31}      @ \n"
    "       mov         r2, lr              @ \n"
    "       mrs         r3, control         @ \n"
    "       stmdb       r0!, {r2-r11}       @ \n"
    "       bl          switch_context      @ \n"
    "       ldmia       r0!, {r2-r11}       @ \n"
    "       mov         lr, r2              @ \n"
    "       msr         control, r3         @ \n"
    "       isb                             @ \n"
    "       tst         lr, #0x10           @ \n"
    "       it          eq                  @ \n"
    "       vldmiaeq    r0!, {s16-s31}      @ \n"
    "       msr         psp, r0             @ \n"
    "       bx          lr                  @ \n");
}

void SVC_Handler(void) __attribute__((naked));
void SVC_Handler(void) {
    asm volatile(
    "       tst         lr, #4              @ EXC_RETURN_PROCESS_STACK_POINTER \n"
    "       ite         eq                  @ \n"
    "       mrseq       r0, msp             @ R0 (SP) will be first parameter \n"
    "       mrsne       r0, psp             @ of SCV_Handler_C, \n"
    "       tst         lr, 0x20            @ EXC_RETURN_NORMAL_CALLEE_STACKING \n"
    "       it          eq                  @ \n"
    "       addeq       r0, #40             @ \n"
    "       mov         r1, lr              @ R1 (LR) is second parameter \n"
    "       bl          SVC_Handler_C       @ Call C part of SVC handler \n"
    "       bx          r0                  @ Use return value as EXC_RETURN \n"
    );
}

uint32_t SVC_Handler_C(uint32_t * sp, uint32_t exc_return) {

    // Get the PC value from the stack
    auto * pc = (uint16_t *)sp[6];
    // Move back one instruction (SVC call) and extract parameter
    uint16_t svc_arg = pc[-1] & 0xff;

    // uint32_t p2 = sp[2]; // R2
    // uint32_t p3 = sp[3]; // R3

    switch(svc_arg) {
        /////////////////////////
        case SYS_START_SCHEDULER:
        /////////////////////////
        {
            // Disable the sysTick Timer
            SysTick->CTRL = 0;

            // Start the Idle Task with the lowest priority (1).
            idle_task.start(1);

            // The first Task to run is the first created task
            task::_switchToHead();

            // Set scheduler priorities
            // NVIC_SetPriority(SVCall_IRQn,  14);
            NVIC_SetPriority(PendSV_IRQn,  15);
            NVIC_SetPriority(SysTick_IRQn, 15); // Lowest possible value

            // Set SysTick to TICK_FREQUENCY. Use the internal
            // reference clock, not the CPU system clock.
            PPB.SYST_RVR = (systick_ref_freq / TICK_FREQUENCY)-1;
            PPB.SYST_CVR = 0;
            PPB.SYST_CSR.CLKSOURCE = 0; // use external ref clock
            PPB.SYST_CSR.TICKINT   = 1;
            PPB.SYST_CSR.ENABLE    = 1;

            // Return to (secure) thread mode and use PSP
            exc_return = EXC_RETURN_THREAD_PSP_NOFP;

            // Only restore registers r0-PSR, because these
            // will be restored on return of the SVC-handler
            __set_PSP((uint32_t)(task::_getStackPtr() +
                      sizeof(callee_saved_registers)));

            // Set control register (set privileged)
            __set_CONTROL(((Stack_Frame *)task::_getStackPtr())->cesr.ctrl);
            __ISB();
            break;
        }
        ///////////////
        case SYS_YIELD:
        ///////////////
        {
            task::_scheduler();
            break;
        }
        ////////
        default:
        ////////
        {
            assert(false);
        }
    }
    return exc_return;
}

} // extern "C"

#pragma GCC diagnostic pop
