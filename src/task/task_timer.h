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
// A simple timer_interface implementation based on
// the task class. The maximum timer resolution is
// the tick count period - typically 1ms.
//
#ifndef _TASK_TIMER_H_
#define _TASK_TIMER_H_

#include "timer_interface.h"
#include "task.h"
#include <yahal_assert.h>

class task_timer : public task, public timer_interface
{
  public:
    task_timer(const char * name,
               uint16_t stack_size = DEFAULT_STACK_SIZE,
               uint16_t priority   = DEFAULT_PRIORITY,
               bool privileged     = false) : task(name, stack_size) {
        _priority   = priority;
        _privileged = privileged;

        _mode     = TIMER::ONE_SHOT;
        _running  = false;

        _start_ms = 0;
        _delta_ms = 0;
        _next_ms  = 0;

        _callback = nullptr;
    }

    virtual ~task_timer() = default;

    // No copy, no assignment
    task_timer             (const task_timer &) = delete;
    task_timer & operator= (const task_timer &) = delete;

    void setPeriod(uint32_t us, TIMER::timer_mode mode) override {
        yahal_assert((us % 1000) == 0);
        _delta_ms = us/1000;
        _mode     = mode;
    }

    uint32_t getPeriod() override {
        return _delta_ms * 1000;
    }

    void setCallback(function<void()> f) override {
        _callback     = f;
        _running      = false;
    }

    void start() override {
        reset();
        task::start(_priority, _privileged);
        _running = true;
    }

    void stop() override {
        _running = false;
        task::stop();
    }

    bool isRunning() override {
        return _running;
    }

    void reset() override {
        uint64_t now = task::millis();
        _start_ms = now;
        _next_ms  = now + _delta_ms;
    }

    void run(void) override {
        while(true) {
            uint64_t now = task::millis();
            if (now < _next_ms) {
                int64_t diff = _next_ms - now;
                sleep_ms(diff);
            } else {
                _callback();
                _start_ms = _next_ms;
                _next_ms += _delta_ms;
                if (_mode == TIMER::ONE_SHOT) {
                    _running = false;
                    break;
                }
            }
        }
    }

  private:

    uint16_t _priority;
    bool     _privileged;

    TIMER::timer_mode _mode;
    bool     _running;

    uint64_t _start_ms;
    uint64_t _delta_ms;
    uint64_t _next_ms;

    function<void()> _callback;
};

#endif /* _TASK_TIMER_H_ */
