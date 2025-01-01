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
#include "lock_base_rp2350.h"
#include <cassert>

uint32_t lock_base_rp2350::_index = 0;

lock_base_rp2350::lock_base_rp2350() {
    assert(_index < 32);
    _lock = SIO.SPINLOCK + _index;
    _mask = 1 << _index;
    _index++;
}

lock_base_rp2350::~lock_base_rp2350() {
    unlock();
    _index--;
}
