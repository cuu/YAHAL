/*
 * TaskMonitor.h
 *
 *  Created on: 10.07.2017
 *      Author: Andreas Terstegge
 */

#ifndef TASK_IDLE_H
#define TASK_IDLE_H

template<typename TASK>
class task_idle : public TASK
{
  public:
    task_idle() : TASK("IDLE", 200) { }
    virtual ~task_idle() = default;

    // No copy, no assignment
    task_idle             (const task_idle &) = delete;
    task_idle & operator= (const task_idle &) = delete;

    inline void run(void) override {
        // Do nothing but sleep ...
        ///////////////////////////
        while(true) task_base::cpu_sleep();
    }
};

#endif /* TASKIDLE_H */

