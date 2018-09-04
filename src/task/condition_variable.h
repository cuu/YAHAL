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
// Simple condition variable implementation. It
// relies on a lock_base implementation of a
// specific HW platform, which is passed in as the
// template parameter. The condition variable stores
// the locks in a circular list and uses these to
// control the waiting tasks.
//
#ifndef _CONDITION_VARIABLE_H_
#define _CONDITION_VARIABLE_H_

#include "circular_list.h"
#include "mutex.h"
#include "yahal_assert.h"

template<typename T>
class condition_variable {
public:

    condition_variable() = default;

    void wait(mutex_interface & m) {
        // create a new element and store task pointer
        stop_list_elem elem;
        elem._task = task::currentTask();
        // store element so we can resume the task afterwards
        _stop_list_mutex.lock();
        _stop_list.push_back(&elem);
        _stop_list_mutex.unlock();
        // Stop now. We have to suspend this task and
        // also unlock the mutex m. This operation has
        // to be atomic, so a critical section is used.
        task::enterCritical();
        elem._task->suspend();
        m.unlock();
        task::leaveCritical();
        // Switch to other task
        task::yield();
        m.lock();
    }

    template<typename Predicate>
    void wait(mutex_interface & m, Predicate p) {
        while (!p()) wait(m);
    }

    void notify_one() {
        _stop_list_mutex.lock();
        if (_stop_list.getSize()) {
            stop_list_elem * elem = _stop_list.getHead();
            _stop_list.remove(elem);
            elem->_task->resume();
        }
        _stop_list_mutex.unlock();
        // Give the resumed task a chance to run
        task::yield();
    }

    void notify_all() {
        _stop_list_mutex.lock();
        while (_stop_list.getSize()) {
            stop_list_elem * elem = _stop_list.getHead();
            _stop_list.remove(elem);
            elem->_task->resume();
        }
        _stop_list_mutex.unlock();
        // Give the resumed tasks a chance to run
        task::yield();
    }

    // No copy, no assignment
    condition_variable             (const condition_variable &) = delete;
    condition_variable & operator= (const condition_variable &) = delete;

private:

    struct stop_list_elem {
        stop_list_elem * _prev;
        stop_list_elem * _next;
        bool             _linked_in;
        task *           _task;
    };

    mutex<T>                      _stop_list_mutex;
    circular_list<stop_list_elem> _stop_list;
};

#endif // _CONDITION_VARIABLE_H_
