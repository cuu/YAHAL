/*
 * espTimer.h
 *
 *  Created on: 09.07.2016
 *      Author: aterstegge
 */

#ifndef _TIMER_ESP8266_H_
#define _TIMER_ESP8266_H_
#include "timer_interface.h"

class timer_esp8266 : public timer_interface {
  public:
	timer_esp8266();
	virtual ~timer_esp8266();

	void	 setPeriod(uint32_t us, TIMER::timer_mode mode = TIMER::ONE_SHOT);
	uint32_t getPeriod();

	void	 setCallback( void (*f)(timer_interface *) );

	void	 start();
	void	 stop();
	bool	 isRunning();

	uint32_t getCounter();
	void	 resetCounter();

  private:
	uint32_t _period_us ; // load value in us
	uint32_t _period_load;
	uint32_t _divider;
};

#endif // _TIMER_ESP8266_H_
