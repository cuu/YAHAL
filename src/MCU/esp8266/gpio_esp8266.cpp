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
// GPIO implementation for ESP8266.
//
#include "gpio_esp8266.h"
#include "ESP8266.h"
#include <cassert>

using namespace _IO_MUX_;

extern "C"
{
#include "ets_sys.h"
}

const uint8_t gpio_esp8266::GPIO_TO_IOMUX[] = { 12,5,13,4,14,15,6,7,8,9,10,11,0,1,2,3 };

gpio_esp8266::gpio_esp8266(gpio_pin_t gpio)
: _gpio(gpio)
{
    for (int i = 0; i < 16; ++i) {
        intHandler[i] = 0;
        intMode[i]    = _GPIO_::PIN_INT_TYPE__DISABLE;
    }
    ETS_GPIO_INTR_ATTACH(gpio_irq_handler, this);
    ETS_GPIO_INTR_ENABLE();
}

void gpio_esp8266::setGpio(gpio_pin_t gpio) {
    assert(gpio < 16);
    _gpio = gpio;
    _mask = 1 << gpio;
}

gpio_pin_t gpio_esp8266::getGpio() const {
    return _gpio;
}

void gpio_esp8266::gpioMode(uint16_t mode) {
    assert(_gpio < 16);

    // Select GPIO as pin function
    uint8_t mux_idx = GPIO_TO_IOMUX[_gpio];
    IO_MUX.ENTRY[mux_idx].FUNC = (mux_idx > 11) ? 1 : 4;

    // Configure basic GPIO modes
    if (mode & GPIO::INPUT) {
        IO_MUX.ENTRY[mux_idx].OE = 0;
        _GPIO_::GPIO.ENABLE_W1TC = _mask;
    }
    else if (mode & GPIO::OUTPUT) {
        IO_MUX.ENTRY[mux_idx].OE = 1;
        _GPIO_::GPIO.ENABLE_W1TS = _mask;
        _GPIO_::GPIO.PIN[_gpio].DRIVER = _GPIO_::PIN_DRIVER__PUSH_PULL;
    }
    else if (mode & GPIO::OUTPUT_OPEN_DRAIN) {
        IO_MUX.ENTRY[mux_idx].OE = 1;
        _GPIO_::GPIO.ENABLE_W1TS = _mask;
        _GPIO_::GPIO.PIN[_gpio].DRIVER = _GPIO_::PIN_DRIVER__OPEN_DRAIN;
    }
    else assert(false);

    IO_MUX.ENTRY[mux_idx].PULLUP   = (mode & GPIO::PULLUP) ?   1 : 0;
    IO_MUX.ENTRY[mux_idx].PULLDOWN = (mode & GPIO::PULLDOWN) ? 1 : 0;
    if (mode & GPIO::INIT_HIGH) {
        _GPIO_::GPIO.OUT_W1TS = _mask;
    }
    if (mode & GPIO::INIT_LOW) {
        _GPIO_::GPIO.OUT_W1TC = _mask;
    }
}

bool gpio_esp8266::gpioRead() const {
    assert(_gpio < 16);
    return (_GPIO_::GPIO.IN.DATA & _mask);
}

void gpio_esp8266::gpioWrite(bool value) {
    assert(_gpio < 16);
    if (value) {
        _GPIO_::GPIO.OUT_W1TS = _mask;
    } else {
        _GPIO_::GPIO.OUT_W1TC = _mask;;
    }
}

void gpio_esp8266::gpioToggle() {
    assert(_gpio < 16);
    _GPIO_::GPIO.OUT ^= _mask;
}

void gpio_esp8266::gpioAttachIrq(uint16_t irq_mode,
                                 function<void()> handler) {
    assert(_gpio < 16);
    intHandler[_gpio] = handler;
    int esp_mode = _GPIO_::PIN_INT_TYPE__DISABLE;
    switch (irq_mode)
    {
        case GPIO::RISING:
            esp_mode = _GPIO_::PIN_INT_TYPE__RAISING_EDGE;
            break;
        case GPIO::FALLING:
            esp_mode = _GPIO_::PIN_INT_TYPE__FALLING_EDGE;
            break;
        case GPIO::RISING | GPIO::FALLING:
            esp_mode = _GPIO_::PIN_INT_TYPE__BOTH_EDGES;
            break;
        case GPIO::LEVEL_HIGH:
            esp_mode = _GPIO_::PIN_INT_TYPE__LEVEL_HIGH;
            break;
        case GPIO::LEVEL_LOW:
            esp_mode = _GPIO_::PIN_INT_TYPE__LEVEL_LOW;
            break;
        default:
            assert(false);
    }
    intMode[_gpio]                   = esp_mode;
    _GPIO_::GPIO.PIN[_gpio].INT_TYPE = esp_mode;
}

void gpio_esp8266::gpioDetachIrq() {
    assert(_gpio < 16);
    gpioDisableIrq();
    intMode[_gpio] = _GPIO_::PIN_INT_TYPE__DISABLE;
    intHandler[_gpio] = nullptr;
}

void gpio_esp8266::gpioEnableIrq() {
    assert(_gpio < 16);
    // Clear pending interrupts
    _GPIO_::GPIO.STATUS_W1TC = (1 << _gpio);
    _GPIO_::GPIO.PIN[_gpio].INT_TYPE = intMode[_gpio];
}

void gpio_esp8266::gpioDisableIrq() {
    assert(_gpio < 16);
    _GPIO_::GPIO.PIN[_gpio].INT_TYPE = _GPIO_::PIN_INT_TYPE__DISABLE;
}

void gpio_esp8266::handleInterrupt() {
    // Acknowledge all pending IRQs
    uint16_t status = _GPIO_::GPIO.STATUS;
    _GPIO_::GPIO.STATUS_W1TC = status;

    // Serve all pending IRQs
    while (uint8_t gpio = __builtin_ffs(status)) {
        --gpio;
        status &= ~(1 << gpio);
        if (intHandler[gpio])
            intHandler[gpio]();
    }
}

void gpio_irq_handler(gpio_esp8266 * gpio) {
    gpio->handleInterrupt();
}

void gpio_esp8266::brightnessControl(bool on) {
    assert(_gpio < 16);
    if (on) {
        _GPIO_::GPIO.PIN[_gpio].SOURCE = _GPIO_::PIN_SOURCE__SIGMA_DELTA;
    } else {
        _GPIO_::GPIO.PIN[_gpio].SOURCE = _GPIO_::PIN_SOURCE__GPIO;
    }
}

void gpio_esp8266::setBrightness(uint8_t value) {
    _GPIO_::GPIO.SIGMA_DELTA.ENABLE = 1;
    _GPIO_::GPIO.SIGMA_DELTA.PRESCALE = 0x80;
    _GPIO_::GPIO.SIGMA_DELTA.TARGET = value;
}

