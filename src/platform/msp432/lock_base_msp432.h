/*
 * lock_base_msp432.h
 *
 * A basic lock implementation for msp432
 *
 *  Created on: 24.07.2017
 *      Author: Andreas Terstegge
 */

#ifndef _LOCK_BASE_MSP432_H
#define _LOCK_BASE_MSP432_H

#include "lock_base_interface.h"
#include "msp.h"
#include "core_cm4.h"

class lock_base_msp432 : public lock_base_interface
{
  public:
    lock_base_msp432() : _lock(0) { }
    virtual ~lock_base_msp432() = default;

    // No copy, no assignment
    lock_base_msp432             (const lock_base_msp432 &) = delete;
    lock_base_msp432 & operator= (const lock_base_msp432 &) = delete;

    bool try_lock() override {
        // Try to get exclusive access
        if (__LDREXB(&_lock)) return false;
        // Okay, we got it. Try to set the lock
        bool res = (__STREXB(1, &_lock) == 0);
        __DMB();
        return res;
    }

    void unlock() override {
        __DMB();
        _lock = 0;
    }

    bool is_locked() override {
        __DMB();
        return (_lock);
    }

  private:
    uint8_t _lock;
};

#endif // _LOCK_BASE_MSP432_H
