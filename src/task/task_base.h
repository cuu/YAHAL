/*
 * Task.h
 *
 *  Created on: 10.07.2017
 *      Author: andreas
 */

#ifndef TASK_BASE_H
#define TASK_BASE_H

#include <cstdint>
#include <cstring>
#include "circular_list.h"
#include "yahal_assert.h"

///////////////////////////
// Configuration parameters
///////////////////////////

#ifndef TICK_FREQUENCY
#define TICK_FREQUENCY 1000 // in Hz
#endif

#ifndef DEFAULT_STACK_SIZE
#define DEFAULT_STACK_SIZE 1024 // in bytes
#endif

#ifndef DEFAULT_PRIORITY
#define DEFAULT_PRIORITY 100
#endif

#ifndef STACK_MAGIC
#define STACK_MAGIC 0xDEADBEEF
#endif

//#define CHECK_STACK_OVERFLOW
//#define SIMPLE_ROUND_ROBIN

class task_base : public circular_list<task_base> {
  public:

    enum state_t : uint8_t { READY=0, SLEEPING=1, SUSPENDED=2 };

    inline const char * state_to_str(state_t state) {
        static const char * names[] = { "READY", "SLEEPING", "SUSPENDED"};
        return names[state];
    }

    task_base(const char * n, uint16_t stack_size);
    virtual ~task_base();

    // No copy, no assignment
    task_base             (const task_base &) = delete;
    task_base & operator= (const task_base &) = delete;

    void start(uint16_t priority = DEFAULT_PRIORITY, bool priv = false);
    void end();

    void sleep(uint32_t ms);
    void suspend();
    void resume();
    void join();
    void setPriority(uint16_t p);

    // This method contains the Task code
    /////////////////////////////////////
    virtual void run(void) = 0;

    // Special getter to get the ticks of this
    // task since the last call to this method
    //////////////////////////////////////////
    uint32_t getDeltaTicks();

    // Conversion methods ticks <-> millis
    //////////////////////////////////////
    static inline uint64_t ticks2millis(uint64_t ticks) {
        return ticks * (1000 / TICK_FREQUENCY);
    }
    static inline uint64_t millis2ticks(uint64_t millis) {
        return (millis * TICK_FREQUENCY) / 1000;
    }

    // Helper method to execute the pure virtual run() method
    void _run(void);

    // The scheduler (round robin with priorities)
    static void run_scheduler(void);

    // The tick handler, which has to be called
    static void tick_handler();

    // instance members
    ///////////////////
    char            _name[16];    // name of the task
    uint16_t        _priority;    // Task priority
    state_t         _state;       // state of this task
    uint32_t *      _stack_base;  // Stack base address
    uint16_t        _stack_size;  // Stack size in words
    uint32_t *      _stack_ptr;   // the saved stack pointer of this task
    uint32_t        _ticks;       // consumed tick_count
    uint32_t        _last_ticks;  // _ticks at last call to getDeltaTicks()
    uint64_t        _sleep_until; // tick count until sleep ends

    // class members
    ////////////////
    static uint64_t    _up_ticks; // global tick count from start
    static task_base * _run_ptr;  // Pointer to running Task
    static task_base * _run_next; // Pointer to next running Task

    ////////////////////////////////////////////
    // CPU-specific interface, which needs to be
    // implemented by all different CPU cores.
    ////////////////////////////////////////////

    virtual bool isPrivileged() const    = 0;
    virtual bool isUsingFloat() const    = 0;
    virtual void setup_stack (bool priv) = 0;

    // do not use virtual tables for these functions
    static void enable_irq();
    static void disable_irq();
    static void yield();
    static void cpu_sleep();
    static void trigger_context_switch();
};

#endif /* TASK_H */

