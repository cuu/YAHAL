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

#ifndef _AUDIO_OUTPUT_H_
#define _AUDIO_OUTPUT_H_

#define PCM_FIFO_SIZE 4096

#include <cstdint>
#include "gpio_msp432.h"
#include "spi_msp432.h"
#include "timer_msp432.h"
#include "dma_msp432.h"
#include "FIFO.h"

extern uint32_t SubsystemMasterClock;

extern "C" {
void TA0_0_IRQHandler();
}

class audio_output
{
public:
    audio_output();
    virtual ~audio_output() = default;

    inline void enable_output(bool v) {
        (void)(v);
    }

    inline void start() { TIMER_A0->CTL |=  TIMER_A_CTL_MC__UP;  }
    inline void stop()  { TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK; }

    inline void setRate(uint32_t kHz) {
        TIMER_A0->CCR[0] = SubsystemMasterClock / kHz - 1;
    }

    inline int  fifo_available_put() { return _pcm_fifo.available_put(); }
    inline void fifo_put(uint16_t v) { _pcm_fifo.put(v); }

    friend void TA0_0_IRQHandler();

private:
    // Edu MK II Buzzer
    gpio_msp432_pin _buzz;

    // PCM FIFO buffer
    FIFO  <uint16_t> _pcm_fifo;
    uint16_t         _pcm_value;

public:
    static audio_output * _this;
};

#endif // _AUDIO_OUTPUT_H_
