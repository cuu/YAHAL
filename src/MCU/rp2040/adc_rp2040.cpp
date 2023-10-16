/*
 * gpio_msp432.cpp
 *
 *  Created on: 29.02.2016
 *      Author: Andreas Terstegge
 */

#include "RP2040.h"

#include "adc_rp2040.h"
#include "gpio_rp2040.h"
#include <cassert>

adc_rp2040 adc_rp2040::inst;

adc_rp2040::adc_rp2040() {
    // Enable the ADC
    _ADC_::ADC.CS.EN = 1;
    // Prepare GPIO18
    gpio_rp2040::inst.gpioMode(18, GPIO::OUTPUT | GPIO::INIT_HIGH);
    // Prepare ADC inputs
    gpio_rp2040::inst.setSEL(26, _IO_BANK0_::GPIO_CTRL_FUNCSEL__null);
    gpio_rp2040::inst.setSEL(27, _IO_BANK0_::GPIO_CTRL_FUNCSEL__null);
    gpio_rp2040::inst.setSEL(28, _IO_BANK0_::GPIO_CTRL_FUNCSEL__null);
    gpio_rp2040::inst.setSEL(29, _IO_BANK0_::GPIO_CTRL_FUNCSEL__null);
}

void adc_rp2040::adcMode(uint8_t channel, uint16_t mode) {
    assert(channel < 8);
    _modes[channel] = mode;
}

adc_mode_t adc_rp2040::getMode(uint8_t channel) {
    assert(channel < 8);
    return _modes[channel];
}

uint16_t adc_rp2040::adcReadRaw(uint8_t channel) {
    assert(channel < 8);
    // Calculate parameters
//    gpio_pin_t gpio = (channel / 2) + 26;
    bool gpio18_val = (channel & 1);

//    gpio_rp2040::inst.setSEL(gpio, _IO_BANK0_::GPIO_CTRL_FUNCSEL__null);
    gpio_rp2040::inst.gpioWrite(18, gpio18_val);
    _ADC_::ADC.CS.AINSEL     = (channel / 2);
    _ADC_::ADC.CS.START_ONCE = 1;
    while(! _ADC_::ADC.CS.READY) ;
    gpio_rp2040::inst.gpioWrite(18, HIGH);
    return _ADC_::ADC.RESULT;
}

float adc_rp2040::adcReadVoltage(uint8_t channel) {
    return rawToVoltage(channel, adcReadRaw(channel));
}

float adc_rp2040::rawToVoltage(uint8_t channel, uint16_t raw) {
    float voltage = 3.3f * (float)raw;
    voltage /= 4095.0f;
    return voltage;
}

void adc_rp2040::adcSetupScan(uint16_t mode) {
}

void adc_rp2040::adcStartScan(uint8_t  start, uint8_t end) {
}

void adc_rp2040::adcStopScan() {
}

uint16_t adc_rp2040::adcReadScan(uint8_t channel) {
}

void adc_rp2040::attachScanIrq(uint8_t channel,
                                 void (*handler)(uint16_t chan, uint16_t val) ) {
}

void adc_rp2040::attachWinIrq(uint8_t channel,
                                void (*handler)(uint16_t val, uint16_t mode),
                                uint16_t low, uint16_t high,
                                uint16_t mode) {
}

void adc_rp2040::set_resolution(uint16_t mode) {
}

void adc_rp2040::handleIrq(uint32_t iv) {
}

extern "C" {

//void ADC14_IRQHandler(void) {
//    uint32_t iv = ADC14->IV;
//    adc_rp2040::inst.handleIrq( iv );
//}

} // extern "C"

