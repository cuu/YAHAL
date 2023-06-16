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
#include "gpio_rp2040.h"
#include "pio_rp2040.h"
#include "timer_rp2040.h"
#include "FIFO.h"

class audio_output
{
public:
    audio_output();
    virtual ~audio_output() = default;

    inline void enable_output(bool v) {
        _audio_en.gpioWrite(!v);
    }

    void setRate(uint32_t Hz);

    inline void start() { _pcm_timer.start(); }
    inline void stop()  { _pcm_timer.stop();  }

    inline int  fifo_available_put() { return _pcm_fifo.available_put(); }
    inline void fifo_put(uint16_t v) { _pcm_fifo.put(v); }

private:
    gpio_rp2040_pin  _audio_en;
    // The PCM output timer
    timer_rp2040 _pcm_timer;

    // State Machine
    SM * _sm;
    
    // PCM FIFO buffer
    FIFO  <int16_t> _pcm_fifo;
    int16_t _pcm_value;
};

#endif // _AUDIO_OUTPUT_H_
