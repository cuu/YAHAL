#ifndef _GPIO_BBB_H_
#define _GPIO_BBB_H_

#include "gpio_interface.h"
#include "gpio_module/gpio_bbb_if.h"
#include <thread>

class gpio_BBB : public gpio_interface {

  public:
    virtual ~gpio_BBB();
    static gpio_BBB inst;

    // Basic GPIO handling
    void gpioMode  (gpio_pin_t gpio, gpio_mode_t mode);
    bool gpioRead  (gpio_pin_t gpio);
    void gpioWrite (gpio_pin_t gpio, bool value);
    void gpioToggle(gpio_pin_t gpio);

    // Interrupt handling
    void gpioAttachIrq (gpio_pin_t gpio, gpio_irq_t irq_mode,
                        void (*handler)(gpio_pin_t, void *),
                        void * arg = nullptr);
    void gpioDetachIrq (gpio_pin_t gpio);
    void gpioEnableIrq (gpio_pin_t gpio);
    void gpioDisableIrq(gpio_pin_t gpio);

    /* Additional functionality */      
    void setDebounce (uint8_t gpio, uint16_t msdelay);

  private:
    gpio_BBB();

    void irq_handler();
    std::thread irq_thread;
    void (*usrHandler[GPIO_COUNT])(gpio_pin_t gpio, void *);

    int _fd_gpio;
};


// This small wrapper class provides GPIO
// functionality for a single GPIO pin.
class gpio_BBB_pin : public gpio_pin {
public:
    gpio_BBB_pin() : gpio_pin(gpio_BBB::inst) { }
    gpio_BBB_pin(gpio_pin_t gpio) : gpio_pin(gpio_BBB::inst, gpio) { }
    void setDebounce(uint16_t msdelay) {
      gpio_BBB::inst.setDebounce(_gpio, msdelay);
    }
};

#endif

