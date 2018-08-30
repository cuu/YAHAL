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
//  This file defines a generic and abstract C++
//  interface for a elementary, simple lock. This
//  interface is the basis for all mutexes, semaphores
//  or condition variables, and has to be implemented
//  by every platform.
//  It has to be made sure that locking/unlocking can
//  be performed from anywhere in the code (different
//  task etc.). Other classes like mutex will define
//  stronger constraints in this respect (e.g. a mutex
//  can only be locked/unlocked from the same task).

#ifndef _LOCK_BASE_INTERFACE_H_
#define _LOCK_BASE_INTERFACE_H_

class lock_base_interface {
public:
    // Try to lock. Return true on success.
    virtual bool try_lock() = 0;

    // Unlock lock
    virtual void unlock() = 0;

    // Status of lock
    virtual bool is_locked() = 0;

protected:
    virtual ~lock_base_interface() = default;
};

#endif // _LOCK_BASE_INTERFACE_H_
