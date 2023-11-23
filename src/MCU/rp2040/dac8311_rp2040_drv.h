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
#ifndef _DAC8311_RP2040_DRV_H_
#define _DAC8311_RP2040_DRV_H_

#include <cstdint>
#include "pcm_audio_interface.h"
#include "gpio_rp2040.h"
#include "pio_rp2040.h"
#include "FIFO.h"

class dac8311_rp2040_drv : public pcm_audio_interface
{
public:
    dac8311_rp2040_drv(gpio_pin_t mosi_pin,
                       gpio_pin_t sclk_pin,
                       gpio_pin_t sync_pin,
                       gpio_pin_t enable);

    virtual ~dac8311_rp2040_drv() = default;

    inline void enable_output(bool v) {
        _enable.gpioWrite(!v);
    }

    void setPcmRate(uint32_t Hz = 44100) override;

private:
    gpio_rp2040_pin _enable;    // Audio enable Pin
    SM *            _pcm_sm;    // The PIO State Machine
};

#endif // _DAC8311_RP2040_DRV_H_
