/*
 * timer_esp8266.cpp
 *
 *  Created on: 09.07.2016
 *      Author: aterstegge
 */

#include "timer_esp8266.h"
#include "esp8266ex.h"
#include "assert.h"

#include "ets_sys.h"
/*
extern "C" {
	// Missing defines for ROM code
	void ets_isr_attach(int intr, void (*handler)(void *), void * arg);
	void ets_isr_mask  (unsigned intr);
	void ets_isr_unmask(unsigned intr);
}
*/

ICACHE_FLASH_ATTR
timer_esp8266::timer_esp8266() {
	ESP_FRC1.CTRL.value = 0;
	_period_us   = 0;
	_period_load = 0;
	_divider     = 1;
}

ICACHE_FLASH_ATTR
timer_esp8266::~timer_esp8266() {
	ESP_FRC1.CTRL.value = 0;	// stop the timer and
	TM1_EDGE_INT_DISABLE();		// disable the interrupts
	ETS_FRC1_INTR_DISABLE();
}

ICACHE_FLASH_ATTR
void timer_esp8266::setPeriod(uint32_t us, TIMER::timer_mode mode) {
	ESP_FRC1.CTRL.RELOAD = (mode == TIMER::PERIODIC); // ? 1 : 0);
	// Start with divider = 1
	_period_us   = us;
	_period_load = 80 * us;
	_divider     = 1;
	ESP_FRC1.CTRL.DIVIDER = _FRC_::DIVIDER_1;
	// check if we need a divider = 16
	if (_period_load > 0x7fffff) {
		_period_load /= 16;
		_divider     *= 16;
		ESP_FRC1.CTRL.DIVIDER = _FRC_::DIVIDER_16;
		// even a divider = 256 ?
		if (_period_load > 0x7fffff) {
			_period_load /= 16;
			_divider     *= 16;
			ESP_FRC1.CTRL.DIVIDER = _FRC_::DIVIDER_256;
		}
	}
	// the period should be in the valid range now
	assert(_period_load <= 0x7fffff);
	ESP_FRC1.LOAD = _period_load;
}

ICACHE_FLASH_ATTR
uint32_t timer_esp8266::getPeriod() {
	return _period_us;
}

ICACHE_FLASH_ATTR
void timer_esp8266::setCallback(void (*f)(void *), void * arg) {
	ESP_FRC1.CTRL.INT_TYPE = _FRC_::INT_TYPE_EDGE;
	ETS_FRC_TIMER1_INTR_ATTACH(f, arg);
	TM1_EDGE_INT_ENABLE();
	ETS_FRC1_INTR_ENABLE();
}

ICACHE_FLASH_ATTR
void timer_esp8266::start() {
	ESP_FRC1.CTRL.ENABLE = 1;
}

ICACHE_FLASH_ATTR
void timer_esp8266::stop() {
	ESP_FRC1.CTRL.ENABLE = 0;
}

ICACHE_FLASH_ATTR
bool timer_esp8266::isRunning() {
	return ESP_FRC1.CTRL.ENABLE;
}

ICACHE_FLASH_ATTR
uint32_t timer_esp8266::getCounter() {
	return (_period_load - ESP_FRC1.COUNT) * _divider / 80;
}

ICACHE_FLASH_ATTR
void timer_esp8266::resetCounter() {
	ESP_FRC1.LOAD = _period_load;
}
