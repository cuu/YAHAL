
#ifndef _GPIO_ESP8266_H_
#define _GPIO_ESP8266_H_
#include "gpio_interface.h"

class gpio_esp8266 : public gpio_interface {
  public:
	static gpio_esp8266 inst;
	virtual ~gpio_esp8266();

	// Basic GPIO handling
    void gpioMode  (uint16_t gpio, uint16_t mode);
    bool gpioRead  (uint16_t gpio);
    void gpioWrite (uint16_t gpio, bool value);

    // Interrupt handling
    void gpioAttachIrq (uint16_t gpio,
    					void (*handler)(uint16_t gpio),
                        uint16_t irq_mode);
    void gpioDetachIrq (uint16_t gpio);
    void gpioEnableIrq (uint16_t gpio);
    void gpioDisableIrq(uint16_t gpio);
    void handleInterrupt();

  private:
    gpio_esp8266();

    void   (*intHandler[16])(uint16_t gpio);
    uint16_t intMode[16];
};

void gpio_irq_handler(gpio_esp8266 *);

#endif // _GPIO_ESP8266_H_
