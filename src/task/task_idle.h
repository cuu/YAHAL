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
// The idle task. It does nothing but sleep.
//
#ifndef _TASK_IDLE_H_
#define _TASK_IDLE_H_

#include "task.h"

class task_idle : public task
{
  public:
    task_idle() : task("IDLE", 200) { }
    ~task_idle() override = default;

    // No copy, no assignment
    task_idle             (const task_idle &) = delete;
    task_idle & operator= (const task_idle &) = delete;

    [[noreturn]] inline void run() override {
        // Do nothing but sleep ...
        ///////////////////////////
        while(true) cpu_sleep();
    }
};

#endif // _TASK_IDLE_H_

