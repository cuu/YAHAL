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
// Timer implementation for ESP8266.
//
#ifndef _TIMER_ESP8266_H_
#define _TIMER_ESP8266_H_

#include "timer_interface.h"

class timer_esp8266 : public timer_interface {
public:
    timer_esp8266();
    ~timer_esp8266() override;

    void setPeriod(uint32_t us, TIMER::timer_mode mode) override;
    uint32_t getPeriod() override;

    void setCallback(function<void()> f) override;

    void start() override;
    void stop() override;
    bool isRunning() override;

    uint32_t getCounter();
    void resetCounter();

    friend void timer_irq_handler(timer_esp8266 *);

private:
    function<void()> _handler;
    uint32_t         _period_us; // load value in us
    uint32_t         _period_load;
    uint32_t         _divider;
};

void timer_irq_handler(timer_esp8266 *);

#endif // _TIMER_ESP8266_H_
