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
#ifndef _PCM_PWM_RP2040_DRV_H_
#define _PCM_PWM_RP2040_DRV_H_

#include <cstdint>
#include "pcm_audio_interface.h"
#include "gpio_rp2040.h"
#include "timer_rp2040.h"
#include "RP2040.h"

using namespace _PWM_;

class pcm_pwm_rp2040_drv : public pcm_audio_interface {
public:
    pcm_pwm_rp2040_drv(gpio_pin_t left, gpio_pin_t right);

    virtual ~pcm_pwm_rp2040_drv() = default;

    void enable_output(bool v);

    void setPcmRate(uint32_t Hz = 44100) override;

private:
    timer_rp2040    _pcm_timer;
    bool            _left_is_pwm_b;
    bool            _right_is_pwm_b;
    CH_CSR_t *      _left_pwm_csr;
    CH_CC_t *       _left_pwm_cc;
    CH_CSR_t *      _right_pwm_csr;
    CH_CC_t *       _right_pwm_cc;
};

#endif // _PCM_PWM_RP2040_DRV_H_
