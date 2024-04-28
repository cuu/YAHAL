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
#include "RP2040.h"
#include "adc_rp2040.h"
#include "task.h"
#include <cassert>

using namespace _IO_BANK0_;

adc_rp2040 adc_rp2040::inst;

adc_rp2040::adc_rp2040() {
    // Enable the ADC
    _ADC_::ADC.CS.EN = 1;
    while (!_ADC_::ADC.CS.READY) ;
    // Prepare ADC inputs
    for (int i=26; i <= 29; ++i) {
        // Disable pull-resistors
        _PADS_BANK0_::PADS_BANK0.GPIO[i].PUE = 0;
        _PADS_BANK0_::PADS_BANK0.GPIO[i].PDE = 0;
    }
}

void adc_rp2040::adcMode(uint8_t channel, uint16_t mode) {
    assert(channel < 8);
    assert(mode < ADC::ADC_14_BIT);
    _modes[channel] = mode;
}

adc_mode_t adc_rp2040::getMode(uint8_t channel) {
    assert(channel < 8);
    return _modes[channel];
}

uint16_t adc_rp2040::adcReadRaw(uint8_t channel) {
    assert(channel < 8);
    // Enter a critical section for setting GPIO18 and
    // reading the ADC value.
    task::enterCritical();
    // Set GPIO18 according to the ADC channel
    IO_BANK0_SET.GPIO18_CTRL.OEOVER <<= GPIO_CTRL_OEOVER__ENABLE;
    if (channel & 1) {
        IO_BANK0.GPIO18_CTRL.OUTOVER = GPIO_CTRL_OUTOVER__HIGH;
    } else {
        IO_BANK0.GPIO18_CTRL.OUTOVER = GPIO_CTRL_OUTOVER__LOW;
    }
    // Read the 12 bit ADC result
    _ADC_::ADC.CS.AINSEL = (channel / 2);
    _ADC_::ADC.CS.START_ONCE = 1;
    while(!_ADC_::ADC.CS.READY) ;
    uint16_t result = _ADC_::ADC.RESULT;
    // Leave the critical section
    task::leaveCritical();
    // Release GPIO18
    IO_BANK0_CLR.GPIO18_CTRL.OEOVER  <<= GPIO_CTRL_OEOVER__ENABLE;
    IO_BANK0_CLR.GPIO18_CTRL.OUTOVER <<= GPIO_CTRL_OUTOVER__HIGH;
    // Our ADC has no real 8 or 10 bit modes, so we simulate
    // the behaviour by shifting the result...
    switch(_modes[channel]) {
        case ADC::ADC_8_BIT:
            return result >> 4;
        case ADC::ADC_10_BIT:
            return result >> 2;
        default:
        case ADC::ADC_12_BIT:
            return result;
    }
}

float adc_rp2040::adcReadVoltage(uint8_t channel) {
    return rawToVoltage(channel, adcReadRaw(channel));
}

float adc_rp2040::rawToVoltage(uint8_t channel, uint16_t raw) {
    float voltage = 3.3f * (float)raw;
    switch(_modes[channel]) {
        case ADC::ADC_8_BIT:
            voltage /= 255.0f;
            break;
        case ADC::ADC_10_BIT:
            voltage /= 1023.0f;
            break;
        default:
        case ADC::ADC_12_BIT:
            voltage /= 4095.0f;
            break;
    }
    return voltage;
}
