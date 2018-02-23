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
	assert(channel == 0 && (mode & ~ADC::FAST) == ADC::ADC_10_BIT);
	_mode = mode;
}

ICACHE_FLASH_ATTR
uint16_t adc_esp8266::adcReadRaw(uint8_t channel) {
	assert(channel == 0);
	uint16_t res = 0;
	if (_mode & ADC::FAST) {
		res = 0; //system_get_vdd33();
	} else {
		res = system_adc_read();
	}
	return res;
}

ICACHE_FLASH_ATTR
float adc_esp8266::adcReadVoltage(uint8_t channel) {
	assert(channel == 0);
	return rawToVoltage(0, adcReadRaw(channel));
}

ICACHE_FLASH_ATTR
float adc_esp8266::rawToVoltage(uint8_t channel, uint16_t raw) {
	assert(channel == 0);
	return (float)raw / 960.0f;
}
