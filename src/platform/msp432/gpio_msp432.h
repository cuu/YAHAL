/*
 * gpio_msp432.h
 *
 *  Created on: 29.02.2016
 *      Author: Andreas Terstegge
 */

#ifndef _GPIO_MSP432_H_
#define _GPIO_MSP432_H_

#include "gpio_interface.h"

class gpio_msp432 : public gpio_interface {
  public:
    static gpio_msp432 inst;

    // Generic GPIO methods
    ///////////////////////
    void gpioMode (uint8_t port, uint8_t pin, uint16_t mode);
    bool gpioRead (uint8_t port, uint8_t pin);
    void gpioWrite(uint8_t port, uint8_t pin, bool value);

    // Interrupt handling
    void gpioAttachIrq (uint8_t port, uint8_t pin,
    			void (*)(uint8_t port, uint8_t pin), uint16_t mode);
    void gpioDetachIrq (uint8_t port, uint8_t pin);
    void gpioEnableIrq (uint8_t port, uint8_t pin);
    void gpioDisableIrq(uint8_t port, uint8_t pin);
    void handleIrq     (uint8_t port, uint8_t pin);

    // MSP432 specific methods
    //////////////////////////
    void setSEL (uint8_t port, uint8_t pin, uint8_t  sel);
    void setMode(uint8_t port, uint8_t pin, uint16_t mode);

  private:
    gpio_msp432();

    volatile int8_t * _port_base[10];
    void (*_intHandler[6][8])(uint8_t port, uint8_t gpio);
};


// This small wrapper class provides GPIO
// functionality for a single GPIO pin.

class gpio_msp432_pin : public gpio_pin {
  public:
	gpio_msp432_pin() : gpio_pin(gpio_msp432::inst) { }

	gpio_msp432_pin(uint8_t port, uint8_t pin) : gpio_pin(gpio_msp432::inst) {
		setPortPin(port, pin);
	}

	inline void setSEL (uint8_t sel) {
		gpio_msp432::inst.setSEL(_port, _pin, sel);
    }
    inline void setMode(uint16_t mode) {
    	gpio_msp432::inst.setMode(_port, _pin, mode);
    }
};

#endif // _GPIO_MSP432_H_
