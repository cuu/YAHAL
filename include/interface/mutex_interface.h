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
// This file defines a generic and abstract C++
// interface for a simple mutex. A concrete class
// implementing this interface will typically use an
// instance implementing the lock_base_interface.
//
// Note that lock() and unlock() have to be called from
// the same task! Otherwise an assertion should fail.
// There are 3 modes for a mutex when waiting for the lock.
// The mode is typically specified as the constructor
// parameter (not part of this interface!).
//
// ACTIVE_WAIT:
// The mutex actively polls for the lock. This makes sense
// if e.g. a HW trigger/IRQ handler releases the lock.
//
// YIELD:
// The mutex passes back the control to the scheduler, but
// does not block the task.
//
// BLOCK:
// The task is blocked and does not get any further time
// slices until the lock is unlocked. This is also the
// default mode!
//

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
