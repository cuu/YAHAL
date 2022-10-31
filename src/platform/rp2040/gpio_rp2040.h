/*
 * gpio_rp2040.h
 *
 *  Created on: 29.02.2016
 *      Author: Andreas Terstegge
 */

#ifndef _GPIO_RP2040_H_
#define _GPIO_RP2040_H_

#include "gpio_interface.h"

namespace GPIO {
// additional gpio modes
const gpio_mode_t  DRIVE_2mA   = 0x0000;
const gpio_mode_t  DRIVE_4mA   = 0x0400;
const gpio_mode_t  DRIVE_8mA   = 0x0800;
const gpio_mode_t  DRIVE_12mA  = 0x0c00;
}

extern "C" {
void IO_IRQ_BANK0_Handler(void);
}

class gpio_rp2040 : public gpio_interface {
public:
    virtual ~gpio_rp2040() { }
    static gpio_rp2040 inst;

    // Generic GPIO methods
    ///////////////////////
    void gpioMode  (gpio_pin_t gpio, gpio_mode_t mode);
    bool gpioRead  (gpio_pin_t gpio);
    void gpioWrite (gpio_pin_t gpio, bool value);
    void gpioToggle(gpio_pin_t gpio);

    // Interrupt handling
    void gpioAttachIrq (gpio_pin_t gpio, gpio_mode_t mode,
                        function<void()> handler);
    void gpioDetachIrq (gpio_pin_t gpio);
    void gpioEnableIrq (gpio_pin_t gpio);
    void gpioDisableIrq(gpio_pin_t gpio);

    // MSP432 specific methods
    //////////////////////////
    void setSEL (gpio_pin_t gpio, uint8_t  sel);
    void setMode(gpio_pin_t gpio, gpio_mode_t mode);

    // IRQ handlers are our best friends
    ////////////////////////////////////
    friend void IO_IRQ_BANK0_Handler(void);

private:
    gpio_rp2040() : _open_source(0), _open_drain(0) { }

    function<void()> _intHandler[30];
    uint8_t          _irqConfig [30];

    uint32_t _open_source;
    uint32_t _open_drain;
};


// This small wrapper class provides GPIO
// functionality for a single GPIO pin.

class gpio_rp2040_pin : public gpio_pin {
public:
    gpio_rp2040_pin()
    : gpio_pin(gpio_rp2040::inst) { }
    gpio_rp2040_pin(gpio_pin_t gpio)
    : gpio_pin(gpio_rp2040::inst, gpio) { }

    inline void setSEL (uint8_t sel) {
        gpio_rp2040::inst.setSEL(_gpio, sel);
    }
    inline void setMode(gpio_mode_t mode) {
        gpio_rp2040::inst.setMode(_gpio, mode);
    }
    using gpio_pin::operator =;
    using gpio_pin::operator bool;
};

#endif // _GPIO_RP2040_H_
