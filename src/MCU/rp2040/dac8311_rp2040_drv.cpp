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

#include "dac8311_rp2040_drv.h"
#include "dac8311.pio.h"

dac8311_rp2040_drv::dac8311_rp2040_drv( gpio_pin_t mosi_pin,
                                        gpio_pin_t sclk_pin,
                                        gpio_pin_t sync_pin,
                                        gpio_pin_t enable)
    :  pcm_audio_interface(PCM_FIFO_SIZE), _enable(enable)
{
    // Set up GPIOs
    gpio_rp2040_pin mosi( mosi_pin );
    gpio_rp2040_pin sclk( sclk_pin );
    gpio_rp2040_pin sync( sync_pin );
    mosi.setSEL(_IO_BANK0_::GPIO_CTRL_FUNCSEL__pio0);
    sclk.setSEL(_IO_BANK0_::GPIO_CTRL_FUNCSEL__pio0);
    sync.setSEL(_IO_BANK0_::GPIO_CTRL_FUNCSEL__pio0);
    _enable.gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);

    // Create and set up the PIO state machines
    _pcm_sm = pio_rp2040::pio0.loadProgram(dac8311_program);
    configure_SM(_pcm_sm, mosi_pin, sclk_pin, sync_pin);
    _pcm_sm->attachIrq([this]() -> void {
        // Fill the PIO TX FIFO
        pcm_value_t pcm_value;
        while (!_pcm_sm->TxFifoFull()) {
            uint32_t val = 0;
            if (pcmFifoGet(pcm_value)) {
                // Calculate a mono signal by taking
                // the average of left and right channel
                val = (pcm_value.left + pcm_value.right) / 2;
            }
            // Convert the 16 bit signed PCM value
            // to a 14 bit unsigned value, as needed
            // by the DAC8311. The upper 16 bits of
            // the value written to writeTxFifo are
            // transferred by the PIO code.
            _pcm_sm->writeTxFifo((val + 32768) << 14);
        }
    });
    _pcm_sm->enableIrq();
    _pcm_sm->enable();
    enable_output(true);
}

void dac8311_rp2040_drv::setPcmRate(uint32_t Hz) {
    // Delegate the rate setting to the PIO support code
    setRate(_pcm_sm, Hz);
}
