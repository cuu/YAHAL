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
#define PCM_FIFO_SIZE 2048

#include "max98357_rp2040_drv.h"
#include "max98357.pio.h"

max98357_rp2040_drv::max98357_rp2040_drv(gpio_pin_t din_pin,
                                         gpio_pin_t bclk_pin,
                                         gpio_pin_t lrclk_pin,
                                         gpio_pin_t sd_pin)
    :  pcm_audio_interface(PCM_FIFO_SIZE), _sd(sd_pin), _edge(28)
{
    // Set up GPIOs
    gpio_rp2040 din  ( din_pin   );
    gpio_rp2040 bclk ( bclk_pin  );
    gpio_rp2040 lrclk( lrclk_pin );
    din.setSEL  (_IO_BANK0_::GPIO_CTRL_FUNCSEL__pio0);
    bclk.setSEL (_IO_BANK0_::GPIO_CTRL_FUNCSEL__pio0);
    lrclk.setSEL(_IO_BANK0_::GPIO_CTRL_FUNCSEL__pio0);
    _sd.gpioMode(GPIO::OUTPUT_OPEN_DRAIN | GPIO::INIT_HIGH);
    _edge.gpioMode(GPIO::OUTPUT);

    // Create and set up the PIO state machines
    _pcm_sm = pio_rp2040::pio0.loadProgram(max98357_program);
    configure_SM(_pcm_sm, din_pin, bclk_pin, lrclk_pin);
    _pcm_sm->attachIrq([this]() -> void {
        // Fill the PIO TX FIFO
        pcm_value_t pcm_value;
        int16_t last_val = 0;
        while (!_pcm_sm->TxFifoFull()) {
            uint32_t val = 0;
            if (pcmFifoGet(pcm_value)) {
                // MAX98357 PIO state machine expects 32 bit integers
                // (upper 16 bit left channel, lower 16 bit right channel)
                if (last_val <= 0 && pcm_value.left >= 0) _edge = HIGH;
                if (last_val >= 0 && pcm_value.left <= 0) _edge = LOW;
                last_val = pcm_value.left;
                val = (pcm_value.left << 16) | pcm_value.right;
            }
            _pcm_sm->writeTxFifo(val);
        }
    });
    _pcm_sm->enableIrq();
    _pcm_sm->enable();
}

void max98357_rp2040_drv::setPcmRate(uint32_t Hz) {
    // Delegate the rate setting to the PIO support code
    setRate(_pcm_sm, Hz);
}
