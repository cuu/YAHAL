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
// Low-level task implementation for RP2040/Cortex M0+
//
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpmf-conversions"

#include <cassert>
#include "task_rp2040.h"
#include "multicore_rp2040.h"
#include "task_idle.h"
#include "system_rp2040.h"
#include "yahal_config.h"

#include "RP2040.h"
using namespace _PPB_;
using namespace _SIO_;
using namespace _TIMER_;

// Global vars
//////////////
bool multitasking_on_core[NUMBER_OF_CORES] {false};
task_idle idle_tasks[NUMBER_OF_CORES];

void task::_setup_stack(bool priv) {
    assert(_stack_size > sizeof(Stack_Frame));

    _stack_ptr = _stack_base +
                (_stack_size - sizeof(Stack_Frame));

    auto *frame = (Stack_Frame *)_stack_ptr;
    frame->crsr.psr         = 0x01000000;   // Set the Thumb-Bit
    frame->crsr.pc          = (void (*)(void))(&task::_run);
    frame->crsr.r0          = this;         // Set the 'this'-pointer
    frame->cesr.exc_return  = EXC_RETURN_THREAD_PSP;
    frame->cesr.ctrl        = priv ? 0x02 : 0x03;
}

void task::_context_switch() {
    // Trigger a PendSV interrupt
    PPB.ICSR.PENDSVSET = 1;
}

uint64_t task::millis() {
    uint32_t lo = TIMER.TIMELR;
    uint32_t hi = TIMER.TIMEHR;
    return (((uint64_t)hi << 32l) | lo) / _ticks_per_millis;
}

bool task::is_irq_context() {
    return __get_IPSR() != 0;
}

bool task::multitasking_running() {
    return multitasking_on_core[SIO.CPUID];
}

int8_t task::get_core() {
    return SIO.CPUID;
}

void task::start_scheduler() {
    assert(!multitasking_running());
    sys_call(SYS_START_SCHEDULER);
}

void task::yield() {
    if(multitasking_running() && !is_irq_context()) {
        sys_call(SYS_YIELD);
    }
}

void task::cpu_sleep() {
    __WFE();
}

void task::enterCritical() {
    NVIC_DisableIRQ(PendSV_IRQn);
//    __disable_irq();
}

void task::leaveCritical() {
    NVIC_EnableIRQ(PendSV_IRQn);
//    __enable_irq();
}

bool task::isPrivileged() const {
    uint32_t ctrl;
    if (_run_ptr[_core] == this) {
        ctrl = __get_CONTROL();
    } else {
        ctrl = ((Stack_Frame *)_stack_ptr)->cesr.ctrl;
    }
    return (ctrl & CONTROL_nPRIV_Msk) == 0;
}

bool task::isUsingFloat() const {
    uint32_t ctrl;
    if (_run_ptr[_core] == this) {
        ctrl = __get_CONTROL();
        return ctrl & 0x04;
    } else {
        ctrl = ((Stack_Frame *)_stack_ptr)->cesr.ctrl;
        return ctrl & 0x10;
    }
}

////////////////
// IRQ handlers
////////////////

extern "C" {

void __attribute__((weak)) SysTick_Handler(void) {
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

void __attribute__((naked)) PendSV_Handler(void) {
    asm volatile(
    "       .syntax unified             @ \n"
    "       mrs     r0, psp             @ \n"
    "       mov     r2, lr              @ \n"
    "       mrs     r3, control         @ \n"
    "       subs    r0, r0, #40         @ \n"
    "       stmia   r0!,{r2-r7}         @ \n"
    "       mov     r4, r8              @ \n"
    "       mov     r5, r9              @ \n"
    "       mov     r6, r10             @ \n"
    "       mov     r7, r11             @ \n"
    "       stmia   r0!,{r4-r7}         @ \n"
    "       subs    r0, r0, #40         @ \n"
    "       bl      switch_context      @ \n"
    "       adds    r0, r0, #24         @ \n"
    "       ldmia   r0!, {r4-r7}        @ \n"
    "       mov     r8, r4              @ \n"
    "       mov     r9, r5              @ \n"
    "       mov     r10, r6             @ \n"
    "       mov     r11, r7             @ \n"
    "       msr     psp, r0             @ \n"
    "       subs    r0, r0, #40         @ \n"
    "       ldmia   r0!, {r2-r7}        @ \n"
    "       mov     lr, r2              @ \n"
    "       msr     control, r3         @ \n"
    "       bx      lr                  @ \n");
}

void __attribute__((naked)) SVC_Handler(void) {
    asm volatile(
    "       movs    r0, #4              @ EXC_RETURN_PROCESS_STACK_POINTER \n"
    "       mov     r1, lr              @ \n"
    "       tst     r0, r1              @ Check which stack to use \n"
    "       beq     svc1                @ \n"
    "       mrs     r0, psp             @ Use PSP \n"
    "       b       svc2                @ \n"
    "svc1:  mrs     r0, msp             @ Use MSP \n"
    "svc2:  mov     r1, lr              @ R1 (LR) is second parameter \n"
    "       bl      SVC_Handler_C       @ Call C part of SVC_Handler \n"
    "       bx      r0                  @ Use return value as EXC_RETURN \n"
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
            // Mark this core as multitasking
            multitasking_on_core[SIO.CPUID] = true;

            // Disable the sysTick Timer
            SysTick->CTRL = 0;

            // Start the Idle task with the lowest priority (1).
            idle_tasks[SIO.CPUID].sign_up(core_t::CURRENT_CORE, 1);

            // The first task to run is the first created task
            task::_switchToHead();

            // Set scheduler priorities
            // NVIC_SetPriority(SVCall_IRQn,  2);
            NVIC_SetPriority(PendSV_IRQn,  3);
            NVIC_SetPriority(SysTick_IRQn, 3); // Lowest possible value

            // set SysTick to TICK_FREQUENCY and priority to
            // second-highest level (highest is used for
            // application IRQs like timers and GPIO)
            PPB.SYST_RVR = (CLK_SYS / TICK_FREQUENCY)-1;
            PPB.SYST_CVR = 0;
            PPB.SYST_CSR.CLKSOURCE = 1; // use CLK_SYS
            PPB.SYST_CSR.TICKINT   = 1;
            PPB.SYST_CSR.ENABLE    = 1;

            // Return to thread mode and use PSP
            exc_return = EXC_RETURN_THREAD_PSP;

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
