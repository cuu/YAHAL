/*
 * gp2y1010au0fdrv.cpp
 *
 *  Created on: 27.01.2017
 *      Author: aterstegge
 */

#include "gp2y1010au0f_drv.h"
#include "assert.h"
#include "osapi.h"

extern "C" {
// Missing defines for ROM code
void ets_delay_us(uint16_t);
}

gp2y1010au0f_drv * gp2y1010au0f_drv::inst = 0;

void callback_helper(timer_interface * t) {
	if (gp2y1010au0f_drv::inst)
		gp2y1010au0f_drv::inst->process_state(t);
}

gp2y1010au0f_drv::gp2y1010au0f_drv(adc_pin  & adc,
								   gpio_pin & led,
								   timer_interface & timer,
								   float voltage_factor)
: _adc(adc), _led(led), _timer(timer), _voltage_factor(voltage_factor) {

	_led.gpioMode(GPIO::OUTPUT);
	_timer.stop();
	_timer.setCallback(callback_helper);
	_state   = STOP;
	_VO_avg  = 0.0;
	_samples = 0;
	_sample_counter = 0;
}

gp2y1010au0f_drv::~gp2y1010au0f_drv() {
	_led.gpioMode(GPIO::INPUT);
	_timer.stop();
}

void gp2y1010au0f_drv::process_state(timer_interface *timer) {
	switch (_state) {
		case START_MEASURE: {
			// Switch on IR LED
			_led.gpioWrite(HIGH);
			// Start the timer because the measurement
			// is delayed ...
			_timer.setPeriod(DELAY, TIMER::ONE_SHOT);
			// Set new state
			_state = DO_MEASURE;
			break;
		}
		case DO_MEASURE: {
			// Read out voltage
			_VO_avg += get_VO();
			_sample_counter--;
			// Start the timer for after-measurement delay
			_timer.setPeriod(PULSEWIDTH - DELAY, TIMER::ONE_SHOT);
			// Set new state
			_state = WAIT_FOR_NEXT_MEASURE;
			break;
		}
		case WAIT_FOR_NEXT_MEASURE: {
			// Switch off IR LED
			_led.gpioWrite(LOW);
			if (_sample_counter) {
				// Start timer for inter-measurement delay
				_timer.setPeriod(T - PULSEWIDTH, TIMER::ONE_SHOT);
				// Set new state
				_state = START_MEASURE;
			} else {
				_timer.stop();
				// Calculate average VO value
				_VO_avg /= (float)_samples;
				_state = STOP;
			}
			break;
		}
		case STOP: {
			// NOOP. We should never come here
			assert(false);
			break;
		}
	}
}

float gp2y1010au0f_drv::get_dust(uint16_t samples) {
	gp2y1010au0f_drv::inst = this;
	_VO_avg  = 0.0;
	_samples = samples;
	_sample_counter = _samples;
	_state   = START_MEASURE;
	_timer.resetCounter();
	_timer.start();
	process_state(&_timer);

	while (_state != STOP)
		os_delay_us(10000);

	return voltage_to_dust(_VO_avg);
}

float gp2y1010au0f_drv::get_VO() {
	return _adc.adcReadVoltage() * this->_voltage_factor;
}

// This method is based on the output voltage
// graph in the data sheet. It interpolates the
// the graph with two linear sections.
// Output range and unit is: 0..800 ug/m3
float gp2y1010au0f_drv::voltage_to_dust(float VO) {
	if (VO  < 0.6f) return 0.0f;
	if (VO  < 3.5f) {
	    VO -= 0.6f;
	    return 500.0f / 2.9f * VO;
	}
	if (VO  < 3.7f) {
	    VO -= 3.5f;
	    return 300.0f / 0.2f * VO + 500.0f;
	}
	return 800.0f;
}

