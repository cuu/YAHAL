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
//  interface for a simple mutex

#ifndef _MUTEX_INTERFACE_H_
#define _MUTEX_INTERFACE_H_

namespace MUTEX {
    enum mutex_type { ACTIVE_WAIT, YIELD, BLOCK };
}

class mutex_interface {
public:
    // Lock the mutex
    virtual void lock() = 0;

    // Unlock the mutex
    virtual void unlock() = 0;

    // Try to lock. Return true on success.
    virtual bool try_lock() = 0;

protected:
    virtual ~mutex_interface() = default;
};

#endif /* _MUTEX_INTERFACE_H_ */
