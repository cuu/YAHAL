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
#include "adc_esp8266.h"
#include "assert.h"

extern "C" {
#include "user_interface.h"
}
adc_esp8266 adc_esp8266::inst;

adc_esp8266::adc_esp8266() {}

adc_esp8266::~adc_esp8266() {}

void adc_esp8266::adcMode(uint8_t channel, uint16_t mode) {
    assert(channel == 0 && (mode & ~ADC::FAST) == ADC::ADC_10_BIT);
    _mode = mode;
}

adc_mode_t adc_esp8266::getMode(uint8_t channel) {
    assert(channel == 0);
    return ADC::ADC_10_BIT;
}

uint16_t
adc_esp8266::adcReadRaw(uint8_t
                        channel) {
    assert(channel == 0);
    uint16_t res = 0;
    if (
            _mode & ADC::FAST
            ) {
        res = 0; //system_get_vdd33();
    } else {
        res = system_adc_read();
    }
    return
            res;
}

float adc_esp8266::adcReadVoltage(uint8_t channel) {
    assert(channel == 0);
    return rawToVoltage(0, adcReadRaw(channel));
}

float adc_esp8266::rawToVoltage(uint8_t channel, uint16_t raw) {
    assert(channel == 0);
    return (float) raw / 960.0f;
}
