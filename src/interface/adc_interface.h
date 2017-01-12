//
//  gpio_interface.h
//
//  This file is part of the YAHAL Hardware Abstraction Libray
//
//  Created on: 10.04.2016
//      Author: Andreas Terstegge
//

#ifndef _ADC_INTERFACE_H_
#define _ADC_INTERFACE_H_

#include <stdint.h>

namespace ADC {
  // adc modes
  const uint16_t  ADC_8_BIT          = 0x0001;
  const uint16_t  ADC_10_BIT         = 0x0002;
  const uint16_t  ADC_12_BIT         = 0x0004;
  const uint16_t  ADC_14_BIT         = 0x0008;
}

class adc_interface {

  public:
    // Basic GPIO handling
    virtual void     adcMode  (uint8_t channel, uint16_t mode) = 0;
    virtual uint16_t adcRead  (uint8_t channel) = 0;
};

#endif // _ADC_INTERFACE_H_

