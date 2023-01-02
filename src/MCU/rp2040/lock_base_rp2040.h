/*
 * lock_base_rp2040.h
 *
 * A basic lock implementation for rp2040
 *
 *  Created on: 05.11.2022
 *      Author: Andreas Terstegge
 */

#ifndef _LOCK_BASE_RP2040_H
#define _LOCK_BASE_RP2040_H

#include "lock_base_interface.h"
#include "RP2040.h"
#include <cstdint>
using namespace _SIO_;

class lock_base_rp2040 : public lock_base_interface
{
  public:
    lock_base_rp2040();
    virtual ~lock_base_rp2040();

    // No copy, no assignment
    lock_base_rp2040             (const lock_base_rp2040 &) = delete;
    lock_base_rp2040 & operator= (const lock_base_rp2040 &) = delete;

    inline bool try_lock() override {
        return *_lock;
    }

    inline void unlock() override {
        *_lock = 1;
    }

    inline bool is_locked() override {
        return SIO.SPINLOCK_ST & _mask;
    }

  private:
    static uint32_t _index;
    uint32_t        _mask;
    SPINLOCK_t *    _lock;
};

#endif // _LOCK_BASE_RP2040_H
