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

#include "task.h"
#include "task_idle.h"
#include "yahal_assert.h"
#include <cstring>

// Definition of static members
///////////////////////////////
uint64_t            task::_up_ticks  = 0;
task *              task::_run_ptr   = nullptr;
task *              task::_run_next  = nullptr;
circular_list<task> task::_list;

// CTOR and DTOR
////////////////
task::task(std::function<void()> f,
           const char * n, uint16_t stack_size) : task(n, stack_size) {
    _f = f;
}

task::~task() {
    stop();
    delete [] _stack_base;
    _stack_base = nullptr;
}

task::task(const char * n, uint16_t stack_size)
{
    // Initialize task attributes
    strncpy(_name, n, 15);
    _name[15]    = '\0';
    _priority    = 0;
    _state       = state_t::SUSPENDED;
    _ticks       = 0;
    _last_ticks  = 0;
    _sleep_until = 0;
    _lock        = nullptr;

    // Allocate the stack
    _stack_size = stack_size;
    _stack_base = new uint8_t[_stack_size];
    yahal_assert(_stack_base);
    _stack_ptr   = nullptr;

    // Initialize circular list attributes
    _linked_in   = false;
    _next        = nullptr;
    _prev        = nullptr;
}

// public task methods
//////////////////////
void task::start(uint16_t priority, bool priv) {
    yahal_assert((priority > 0) && !_linked_in);

    // Initialize the stack with a magic number
    for(register uint16_t i=0; i < _stack_size; ++i) {
        _stack_base[i] = STACK_MAGIC;
    }

    // Setup HW specific stack stuff
    _setup_stack(priv);

    // Set remaining Task data members
    _priority    = priority;
    _state       = state_t::READY;
    _ticks       = 0;
    _last_ticks  = 0;
    _sleep_until = 0;
    _lock        = nullptr;

    // Finally link in the Task
    enterCritical();
    _list.push_back(this);
    leaveCritical();
}

void task::stop() {
    if (_linked_in) {
        // Link out the Task, so it will not
        // consume any further runtime ...
        enterCritical();
        _list.remove(this);
        leaveCritical();
        // and switch to another task
        yield();
    }
}

void task::sleep(uint32_t ms) {
    task * c = task::currentTask();
    if (c) {
        // Multitasking running: Sleep using
        // TCB entry '_sleep_until'
        c->_sleep_until  = _up_ticks;
        c->_sleep_until += (ms * TICK_FREQUENCY) / 1000;
        c->_state = state_t::SLEEPING;
        yield();
    } else {
        // Multitasking not running: Call the
        // nonOS-version of sleep
        _nonOS_sleep(ms);
    }
}

void task::suspend() {
    _state  = state_t::SUSPENDED;
}

void task::resume() {
    _state  = state_t::READY;
}

void task::block(lock_base_interface * lbi) {
    _lock  = lbi;
    _state = state_t::BLOCKED;
}

void task::join() {
    while ( _linked_in ) yield();
}

uint16_t task::getUsedStack() {
    uint16_t i;
    for (i=0; i < _stack_size; ++i) {
        if (_stack_base[i] != STACK_MAGIC) break;
    }
    return _stack_size - i;
}

uint32_t task::getDeltaTicks() {
    uint32_t now = _ticks;
    uint32_t ret = now - _last_ticks;
    _last_ticks  = now;
    return ret;
}

// private methods
//////////////////
void task::_run(void) {
    run();
    stop();
}

// methods which will be called by IRQ handlers
///////////////////////////////////////////////
void task::_scheduler(void) {
    register task *     cur_ptr  = _run_ptr->_next;
    register task *     next_ptr = nullptr;
    register uint16_t   max_prio = 0;

    for(uint16_t i=0; i < _list.getSize(); ++i) {
        register state_t & state = cur_ptr->_state;
        register uint16_t  prio  = cur_ptr->_priority;

        // Handle sleeping Tasks
        if (state == state_t::SLEEPING) {
            if (_up_ticks >= cur_ptr->_sleep_until) {
                state = state_t::READY;
            }
        }
        // Handle blocked Tasks
        if (state == state_t::BLOCKED) {
            if (cur_ptr->_lock->is_locked() == false) {
                state = state_t::READY;
            }
        }
        // Look for potential new Tasks to run
        if ((state == state_t::READY) && (prio > max_prio)) {
            max_prio = prio;
            next_ptr = cur_ptr;
            #ifdef SIMPLE_ROUND_ROBIN
            break;
            #endif
        }
        cur_ptr = cur_ptr->_next;
    }

    yahal_assert(next_ptr);

    // Check if we need a context switch
    if (next_ptr != _run_ptr) {
        _run_next = next_ptr;
        _context_switch();
    }
}

void task::_tick_handler() {
    // Increment the global tick counter ...
    ++(_up_ticks);
    // ... and the ticks of the running task.
    ++(_run_ptr->_ticks);
    // Find new task to execute
    _scheduler();
}

