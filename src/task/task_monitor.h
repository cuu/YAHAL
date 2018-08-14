/*
 * TaskMonitor.h
 *
 *  Created on: 10.07.2017
 *      Author: Andreas Terstegge
 */

#ifndef TASKMONITOR_H
#define TASKMONITOR_H

#include <cstdio>
#include "yahal_config.h"
#include "task.h"
#include "task_timer.h"

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

class task_monitor : public task_timer
{
public:
    task_monitor() : task_timer("Monitor", 600, 5) {
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
        uint32_t millis  = task::ticks2millis( _this->getUpTicks() );
        printf(CLEAR_SCREEN);
        printf(VT100_COLOR, BLUE);
        printf("\n             ---< YAHAL Task Monitor  (uptime: %ldh %ldm %ld.%lds) >--- \n\n",
                millis/3600000,
               (millis/60000) % 60,
               (millis/1000)  % 60,
                millis%1000);
        printf(VT100_COLOR, BLACK);
        printf("+------------------+-----+------+-----------+-------------+---------+--------+\n");
        printf("| Task Name        | Flg | Prio | State     | Stack usage | Ticks/s |  CPU %% |\n");
        printf("+------------------+-----+------+-----------+-------------+---------+--------+\n");
        do {
            register uint32_t t = p->getDeltaTicks();
            printf("| %-16s | %c/%c | %4d | %-9s | %4d / %-4d | %7ld | %2ld.%1ld %% |\n",
                   p->getName(),
                   p->isPrivileged() ? 'P' : 'U', p->isUsingFloat() ? 'F' : 'I',
                           p->getPriority(),
                           _this->state_to_str(p->getState()),
                           _this->used_stack  (p->_stack_base, p->_stack_size),
                           p->_stack_size,
                            t        / MONITOR_WAIT,
                            t * 100  / MONITOR_WAIT / TICK_FREQUENCY,
                           (t * 1000 / MONITOR_WAIT / TICK_FREQUENCY) % 10
            );
            p = p->_next;
        } while(p != _this->_list.getHead());
        printf("+------------------+-----+------+-----------+-------------+---------+--------+\n");
    }

    friend void callback(void * data);

private:

    uint16_t used_stack  (const uint32_t * stack_base, uint16_t stack_size) {
        const uint32_t * p = 0;
        for (p = stack_base; p < (stack_base + stack_size); ++p) {
            if (*p != STACK_MAGIC) break;
        }
        return ((uint32_t)stack_base + (uint32_t)stack_size - (uint32_t)p);
    }
};

#endif /* TASKMONITOR_H */
