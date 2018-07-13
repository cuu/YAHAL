// This is a checked mutex implementation

#ifndef _MUTEX_H_
#define _MUTEX_H_

#include "mutex_interface.h"
#include "lock_base_interface.h"
#include "task_base.h"

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
                    task_base::_run_ptr->yield();
                    break;
                }
                case MUTEX::BLOCK: {
                    task_base::_run_ptr->block(&_lock);
                }
            }
        }
        // Store which task did get the lock...
        _task = task_base::_run_ptr;
    }

    inline void unlock() override {
        if (_task){
            yahal_assert(task_base::_run_ptr == _task);
        }
        _task = nullptr;
        _lock.unlock();
    }

    inline bool try_lock() override {
        bool res = _lock.try_lock();
        if (res) {
            _task = task_base::_run_ptr;
        }
        return res;
    }

    T * getLock() { return &_lock; }

    // No copy, no assignment
    mutex             (const mutex &) = delete;
    mutex & operator= (const mutex &) = delete;

private:
    T                   _lock;
    MUTEX::mutex_type   _type;
    task_base *         _task;
};

#endif // _MUTEX_H_
