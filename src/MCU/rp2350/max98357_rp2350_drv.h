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
#ifndef _MAX98357_RP2350_DRV_H_
#define _MAX98357_RP2350_DRV_H_

#include <cstdint>
#include "pcm_audio_interface.h"
#include "gpio_rp2350.h"
#include "pio_rp2350.h"
#include "FIFO.h"

class max98357_rp2350_drv : public pcm_audio_interface
{
public:
    max98357_rp2350_drv(gpio_pin_t din_pin,
                        gpio_pin_t bclk_pin,
                        gpio_pin_t lrclk_pin,
                        gpio_pin_t sd_pin);

    virtual ~max98357_rp2350_drv() = default;

    inline void shutdown(bool v) {
        _sd.gpioWrite(!v);
    }

    void setPcmRate(uint32_t Hz = 44100) override;

private:
    gpio_rp2350 _sd;        // Shutdown Pin (also channel select)
    SM *        _pcm_sm;    // The PIO State Machine
    gpio_rp2350 _edge;
};

#endif // _MAX98357_RP2040_DRV_H_
