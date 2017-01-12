// ---------------------------------------------
//           This file is part of
//      _  _   __    _   _    __    __
//     ( \/ ) /__\  ( )_( )  /__\  (  )
//      \  / /(__)\  ) _ (  /(__)\  )(__
//      (__)(__)(__)(_) (_)(__)(__)(____)
//
//    YAHAL - Another HW Abstraction Library
//     Copyright (C) 2016 Andreas Terstegge
//       BSD Licensed (see file LICENSE)
//
// ---------------------------------------------
//
//  This file defines a generic C++ interface for
//  all kinds of GPIO devices. Error handling is
//  intentionally left out: A concrete GPIO class
//  on smaller microcontrollers might not perform
//  any error handling at all or only use assert()
//  in error cases, while an advanced platform like
//  a linux-based board might throw exceptions...

#ifndef _GPIO_INTERFACE_H_
#define _GPIO_INTERFACE_H_

#include <stdint.h>

#ifndef HIGH
#define HIGH true
#endif

#ifndef LOW
#define LOW false
#endif

namespace GPIO {

  // basic gpio modes
  const uint16_t  INPUT              = 0x0001;
  const uint16_t  OUTPUT             = 0x0002;
  const uint16_t  OUTPUT_OPEN_DRAIN  = 0x0004;
  const uint16_t  OUTPUT_OPEN_SOURCE = 0x0008;

  // additional gpio flags
  const uint16_t  PULLUP             = 0x0010;
  const uint16_t  PULLDOWN           = 0x0020;
  const uint16_t  SLOW               = 0x0040;
  const uint16_t  FAST               = 0x0080;
  const uint16_t  INIT_HIGH          = 0x0100;
  const uint16_t  INIT_LOW           = 0x0200;

  // irq modes
  const uint16_t  RISING             = 0x0001;
  const uint16_t  FALLING            = 0x0002;
  const uint16_t  LEVEL_HIGH         = 0x0004;
  const uint16_t  LEVEL_LOW          = 0x0008;
}

class gpio_interface {

  public:
    // Basic GPIO handling
    virtual void gpioMode  (uint8_t port, uint8_t pin, uint16_t mode) = 0;
    virtual bool gpioRead  (uint8_t port, uint8_t pin) = 0;
    virtual void gpioWrite (uint8_t port, uint8_t pin, bool value) = 0;

    // Interrupt handling
    virtual void gpioAttachIrq (uint8_t port, uint8_t pin,
    							void (*handler)(uint8_t port, uint8_t pin),
                                uint16_t irq_mode) = 0;
    virtual void gpioDetachIrq (uint8_t port, uint8_t pin) = 0;
    virtual void gpioEnableIrq (uint8_t port, uint8_t pin) = 0;
    virtual void gpioDisableIrq(uint8_t port, uint8_t pin) = 0;
};

// This small wrapper class provides GPIO
// functionality for a single GPIO pin.

class gpio_pin {
  public:
	gpio_pin(gpio_interface & interf)
    : _interf(interf) { }

	gpio_pin(gpio_interface & interf, uint8_t port, uint8_t pin)
	: _interf(interf), _port(port), _pin(pin) { }

	inline void setPortPin(uint8_t port, uint8_t pin) {
		_port = port;
		_pin  = pin;
	}
	inline void gpioMode(uint16_t mode) {
		_interf.gpioMode(_port, _pin, mode);
	}
	inline bool gpioRead() {
		return _interf.gpioRead (_port, _pin);
	}
	inline void gpioWrite(bool val) {
		_interf.gpioWrite(_port, _pin, val);
	}
	inline void gpioAttachIrq (void (*handler)(uint8_t port, uint8_t pin),
							   uint16_t irq_mode)  {
		_interf.gpioAttachIrq(_port, _pin, handler, irq_mode);
	}
    inline void gpioDetachIrq() {
    	_interf.gpioDetachIrq(_port, _pin);
    }
    inline void gpioEnableIrq() {
    	_interf.gpioEnableIrq(_port, _pin);
    }
    inline void gpioDisableIrq() {
    	_interf.gpioDisableIrq(_port, _pin);
    }

  protected:
	gpio_interface & _interf;
	uint8_t          _port;
	uint8_t          _pin;
};

#endif // _GPIO_INTERFACE_H_

