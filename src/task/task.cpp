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
#include <cstring>
#include <utility>
#include <cassert>
#include <cstdlib>

// Definition of static members
///////////////////////////////
uint64_t            task::_up_ticks[NUMBER_OF_CORES] {0};
task *              task::_run_ptr [NUMBER_OF_CORES] {nullptr};
task *              task::_run_next[NUMBER_OF_CORES] {nullptr};
circular_list<task> task::_list    [NUMBER_OF_CORES];

// CTOR and DTOR
////////////////
task::task(std::function<void()> f, const char *n, uint16_t stack_size)
        : task(n, stack_size) {
    _f = std::move(f);
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
    _state       = state_t::SUSPENDED;
    _lock        = nullptr;

    // Allocate the stack
    _stack_size = stack_size;
    _stack_base = new uint8_t[_stack_size];
    assert(_stack_base);
    _stack_ptr   = nullptr;

    // Initialize circular list attributes
    _linked_in   = false;
    _next        = nullptr;
    _prev        = nullptr;
}

// public task methods
//////////////////////
void task::sign_up(core_t c, uint16_t priority, bool priv) {
    assert((priority > 0) && !_linked_in);

    // If no core is specified, use the current one
    _core = (c == core_t::CURRENT_CORE) ? get_core() : (int8_t)c;

    // Initialize the stack with a magic number
    for(uint16_t i=0; i < _stack_size; ++i) {
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
    _list[_core].push_back(this);
    leaveCritical();
}

void task::stop() {
    if (_linked_in) {
        // Link out the Task, so it will not
        // consume any further runtime ...
        enterCritical();
        _list[_core].remove(this);
        leaveCritical();
        // and switch to another task
        yield();
    }
}

void task::sleep_ms(uint32_t ms) {
    //assert(!task::is_irq_context());
    // Calculate the target time
    uint64_t until = millis() + ms;
    if (multitasking_running()) {
        // Get current task
        task * t = task::currentTask();
        assert(t);
        // Update TCB and hand over control to another task
        t->_sleep_until = until;
        t->_state = state_t::SLEEPING;
        yield();
    } else {
        // Active waiting until time has elapsed
        while(millis() < until) ;
    }
}

void task::suspend() {
    _state = state_t::SUSPENDED;
}

void task::resume() {
    _state = state_t::READY;
}

void task::block(lock_base_interface * lbi) {
    _lock  = lbi;
    _state = state_t::BLOCKED;
}

void task::join() const {
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
void task::_run() {
    run();
    stop();
    // in case a task is run without the scheduler
    exit(0);
}

// methods which will be called by IRQ handlers
///////////////////////////////////////////////
void task::_scheduler() {
    int8_t c = get_core();
    task *   cur_ptr  = _run_ptr[c]->_next;
    task *   next_ptr = nullptr;
    uint16_t max_prio = 0;

    for(int i=0; i < _list[c].getSize(); ++i) {
        state_t & state = cur_ptr->_state;
        uint16_t  prio  = cur_ptr->_priority;

        // Handle sleeping Tasks
        if (state == state_t::SLEEPING) {
            if (millis() >= cur_ptr->_sleep_until) {
                state = state_t::READY;
            }
        }
        // Handle blocked Tasks
        if (state == state_t::BLOCKED) {
            if (!cur_ptr->_lock->is_locked()) {
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

    assert(next_ptr);

    // Check if we need a context switch
    if (next_ptr != _run_ptr[c]) {
        _run_next[c] = next_ptr;
        _context_switch();
    }
}

void task::_tick_handler() {
    // Get the core
    int8_t c = get_core();
    // Increment the global tick counter (might be used for the millis()
    // method in case the MCU does not have an independent timer)
    ++(_up_ticks[c]);
    // Find new task to execute, in case
    // multitasking is running
    if (_run_ptr[c]) {
        // Increment ticks of the running task...
        ++(_run_ptr[c]->_ticks);
        // ... and let the scheduler check for a task switch
        _scheduler();
    }
}

