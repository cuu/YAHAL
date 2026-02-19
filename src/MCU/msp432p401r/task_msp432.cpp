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
// Low-level task implementation for MSP432/Cortex M4(F)
//
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpmf-conversions"

#include <cassert>
#include "task_msp432.h"
#include "task.h"
#include "task_idle.h"
#include "yahal_config.h"

#include "msp.h"
// Global vars
//////////////
bool multitasking_on_core {false};
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
    frame->cesr.ctrl = priv ? 0x02 : 0x03;
}

void task::_context_switch() {
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

uint64_t task::millis() {
    return _up_ticks[0];
}

bool task::is_irq_context() {
    return __get_IPSR() != 0;
}

bool task::multitasking_running() {
    return multitasking_on_core;
}

int8_t task::get_core() {
    return 0;
}

void task::start_scheduler() {
    assert(!multitasking_running());
    sys_call(SYS_START_SCHEDULER);
}

void task::yield() {
    if(multitasking_running()) {
        sys_call(SYS_YIELD);
    }
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
    if (_run_ptr[0] == this) {
        ctrl = __get_CONTROL();
    } else {
        ctrl = _stack_ptr[0];
    }
    return (ctrl & 0x01) == 0;
}

bool task::isUsingFloat() const {
    if (_run_ptr[0] == this) {
        return __get_CONTROL() & 0x04;
    } else {
        return _stack_ptr[0] & 0x10;
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
    "       mrs         r0, psp             @ get the current SP \n"
    "       tst         lr, #0x10           @ EXC_RETURN_INT_ONLY_STACK_FRAME \n"
    "       it          eq                  @ \n"
    "       vstmdbeq    r0!, {s16-s31}      @ push additional FP registers \n"
    "       mov         r2, lr              @ \n"
    "       mrs         r3, control         @ \n"
    "       stmdb       r0!, {r2-r11}       @ save lr, control, r4-r11 \n"
    "       bl          switch_context      @ \n"
    "       ldmia       r0!, {r2-r11}       @ get lr, control, r4-r11 \n"
    "       mov         lr, r2              @ \n"
    "       msr         control, r3         @ \n"
    "       isb                             @ arch recommendation \n"
    "       tst         lr, #0x10           @ EXC_RETURN_INT_ONLY_STACK_FRAME \n"
    "       it          eq                  @ \n"
    "       vldmiaeq    r0!, {s16-s31}      @ pop additional FP registers \n"
    "       msr         psp, r0             @ \n"
    "       bx          lr                  @ jump to new task \n");
}

void __attribute__((naked)) SVC_Handler(void) {
    asm volatile(
    "       tst         lr, #4              @ EXC_RETURN_PROCESS_STACK_POINTER \n"
    "       ite         eq                  @ \n"
    "       mrseq       r0, msp             @ R0 (SP) will be first parameter \n"
    "       mrsne       r0, psp             @ of SCV_Handler_C, \n"
    "       tst         lr, 0x20            @ EXC_RETURN_NORMAL_CALLEE_STACKING \n"
    "       it          eq                  @ \n"
    "       addeq       r0, #40             @ skip additional context if existing \n"
    "       mov         r1, lr              @ R1 (LR) is second parameter \n"
    "       bl          SVC_Handler_C       @ Call C part of SVC handler \n"
    "       bx          r0                  @ Use return value as EXC_RETURN \n"
    );
}

uint32_t SVC_Handler_C(uint32_t * sp, uint32_t exc_return) {

    // Get the PC value from the stack
    auto * pc = (uint16_t *)sp[6];
    // Move back one instruction (SVC call) and extract parameter
    uint16_t   svc_arg = pc[-1] & 0xff;

    // uint32_t p2 = sp[2]; // R2
    // uint32_t p3 = sp[3]; // R3

    switch(svc_arg) {
        /////////////////////////
        case SYS_START_SCHEDULER:
        /////////////////////////
        {
            // Mark this core as multitasking
            multitasking_on_core = true;

            // Disable the sysTick Timer
            SysTick->CTRL = 0;

            // Start the Idle task with the lowest priority (1).
            idle_tasks[0].sign_up(core_t::CURRENT_CORE, 1);

            // The first Task to run is the first created task
            task::_switchToHead();

            // Set scheduler priority to lowest possible value
            NVIC_SetPriority(PendSV_IRQn, 0xff);

            // set SysTick to TICK_FREQUENCY
            SysTick_Config(SystemCoreClock / TICK_FREQUENCY);

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
