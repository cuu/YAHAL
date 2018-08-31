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
// A simple mutex implementation with the typical
// lock() / unlock() / try_lock() methods.
// See mutex_interface.h for more information.

#ifndef _MUTEX_H_
#define _MUTEX_H_

#include "mutex_interface.h"
#include "lock_base_interface.h"
#include "yahal_assert.h"
#include "task.h"

template<typename T>
class mutex : public mutex_interface {
public:
    mutex(MUTEX::mutex_type type = MUTEX::BLOCK) : _type(type), _task(nullptr) { }

    inline void lock() override {
        while (!try_lock())
        {
            switch(_type) {
                case MUTEX::ACTIVE_WAIT: {
                    continue;
                }
                case MUTEX::YIELD: {
                    task::yield();
                    break;
                }
                case MUTEX::BLOCK: {
                    task::currentTask()->block(&_lock);
                    task::yield();
                }
            }
        }
        // Store which task did get the lock...
        _task = task::currentTask();
    }

    inline void unlock() override {
        if (_task){
            yahal_assert(task::currentTask() == _task);
        }
        _task = nullptr;
        _lock.unlock();
    }

    inline bool try_lock() override {
        bool res = _lock.try_lock();
        if (res) {
            _task = task::currentTask();
        }
        return res;
    }

    // No copy, no assignment
    mutex             (const mutex &) = delete;
    mutex & operator= (const mutex &) = delete;

private:
    T                   _lock;
    MUTEX::mutex_type   _type;
    task *              _task;
};

#endif // _MUTEX_H_
