/*
 * Task.h
 *
 *  Created on: 10.07.2017
 *      Author: andreas
 */

#ifndef _TASK_MSP432_H
#define _TASK_MSP432_H

#include "msp.h"
#include "task_base.h"

//////////////////
// System call API
//////////////////
#define sys_call(code)  asm volatile ("svc %0":: "I" (code));

#define SYS_START_SCHEDULER     0
#define SYS_YIELD               1

///////////////////
// The IRQ handlers
///////////////////

extern "C" {
void SysTick_Handler(void);
void PendSV_Handler (void);
void SVC_Handler    (void);
void SVC_Handler_C  (uint32_t *);
}

class task_msp432 : public task_base {
protected:

    task_msp432(const char * n, uint16_t stack_size = DEFAULT_STACK_SIZE)
    : task_base(n, stack_size) {
        // Dummy code to get rid of some warning...
        _stack_base = task_base::_stack_base;
        _stack_size = task_base::_stack_size;
        _stack_ptr  = task_base::_stack_ptr;
    }

    virtual ~task_msp432() = default;

    // No copy, no assignment
    task_msp432             (const task_msp432 &) = delete;
    task_msp432 & operator= (const task_msp432 &) = delete;

    // The IRQ handlers are our friends
    ///////////////////////////////////
    friend void SysTick_Handler(void);
    friend void PendSV_Handler (void);
    friend void SVC_Handler    (void);
    friend void SVC_Handler_C  (uint32_t *);

    bool isPrivileged() const override;
    bool isUsingFloat() const override;

private:

    using task_base::_stack_base;
    using task_base::_stack_size;
    using task_base::_stack_ptr;

    void _setup_stack(bool priv) override;

    // The stack frame as a struct
    struct Stack_Frame;

    static uint32_t _exc_ret;
};

#endif /* _TASK_MSP432_H */
