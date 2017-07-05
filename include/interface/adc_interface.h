//
//  adc_interface.h
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
  // ADC modes
  const uint16_t  ADC_8_BIT          = 0x0001;
  const uint16_t  ADC_10_BIT         = 0x0002;
  const uint16_t  ADC_12_BIT         = 0x0004;
  const uint16_t  ADC_14_BIT         = 0x0008;
}

class adc_interface {

  public:
	virtual ~adc_interface() { }

    virtual void     adcMode(uint8_t channel, uint16_t mode) = 0;
    virtual uint16_t adcReadRaw(uint8_t channel) = 0;
    virtual float    adcReadVoltage(uint8_t channel) = 0;
    virtual float	 rawToVoltage(uint8_t channel, uint16_t raw) = 0;
};

// This small wrapper class provides ADC
// functionality for a single channel.

class adc_channel {
  public:
	adc_channel(adc_interface & interf)
    : _interf(interf), _channel(0) { }

	adc_channel(adc_interface & interf, uint8_t c)
	: _interf(interf), _channel(c) { }

	inline void setChannel(uint8_t c) {
		_channel = c;
	}
	inline void adcMode(uint16_t mode) {
		_interf.adcMode(_channel, mode);
	}
	inline uint16_t adcReadRaw() {
		return _interf.adcReadRaw(_channel);
	}
	inline float adcReadVoltage() {
		return _interf.adcReadVoltage(_channel);
	}
	inline float rawToVoltage(uint16_t raw) {
		return _interf.rawToVoltage(_channel, raw);
	}
  protected:
	adc_interface & _interf;
	uint8_t         _channel;
};

#endif // _ADC_INTERFACE_H_

