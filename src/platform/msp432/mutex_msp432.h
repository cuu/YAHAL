/*
 * task_mutex.h
 *
 * A mutex implementation for tasks
 *
 *  Created on: 24.07.2017
 *      Author: Andreas Terstegge
 */

#ifndef _MUTEX_MSP432_H
#define _MUTEX_MSP432_H

#include "yahal_assert.h"
#include "mutex_interface.h"
#include "task_msp432.h"
#include "core_cm4.h"

class mutex_msp432 : public mutex_interface
{
  public:
    mutex_msp432() : _lock(0) { }
    virtual ~mutex_msp432() = default;

    // No copy, no assignment
    mutex_msp432             (const mutex_msp432 &) = delete;
    mutex_msp432 & operator= (const mutex_msp432 &) = delete;

    void lock() override {
        int status;
        do {
            while(__LDREXW(&_lock) != 0) task_msp432::yield();
            status = __STREXW(1, &_lock);
        } while (status);
        __DMB();
    }

    void unlock() override {
        __DMB();
        _lock = 0;
    }

    bool try_lock() override {
        if (__LDREXW(&_lock) == 0) {
            return __STREXW(1, &_lock) == 0;
        } else {
            return false;
        }
        __DMB();
    }

  private:

    volatile uint32_t _lock;
};

#endif /* _MUTEX_MSP432_H */
