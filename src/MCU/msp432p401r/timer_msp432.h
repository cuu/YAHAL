/*
 *
 *  Created on: 27.02.2017
 *      Author: aterstegge
 */

#ifndef _TIMER_MSP432_H_
#define _TIMER_MSP432_H_
#include "timer_interface.h"
#include "msp.h"

extern "C" {
void T32_INT1_IRQHandler (void);
void T32_INT2_IRQHandler (void);
}

class timer_msp432 : public timer_interface {
  public:
	timer_msp432(Timer32_Type * timer = TIMER32_1);
	virtual ~timer_msp432();

	void	 setPeriod(uint32_t us, TIMER::timer_mode mode = TIMER::ONE_SHOT);
	uint32_t getPeriod();

	void	 setCallback(function<void()> f);

	void	 start();
	void	 stop();
	bool	 isRunning();

	void	 reset();

    // Additional methods (not in timer_interface)
	void     setNanoPeriod(uint32_t ns, TIMER::timer_mode mode = TIMER::ONE_SHOT);
    uint32_t getNanoPeriod();

	// IRQ handlers are our best friends
    friend void T32_INT1_IRQHandler(void);
    friend void T32_INT2_IRQHandler(void);

  private:

    static function<void()> _intHandler1;
    static function<void()> _intHandler2;

	Timer32_Type * _timer;
	uint32_t _factor;     // count for one us
    uint32_t _period_us ; // load value in us
    uint32_t _period_ns ; // load value in ns
    uint32_t _period_load;
};

#endif // _TIMER_MSP432_H_

