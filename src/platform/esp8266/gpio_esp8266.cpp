#include "gpio_esp8266.h"
#include "esp8266ex.h"
#include "yahal_assert.h"

extern "C" {
#include "ets_sys.h"
}

gpio_esp8266 gpio_esp8266::inst;

ICACHE_FLASH_ATTR
gpio_esp8266:: gpio_esp8266() {
	for (int i=0; i < 16; ++i) {
		intHandler[i] = 0;
		intMode[i]    = _GPIO_::INT_DISABLE;
	}
	ETS_GPIO_INTR_ATTACH(gpio_irq_handler, this);
	ETS_GPIO_INTR_ENABLE();
}

ICACHE_FLASH_ATTR
gpio_esp8266::~gpio_esp8266() {
	ETS_GPIO_INTR_DISABLE();
}

ICACHE_FLASH_ATTR
void gpio_esp8266::gpioMode(uint16_t gpio, uint16_t mode) {
	yahal_assert(gpio < 16);

	// Select GPIO as pin function
	ESP_IOMUX(gpio).FUNC = (_IOMUX_::GPIO_TO_IOMUX[gpio] > 11) ? 1 : 4;

	// Configure basic GPIO modes
	if (mode & GPIO::INPUT) {
		ESP_IOMUX(gpio).OE = 0;
		ESP_GPIO.ENABLE_W1TC = 1 << gpio;
	} else if (mode & GPIO::OUTPUT) {
		ESP_IOMUX(gpio).OE = 1;
		ESP_GPIO.ENABLE_W1TS = 1 << gpio;
		ESP_GPIO.PIN[gpio].DRIVER = _GPIO_::DRIVER_PUSH_PULL;
	} else if (mode & GPIO::OUTPUT_OPEN_DRAIN) {
		ESP_IOMUX(gpio).OE = 1;
		ESP_GPIO.ENABLE_W1TS = 1 << gpio;
		ESP_GPIO.PIN[gpio].DRIVER = _GPIO_::DRIVER_OPEN_DRAIN;
	} else yahal_assert(false);

	ESP_IOMUX(gpio).PULLUP   = (mode & GPIO::PULLUP)   ? 1:0;
	ESP_IOMUX(gpio).PULLDOWN = (mode & GPIO::PULLDOWN) ? 1:0;
	if (mode & GPIO::INIT_HIGH) {
		ESP_GPIO.OUT_DATA_W1TS = (1 << gpio);
	}
	if (mode & GPIO::INIT_LOW) {
		ESP_GPIO.OUT_DATA_W1TC = (1 << gpio);
	}
}

ICACHE_FLASH_ATTR
bool gpio_esp8266::gpioRead(uint16_t gpio) {
	yahal_assert(gpio < 16);
	return (ESP_GPIO.IN.DATA & (1 << gpio));
}

ICACHE_FLASH_ATTR
void gpio_esp8266::gpioWrite(uint16_t gpio, bool value) {
	yahal_assert(gpio < 16);
	if (value) {
		ESP_GPIO.OUT_DATA_W1TS = (1 << gpio);
	} else {
		ESP_GPIO.OUT_DATA_W1TC = (1 << gpio);
	}
}

ICACHE_FLASH_ATTR
void gpio_esp8266::gpioToggle(uint16_t gpio) {
	yahal_assert(gpio < 16);
	ESP_GPIO.OUT ^= (1 << gpio);
}

ICACHE_FLASH_ATTR
void gpio_esp8266::gpioAttachIrq(uint16_t gpio, void (*handler)(uint16_t gpio),
                                 uint16_t irq_mode) {
	yahal_assert(gpio < 16);
	intHandler[gpio] = handler;
	int esp_mode = _GPIO_::INT_DISABLE;
	switch(irq_mode) {
	case GPIO::RISING:      esp_mode = _GPIO_::INT_RAISING_EDGE; break;
	case GPIO::FALLING:     esp_mode = _GPIO_::INT_FALLING_EDGE; break;
	case GPIO::RISING |
	     GPIO::FALLING: 	esp_mode = _GPIO_::INT_BOTH_EDGES;   break;
	case GPIO::LEVEL_HIGH:	esp_mode = _GPIO_::INT_LEVEL_HIGH;   break;
	case GPIO::LEVEL_LOW:	esp_mode = _GPIO_::INT_LEVEL_LOW;    break;
	default: yahal_assert(false);
	}
	intMode[gpio] = esp_mode;
	ESP_GPIO.PIN[gpio].INT_TYPE = esp_mode;
}

ICACHE_FLASH_ATTR
void gpio_esp8266::gpioDetachIrq(uint16_t gpio) {
	yahal_assert(gpio < 16);
	gpioDisableIrq(gpio);
	intMode[gpio] = _GPIO_::INT_DISABLE;
	intHandler[gpio] = 0;
}

ICACHE_FLASH_ATTR
void gpio_esp8266::gpioEnableIrq(uint16_t gpio) {
	yahal_assert(gpio < 16);
	ESP_GPIO.PIN[gpio].INT_TYPE = intMode[gpio];
}

ICACHE_FLASH_ATTR
void gpio_esp8266::gpioDisableIrq(uint16_t gpio) {
	yahal_assert(gpio < 16);
	ESP_GPIO.PIN[gpio].INT_TYPE = _GPIO_::INT_DISABLE;
}

ICACHE_FLASH_ATTR
void gpio_esp8266::handleInterrupt() {
	// Acknowledge all pending IRQs
	uint16_t status = ESP_GPIO.STATUS;
	ESP_GPIO.STATUS_W1TC = status;

	// Serve all pending IRQs
	while(uint8_t gpio = __builtin_ffs(status)) {
		--gpio;
		status &= ~(1 << gpio);
		if (intHandler[gpio]) intHandler[gpio](gpio);
	}
}

ICACHE_FLASH_ATTR
void gpio_irq_handler(gpio_esp8266 * gpio) {
	gpio->handleInterrupt();
}

ICACHE_FLASH_ATTR
void gpio_esp8266::brightnessControl(uint16_t gpio, bool on) {
	yahal_assert(gpio < 16);
	if (on) {
		ESP_GPIO.PIN[gpio].SOURCE = _GPIO_::SOURCE_SIGMA_DELTA;
	} else {
		ESP_GPIO.PIN[gpio].SOURCE = _GPIO_::SOURCE_GPIO;
	}
}

ICACHE_FLASH_ATTR
void gpio_esp8266::setBrightness(uint8_t value) {
	ESP_GPIO.SIGMA_DELTA.ENABLE   = 1;
	ESP_GPIO.SIGMA_DELTA.PRESCALE = 0x80;
	ESP_GPIO.SIGMA_DELTA.TARGET   = value;
}

