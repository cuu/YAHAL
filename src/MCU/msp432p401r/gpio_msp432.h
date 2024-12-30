/*
 * gpio_msp432.h
 *
 *  Created on: 29.02.2016
 *      Author: Andreas Terstegge
 */

#ifndef _GPIO_MSP432_H_
#define _GPIO_MSP432_H_

#include "gpio_interface.h"
#include <cassert>

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
    explicit gpio_msp432(gpio_pin_t gpio = 0xffff) {
        _port = PORT(gpio);
        _pin  = PIN (gpio);
    }
    ~gpio_msp432() override = default;

    // No copy, assignment is value passing
    gpio_msp432 (const gpio_msp432&) = delete;
    gpio_msp432& operator= (const gpio_msp432 & lhs) {
        this->gpioWrite(lhs.operator bool());
        return *this;
    };

    inline void setGpio(gpio_pin_t gpio) override {
        _port = PORT(gpio);
        _pin  = PIN (gpio);
        assert((_port > 0) && (_port < 11) && (_pin < 8));
    }
    inline gpio_pin_t getGpio() const override {
        return (_port << 8) | _pin;
    }

    // Generic GPIO methods
    ///////////////////////
    void gpioMode  (gpio_mode_t mode) override;
    bool gpioRead  () const override;
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
    void setSEL (uint8_t  sel) const;
    void setMode(gpio_mode_t mode);

    // IRQ handlers are our best friends
    ////////////////////////////////////
    friend void PORT1_IRQHandler(void);
    friend void PORT2_IRQHandler(void);
    friend void PORT3_IRQHandler(void);
    friend void PORT4_IRQHandler(void);
    friend void PORT5_IRQHandler(void);
    friend void PORT6_IRQHandler(void);

    using gpio_interface::operator =;
    using gpio_interface::operator bool;

private:
    uint8_t _port;
    uint8_t _pin;
    bool    _open_source {false};
    bool    _open_drain {false};
    bool    _pull_up {false};
    bool    _pull_down {false};

    static void handleIrq(uint8_t port, uint8_t pin);
    static function<void()> _intHandler[6][8];
    static bool _both[6][8];
};

#endif // _GPIO_MSP432_H_
