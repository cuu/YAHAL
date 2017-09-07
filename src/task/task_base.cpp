/*
 * Task.cpp
 *
 *  Created on: 10.07.2017
 *      Author: andreas
 */

#include <task_base.h>
#include <task_idle.h>
#include "yahal_assert.h"

#include <cstring>

///////////////////////////////
// Definition of static members
///////////////////////////////

uint64_t task_base::_up_ticks  = 0;
task_base *   task_base::_run_ptr   = nullptr;
task_base *   task_base::_run_next  = nullptr;

////////////////
// CTOR and DTOR
////////////////

task_base::task_base(const char * n, uint16_t stack_size)
{
    // Set the Task name
    strncpy(_name, n, 15);
    _name[15] = '\0';

    _priority    = 0;
    _state       = task_base::state_t::SUSPENDED;
    _stack_ptr   = nullptr;
    _ticks       = 0;
    _last_ticks  = 0;
    _sleep_until = 0;

    // Allocate stack
    _stack_size = stack_size / sizeof(uint32_t);
    _stack_base = new uint32_t[_stack_size];
    yahal_assert(_stack_base);
}

task_base::~task_base() {
    delete [] _stack_base;
    _stack_base = nullptr;
}

void task_base::start(uint16_t priority, bool priv) {
    yahal_assert((priority > 0) && !linkedIn());

    // Initialize the stack with a magic number
    for(register uint16_t i=0; i < _stack_size; ++i) {
        _stack_base[i] = STACK_MAGIC;
    }

    setup_stack(priv);

    // Set remaining Task data members
    _priority    = priority;
    _state       = task_base::state_t::READY;
    _ticks       = 0;
    _last_ticks  = 0;
    _sleep_until = 0;

    // Finally link in the Task
    disable_irq();
    push_back(this);
    enable_irq();
}

void task_base::end() {
    yahal_assert(linkedIn());
    // Link out the Task, so it will not
    // consume any further runtime ...
    disable_irq();
    remove(this);
    enable_irq();
    // and switch to another task
    yield();
}

void task_base::sleep(uint32_t ms) {
    _sleep_until  = task_base::_up_ticks;
    _sleep_until += millis2ticks(ms);
    _state = task_base::state_t::SLEEPING;
    yield();
}

void task_base::suspend() {
    if (_state != task_base::state_t::SUSPENDED) {
        _state  = task_base::state_t::SUSPENDED;
        yield();
    }
}

void task_base::resume() {
    if (_state != task_base::state_t::READY) {
        _state  = task_base::state_t::READY;
    }
}

void task_base::join() {
    while ( linkedIn() ) yield();
}

//void Task::setPriority(uint16_t p) {
//    yahal_assert(p > 0);
//    _priority = p;
//}

uint32_t task_base::getDeltaTicks() {
    uint32_t now = _ticks;
    uint32_t ret = now - _last_ticks;
    _last_ticks  = now;
    return ret;
}

///////////////////////////////////////
////////// Private methods ////////////
///////////////////////////////////////

void task_base::_run(void) {
    run();
    end();
}

void task_base::run_scheduler(void) {
    register task_base *   cur_ptr  = task_base::_run_ptr->_next;
    register task_base *   next_ptr = nullptr;
    register uint16_t max_prio = 0;

    for(uint16_t i=0; i < _size; ++i) {
        register task_base::state_t & state = cur_ptr->_state;
        register uint16_t        prio  = cur_ptr->_priority;

        // Handle sleeping Tasks
        if (state == task_base::state_t::SLEEPING) {
            if (task_base::_up_ticks >= cur_ptr->_sleep_until) {
                state = task_base::state_t::READY;
            }
        }
        // Look for potential new Tasks to run
        if ((state == task_base::state_t::READY) && (prio > max_prio)) {
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
    if (next_ptr != task_base::_run_ptr) {
        task_base::_run_next = next_ptr;
        trigger_context_switch();
    }
}

void task_base::tick_handler() {
    // Increment the global millisecond timer
    // and the millisecond ticks of the running Task
    ++(task_base::_up_ticks);
    ++(task_base::_run_ptr->_ticks);
    task_base::run_scheduler();
}

