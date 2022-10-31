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
//  This file defines a generic and abstract C++
//  interface for a timer. A timer can operate
//  in a ONE_SHOT mode or can be re-triggered
//  automatically (PERIODIC). The timeout is
//  specified in microseconds, but not every timer
//  implementation might support this resolution.
//  When the timer expires, a callback handler is
//  called, which has been set with the setCallback()
//  method before.

#ifndef _TIMER_INTERFACE_H_
#define _TIMER_INTERFACE_H_

#include <stdint.h>
#include <functional>
using std::function;

namespace TIMER {
enum timer_mode { ONE_SHOT, PERIODIC };
}

class timer_interface {

public:
    // set the timeout period and the mode of the timer
    virtual void     setPeriod(uint32_t us, TIMER::timer_mode mode) = 0;
    virtual uint32_t getPeriod() = 0;

    // set the callback function
    virtual void	 setCallback(function<void()> f) = 0;

    // starting and stopping the timer
    virtual void     start() = 0;
    virtual void     stop()  = 0;
    virtual bool     isRunning() = 0;

    // getter for the internal counter (counting up).
    // By resetting the counter the defined time period
    // starts from the beginning
    virtual uint32_t getCounter()   = 0;
    virtual void     resetCounter() = 0;

protected:
    virtual ~timer_interface() = default;
};

#endif // _TIMER_INTERFACE_H_
