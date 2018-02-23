// ---------------------------------------------
//           This file is part of
//     _  _   __    _   _    __    __      _  _____  ___
//    ( \/ ) /__\  ( )_( )  /__\  (  )    / )(  _  )/ __)
//     \  / /(__)\  ) _ (  /(__)\  )(__  / /  )(_)(
//     (__)(__)(__)(_) (_)(__)(__)(____)(_/  (_____)(___/
//
//  YAHAL/OS,  Another HW Abstraction Library/Operating System
//
//     Copyright (C) 2016 Andreas Terstegge
//     BSD Licensed (see file LICENSE)
//
// ---------------------------------------------
//
//  This file defines a generic C++ interface for
//  all kinds of GPIO devices. Error handling is
//  intentionally left out: A concrete GPIO class
//  on smaller microcontrollers might not perform
//  any error handling at all or only use assert()
//  in error cases, while an advanced platform like
//  a linux-based board might throw exceptions.
//  Since error handling is mostly important during
//  development, this might not influence SW portability
//  between platforms too bad.

#ifndef _GPIO_INTERFACE_H_
#define _GPIO_INTERFACE_H_

#include <stdint.h>

#ifndef HIGH
#define HIGH true
#endif

#ifndef LOW
#define LOW false
#endif

// For Arduino compatibility
#undef INPUT
#undef OUTPUT
#undef OUTPUT_OPEN_DRAIN
#undef RISING
#undef FALLING

// PORT and PIN macros for systems having
// these concepts. Value is 0...255 each.
#define PORT_PIN(port, pin) ((port) << 8 | (pin))
#define PORT(gpio)          ((gpio) >> 8)
#define PIN(gpio)           ((gpio) & 0xff)

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
	virtual ~gpio_interface() { }

	// Basic GPIO handling
    virtual void gpioMode  (uint16_t gpio, uint16_t mode) = 0;
    virtual bool gpioRead  (uint16_t gpio) = 0;
    virtual void gpioWrite (uint16_t gpio, bool value) = 0;

    // Interrupt handling
    virtual void gpioAttachIrq (uint16_t gpio,
    							void (*handler)(uint16_t gpio),
                                uint16_t irq_mode) = 0;
    virtual void gpioDetachIrq (uint16_t gpio) = 0;
    virtual void gpioEnableIrq (uint16_t gpio) = 0;
    virtual void gpioDisableIrq(uint16_t gpio) = 0;
};

// This small wrapper class provides GPIO
// functionality for a single GPIO pin.

class gpio_pin {
  public:
	gpio_pin(gpio_interface & interf)
    : _interf(interf), _gpio(0) { }

	gpio_pin(gpio_interface & interf, uint16_t gpio)
	: _interf(interf), _gpio(gpio) { }

	inline void setGpio(uint16_t gpio) {
		_gpio = gpio;
	}
	inline void gpioMode(uint16_t mode) {
		_interf.gpioMode(_gpio, mode);
	}
	inline bool gpioRead() {
		return _interf.gpioRead (_gpio);
	}
	inline void gpioWrite(bool val) {
		_interf.gpioWrite(_gpio, val);
	}
	inline void gpioAttachIrq (void (*handler)(uint16_t gpio),
							   uint16_t irq_mode)  {
		_interf.gpioAttachIrq(_gpio, handler, irq_mode);
	}
    inline void gpioDetachIrq() {
    	_interf.gpioDetachIrq(_gpio);
    }
    inline void gpioEnableIrq() {
    	_interf.gpioEnableIrq(_gpio);
    }
    inline void gpioDisableIrq() {
    	_interf.gpioDisableIrq(_gpio);
    }

  protected:
	gpio_interface & _interf;
	uint16_t         _gpio;
};

#endif // _GPIO_INTERFACE_H_

