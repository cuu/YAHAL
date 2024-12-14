/*
 * gpio_rp2040.h
 *
 *  Created on: 29.02.2016
 *      Author: Andreas Terstegge
 */

#ifndef _GPIO_RP2040_H_
#define _GPIO_RP2040_H_

#include "gpio_interface.h"
#include <cassert>

namespace GPIO {
// additional gpio modes
const gpio_mode_t  DRIVE_2mA     = 0x0000;
const gpio_mode_t  DRIVE_4mA     = 0x0400;
const gpio_mode_t  DRIVE_8mA     = 0x0800;
const gpio_mode_t  DRIVE_12mA    = 0x0c00;
const gpio_mode_t  INPUT_INVERT  = 0x1000;
}

extern "C" {
void IO_IRQ_BANK0_Handler(void);
}

class gpio_rp2040 : public gpio_interface {
public:
    // CTOR / DTOR
    explicit gpio_rp2040(gpio_pin_t gpio = 0xffff);
    ~gpio_rp2040() override = default;

    inline void setGpio(gpio_pin_t gpio) override {
        assert(gpio < 30);
        _gpio = gpio;
        _mask = 1 << gpio;
    }
    inline gpio_pin_t getGpio() override {
        return _gpio;
    }

    // Generic GPIO methods
    ///////////////////////
    void gpioMode  (gpio_mode_t mode) override;
    bool gpioRead  () override;
    void gpioWrite (bool value) override;
    void gpioToggle() override;

    // Interrupt handling
    void gpioAttachIrq (gpio_mode_t mode,
                        function<void()> handler) override;
    void gpioDetachIrq () override;
    void gpioEnableIrq () override;
    void gpioDisableIrq() override;

    // MSP432 specific methods
    //////////////////////////
    void setSEL (uint8_t  sel);
    void setMode(gpio_mode_t mode);

    using gpio_interface::operator =;
    using gpio_interface::operator bool;

    // IRQ handlers are our best friends
    ////////////////////////////////////
    friend void IO_IRQ_BANK0_Handler(void);

private:
    gpio_pin_t  _gpio;
    bool        _open_source;
    bool        _open_drain;
    uint32_t    _mask;

    static function<void()> _intHandler[30];
    static uint8_t          _irqConfig [30];
};

#endif // _GPIO_RP2040_H_
