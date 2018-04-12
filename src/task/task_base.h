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
#define DEFAULT_PRIORITY 100 // 1..N, 1 lowest
#endif

#ifndef STACK_MAGIC
#define STACK_MAGIC 0xDEADBEEF
#endif

//#define CHECK_STACK_OVERFLOW
//#define SIMPLE_ROUND_ROBIN

class task_base {
protected:

    // CTOR/DTOR is protected (this is a abstract class!)
    task_base(const char * n, uint16_t stack_size);
    virtual ~task_base();
    // No copy, no assignment
    task_base             (const task_base &) = delete;
    task_base & operator= (const task_base &) = delete;

    // enum type for the different task states.
    enum state_t : uint8_t { READY=0, SLEEPING=1, SUSPENDED=2 };

    // helper method to convert a state to a string
    inline const char * state_to_str(state_t state) {
        static const char * names[] = { "READY", "SLEEPING", "SUSPENDED"};
        return names[state];
    }

public:
    ///////////////////////////
    // public task interface //
    ///////////////////////////
    void start(uint16_t priority = DEFAULT_PRIORITY, bool priv = false);
    void end();

    void sleep(uint32_t ms);
    void suspend();
    void resume();
    void join();

    // getters for various attributes
    inline const char * getName()      const { return _name;       }
    inline uint16_t     getPriority()  const { return _priority;   }
    inline state_t      getState()     const { return _state;      }

    // setters
    inline void setPriority(uint16_t p)   { yahal_assert(p > 0); _priority = p; }

    // Special getter to get the ticks of this
    // task since the last call to this method
    uint32_t getDeltaTicks();

    // Access to some static members. The list-related
    // methods are needed for e.g. task monitors, which
    // need to iterate over all tasks in the list.
    inline static uint64_t    getUpTicks()  { return _up_ticks;       }
    inline static task_base * getListHead() { return _list.getHead(); }
    inline static int         getListSize() { return _list.getSize(); }
    inline bool               linkedIn() const { return _linked_in;   }
    inline task_base *        getNext()  const { return _next;        }

    // if a concrete implementation supports these
    // features, the methods can be overwritten
    virtual bool isPrivileged() const { return false; }
    virtual bool isUsingFloat() const { return false; }

    // The stack base, size and saved stack pointer of this task.
    // Needs to be public so IRQ routines have access. But a
    // derived class can move these attributes to 'private'.
    uint32_t * _stack_base;
    uint16_t   _stack_size;
    uint32_t * _stack_ptr;

protected:
    // This section contains non-public items, which are needed
    // by a concrete implementation of a task class

    // Handling of run pointers
    static task_base * _run_ptr;  // Pointer to running Task
    static task_base * _run_next; // Pointer to next running Task

    static inline void switchToHead() { _run_ptr = _list.getHead(); }

    // Conversion methods ticks <-> millis
    static inline uint64_t ticks2millis(uint64_t ticks) {
        return ticks * (1000 / TICK_FREQUENCY);
    }
    static inline uint64_t millis2ticks(uint64_t millis) {
        return (millis * TICK_FREQUENCY) / 1000;
    }

    // The method containing the task code and the related
    // helper function to execute the pure virtual function
    virtual void run(void) = 0;
    void _run(void);

    // The IRQ handler functions, which will be
    // called from a concrete implementation
    static void run_scheduler(void);
    static void tick_handler ();

    // CPU-specific interface, which needs to be
    // implemented by all different CPU cores.
    virtual void _setup_stack (bool priv) = 0;
    static  void _enable_irq();
    static  void _disable_irq();
    static  void _cpu_sleep();
    static  void _trigger_context_switch();
public:
    static  void yield();

private:
    // Instances of task_base are organized as a circular list
    friend class circular_list<task_base>;
    static circular_list<task_base> _list;
    static uint64_t _up_ticks; // global tick count from start

    // private members dealing with linked list
    bool         _linked_in;   // is this task in the list?
    task_base *  _next;        // pointer to next task
    task_base *  _prev;        // pointer to previous task

    // private task members
    char         _name[16];    // name of the task
    uint16_t     _priority;    // Task priority
    state_t      _state;       // state of this task
    uint32_t     _ticks;       // consumed tick_count
    uint32_t     _last_ticks;  // _ticks at last call to getDeltaTicks()
    uint64_t     _sleep_until; // tick count until sleep ends
};

#endif /* TASK_H */
