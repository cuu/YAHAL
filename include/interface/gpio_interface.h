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
//  This file defines a generic and abstract C++
//  interface for all kinds of GPIO devices.
//  A single pin is identified by a uint16_t, but
//  macros are provided for PORT/PIN syntax, if
//  these concepts are supported by the platform.
//
//  Error handling is intentionally left out: A
//  concrete GPIO class on smaller microcontrollers
//  might not perform any error handling at all
//  or only use assert() in error cases, while an
//  advanced platform like a Linux-based board
//  might throw exceptions...

#ifndef _GPIO_INTERFACE_H_
#define _GPIO_INTERFACE_H_

#include <stdint.h>
#include <functional>
using std::function;

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
typedef uint16_t gpio_pin_t;
#define PORT_PIN(port, pin) ((port) << 8 | (pin))
#define PORT(gpio)          ((gpio) >> 8)
#define PIN(gpio)           ((gpio) & 0xff)

typedef uint16_t gpio_mode_t;
typedef uint16_t gpio_irq_t;

namespace GPIO {

// basic gpio modes
const gpio_mode_t  INPUT              = 0x0001;
const gpio_mode_t  OUTPUT             = 0x0002;
const gpio_mode_t  OUTPUT_OPEN_DRAIN  = 0x0004;
const gpio_mode_t  OUTPUT_OPEN_SOURCE = 0x0008;

// additional gpio modes
const gpio_mode_t  PULLUP             = 0x0010;
const gpio_mode_t  PULLDOWN           = 0x0020;
const gpio_mode_t  SLOW               = 0x0040;
const gpio_mode_t  FAST               = 0x0080;
const gpio_mode_t  INIT_HIGH          = 0x0100;
const gpio_mode_t  INIT_LOW           = 0x0200;

// the gpio irq modes
const gpio_irq_t  RISING              = 0x0001;
const gpio_irq_t  FALLING             = 0x0002;
const gpio_irq_t  LEVEL_HIGH          = 0x0004;
const gpio_irq_t  LEVEL_LOW           = 0x0008;
}

class gpio_interface {
public:
    // Basic GPIO handling
    virtual void gpioMode  (gpio_pin_t gpio, gpio_mode_t mode) = 0;
    virtual bool gpioRead  (gpio_pin_t gpio) = 0;
    virtual void gpioWrite (gpio_pin_t gpio, bool value) = 0;
    virtual void gpioToggle(gpio_pin_t gpio) = 0;

    // Attach a interrupt handler to the GPIO pin 'gpio'.
    // The irq_mode specifies the the signal edges to listen to.
    // The handler will be called when the event occurs.
    virtual void gpioAttachIrq (gpio_pin_t        gpio,
                                gpio_irq_t        irq_mode,
                                function<void()>  handler) = 0;
    // Remove the interrupt from the GPIO pin
    virtual void gpioDetachIrq (gpio_pin_t gpio) = 0;
    // Enable the interrupt on the GPIO pin
    virtual void gpioEnableIrq (gpio_pin_t gpio) = 0;
    // Disable the interrupt on the GPIO pin
    virtual void gpioDisableIrq(gpio_pin_t gpio) = 0;

protected:
    virtual ~gpio_interface() = default;
};

// This small wrapper class provides GPIO
// functionality for a single GPIO pin.

class gpio_pin {
public:
    gpio_pin(gpio_interface & interf)
    : _interf(interf), _gpio(0) { }

    gpio_pin(gpio_interface & interf, gpio_pin_t gpio)
    : _interf(interf), _gpio(gpio) { }

    inline void setGpio(gpio_pin_t gpio) {
        _gpio = gpio;
    }
    inline void gpioMode(gpio_mode_t mode) {
        _interf.gpioMode(_gpio, mode);
    }
    inline bool gpioRead() {
        return _interf.gpioRead (_gpio);
    }
    inline void gpioWrite(bool val) {
        _interf.gpioWrite(_gpio, val);
    }
    inline void gpioToggle() {
        _interf.gpioToggle(_gpio);
    }
    inline void gpioAttachIrq (uint16_t         irq_mode,
                               function<void()> handler) {
        _interf.gpioAttachIrq(_gpio, irq_mode, handler);
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
    inline void operator = (bool b) {
        gpioWrite(b);
    }
protected:
    gpio_interface & _interf;
    gpio_pin_t       _gpio;
};

#endif // _GPIO_INTERFACE_H_
