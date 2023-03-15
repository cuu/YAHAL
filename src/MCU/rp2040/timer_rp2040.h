/*
 *
 *  Created on: 01.11.2022
 *      Author: aterstegge
 */

#ifndef _TIMER_RP2040_H_
#define _TIMER_RP2040_H_

#include "timer_interface.h"
#include "RP2040.h"

extern "C" {
void TIMER_IRQ_0_Handler(void);
void TIMER_IRQ_1_Handler(void);
void TIMER_IRQ_2_Handler(void);
void TIMER_IRQ_3_Handler(void);
}

class timer_rp2040: public timer_interface {
public:
    timer_rp2040(uint32_t index);
    virtual ~timer_rp2040();

    void setPeriod(uint32_t us, TIMER::timer_mode mode = TIMER::ONE_SHOT);
    uint32_t getPeriod();

    void setCallback(function<void()> f);

    void start();
    void stop();
    bool isRunning();

    uint32_t getCounter();
    void resetCounter();

    // IRQ handlers are our best friends
    friend void TIMER_IRQ_0_Handler(void);
    friend void TIMER_IRQ_1_Handler(void);
    friend void TIMER_IRQ_2_Handler(void);
    friend void TIMER_IRQ_3_Handler(void);

private:

    void irqHandler();

    static timer_rp2040 *   _timerinst[4];
    static function<void()> _callback[4];

    uint32_t    _index;
    uint32_t    _mask;
    uint32_t *  _ALARM;
    TIMER::timer_mode _mode;
    uint32_t    _period_us;
};

#endif // _TIMER_RP2040_H_
