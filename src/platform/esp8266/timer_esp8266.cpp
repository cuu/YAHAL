/*
 * espTimer.cpp
 *
 *  Created on: 09.07.2016
 *      Author: aterstegge
 */

//#include "Arduino.h"
#include "esp8266ex.h"
//#include "ets_sys.h"
#include "assert.h"
#include "timer_esp8266.h"

extern "C" {
// #include "user_interface.h"
}

timer_esp8266::timer_esp8266() {
	FRC1.CTRL.value = 0;
	_period_us   = 0;
	_period_load = 0;
	_divider     = 1;
}

timer_esp8266::~timer_esp8266() {
	FRC1.CTRL.value = 0;		// stop the timer and
	TM1_EDGE_INT_DISABLE();		// disable the interrupts
	ETS_FRC1_INTR_DISABLE();
}

void timer_esp8266::setPeriod(uint32_t us, TIMER::timer_mode mode) {
	FRC1.CTRL.RELOAD = (mode == TIMER::PERIODIC); // ? 1 : 0);
	// Start with divider = 1
	_period_us   = us;
	_period_load = 80 * us;
	_divider     = 1;
	FRC1.CTRL.DIVIDER = FRC::DIVIDER_1;
	// check if we need a divider = 16
	if (_period_load > 0x7fffff) {
		_period_load /= 16;
		_divider     *= 16;
		FRC1.CTRL.DIVIDER = FRC::DIVIDER_16;
		// even a divider = 256 ?
		if (_period_load > 0x7fffff) {
			_period_load /= 16;
			_divider     *= 16;
			FRC1.CTRL.DIVIDER = FRC::DIVIDER_256;
		}
	}
	// the period should be in the valid range now
	assert(_period_load <= 0x7fffff);
	FRC1.LOAD = _period_load;
}

uint32_t timer_esp8266::getPeriod() {
	return _period_us;
}

void timer_esp8266::setCallback(void (*f)(timer_interface *)) {
	FRC1.CTRL.INT_TYPE = FRC::INT_TYPE_EDGE;
	ETS_FRC_TIMER1_INTR_ATTACH(f, this);
	TM1_EDGE_INT_ENABLE();
	ETS_FRC1_INTR_ENABLE();
}

void timer_esp8266::start() {
	FRC1.CTRL.ENABLE = 1;
}

void timer_esp8266::stop() {
	FRC1.CTRL.ENABLE = 0;
}

bool timer_esp8266::isRunning() {
	return FRC1.CTRL.ENABLE;
}

uint32_t timer_esp8266::getCounter() {
	return (_period_load - FRC1.COUNT) * _divider / 80;
}

void timer_esp8266::resetCounter() {
	FRC1.LOAD = _period_load;
}
