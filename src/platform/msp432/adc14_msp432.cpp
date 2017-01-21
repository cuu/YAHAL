/*
 * gpio_msp432.cpp
 *
 *  Created on: 29.02.2016
 *      Author: Andreas Terstegge
 */

#include "msp.h"

#include "adc14_msp432.h"
#include "gpio_msp432.h"
#include "assert.h"

adc14_msp432 adc14_msp432::inst;

adc14_msp432::adc14_msp432() {
	// wait until ADC is not busy
	while (BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_BUSY_OFS));
	BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_ENC_OFS) = 0; // disable ADC

	uint32_t ctl0 = 0;
	ctl0 |= ADC14_CTL0_ON;			// switch on ADC module
	ctl0 |= ADC14_CTL0_SHT0__32;	// 32 clocks for sample/hold
	ctl0 |= ADC14_CTL0_CONSEQ_0;	// single channel/single conversion
	ctl0 |= ADC14_CTL0_SSEL__MCLK;	// Use SMCLK
	ctl0 |= ADC14_CTL0_DIV__1;		// clock divider is 1
	ctl0 |= ADC14_CTL0_SHP;			// use sample/hold counter
	ctl0 |= ADC14_CTL0_SHS_0;		// use ADC14SC bit as sample/hold trigger
	ctl0 |= ADC14_CTL0_PDIV__4;		// clock pre-divider is 4
	ADC14->CTL0 = ctl0;

	uint32_t ctl1 = 0;
	ctl1 |= ADC14_CTL1_PWRMD_0;		// regular power mode
	ADC14->CTL1 = ctl1;

	uint32_t mctl0 = 0;
	mctl0 |= ADC14_MCTLN_EOS;		// end of sequence
	mctl0 |= ADC14_MCTLN_VRSEL_0;	// V(R+) = AVCC, V(R-) = AVSS
	ADC14->MCTL[0] = mctl0;

	ADC14->IER0 = 0;				// no interrupts
	ADC14->IER1 = 0;
}

void adc14_msp432::adcMode  (uint8_t channel, uint16_t mode) {
	uint16_t port_pin = (5 << 3) + 5; // A0 is on P5.5
	if (channel > 13)
		port_pin = (6 << 3) + 1 + 14; // A14 is on P6.1
	if (channel > 15)
		port_pin = (9 << 3) + 1 + 16; // A16 is on P9.1
	if (channel > 23)
		assert(false);
	// Calculate the port and pin for the given ADC channel
	port_pin -= channel;
	uint8_t port = port_pin >>  3;
	uint8_t pin  = port_pin & 0x7;
	gpio_msp432::inst.setSEL(PORT_PIN(port, pin), 3); // Select ADC mode

	uint8_t ctl1;
	switch(mode) {
	case ADC::ADC_8_BIT:
		ctl1 = ADC14_CTL1_RES__8BIT;
		break;
	case ADC::ADC_10_BIT:
		ctl1 = ADC14_CTL1_RES__10BIT;
		break;
	case ADC::ADC_12_BIT:
		ctl1 = ADC14_CTL1_RES__12BIT;
		break;
	case ADC::ADC_14_BIT:
	default:
		ctl1 = ADC14_CTL1_RES__14BIT;
		break;
	}
	BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_ENC_OFS) = 0; // disable ADC
	ADC14->CTL1 &= ~ADC14_CTL1_RES_MASK;
	ADC14->CTL1 |= ctl1;
}

uint16_t adc14_msp432::adcRead  (uint8_t channel) {
	// wait until active conversion is done
	while (BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_BUSY_OFS));
	// set the channel
	BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_ENC_OFS) = 0; // disable ADC
	ADC14->MCTL[0] &= ~ADC14_MCTLN_INCH_MASK;
	ADC14->MCTL[0] |= channel;

	BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_ENC_OFS) = 1; // enable ADC
	BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_SC_OFS)  = 1; // start conversion
//	BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_SC_OFS)  = 0; // start conversion

	// wait until active conversion is done
	while (BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_BUSY_OFS));
	BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_ENC_OFS) = 0; // disable ADC

	return ADC14->MEM[0];
}

