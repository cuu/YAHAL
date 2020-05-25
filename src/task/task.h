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
// This a abstract base class for the YAHAL multitasking
// functionality. It is generic for all HW platforms.
// The user code, which is run by the task, is located
// inside the abstract method run(), which has to be
// implemented by a derived class.
// The platform-specific part is implemented in some
// static functions, which can be found at the end of
// this file.

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
    // helper method to convert a state to a string.
    // The enum and methods are public and the methods
    // static, so they can be used also in non-derived
    // classes and other code without a task object.
    enum state_t : uint8_t {
        READY     = 0,  // task is ready to run
        SLEEPING  = 1,  // sleep() was called on task
        SUSPENDED = 2,  // suspend() was called on task
        BLOCKED   = 3   // block() was called on task
    };

    inline const char * state_to_str(state_t state) {
        static const char * names[] =
        { "READY", "SLEEPING", "SUSPENDED", "BLOCKED" };
        return names[state];
    }

    // Start a thread. This means that the stack space of
    // the task is set up, and the task is linked into the
    // circular list of tasks, which is used by the scheduler.
    // The second parameter offers the possibility to start
    // this thread as a privileged task, if this is supported
    // by the HW platform.
    void start(uint16_t priority = DEFAULT_PRIORITY, bool priv = false);

    // Stop a task. This means that the task is immediately
    // linked out of the circular list of tasks, and will
    // not get any further processing time. This method is
    // called automatically when the run() method of a task
    // ends. Calling this method manually is dangerous,
    // because the task could still own some resources, which
    // would never be given back after stop().
    void stop();

    // Let the current task (the task entering this method)
    // sleep for a certain amount of time. Time is specified
    // in milliseconds. yield() will be called so that execution
    // proceeds with the next ready task.
    void sleep(uint32_t ms);

    // Suspend a task execution. The task will only come
    // back to life if resume() is called from another
    // task or a interrupt handler. If suspend() is called
    // on the currently running task, a yield() might be
    // necessary to stop the current task and proceed with
    // the next ready task.
    void suspend();

    // Resume a task, which was suspended before. If the
    // resumed task should run immediately, a consecutive
    // yield() might be necessary.
    void resume();

    // Block a task on a lock. As long as the lock is locked,
    // the task will not be executed by the scheduler. block()
    // will never call yield(), so if block() is called on the
    // currently running task, a yield() could follow block()
    // so that execution proceeds with the next ready task.
    // block() is e.g. used in mutexes.
    void block(lock_base_interface * lbi);

    // Join a task. This means that the caller of this method
    // waits until the called thread has ended its execution
    // (returns from the run() method).
    void join();

    // getters and setters for some attributes
    inline const char *  getName()      const    { return _name;     }
    inline uint8_t       getPriority()  const    { return _priority; }
    inline void          setPriority(uint8_t p)  { _priority = p;    }
    inline state_t       getState()     const    { return _state;    }
    inline uint32_t      getMillisRun() const    { return (_ticks * 1000) / TICK_FREQUENCY; }
    inline uint16_t      getStackSize() const    { return _stack_size; }
    inline static task * currentTask()           { return _run_ptr;    }
    inline bool          isAlive()      const    { return _linked_in;  }

    // method to report the number of used bytes in the stack
    uint16_t getUsedStack();

    // method to report current uptime in milliseconds
    static inline uint64_t millis() {
        return (_up_ticks * 1000) / TICK_FREQUENCY;
    }

    // Special getter to get the ticks of this task since the last call to this method
    uint32_t getDeltaTicks();

private:
    char            _name[16];      // name of the task
    uint8_t         _priority;      // Task priority
    state_t         _state;         // state of this task
    uint32_t        _ticks;         // consumed tick_count
    uint32_t        _last_ticks;    // _ticks at last call to getDeltaTicks()
    uint64_t        _sleep_until;   // tick count until sleep ends
    lock_base_interface * _lock;    // pointer to lock if thread is blocked

    // stack-pointer related attributes
    uint8_t *       _stack_base;    // stack base addr
    uint16_t        _stack_size;    // stack size in bytes
    uint8_t *       _stack_ptr;     // saved stack pointer of this task

    // static members for global ticks and current task
    static task *   _run_ptr;       // Pointer to running Task
    static task *   _run_next;      // Pointer to next running Task
    static uint64_t _up_ticks;      // global tick count from start

    // tasks are organized as a circular list, so
    // here are the related private members
    friend class circular_list<task>;
    friend class task_monitor;
    static circular_list<task> _list;
    bool            _linked_in;     // is this task in the list?
    task *          _next;          // pointer to next task
    task *          _prev;          // pointer to previous task

    // Helper method for calling the virtual run() method
    void _run(void);

    ///////////////////////////////////////////////
    // CPU-specific interface, which needs to be //
    // implemented by all different CPU cores.   //
    ///////////////////////////////////////////////
    void        _setup_stack (bool priv);
    static void _context_switch();

public:
    static void start_scheduler();
    static void yield();
    static void cpu_sleep();
    static void enterCritical();
    static void leaveCritical();

    bool isPrivileged() const;
    bool isUsingFloat() const;

    ///////////////////////////////////////////////////
    // Methods which will be called by a concrete    //
    // task implementation (IRQ handlers). Therefore //
    // these methods need to be public and static.   //
    ///////////////////////////////////////////////////
    static void      _scheduler(void);
    static void      _tick_handler ();
    static void      _switchToHead()          { _run_ptr = _list.getHead();   }
    static void      _switchToNext()          { _run_ptr = _run_next;         }
    static uint8_t * _getStackBase()          { return _run_ptr->_stack_base; }
    static uint8_t * _getStackPtr()           { return _run_ptr->_stack_ptr;  }
    static void      _setStackPtr(uint8_t *s) { _run_ptr->_stack_ptr = s;     }

};

#endif // _TASK_H
