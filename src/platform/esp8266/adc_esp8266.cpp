#include "adc_esp8266.h"
#include "assert.h"

extern "C" {
#include "user_interface.h"
}
adc_esp8266 adc_esp8266::inst;

ICACHE_FLASH_ATTR
adc_esp8266::adc_esp8266() {}

ICACHE_FLASH_ATTR
adc_esp8266::~adc_esp8266() {}

ICACHE_FLASH_ATTR
void adc_esp8266::adcMode(uint8_t channel, uint16_t mode) {
	assert(channel == 0 && mode == ADC::ADC_10_BIT);
}

ICACHE_FLASH_ATTR
uint16_t adc_esp8266::adcReadRaw(uint8_t channel) {
	assert(channel == 0);
	return system_adc_read();
}

ICACHE_FLASH_ATTR
float adc_esp8266::adcReadVoltage(uint8_t channel) {
	assert(channel == 0);
	return (float)system_adc_read() / 1024.0f;
}

