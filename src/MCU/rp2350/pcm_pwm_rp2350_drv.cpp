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

#include "pcm_pwm_rp2350_drv.h"
using namespace _IO_BANK0_;
using namespace _PWM_;
using namespace _RESETS_;

pcm_pwm_rp2350_drv::pcm_pwm_rp2350_drv( gpio_pin_t left, gpio_pin_t right )
    : pcm_audio_interface(PCM_FIFO_SIZE), _stereo(true),
      _gpio_left(left), _gpio_right(right)
{
    // Get PWM out of reset state
    RESETS_CLR.RESET.PWM <<= 1;
    // Set up GPIO
    _gpio_left.gpioMode(GPIO::DRIVE_4mA);
    _gpio_left.setSEL(GPIO_CTRL_FUNCSEL__pwm);
    _gpio_right.gpioMode(GPIO::DRIVE_4mA);
    _gpio_right.setSEL(GPIO_CTRL_FUNCSEL__pwm);
    // Set up PWM
    // The lover GPIO pins map to PWM0-7
    // The higher GPIO pins map to PWM8-11
    uint8_t index_left{0}, index_right{0};
    if (left < 32) {
        index_left = ((left / 2) % 8) * 5;
    } else {
        index_left = (((left / 2) % 4) + 8) * 5;
    }
    if (right < 32) {
        index_right = ((right / 2) % 8) * 5;
    } else {
        index_right = (((right / 2) % 4) + 8) * 5;
    }
    _left_is_pwm_b  = left  & 0x1;
    _right_is_pwm_b = right & 0x1;

    // Set the PWM CSR and CC pointers
    _left_pwm_csr  = &PWM.CH0_CSR + index_left;
    _right_pwm_csr = &PWM.CH0_CSR + index_right;
    _left_pwm_cc   = &PWM.CH0_CC  + index_left;
    _right_pwm_cc  = &PWM.CH0_CC  + index_right;

    (&PWM.CH0_DIV + index_left)->INT   = 1;
    (&PWM.CH0_DIV + index_left)->FRAC  = 0;
    (&PWM.CH0_TOP + index_left)->TOP   = 2047;
    (&PWM.CH0_DIV + index_right)->INT  = 1;
    (&PWM.CH0_DIV + index_right)->FRAC = 0;
    (&PWM.CH0_TOP + index_right)->TOP  = 2047;

    // Set up timer
    _pcm_timer.setPeriod_ns(1000000000 / 44100, TIMER::PERIODIC);
    _pcm_timer.setCallback([this] () {
        pcm_value_t pcm_value;
        // Try to get next sample
        if (pcmFifoGet(pcm_value)) {
            uint32_t left  = pcm_value.left;
            uint32_t right = pcm_value.right;
            // Convert the int16_t PCM values to uint16_t
            left  += 32768;
            right += 32768;
            // Scale down the 16-bit PCM values to 11 bit
            left  >>= 5;
            right >>= 5;
            // Set the PCM values as PWM counter compare (CC) values
            if (_left_is_pwm_b) {
                _left_pwm_cc->B = left;
            } else {
                _left_pwm_cc->A = left;
            }
            if (_right_is_pwm_b) {
                _right_pwm_cc->B = right;
            } else {
                _right_pwm_cc->A = right;
            }
        }
    });
    _pcm_timer.start();
    enable_output(true);
}

pcm_pwm_rp2350_drv::pcm_pwm_rp2350_drv( gpio_pin_t mono )
        : pcm_audio_interface(PCM_FIFO_SIZE), _stereo(false), _gpio_left(mono)
{
    // Get PWM out of reset state
    RESETS_CLR.RESET.PWM <<= 1;
    // Set up GPIO
    _gpio_left.gpioMode(GPIO::DRIVE_4mA);
    _gpio_left.setSEL(GPIO_CTRL_FUNCSEL__pwm);
    // Set up PWM
    // The lover GPIO pins map to PWM0-7
    // The higher GPIO pins map to PWM8-11
    uint8_t index_left{0};
    if (mono < 32) {
        index_left = ((mono / 2) % 8) * 5;
    } else {
        index_left = (((mono / 2) % 4) + 8) * 5;
    }
    _left_is_pwm_b  = mono & 0x1;

    // Set the PWM CSR and CC pointers
    _left_pwm_csr  = &PWM.CH0_CSR + index_left;
    _left_pwm_cc   = &PWM.CH0_CC  + index_left;

    (&PWM.CH0_DIV + index_left)->INT   = 1;
    (&PWM.CH0_DIV + index_left)->FRAC  = 0;
    (&PWM.CH0_TOP + index_left)->TOP   = 2047;

    // Set up timer
    _pcm_timer.setPeriod_ns(1000000000 / 44100, TIMER::PERIODIC);
    _pcm_timer.setCallback([this] () {
        pcm_value_t pcm_value;
        // Try to get next sample
        if (pcmFifoGet(pcm_value)) {
            // Add left and right channel for mono signal
            uint32_t mono  = (pcm_value.left + pcm_value.right) / 2;
            // Convert the int16_t PCM values to uint16_t
            mono += 32768;
            // Scale down the 16-bit PCM values to 11 bit
            mono >>= 5;
            // Set the PCM values as PWM counter compare (CC) values
            if (_left_is_pwm_b) {
                _left_pwm_cc->B = mono;
            } else {
                _left_pwm_cc->A = mono;
            }
        }
    });
    _pcm_timer.start();
    enable_output(true);
}

pcm_pwm_rp2350_drv::~pcm_pwm_rp2350_drv() {
    // De-configure GPIO pins
    _gpio_left.setSEL(GPIO_CTRL_FUNCSEL__null);
    if (_stereo) {
        _gpio_right.setSEL(GPIO_CTRL_FUNCSEL__null);
    }
}

void pcm_pwm_rp2350_drv::enable_output(bool v) {
    _left_pwm_csr->EN = v;
    if (_stereo) {
        _right_pwm_csr->EN = v;
    }
}

void pcm_pwm_rp2350_drv::setPcmRate(uint32_t Hz) {
    _pcm_timer.setPeriod_ns(1000000000 / Hz, TIMER::PERIODIC);
}
