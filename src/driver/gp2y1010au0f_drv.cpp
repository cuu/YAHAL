/*
 * gp2y1010au0fdrv.cpp
 *
 *  Created on: 27.01.2017
 *      Author: aterstegge
 */

#include "gp2y1010au0f_drv.h"
#include "assert.h"

void callback_helper(void * arg) {
	gp2y1010au0f_drv * sensor = static_cast<gp2y1010au0f_drv *>(arg);
	sensor->process_state();
}

gp2y1010au0f_drv::gp2y1010au0f_drv(adc_pin  & adc,
								   gpio_pin & led,
								   timer_interface & timer,
								   float divider)
: _adc(adc), _ir_led(led), _timer(timer), _voltage_divider(divider) {

	// HW initialization
	_ir_led.gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
	_timer.setCallback(callback_helper, this);

	// initialize members
	_raw_sum      = 0;
	_measurements = 0;
	_counter      = 0;
	_volt		  = 0.0f;
	_volt_min	  = 1.0f;
	_volt_max	  = 2.5f;
	_dust		  = 0.0f;
	_callback     = 0;
	_state        = STOP_MEASURE;
}

void gp2y1010au0f_drv::start_measure(uint16_t m, void (*callback)(gp2y1010au0f_drv *)) {
	_callback     = callback;
	_raw_sum      = 0.0;
	_measurements = m;
	_counter      = m;
	_state   	  = START_MEASURE;
	_timer.start();
	process_state();
}

gp2y1010au0f_drv::~gp2y1010au0f_drv() {
	_ir_led.gpioMode(GPIO::INPUT);
	_timer.stop();
}

void gp2y1010au0f_drv::process_state() {
	switch (_state) {
		case START_MEASURE: {
			// delay measurement, switch on IR LED
			_timer.setPeriod(DELAY, TIMER::ONE_SHOT);
			// set new state
			_state = DO_MEASURE;
			// switch on IR LED
			_ir_led.gpioWrite(HIGH);
			break;
		}
		case DO_MEASURE: {
			// start the timer for after-measurement delay
			_timer.setPeriod(T - DELAY, TIMER::ONE_SHOT);
			// read out raw adc value
			_raw_sum += _adc.adcReadRaw();
			// switch off IR LED
			_ir_led.gpioWrite(LOW);
			// check if we need another measurement
			_counter--;
			if (_counter) {
				// delay until next measurement
				_timer.setPeriod(T - DELAY, TIMER::ONE_SHOT);
				// set new state
				_state = START_MEASURE;
			} else {
				_timer.stop();
				_state = STOP_MEASURE;
				process_state();
			}
			break;
		}
		case STOP_MEASURE: {
			// do measure post-processing:
			// 1. mean raw ADC value
			_raw_sum  /= _measurements;
			// 2. calculate voltage
			_volt  = _adc.rawToVoltage(_raw_sum);
			_volt /= _voltage_divider;
			// 3. evaluate max/min values
			if (_volt < _volt_min) _volt_min = _volt;
			if (_volt > _volt_max) _volt_max = _volt;
			// 4. calculate dust
			_dust = voltage_to_dust(_volt);
			// Use callback to write value
			_callback(this);
			break;
		}
	}
}

// This method is based on the output voltage
// graph in the data sheet. It interpolates the
// the graph with two linear sections.
// Output range and unit is: 0..800 ug/m3
float gp2y1010au0f_drv::voltage_to_dust(float VO) {
	float v1 = _volt_min + 0.05f;
	float v2 = _volt_max - 0.2f;

	if (VO  < v1) return 0.0f;
	if (VO  < v2) {
	    VO -= v1;
		return 500.0f / (v2-v1) * VO;
	}
	if (VO  < _volt_max) {
		VO -= v2 ;
		return 300.0f / (_volt_max - v2) * VO + 500.0f;
	}
	return 800.0f;
}

