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
#ifndef _GPIO_ESP8266_H_
#define _GPIO_ESP8266_H_

#include "gpio_interface.h"

class gpio_esp8266: public gpio_interface
{
public:
    explicit gpio_esp8266(gpio_pin_t gpio = 0xffff);
    ~gpio_esp8266() override = default;

    // No copy, assignment is value passing
    gpio_esp8266 (const gpio_esp8266&) = delete;
    gpio_esp8266& operator= (const gpio_esp8266 & lhs) {
        this->gpioWrite(lhs.operator bool());
        return *this;
    };

    // Get and Set the GPIO number during runtime
    void setGpio(gpio_pin_t gpio) override;
    gpio_pin_t getGpio() const override;

    // Generic GPIO methods
    void gpioMode  (gpio_mode_t mode) override;
    bool gpioRead  () const override;
    void gpioWrite (bool value) override;
    void gpioToggle() override;

    // Interrupt handling
    // Interrupt handling
    void gpioAttachIrq (gpio_mode_t mode,
                        function<void()> handler) override;
    void gpioDetachIrq () override;
    void gpioEnableIrq () override;
    void gpioDisableIrq() override;

    // Special functions of ESP8266
    void brightnessControl(bool);
    void setBrightness(uint8_t);

    using gpio_interface::operator =;
    using gpio_interface::operator bool;

    // IRQ handlers are our best friends
    friend void gpio_irq_handler(gpio_esp8266 *);

private:
    gpio_pin_t  _gpio;
    uint32_t    _mask;

    function<void()>     intHandler[16];
    uint16_t             intMode[16];
    const static uint8_t GPIO_TO_IOMUX[];
    void handleInterrupt();
};

void gpio_irq_handler(gpio_esp8266 *);

#endif // _GPIO_ESP8266_H_
