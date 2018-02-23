/*
 * Task.cpp
 *
 *  Created on: 10.07.2017
 *      Author: andreas
 */

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpmf-conversions"

#include <task_msp432.h>
#include <task_idle.h>
#include "yahal_assert.h"

#include <cstring>

inline void task_base::enable_irq()             { __enable_irq();      }
inline void task_base::disable_irq()            { __disable_irq();     }
inline void task_base::yield()                  { sys_call(SYS_YIELD); }
inline void task_base::cpu_sleep()              { __WFE();             }
inline void task_base::trigger_context_switch() { SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk; }

//////////////////////////////////////////
// The following structure defines a stack
// frame without floating-point data. Such
// a frame is set up for every Task before
// it is started.
//////////////////////////////////////////

struct task_msp432::Stack_Frame {

    // The following 9 registers have to be saved by
    // the context switching handler (callee-saved registers)

    uint32_t    ctrl;   // the CONTROL register, bit 8 set: FP stack frame
    uint32_t    r4;     // register R4 to R11
    uint32_t    r5;     // .
    uint32_t    r6;     // .
    uint32_t    r7;     // . to ...
    uint32_t    r8;     // .
    uint32_t    r9;     // .
    uint32_t    r10;    // .
    uint32_t    r11;    // register R11

    // The following 8 registers are automatically
    // saved when handling an exception (caller-saved registers)

    task_base *      r0;     // register R0 (the 'this' pointer in C++ calls)
    uint32_t    r1;     // .
    uint32_t    r2;     // . to ...
    uint32_t    r3;     // .
    uint32_t    r12;    // register R12
    uint32_t    lr;     // register R14 (=LR)
    void        (*pc)(void);  //    R15 (=PC)
    uint32_t    psr;    // PSR
};

///////////////////////////////
// Definition of static members
///////////////////////////////

uint32_t task_msp432::_exc_ret = 0;

///////////////////////////////////////////////////
// Our own version of some special getters/setters,
// which are working now with stack POINTERs!
///////////////////////////////////////////////////

__attribute__ (( always_inline))
static inline uint32_t * get_PSP(void)
{
  register uint32_t * result;
  asm volatile ("mrs %0, psp" : "=r" (result) );
  return(result);
}

__attribute__ ((always_inline))
static inline void set_PSP(const uint32_t * psp)
{
  asm volatile ("msr psp, %0" : : "r" (psp) : "sp");
}

__attribute__ ((always_inline))
static inline uint32_t * get_MSP(void)
{
  register uint32_t * result;
  asm volatile ("mrs %0, msp\n" : "=r" (result) );
  return(result);
}

bool task_msp432::isPrivileged() const {
    uint32_t ctrl;
    if (_run_ptr == this) {
        ctrl = __get_CONTROL();
    } else {
        ctrl = _stack_ptr[0];
    }
    return (ctrl & 0x01) == 0;
}

bool task_msp432::isUsingFloat() const {
    if (_run_ptr == this) {
        return __get_CONTROL() & 0x04;
    } else {
        return _stack_ptr[0] & 0x10;
    }
}

void task_msp432::setup_stack(bool priv) {
    uint16_t frame_size = sizeof(Stack_Frame) / sizeof(uint32_t);
    yahal_assert(_stack_size > frame_size);

    _stack_ptr = &_stack_base[_stack_size - frame_size];

    Stack_Frame *frame = (Stack_Frame *)_stack_ptr;
    frame->psr  = 0x01000000;   // Set the Thumb-Bit
    frame->pc   = (void (*)(void))(&task_msp432::_run);
    frame->r0   = this;         // Set the 'this'-pointer
    frame->ctrl = priv ? 0x02 : 0x03;
}

////////////////
// IRQ handlers
////////////////

extern "C" {

    void SysTick_Handler(void) {
        task_base::tick_handler();
    }


    void PendSV_Handler(void) __attribute__((naked));
    void PendSV_Handler(void) {

        asm volatile("mrs       r0, psp       ");
        asm volatile("mrs       r3, control   ");

        asm volatile("tst       lr, #0x10     ");
        asm volatile("itt       eq            ");
        asm volatile("orreq     r3, #0x10     ");
        asm volatile("vstmdbeq  r0!, {s16-s31}");
        asm volatile("stmdb     r0!, {r3-r11} ");

        register uint32_t * psp asm("r0");
        task_base::_run_ptr->_stack_ptr = psp;
        #ifdef CHECK_STACK_OVERFLOW
        yahal_assert((psp - task_base::_run_ptr->_stack_base) > 10);
        #endif
        task_base::_run_ptr = task_msp432::_run_next;
        psp = task_base::_run_ptr->_stack_ptr;

        asm volatile("ldmia     r0!, {r3-r11} ");
        asm volatile("mvn       lr, #2        "); // ~2 = 0xfffffffd
        asm volatile("tst       r3, #0x10     ");
        asm volatile("itt       ne            ");
        asm volatile("bicne     lr, #0x10     ");
        asm volatile("vldmiane  r0!, {s16-s31}");

        asm volatile("msr       control, r3   ");
        asm volatile("msr       psp, r0       ");

        asm volatile("bx        lr            ");
    }

    void SVC_Handler(void) __attribute__((naked));
    void SVC_Handler(void) {
        register uint32_t * sp asm("r0");
        register uint32_t   lr asm("lr");

        // get the correct stack pointer
        sp = (lr & 0x4) ? get_PSP() : get_MSP();
        task_msp432::_exc_ret = lr;
        SVC_Handler_C(sp);
        lr = task_msp432::_exc_ret;
        asm volatile("bx lr");
    }

    void SVC_Handler_C(uint32_t * args) {
        // Get the SVC argument
        uint16_t * pc = (uint16_t *)args[6];
        uint16_t   svc_arg = pc[-1] & 0xff;

//        uint32_t p0 = args[0];
//        uint32_t p1 = args[1];
//        uint32_t p2 = args[2];
//        uint32_t p3 = args[3];

        switch(svc_arg) {
            /////////////////////////
            case SYS_START_SCHEDULER:
            /////////////////////////
            {
                // Start the Idle Task with the lowest priority (1).
                (new task_idle<task_msp432>)->start(1);

                // The first Task to run is the first created task
                task_msp432::_run_ptr = task_msp432::_head;

                // Set scheduler priority to lowest possible value
                NVIC_SetPriority(PendSV_IRQn, 0xff);

                // set SysTick to TICK_FREQUENCY
                SysTick_Config(SystemCoreClock / TICK_FREQUENCY);

                // Return in unprivileged mode
                task_msp432::_exc_ret = 0xfffffffd;

                // Only restore regiters r0-PSR, because these
                // will be restored on return of the SVC-handler
                set_PSP(task_msp432::_run_ptr->_stack_ptr + 9);

                // Set control register
                __set_CONTROL(task_msp432::_run_ptr->_stack_ptr[0]);
                __ISB();
                break;
            }
            ///////////////
            case SYS_YIELD:
            ///////////////
            {
                task_msp432::run_scheduler();
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

}

#pragma GCC diagnostic pop
