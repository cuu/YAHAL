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

#include "RP2040.h"
using namespace _PPB_;

#include "yahal_config.h"
#include "yahal_assert.h"
#include "task.h"
#include "task_idle.h"

uint32_t SystemCoreClk = 125000000;

//////////////////
// System call API
//////////////////
#define sys_call(code)  asm volatile ("svc %0":: "I" (code));

#define SYS_START_SCHEDULER     0
#define SYS_YIELD               1

// Definition of static members
///////////////////////////////
static uint32_t _exec_ret = 0;

//////////////////////////////////////////
// The following structure defines a stack
// frame without floating-point data. Such
// a frame is set up for every Task before
// it is started.
//////////////////////////////////////////

struct Stack_Frame {

    // The following 9 registers have to be saved by
    // the context switching handler (callee-saved registers)

    uint32_t    ctrl;   // the CONTROL register
    uint32_t    r4;     // register R4 ...
    uint32_t    r5;     // .
    uint32_t    r6;     // .
    uint32_t    r7;     // . ...to ...
    uint32_t    r8;     // .
    uint32_t    r9;     // .
    uint32_t    r10;    // .
    uint32_t    r11;    // register R11

    // The following 8 registers are automatically
    // saved when handling an exception (caller-saved registers)

    task *      r0;     // register R0 (the 'this' pointer in C++ calls)
    uint32_t    r1;     // .
    uint32_t    r2;     // . ...to ...
    uint32_t    r3;     // .
    uint32_t    r12;    // register R12
    uint32_t    lr;     // register R14 (=LR)
    void        (*pc)(void);  //    R15 (=PC)
    uint32_t    psr;    // PSR
};

void task::_setup_stack(bool priv) {
    yahal_assert(_stack_size > sizeof(Stack_Frame));

    _stack_ptr = _stack_base +
                (_stack_size - sizeof(Stack_Frame));

    Stack_Frame *frame = (Stack_Frame *)_stack_ptr;

    frame->psr  = 0x01000000;   // Set the Thumb-Bit
    frame->pc   = (void (*)(void))(&task::_run);
    frame->r0   = this;         // Set the 'this'-pointer
    frame->ctrl = priv ? 0x02 : 0x03;
}

void task::_context_switch() {
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

void task::_nonOS_sleep(uint32_t ms) {
    // Configure SysTick as 1 ms timer
    SysTick->LOAD = SystemCoreClk / 1000 - 1;
    SysTick->VAL  = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_ENABLE_Msk;
    for (uint32_t i=0; i < ms; ++i) {
        while ( !(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) ) ;
    }
    // Disable SysTick
    SysTick->CTRL = 0;
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
        ctrl = _stack_ptr[0];
    }
    return (ctrl & 0x01) == 0;
}

bool task::isUsingFloat() const {
    if (_run_ptr == this) {
        return __get_CONTROL() & 0x04;
    } else {
        return _stack_ptr[0] & 0x10;
    }
}

////////////////
// IRQ handlers
////////////////

extern "C" {

void SysTick_Handler(void) {
    task::_tick_handler();
}


void PendSV_Handler(void) __attribute__((naked));
void __attribute__((optimize("O0"))) PendSV_Handler(void) {

    asm volatile(
    "       .syntax unified             @ \n"
    "       mrs     r0, psp             @ \n"
    "       mrs     r3, control         @ \n"
    "       subs    r0, r0, #36         @ \n"
    "       stmia   r0!,{r3-r7}         @ \n"
    "       mov     r4, r8              @ \n"
    "       mov     r5, r9              @ \n"
    "       mov     r6, r10             @ \n"
    "       mov     r7, r11             @ \n"
    "       stmia   r0!,{r4-r7}         @ \n"
    "       subs    r0, r0, #36         @ \n");

    register uint8_t * psp asm("r0");
    task::_setStackPtr(psp);
#ifdef CHECK_STACK_OVERFLOW
    yahal_assert((psp - task::_getStackBase()) > 10);
#endif
    task::_switchToNext();
    psp = task::_getStackPtr();

    asm volatile(
    "       .syntax unified             @ \n"
    "       movs    r1, #2              @ \n"
    "       mvns    r2, r1              @ \n"
    "       mov     lr, r2              @ \n"
    "       adds    r0, r0, #20         @ \n"
    "       ldmia   r0!, {r4-r7}        @ \n"
    "       mov     r8, r4              @ \n"
    "       mov     r9, r5              @ \n"
    "       mov     r10, r6             @ \n"
    "       mov     r11, r7             @ \n"
    "       msr     psp, r0             @ \n"
    "       subs    r0, r0, #36         @ \n"
    "       ldmia   r0!, {r3-r7}        @ \n"
    "       msr     control, r3         @ \n"
    "       bx      lr                  @ \n");
}


void SVC_Handler(void) __attribute__((naked));
void SVC_Handler(void) {
    asm volatile(
    "       movs    r0, #4              @ \n"
    "       mov     r1, lr              @ \n"
    "       tst     r0, r1              @ Check which stack to use \n"
    "       beq     svc1                @ \n"
    "       mrs     r0, psp             @ Use PSP \n"
    "       b       svc2                @ \n"
    "svc1:  mrs     r0, msp             @ Use MSP \n"
    "svc2:  ldr     r2, =%[exec_ret]    @ \n"
    "       str     r1, [r2]            @ Store current LR value\n"
    "       bl      SVC_Handler_C       @ Call C part of SVC_Handler \n"
    "       ldr     r2, =%[exec_ret]    @ \n"
    "       ldr     r1, [r2]            @ \n"
    "       bx      r1                  @ \n"
    : : [exec_ret] "i" (&_exec_ret) );
}

void SVC_Handler_C(uint32_t * args) {
    // Get the SVC argument
    uint16_t * pc = (uint16_t *)args[6];
    uint16_t   svc_arg = pc[-1] & 0xff;

    // uint32_t p0 = args[0];
    // uint32_t p1 = args[1];
    // uint32_t p2 = args[2];
    // uint32_t p3 = args[3];

    switch(svc_arg) {
        /////////////////////////
        case SYS_START_SCHEDULER:
        /////////////////////////
        {
            // Start the Idle Task with the lowest priority (1).
            (new task_idle)->start(1);

            // The first Task to run is the first created task
            task::_switchToHead();

            // Set scheduler priority to lowest possible value
            NVIC_SetPriority(PendSV_IRQn, 0xff);

            // set SysTick to TICK_FREQUENCY
            SysTick_Config(SystemCoreClk / TICK_FREQUENCY);

            // Return to thread mode and use PSP
            _exec_ret = EXC_RETURN_THREAD_PSP;

            // Only restore registers r0-PSR, because these
            // will be restored on return of the SVC-handler
            __set_PSP((uint32_t)(task::_getStackPtr() + 36));

            // Set control register (set privileged)
            __set_CONTROL(task::_getStackPtr()[0]);
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
            yahal_assert(false);
        }
    }
}

} // extern "C"

#pragma GCC diagnostic pop
