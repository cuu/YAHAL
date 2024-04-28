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
#ifndef _ADC_RP2040_H_
#define _ADC_RP2040_H_

#include "adc_interface.h"

class adc_rp2040 : public adc_interface {
  public:
	static adc_rp2040 inst;

    // Basic ADC functions
    void       adcMode       (uint8_t channel, uint16_t mode) override;
    adc_mode_t getMode       (uint8_t channel) override;
    uint16_t   adcReadRaw    (uint8_t channel) override;
    float      adcReadVoltage(uint8_t channel) override;
    float      rawToVoltage  (uint8_t channel, uint16_t raw) override;

  private:

    adc_rp2040();

    uint16_t _modes[8];
};


// This small wrapper class provides ADC
// functionality for a single channel.

class adc_rp2040_channel : public adc_channel {
  public:
    adc_rp2040_channel()
     : adc_channel(adc_rp2040::inst) { }

    explicit adc_rp2040_channel(uint16_t c)
     : adc_channel(adc_rp2040::inst, c) { }
};

#endif // _ADC_RP2040_H_

