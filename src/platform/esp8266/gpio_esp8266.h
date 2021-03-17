#ifndef _GPIO_ESP8266_H_
#define _GPIO_ESP8266_H_

#include "gpio_interface.h"

class gpio_esp8266: public gpio_interface
{
public:
    static gpio_esp8266 inst;
    virtual ~gpio_esp8266();

    // Basic GPIO handling
    void gpioMode(uint16_t gpio, uint16_t mode);
    bool gpioRead(uint16_t gpio);
    void gpioWrite(uint16_t gpio, bool value);
    void gpioToggle(uint16_t gpio);

    // Interrupt handling
    void gpioAttachIrq(uint16_t gpio, uint16_t irq_mode,
                       function<void()> handler);
    void gpioDetachIrq(uint16_t gpio);
    void gpioEnableIrq(uint16_t gpio);
    void gpioDisableIrq(uint16_t gpio);
    void handleInterrupt();

    // Special functions of ESP8266
    void brightnessControl(uint16_t gpio, bool);
    void setBrightness(uint8_t);

private:
    gpio_esp8266();

    function<void()> intHandler[16];
    uint16_t         intMode[16];
};

void gpio_irq_handler(gpio_esp8266 *);

// This small wrapper class provides GPIO
// functionality for a single GPIO pin.

class gpio_esp8266_pin: public gpio_pin
{
public:
    gpio_esp8266_pin() : gpio_pin(gpio_esp8266::inst) {
    }

    gpio_esp8266_pin(uint16_t gpio) : gpio_pin(gpio_esp8266::inst) {
        setGpio(gpio);
    }

    inline void brightnessControl(bool on) {
        gpio_esp8266::inst.brightnessControl(_gpio, on);
    }
    inline void setBrightness(uint8_t value) {
        gpio_esp8266::inst.setBrightness(value);
    }
};

#endif // _GPIO_ESP8266_H_
