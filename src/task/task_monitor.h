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
// A task monitor which prints a task table to
// stdout.
//
#ifndef _TASK_MONITOR_H
#define _TASK_MONITOR_H

#include <cstdio>
#include "yahal_config.h"
#include "task.h"
#include "task_timer.h"
#include "malloc.h"

#define MONITOR_WAIT 5  // in seconds !!

#define CLEAR_SCREEN "%c[H%c[J",27,27
#define VT100_COLOR  "%c[%dm",27
#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37

extern uint32_t __data_start__;
extern uint32_t __heap_start__;

class task_monitor : public task_timer
{
public:
    task_monitor() : task_timer("Monitor", 1024, 5) {
        task_timer::setPeriod(MONITOR_WAIT * 1000000, TIMER::PERIODIC);
        task_timer::setCallback(callback, this);
    }

    virtual ~task_monitor() = default;

    // No copy, no assignment
    task_monitor             (const task_monitor &) = delete;
    task_monitor & operator= (const task_monitor &) = delete;  private:

    static void callback(void * data) {
        task_monitor * _this = (task_monitor *)data;

        task * p = _this->_list.getHead();
        uint32_t millis  = task::millis();
        printf(CLEAR_SCREEN);
        printf(VT100_COLOR, BLUE);
        printf("\n       ---< YAHAL Task Monitor  (uptime: %ldh %ldm %ld.%lds) >--- \n\n",
                millis/3600000,
               (millis/60000) % 60,
               (millis/1000)  % 60,
                millis%1000);
        printf(VT100_COLOR, BLACK);

        uint32_t ram_start  = (uint32_t)(&__data_start__);
        uint32_t heap_start = (uint32_t)(&__heap_start__);
        uint32_t heap_used  = mallinfo().uordblks;
        printf("RAM usage: data %ld, heap %ld, total: %ld bytes\n",
               heap_start - ram_start,  heap_used,
               heap_start - ram_start + heap_used);

        printf("+------------------+-----+------+-----------+-------------+--------+\n");
        printf("| Task Name        | Flg | Prio | State     | Stack usage |  CPU %% |\n");
        printf("+------------------+-----+------+-----------+-------------+--------+\n");
        do {
            register uint32_t t = p->getDeltaTicks();
            printf("| %-16s | %c/%c | %4d | %-9s | %4d / %-4d | %2ld.%1ld %% |\n",
                   p->getName(),
                   p->isPrivileged() ? 'P' : 'U', p->isUsingFloat() ? 'F' : 'I',
                           p->getPriority(),
                           _this->state_to_str(p->getState()),
                           _this->used_stack  (p->_stack_base, p->_stack_size),
                           p->_stack_size,
                            t * 100  / MONITOR_WAIT / TICK_FREQUENCY,
                           (t * 1000 / MONITOR_WAIT / TICK_FREQUENCY) % 10
            );
            p = p->_next;
        } while(p != _this->_list.getHead());
        printf("+------------------+-----+------+-----------+-------------+--------+\n");
    }

    friend void callback(void * data);

private:

    uint16_t used_stack  (const uint8_t * stack_base, uint16_t stack_size) {
        uint16_t i;
        for (i=0; i < stack_size; ++i) {
            if (stack_base[i] != STACK_MAGIC) break;
        }
        return stack_size - i;
    }
};

#endif // _TASK_MONITOR_H
