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
// This file defines a generic and abstract C++
// interface for a ADC channel. The channel is
// specified by a uint8_t, so the maximum number
// of channels is limited to 256. The ADC raw data
// uses a uint16_t, so the maximum ADC resolution
// is limited to 16 bits, which should be sufficient
// for most applications.
//

#ifndef _ADC_INTERFACE_H_
#define _ADC_INTERFACE_H_

#include <stdint.h>

typedef uint16_t adc_mode_t;

namespace ADC {
// ADC modes and resolutions
const adc_mode_t  ADC_8_BIT   = 0x0001;
const adc_mode_t  ADC_10_BIT  = 0x0002;
const adc_mode_t  ADC_12_BIT  = 0x0004;
const adc_mode_t  ADC_14_BIT  = 0x0008;
}

class adc_interface {
public:
    // Prepare a ADC channel for reading. On many
    // systems, the mode of a single pin needs to
    // be configured by setting the pin mode.
    // The second parameter specifies the mode
    // (currently the ADC resolution).
    virtual void adcMode(uint8_t channel, adc_mode_t mode) = 0;

    // Read a single raw (binary) ADC value.
    virtual uint16_t adcReadRaw(uint8_t channel) = 0;

    // Read a single voltage ADC value.
    virtual float adcReadVoltage(uint8_t channel) = 0;

    // Convert a raw value to a voltage value.
    virtual float rawToVoltage(uint8_t channel, uint16_t raw) = 0;

protected:
    virtual ~adc_interface() { }
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
    inline void adcMode(adc_mode_t mode) {
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

