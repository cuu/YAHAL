#ifndef _CONDITION_VARIABLE_H_
#define _CONDITION_VARIABLE_H_

#include "circular_list.h"
#include "mutex.h"
#include "yahal_assert.h"

template<typename T>
class condition_variable {
public:

    condition_variable() { }

    void wait(mutex_interface & m) {
        // Get the current task (ASAP)
        task * thisTask = task::thisTask();
        // create a new element and lock the mutex in it
        stop_list_elem elem;
        while(!elem._lock.try_lock()) ;
        // store mutex so we can unlock it afterwards
        _stop_list_mutex.lock();
        _stop_list.push_back(&elem);
        _stop_list_mutex.unlock();
        // Stop now ...
        thisTask->block(&elem._lock, false);
        m.unlock();
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
            elem->_lock.unlock();
        }
        _stop_list_mutex.unlock();
        task::yield();
    }

    void notify_all() {
        _stop_list_mutex.lock();
        while (_stop_list.getSize()) {
            stop_list_elem * elem = _stop_list.getHead();
            _stop_list.remove(elem);
            elem->_lock.unlock();
        }
        _stop_list_mutex.unlock();
        task::_run_ptr->yield();
    }

    // No copy, no assignment
    condition_variable             (const condition_variable &) = delete;
    condition_variable & operator= (const condition_variable &) = delete;

private:

    struct stop_list_elem {
        stop_list_elem * _prev;
        stop_list_elem * _next;
        bool             _linked_in;
        T                _lock;
    };

    mutex<T>                      _stop_list_mutex;
    circular_list<stop_list_elem> _stop_list;
};

#endif // _CONDITION_VARIABLE_H_
