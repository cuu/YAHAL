
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
