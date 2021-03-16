/*
 * gpio_msp432.h
 *
 *  Created on: 29.02.2016
 *      Author: Andreas Terstegge
 */

#ifndef _GPIO_MSP432_H_
#define _GPIO_MSP432_H_

#include "gpio_interface.h"

extern "C" {
void PORT1_IRQHandler(void);
void PORT2_IRQHandler(void);
void PORT3_IRQHandler(void);
void PORT4_IRQHandler(void);
void PORT5_IRQHandler(void);
void PORT6_IRQHandler(void);
}

class gpio_msp432 : public gpio_interface {
public:
    virtual ~gpio_msp432() { }
    static gpio_msp432 inst;

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
    friend void PORT1_IRQHandler(void);
    friend void PORT2_IRQHandler(void);
    friend void PORT3_IRQHandler(void);
    friend void PORT4_IRQHandler(void);
    friend void PORT5_IRQHandler(void);
    friend void PORT6_IRQHandler(void);

private:
    gpio_msp432() { }

    void handleIrq(uint8_t port, uint8_t pin);
    function<void()> _intHandler[6][8];
    void * _arg[6][8];
    bool   _both[6][8];

    uint8_t _open_source[10];
    uint8_t _open_drain [10];
    uint8_t _pull_up    [10];
    uint8_t _pull_down  [10];
};


// This small wrapper class provides GPIO
// functionality for a single GPIO pin.

class gpio_msp432_pin : public gpio_pin {
public:
    gpio_msp432_pin()
    : gpio_pin(gpio_msp432::inst) { }
    gpio_msp432_pin(gpio_pin_t gpio)
    : gpio_pin(gpio_msp432::inst, gpio) { }

    inline void setSEL (uint8_t sel) {
        gpio_msp432::inst.setSEL(_gpio, sel);
    }
    inline void setMode(gpio_mode_t mode) {
        gpio_msp432::inst.setMode(_gpio, mode);
    }
};

#endif // _GPIO_MSP432_H_
