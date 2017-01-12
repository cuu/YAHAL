/*
 * adc14_msp432.h
 *
 *  Created on: 10.04.2016
 *      Author: Andreas Terstegge
 */

#ifndef _ADC14_MSP432_H_
#define _ADC14_MSP432_H_

#include "adc_interface.h"

class adc14_msp432 : public adc_interface {
  public:
	static adc14_msp432 inst;

    // Basic ADC functions
    void     adcMode  (uint8_t channel, uint16_t mode);
    uint16_t adcRead  (uint8_t channel);

  private:
	adc14_msp432();
};

#endif // _ADC14_MSP432_H_
