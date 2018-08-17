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
// Simple lock_guard implementation
//
#ifndef _LOCK_GUARD_H_
#define _LOCK_GUARD_H_

#include "mutex_interface.h"

class lock_guard {
public:
    lock_guard(mutex_interface & mutex) : _mutex(mutex) {
        _mutex.lock();
    }
    ~lock_guard() {
        _mutex.unlock();
    }

    // No copy, no assignment
    lock_guard             (const lock_guard &) = delete;
    lock_guard & operator= (const lock_guard &) = delete;

private:
    mutex_interface &  _mutex;
};

#endif // _LOCK_GUARD_H_
