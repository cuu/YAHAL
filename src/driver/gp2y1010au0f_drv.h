/*
 * gp2y1010au0fdrv.h
 *
 *  Created on: 27.01.2017
 *      Author: aterstegge
 */

#ifndef _GP2Y1010AU0F_DRV_H_
#define _GP2Y1010AU0F_DRV_H_

#include "gpio_interface.h"
#include "adc_interface.h"
#include "timer_interface.h"

void callback_helper(void * arg);

class gp2y1010au0f_drv {
public:

	gp2y1010au0f_drv(adc_channel  & adc,
					 gpio_pin & led,
					 timer_interface & timer,
					 float voltage_factor = 1.0);

	~gp2y1010au0f_drv();

	void start_measure(uint16_t measurements,
					   void (*callback)(gp2y1010au0f_drv *));

	inline float get_volt()     { return _volt;     }
	inline float get_volt_min() { return _volt_min; }
	inline float get_volt_max() { return _volt_max; }
	inline float get_dust()     { return _dust;     }

private:

	// Delay values in us. The pre-measurement delay should be 280us according
	// to the data sheet, but the esp adc takes 90us to convert, so we align the
	// _center_ of the adc 'window' to 280us and start 50us earlier...
	static const uint16_t	T		= 10000;	// T is 10ms according to data sheet
	static const uint16_t	DELAY	= 230;		// Delay before ADC measurement

	friend void callback_helper(void * arg);
	void  process_state();
	float voltage_to_dust(float VO);

	// HW members: ADC, LED and timer references
	adc_channel &		_adc;
	gpio_pin &			_ir_led;
	timer_interface &	_timer;

	float				_voltage_factor;	// factor of voltage divider
	uint32_t			_raw_sum;			// sum of all raw adc values
	uint16_t			_measurements;		// Number of measurements to perform
	uint16_t			_counter;	   		// Measurement counter
	float				_volt;
	float				_volt_min;
	float				_volt_max;
	float				_dust;
	void				(*_callback)(gp2y1010au0f_drv *);

	enum sensor_state_t {
		START_MEASURE, DO_MEASURE, STOP_MEASURE
	};
	sensor_state_t		_state;		// The current state of the sensor

};

#endif /* SRC_DRIVER_GP2Y1010AU0FDRV_H_ */

