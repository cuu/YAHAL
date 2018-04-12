// A simple mutex implementation. It implements
// a active wait loop if the mutex is locked.

#ifndef _SIMPLE_MUTEX_H_
#define _SIMPLE_MUTEX_H_

#include "mutex_interface.h"
#include "yahal_assert.h"

class simple_mutex : public mutex_interface {
public:

    simple_mutex() : _lock(false) { }
    virtual ~simple_mutex();

    void lock() override {
        while(_lock) ;
        _lock = true;
    }

    void unlock() override {
        _lock = false;
    }

    bool try_lock() override {
        if (!_lock) {
            _lock = true;
            return true;
        } else {
            return false;
        }
    }

private:

    bool _lock;
};

#endif // _SIMPLE_MUTEX_H_
