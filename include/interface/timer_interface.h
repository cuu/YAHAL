/*
 * timer_interface.h
 *
 *  Created on: 09.07.2016
 *      Author: aterstegge
 */

#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H
#include <stdint.h>

namespace TIMER {
	enum timer_mode {
		ONE_SHOT,
		PERIODIC
	};
}

class timer_interface {

  public:
	virtual void	 setPeriod(uint32_t us, TIMER::timer_mode mode) = 0;
	virtual uint32_t getPeriod() = 0;

	virtual void	 setCallback(void (*f)(void *), void * arg) = 0;

	virtual void	 start() = 0;
	virtual void	 stop()  = 0;
	virtual bool	 isRunning() = 0;

	virtual uint32_t getCounter()   = 0;
	virtual void	 resetCounter() = 0;

  protected:
	virtual ~timer_interface() { };

};

#endif // TIMER_INTERFACE_H
