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
// Timer implementation for RP2350.
//
#ifndef _TIMER_RP2350_H_
#define _TIMER_RP2350_H_

#include "timer_interface.h"
#include "RP2350.h"

extern "C" {
void TIMER0_IRQ_0_Handler(void);
void TIMER0_IRQ_1_Handler(void);
void TIMER0_IRQ_2_Handler(void);
void TIMER0_IRQ_3_Handler(void);
}

class timer_rp2350: public timer_interface {
public:
    // The index is in the range of 0...3 (4 timers).
    // When no index is given (-1), the next free timer will be used!
    explicit timer_rp2350(int8_t index = -1);
    ~timer_rp2350() override;

    void setPeriod   (uint32_t us, TIMER::timer_mode mode) override;
    void setPeriod_ns(uint32_t ns, TIMER::timer_mode mode);
    uint32_t getPeriod() override;

    void setCallback(function<void()> f) override;

    void start() override;
    void stop() override;
    bool isRunning() override;

    void reset() override;

    // IRQ handlers are our best friends
    friend void TIMER0_IRQ_0_Handler(void);
    friend void TIMER0_IRQ_1_Handler(void);
    friend void TIMER0_IRQ_2_Handler(void);
    friend void TIMER0_IRQ_3_Handler(void);

private:

    void irqHandler();

    static timer_rp2350 *   _timerinst[4];
    static function<void()> _callback[4];

    uint8_t     _index {0};
    uint32_t    _mask  {0};
    uint32_t *  _alarm {nullptr};
    TIMER::timer_mode _mode;
    uint32_t    _period {0};
    uint32_t    _tick_factor {0};
};

#endif // _TIMER_RP2350_H_
