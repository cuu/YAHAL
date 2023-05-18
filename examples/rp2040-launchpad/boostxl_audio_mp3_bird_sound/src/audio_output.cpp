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

#include "audio_output.h"
#include "dac8311.pio.h"
using namespace _IO_BANK0_;

audio_output::audio_output() : _audio_en(5), _pcm_timer(0),
        _sm(pio_rp2040::pio0.loadProgram(dac8311_program)),
        _pcm_fifo (PCM_FIFO_SIZE)
{
    _audio_en.gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);
    
    gpio_rp2040_pin mosi( 7);
    gpio_rp2040_pin sclk(22);
    gpio_rp2040_pin sync(15);
    mosi.setSEL(GPIO_CTRL_FUNCSEL__pio0);
    sclk.setSEL(GPIO_CTRL_FUNCSEL__pio0);
    sync.setSEL(GPIO_CTRL_FUNCSEL__pio0);

    // Set up the PIO state machine
    configure_SM(_sm, 7, 22, 15);
    _sm.enable();

    enable_output(true);

    // Configure PCM timer.
    _pcm_timer.setCallback([this]() {
        while(!_sm.TxFifoFull()) {
            if (_pcm_fifo.get(_pcm_value)) {
                // Convert the 16 bit signed PCM value
                // to a 14 bit unsigned value, as needed
                // by the DAC8311. The upper 16 bits of
                // the value written to writeTxFifo are
                // transfered by the PIO code.
                _sm.writeTxFifo((_pcm_value + 32768) << 14);
            } else break;
        }
    });
    // With 44100Hz PCM rate, a single sample takes approx 22.7us
    // The PIO TX FIFO is configured to a size of 8 entries, so
    // the FIFO can buffer approx. 180 us PCM data. So a timer interval
    // of 100us should be sufficient to fill the FIFO in time.
    _pcm_timer.setPeriod(100, TIMER::PERIODIC);
}

void audio_output::setRate(uint32_t Hz) {
    // Delegate the rate setting to the PIO support code
    ::setRate(_sm, Hz);
}

