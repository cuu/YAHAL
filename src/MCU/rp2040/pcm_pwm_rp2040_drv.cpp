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

#include "pcm_pwm_rp2040_drv.h"
#include "RP2040.h"
using namespace _IO_BANK0_;
using namespace _PWM_;

pcm_pwm_rp2040_drv::pcm_pwm_rp2040_drv( gpio_pin_t left, gpio_pin_t right )
    : pcm_audio_interface(PCM_FIFO_SIZE)
{
    // Set up GPIO
    gpio_rp2040_pin gpio_left( left );
    gpio_left.setSEL(GPIO_CTRL_FUNCSEL__pwm);
    gpio_left.setMode(GPIO::DRIVE_4mA);
    gpio_rp2040_pin gpio_right( right );
    gpio_right.setSEL(GPIO_CTRL_FUNCSEL__pwm);
    gpio_right.setMode(GPIO::DRIVE_4mA);
    // Set up PWM
    uint8_t index_left  = ((left  / 2) % 8) * 5;
    uint8_t index_right = ((right / 2) % 8) * 5;
    _left_is_pwm_b  = left  & 0x1;
    _right_is_pwm_b = right & 0x1;

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
            left  += 32768;
            right += 32768;
            left  >>= 5;
            right >>= 5;
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

void pcm_pwm_rp2040_drv::enable_output(bool v) {
    _left_pwm_csr->EN = v;
    _right_pwm_csr->EN = v;
}

void pcm_pwm_rp2040_drv::setPcmRate(uint32_t Hz) {
    _pcm_timer.setPeriod_ns(1000000000 / Hz, TIMER::PERIODIC);
}
