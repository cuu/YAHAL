
#ifndef _TASK_H_
#define _TASK_H_

#include <cstdint>
#include "yahal_config.h"
#include "circular_list.h"
#include "lock_base_interface.h"
#include "yahal_assert.h"

class task {
protected:
    // CTOR/DTOR
    task(const char * n, uint16_t stack_size=DEFAULT_STACK_SIZE);
    virtual ~task();
    // No copy, no assignment
    task             (const task &) = delete;
    task & operator= (const task &) = delete;

    // The method containing the task code
    virtual void run(void) = 0;

public:
    // enum type for the different task states and
    // helper method to convert a state to a string
    enum state_t : uint8_t { READY=0, SLEEPING=1, SUSPENDED=2, BLOCKED=3 };
    inline const char * state_to_str(state_t state) {
        static const char * names[] = { "READY", "SLEEPING", "SUSPENDED", "BLOCKED"};
        return names[state];
    }

    // Conversion methods ticks <-> millis
    static inline uint64_t ticks2millis(uint64_t ticks) {
        return ticks * (1000 / TICK_FREQUENCY);
    }
    static inline uint64_t millis2ticks(uint64_t millis) {
        return (millis * TICK_FREQUENCY) / 1000;
    }

    // getters/setters for some attributes
    inline const char *       getName()      const     { return _name;     }
    inline uint16_t           getPriority()  const     { return _priority; }
    inline void               setPriority(uint16_t p)  { _priority = p;    }
    inline state_t            getState()     const     { return _state;    }
    inline static uint64_t    getUpTicks()             { return _up_ticks; }
    inline static uint32_t * _getStackPtr()            { return _run_ptr->_stack_ptr; }
    inline static void       _setStackPtr(uint32_t *s) { _run_ptr->_stack_ptr = s;    }
    inline static task *      thisTask()               { return _run_ptr;  }

    // Special getter to get the ticks of this task since the last call to this method
    uint32_t getDeltaTicks();

    void start(uint16_t priority = DEFAULT_PRIORITY, bool priv = false);
    void end();
    void sleep(uint32_t ms);
    void suspend();
    void resume();
    void block(lock_base_interface * lbi, bool yield = true);
    void join();

private:
    char            _name[16];      // name of the task
    uint16_t        _priority;      // Task priority
    state_t         _state;         // state of this task
    uint32_t        _ticks;         // consumed tick_count
    uint32_t        _last_ticks;    // _ticks at last call to getDeltaTicks()
    uint64_t        _sleep_until;   // tick count until sleep ends
    lock_base_interface * _lock;    // pointer to lock if thread is blocked


    // stack-pointer related attributes
    uint32_t *      _stack_base;    // stack base addr
    uint16_t        _stack_size;    // stack size in bytes
    uint32_t *      _stack_ptr;     // saved stack pointer of this task

    // static members for global ticks and current task
    static uint64_t _up_ticks;      // global tick count from start
    static task *   _run_ptr;       // Pointer to running Task
    static task *   _run_next;      // Pointer to next running Task

    // tasks are organized as a circular list, so
    // here are the related private members
    friend class circular_list<task>;
    friend class task_monitor;
    static circular_list<task> _list;
    bool    _linked_in;     // is this task in the list?
    task *  _next;          // pointer to next task
    task *  _prev;          // pointer to previous task

    // Helper method for calling the virtual run() method
    void _run(void);

    ////////////////////////////////////////////////
    // Methods which will be called by a concrete //
    // task implementation (IRQ handlers)         //
    ////////////////////////////////////////////////
public:
    static void _scheduler(void);
    static void _tick_handler ();
    inline static void _switchToHead() { _run_ptr = _list.getHead(); }
    inline static void _switchToNext() { _run_ptr = _run_ptr->_next; }

    ///////////////////////////////////////////////
    // CPU-specific interface, which needs to be //
    // implemented by all different CPU cores.   //
    ///////////////////////////////////////////////
private:
    void        _setup_stack (bool priv);
    static void _enable_irq();
    static void _disable_irq();
    static void _trigger_context_switch();

public:
    static void start_scheduler();
    static void yield();
    static void cpu_sleep();

    bool isPrivileged() const;
    bool isUsingFloat() const;

};

#endif // _TASK_H
