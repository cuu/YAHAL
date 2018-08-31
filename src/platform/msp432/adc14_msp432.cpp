/*
 * gpio_msp432.cpp
 *
 *  Created on: 29.02.2016
 *      Author: Andreas Terstegge
 */

#include "msp.h"

#include "adc14_msp432.h"
#include "gpio_msp432.h"
#include "yahal_assert.h"

adc14_msp432 adc14_msp432::inst;

adc14_msp432::adc14_msp432() {
    adcStopScan();
    // Set up the channel -> register mapping
    for(uint8_t channel = 0; channel < 24; ++channel) {
        ADC14->MCTL[channel]  = channel;
        ADC14->MCTL[channel] |= ADC14_MCTLN_VRSEL_0;
    }
    // Initialize resolution
    _current_mode = 0;

    // set up control register 0
    uint32_t ctl0 = 0;
    ctl0 |= ADC14_CTL0_ON;          // switch on ADC module
    ctl0 |= ADC14_CTL0_SSEL__SMCLK; // Use SMCLK
    ctl0 |= ADC14_CTL0_DIV__1;      // clock divider is 1
    ctl0 |= ADC14_CTL0_PDIV__4;     // clock pre-divider is 4
    ctl0 |= ADC14_CTL0_SHS_0;       // use ADC14SC bit as sample/hold trigger
    ctl0 |= ADC14_CTL0_SHP;         // use sample/hold counter
    ctl0 |= ADC14_CTL0_SHT0__64;    // 64 clocks for sample/hold
    ctl0 |= ADC14_CTL0_SHT1__64;    // 64 clocks for sample/hold
    ADC14->CTL0 = ctl0;
    // set up control register 1
    ADC14->CTL1 |= ADC14_CTL1_PWRMD_0;
    // Initialize and disable interrupts
    ADC14->IER0 = 0;
    ADC14->IER1 = 0;
    NVIC_EnableIRQ(ADC14_IRQn);
}

void adc14_msp432::adcMode(uint8_t channel, uint16_t mode) {
    yahal_assert(channel < 24);
    _modes[channel] = mode;
    uint16_t port_pin = (5 << 3) + 5; // A0 is on P5.5
    if (channel > 13)
        port_pin = (6 << 3) + 1 + 14; // A14 is on P6.1
    if (channel > 15)
        port_pin = (9 << 3) + 1 + 16; // A16 is on P9.1
    if (channel > 23)
        yahal_assert(false);
    // Calculate the port and pin for the given ADC channel
    port_pin -= channel;
    uint8_t port = port_pin >>  3;
    uint8_t pin  = port_pin & 0x7;
    // Select ADC mode
    gpio_msp432::inst.setSEL(PORT_PIN(port, pin), 3);
}

uint16_t adc14_msp432::adcReadRaw(uint8_t channel) {
    yahal_assert(channel < 24);
    // set resolution
    if (_current_mode !=_modes[channel]) {
        set_resolution( _modes[channel] );
    } else {
        adcStopScan();
    }
    // set up start channel
    ADC14->CTL1 &= ~ADC14_CTL1_CSTARTADD_MASK;
    ADC14->CTL1 |= (channel << ADC14_CTL1_CSTARTADD_OFS);
    // set single channel / single conversion
    ADC14->CTL0 &= ~ADC14_CTL0_CONSEQ_MASK;
    ADC14->CTL0 |=  ADC14_CTL0_CONSEQ_0;
    // start the conversion process
    ADC14->CTL0 |= (ADC14_CTL0_ENC | ADC14_CTL0_SC);
    // wait until active conversion is done
    while (BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_BUSY_OFS));
    return ADC14->MEM[channel];
}

float adc14_msp432::adcReadVoltage(uint8_t channel) {
    return rawToVoltage(channel, adcReadRaw(channel));
}

float adc14_msp432::rawToVoltage(uint8_t channel, uint16_t raw) {
    float voltage = 3.3f * (float)raw;
    switch(_modes[channel]) {
    case ADC::ADC_8_BIT : voltage /= 255.0f;   break;
    case ADC::ADC_10_BIT: voltage /= 1023.0f;  break;
    case ADC::ADC_12_BIT: voltage /= 4095.0f;  break;
    case ADC::ADC_14_BIT: voltage /= 16383.0f; break;
    default: yahal_assert(false);
    }
    return voltage;
}

void adc14_msp432::adcSetupScan(uint16_t mode) {
    adcStopScan();
    if (_current_mode != mode) {
        set_resolution(mode);
    }
}

void adc14_msp432::adcStartScan(uint8_t  start, uint8_t end) {
    yahal_assert((start < 24) && (end < 24) && (start <= end));
    adcStopScan();
    // set up start channel
    ADC14->CTL1 &= ~ADC14_CTL1_CSTARTADD_MASK;
    ADC14->CTL1 |= (start << ADC14_CTL1_CSTARTADD_OFS);
    // set up end channel
    ADC14->MCTL[end] |= ADC14_MCTLN_EOS;
    // repeat sequence of channels
    ADC14->CTL0 |= ADC14_CTL0_CONSEQ_3;
    // enable automatic multiple samples
    ADC14->CTL0 |= ADC14_CTL0_MSC;
    // start the automatic scan process
    ADC14->CTL0 |= (ADC14_CTL0_ENC | ADC14_CTL0_SC);
}

void adc14_msp432::adcStopScan() {
    // disable conversions
    if (BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_ENC_OFS)) {
        BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_ENC_OFS) = 0;
        // make sure the ENC low pulse has a minimum duration
        for (int i = 0; i < 1000; ++i) ;
    }
}

uint16_t adc14_msp432::adcReadScan(uint8_t channel) {
    yahal_assert(channel < 24);
    return ADC14->MEM[channel];
}

void adc14_msp432::attachScanIrq(uint8_t channel,
                                 void (*handler)(uint16_t chan, uint16_t val) ) {
    yahal_assert(channel < 24);
    adcStopScan();
    // store handler function
    _irqHandlers[channel] = handler;
    // enable the channel irq
    ADC14->IER0 |= (1 << channel);
}

void adc14_msp432::attachWinIrq(uint8_t channel,
                                void (*handler)(uint16_t val, uint16_t mode),
                                uint16_t low, uint16_t high,
                                uint16_t mode) {
    yahal_assert(channel < 24);
    // Window irqs are only allowed on ONE channel!
    yahal_assert(!(ADC14->IER1 & (ADC14_IER1_HIIE |
                                  ADC14_IER1_LOIE |
                                  ADC14_IER1_INIE) ));

    adcStopScan();
    _irqWinHandler = handler;
    _irqWinMode    = mode;
    _irqWinChannel = channel;
    // set and enable window
    ADC14->LO0 = low;
    ADC14->HI0 = high;
    ADC14->MCTL[channel] |= ADC14_MCTLN_WINC;
    // enable the window irqs
    if (mode & ADC::ABOVE_HIGH) ADC14->IER1 |= ADC14_IER1_HIIE;
    if (mode & ADC::BELOW_LOW ) ADC14->IER1 |= ADC14_IER1_LOIE;
    if (mode & ADC::WITHIN_WIN) ADC14->IER1 |= ADC14_IER1_INIE;
}

void adc14_msp432::set_resolution(uint16_t mode) {
    adcStopScan();
    ADC14->CTL1 &= ~ADC14_CTL1_RES_MASK;
    switch(mode) {
    case ADC::ADC_8_BIT:
        ADC14->CTL1 |= ADC14_CTL1_RES__8BIT;
        _current_mode = ADC::ADC_8_BIT;
        break;
    case ADC::ADC_10_BIT:
        ADC14->CTL1 |= ADC14_CTL1_RES__10BIT;
        _current_mode = ADC::ADC_10_BIT;
        break;
    case ADC::ADC_12_BIT:
        ADC14->CTL1 |= ADC14_CTL1_RES__12BIT;
        _current_mode = ADC::ADC_12_BIT;
        break;
    case ADC::ADC_14_BIT:
        ADC14->CTL1 |= ADC14_CTL1_RES__14BIT;
        _current_mode = ADC::ADC_14_BIT;
        break;
    default:
        yahal_assert(false);
    }
}

void adc14_msp432::handleIrq(uint32_t iv) {
    if (iv < 0x000c) {
        // A window interrupt has occurred
        //////////////////////////////////
        uint16_t mode = 0;
        adcStopScan();
        ADC14->MCTL[_irqWinChannel] &= ~ADC14_MCTLN_WINC;
        ADC14->IER1     &= ~(ADC14_IER1_HIIE |
                             ADC14_IER1_LOIE |
                             ADC14_IER1_INIE);
        ADC14->CLRIFGR1 |=  (ADC14_CLRIFGR1_CLRHIIFG |
                             ADC14_CLRIFGR1_CLRLOIFG |
                             ADC14_CLRIFGR1_CLRINIFG);
        switch(iv) {
        case 0x6: mode = ADC::ABOVE_HIGH; break;
        case 0x8: mode = ADC::BELOW_LOW;  break;
        case 0xa: mode = ADC::WITHIN_WIN; break;
        }
        if (_irqWinHandler)
            _irqWinHandler(ADC14->MEM[_irqWinChannel], mode);
        // re-start the automatic scan process
        ADC14->CTL0 |= (ADC14_CTL0_ENC | ADC14_CTL0_SC);
    } else {
        // A channel interrupt has occurred
        ///////////////////////////////////
        iv = (iv >> 1) - 6;
        if (_irqHandlers[iv]) _irqHandlers[iv](iv, ADC14->MEM[iv]);
    }
}

extern "C" {

void ADC14_IRQHandler(void) {
    uint32_t iv = ADC14->IV;
    adc14_msp432::inst.handleIrq( iv );
}

} // extern "C"

