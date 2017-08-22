/*
 * TaskMonitor.h
 *
 *  Created on: 10.07.2017
 *      Author: Andreas Terstegge
 */

#ifndef TASKMONITOR_H
#define TASKMONITOR_H

#include <cstdio>
#include "std_io.h"

#define MONITOR_WAIT 1000

#define CLEAR_SCREEN "%c[H%c[J",27,27
#define VT100_COLOR  "%c[%dm",27
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37

#include "task_base.h"       // Task::state_t
#include "task_timer.h"

template<typename T>
class task_monitor : public task_timer<T>
{
  private:

    static void callback(void * data) {
        task_monitor<T> * _this = (task_monitor<T> *)data;

        task_base * p = _this->getHead();
        uint32_t millis  = task_base::ticks2millis( _this->_up_ticks );
        printf(CLEAR_SCREEN);
    //    printf(VT100_COLOR, BLUE);
        printf("\n             ---< YAHAL Task Monitor  (uptime: %ldh %ldm %ld.%lds) >--- \n\n",
                millis/3600000,
               (millis/60000) % 60,
               (millis/1000)  % 60,
                millis % 1000  );
        printf("+------------------+-----+------+-----------+-------------+---------+--------+\n");
        printf("| Task Name        | Flg | Prio |   State   | Stack usage | Ticks/s |  CPU %% |\n");
        printf("+------------------+-----+------+-----------+-------------+---------+--------+\n");
        do {
            register uint32_t t = p->getDeltaTicks();
            printf("| %-16s | %c/%c | %4d | %-9s | %4d / %-4d | %7ld | %2ld.%1ld %% |\n",
                   p->_name,
                   p->isPrivileged() ? 'P' : 'U', p->isUsingFloat() ? 'F' : 'I',
                   p->_priority,
                   _this->state_to_str(p->_state),
                   _this->used_stack  (p->_stack_base, p->_stack_size) * sizeof(uint32_t),
                                                       p->_stack_size  * sizeof(uint32_t),
                   t,
                    (t * 100 ) / MONITOR_WAIT,
                   ((t * 1000) / MONITOR_WAIT) % 10
            );
            p = p->getNext();
        } while(p != _this->getHead());
        printf("+------------------+-----+------+-----------+-------------+---------+--------+\n");
    }

  public:

    task_monitor() : task_timer<T>("Monitor", 600, 5) {

        task_timer<T>::setPeriod(MONITOR_WAIT * 1000, TIMER::PERIODIC);
        task_timer<T>::setCallback(callback, this);
        task_timer<T>::start();
    }

    virtual ~task_monitor() = default;

    // No copy, no assignment
    task_monitor             (const task_monitor &) = delete;
    task_monitor & operator= (const task_monitor &) = delete;

    friend void callback(void * data);

  private:

    uint16_t used_stack  (const uint32_t * stack_base, uint16_t stack_size) {
        const uint32_t * p = 0;
        for (p = stack_base; p < (stack_base + stack_size); ++p) {
            if (*p != STACK_MAGIC) break;
        }
        return (stack_base + stack_size - p);
    }

};

#endif /* TASKMONITOR_H */
