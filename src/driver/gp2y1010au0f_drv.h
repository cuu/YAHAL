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

class gp2y1010au0f_drv {
public:
	static gp2y1010au0f_drv *inst;

	gp2y1010au0f_drv(adc_pin  & adc,
				     gpio_pin & led,
					 timer_interface & timer,
					 float voltage_factor = 1.0);

	~gp2y1010au0f_drv();

	float get_dust(uint16_t samples);
	void  process_state(timer_interface *timer);

private:

	static const uint16_t	T				= 10000;	// T is 10ms according to data sheet
	static const uint16_t	PULSEWIDTH		= 320;		// Pulse width is 320 us
	static const uint16_t	DELAY			= 280;		// Delay before ADC measurement

	float get_VO();
	float voltage_to_dust(float VO);

	enum sensor_state_t {
		START_MEASURE, DO_MEASURE, WAIT_FOR_NEXT_MEASURE, STOP
	};

	sensor_state_t		_state;
	adc_pin	 &			_adc;
	gpio_pin &			_led;
	timer_interface &	_timer;
	float				_voltage_factor;
	float				_VO_avg;
	uint16_t			_samples;
	uint16_t			_sample_counter;
};

#endif /* SRC_DRIVER_GP2Y1010AU0FDRV_H_ */
