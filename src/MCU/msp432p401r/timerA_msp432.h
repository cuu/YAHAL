/*
 *
 *  Created on: 21.07.2021
 *      Author: aterstegge
 */

#ifndef _TIMER_A_MSP432_H_
#define _TIMER_A_MSP432_H_
#include "timer_interface.h"
#include "msp.h"

extern "C" {
void TA0_0_IRQHandler (void);
void TA1_0_IRQHandler (void);
void TA2_0_IRQHandler (void);
void TA3_0_IRQHandler (void);
}

class timerA_msp432 : public timer_interface {
  public:
	timerA_msp432(Timer_A_Type * timer = TIMER_A0);
	virtual ~timerA_msp432();

	void	 setPeriod(uint32_t us, TIMER::timer_mode mode = TIMER::ONE_SHOT);
	uint32_t getPeriod();

	void	 setCallback(function<void()> f);

	void	 start();
	void	 stop();
	bool	 isRunning();

	uint32_t getCounter();
	void	 resetCounter();

	// IRQ handlers are our best friends
    friend void TA0_0_IRQHandler (void);
    friend void TA1_0_IRQHandler (void);
    friend void TA2_0_IRQHandler (void);
    friend void TA3_0_IRQHandler (void);

  private:

    static function<void()> _intHandler0;
    static function<void()> _intHandler1;
    static function<void()> _intHandler2;
    static function<void()> _intHandler3;

    Timer_A_Type *      _timer;
    TIMER::timer_mode   _mode;

    uint32_t            _period_us ; // period in us
    uint32_t            _ccr0;
    uint32_t            _divider;
};

#endif // _TIMER_A_MSP432_H_
