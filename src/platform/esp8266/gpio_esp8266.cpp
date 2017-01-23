
#include "gpio_esp8266.h"
#include "esp8266ex.h"
#include "assert.h"

//#include "ets_sys.h"
//extern "C" {
//// Missing defines for ROM code
//void ets_isr_attach(int intr, void (*handler)(gpio_interface*), void *arg);
//void ets_isr_mask(unsigned intr);
//void ets_isr_unmask(unsigned intr);
//
//}

gpio_esp8266 gpio_esp8266::inst;

gpio_esp8266:: gpio_esp8266() { }
gpio_esp8266::~gpio_esp8266() { }

void gpio_esp8266::gpioMode  (uint16_t gpio, uint16_t mode) {
	assert(gpio < 16);

	// Select GPIO as pin function
	ESP_IOMUX(gpio).FUNC = (IOMUX::GPIO_TO_IOMUX[gpio] > 11) ? 1 : 4;

	// Configure basic GPIO modes
	if (mode & GPIO::INPUT) {
		ESP_IOMUX(gpio).OE = 0;
		ESP_GPIO.ENABLE_W1TC = 1 << gpio;
	} else if (mode & GPIO::OUTPUT) {
		ESP_IOMUX(gpio).OE = 1;
		ESP_GPIO.ENABLE_W1TS = 1 << gpio;
		ESP_GPIO.PIN[gpio].DRIVER = GPIO::DRIVER_PUSH_PULL;
	} else if (mode & GPIO::OUTPUT_OPEN_DRAIN) {
		ESP_IOMUX(gpio).OE = 1;
		ESP_GPIO.ENABLE_W1TS = 1 << gpio;
		ESP_GPIO.PIN[gpio].DRIVER = GPIO::DRIVER_OPEN_DRAIN;
	} else assert(false);

	ESP_IOMUX(gpio).PULLUP   = (mode & GPIO::PULLUP)   ? 1:0;
	ESP_IOMUX(gpio).PULLDOWN = (mode & GPIO::PULLDOWN) ? 1:0;
	if (mode & GPIO::INIT_HIGH) {
		ESP_GPIO.OUT_DATA_W1TS = (1 << gpio);
	}
	if (mode & GPIO::INIT_LOW) {
		ESP_GPIO.OUT_DATA_W1TC = (1 << gpio);
	}
}

bool gpio_esp8266::gpioRead  (uint16_t gpio) {
	assert(gpio < 16);
	return (ESP_GPIO.IN.DATA & (1 << gpio));
}

void gpio_esp8266::gpioWrite (uint16_t gpio, bool value) {
	assert(gpio < 16);
	if (value) {
		ESP_GPIO.OUT_DATA_W1TS = (1 << gpio);
	} else {
		ESP_GPIO.OUT_DATA_W1TC = (1 << gpio);
	}
}

void gpio_esp8266::gpioAttachIrq (uint16_t gpio, void (*handler)(uint16_t gpio),
                                  uint16_t irq_mode) {

}

void gpio_esp8266::gpioDetachIrq (uint16_t gpio) {

}

void gpio_esp8266::gpioEnableIrq (uint16_t gpio) {

}

void gpio_esp8266::gpioDisableIrq(uint16_t gpio) {

}

