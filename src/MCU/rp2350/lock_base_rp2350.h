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
// Implementation of lock base interface for RP2350.
//
#ifndef _LOCK_BASE_RP2350_H
#define _LOCK_BASE_RP2350_H

#include "lock_base_interface.h"
#include "RP2350.h"
#include <cstdint>
using namespace _SIO_;

class lock_base_rp2350 : public lock_base_interface
{
  public:
    lock_base_rp2350();
    ~lock_base_rp2350() override;

    // No copy, no assignment
    lock_base_rp2350             (const lock_base_rp2350 &) = delete;
    lock_base_rp2350 & operator= (const lock_base_rp2350 &) = delete;

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

#endif // _LOCK_BASE_RP2350_H
