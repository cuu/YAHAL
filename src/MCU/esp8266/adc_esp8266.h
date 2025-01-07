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
// ADC implementation for ESP8266.
//
#ifndef _ADC_ESP8266_H_
#define _ADC_ESP8266_H_

#include "adc_interface.h"

namespace ADC {
    // additional ADC modes
    const uint16_t FAST = 0x1000;
}

class adc_esp8266 : public adc_interface {
public:
    static adc_esp8266 inst;
    ~adc_esp8266() override;

    void       adcMode       (uint8_t channel, uint16_t mode) override;
    adc_mode_t getMode       (uint8_t channel) override;
    uint16_t   adcReadRaw    (uint8_t channel) override;
    float      adcReadVoltage(uint8_t channel) override;
    float      rawToVoltage  (uint8_t channel, uint16_t raw) override;

private:
    adc_esp8266();

    uint16_t _mode;
};

#endif // _ADC_ESP8266_H_
