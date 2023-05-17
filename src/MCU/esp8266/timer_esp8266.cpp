/*
 * timer_esp8266.cpp
 *
 *  Created on: 09.07.2016
 *      Author: aterstegge
 */

#include "timer_esp8266.h"
#include "ESP8266.h"
#include "assert.h"

extern "C" {
#include "ets_sys.h"
}

timer_esp8266::timer_esp8266() {
	_TIMER_::TIMER.FRC1_CTRL = 0;
	_period_us   = 0;
	_period_load = 0;
	_divider     = 1;
}


timer_esp8266::~timer_esp8266() {
	_TIMER_::TIMER.FRC1_CTRL = 0;    // stop the timer and
	TM1_EDGE_INT_DISABLE();	   // disable the interrupts
	ETS_FRC1_INTR_DISABLE();
}


void timer_esp8266::setPeriod(uint32_t us, TIMER::timer_mode mode) {
	_TIMER_::TIMER.FRC1_CTRL.RELOAD = (mode == TIMER::PERIODIC); // ? 1 : 0);
	// Start with divider = 1
	_period_us   = us;
	_period_load = 80 * us;
	_divider     = 1;
	_TIMER_::TIMER.FRC1_CTRL.DIVIDER = _TIMER_::FRC1_CTRL_DIVIDER__1;
	// check if we need a divider = 16
	if (_period_load > 0x7fffff) {
		_period_load /= 16;
		_divider     *= 16;
		_TIMER_::TIMER.FRC1_CTRL.DIVIDER = _TIMER_::FRC1_CTRL_DIVIDER__16;
		// even a divider = 256 ?
		if (_period_load > 0x7fffff) {
			_period_load /= 16;
			_divider     *= 16;
			_TIMER_::TIMER.FRC1_CTRL.DIVIDER = _TIMER_::FRC1_CTRL_DIVIDER__256;
		}
	}
	// the period should be in the valid range now
	assert(_period_load <= 0x7fffff);
	_TIMER_::TIMER.FRC1_LOAD = _period_load;
}


uint32_t timer_esp8266::getPeriod() {
	return _period_us;
}


void timer_esp8266::setCallback(function<void()> f) {
    _handler = f;
    _TIMER_::TIMER.FRC1_CTRL.INT_TYPE = _TIMER_::FRC1_CTRL_INT_TYPE__EDGE;
    ETS_FRC_TIMER1_INTR_ATTACH(timer_irq_handler, this);
    TM1_EDGE_INT_ENABLE();
    ETS_FRC1_INTR_ENABLE();
}


void timer_esp8266::start() {
	_TIMER_::TIMER.FRC1_CTRL.ENABLE = 1;
}


void timer_esp8266::stop() {
	_TIMER_::TIMER.FRC1_CTRL.ENABLE = 0;
}


bool timer_esp8266::isRunning() {
	return _TIMER_::TIMER.FRC1_CTRL.ENABLE;
}


uint32_t timer_esp8266::getCounter() {
	return (_period_load - _TIMER_::TIMER.FRC1_COUNT) * _divider / 80;
}

void timer_esp8266::resetCounter() {
	_TIMER_::TIMER.FRC1_LOAD = _period_load;
}

void timer_irq_handler(timer_esp8266 *timer) {
    if(timer->_handler) timer->_handler();
}
