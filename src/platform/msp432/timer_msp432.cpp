/*
 * timer_msp432.cpp
 *
 *  Created on: 09.07.2016
 *      Author: aterstegge
 */

#include "timer_msp432.h"
#include "yahal_assert.h"

extern uint32_t SystemCoreClock;

void (* timer_msp432::_intHandler1)(void *) = 0;
void (* timer_msp432::_intHandler2)(void *) = 0;
void  * timer_msp432::_arg1 = 0;
void  * timer_msp432::_arg2 = 0;

// We use the TIMER32 instances here (they might not
// be used for other purposes anyway...)

timer_msp432::timer_msp432(Timer32_Type * timer)
   : _timer(timer) {
    // initialize the ctrl register
    _timer->CONTROL = TIMER32_CONTROL_MODE | // periodic mode
                      TIMER32_CONTROL_IE |   // enable irq
                      TIMER32_CONTROL_SIZE;  // use 32 bit counter
    // calculate factor (counts for 1us)
    _factor      = SystemCoreClock / 1000000;
    _period_us   = 0;
    _period_ns   = 0;
    _period_load = 0;
    // enable IRQ in NVIC
    NVIC_EnableIRQ( (timer==TIMER32_1) ? T32_INT1_IRQn : T32_INT2_IRQn );
}

timer_msp432::~timer_msp432() {
    _timer->CONTROL = 0; // reset ctrl to default value
}

void timer_msp432::setPeriod(uint32_t us, TIMER::timer_mode mode) {
    _period_us = us;
    // set load register
    _timer->LOAD = _period_load = us * _factor;
    // set onshot
    if (mode == TIMER::ONE_SHOT) {
        _timer->CONTROL |=  TIMER32_CONTROL_ONESHOT;
    } else {
        _timer->CONTROL &= ~TIMER32_CONTROL_ONESHOT;
    }
}

uint32_t timer_msp432::getPeriod() {
	return _period_us;
}

void timer_msp432::setCallback(void (*f)(void *), void * arg) {
    if (_timer == TIMER32_1) {
        timer_msp432::_intHandler1 = f;
        timer_msp432::_arg1 = arg;
    } else {
        timer_msp432::_intHandler2 = f;
        timer_msp432::_arg2 = arg;
    }
}

void timer_msp432::start() {
    _timer->CONTROL |= TIMER32_CONTROL_ENABLE;
}

void timer_msp432::stop() {
    _timer->CONTROL &= ~TIMER32_CONTROL_ENABLE;
}

bool timer_msp432::isRunning() {
	return _timer->CONTROL & TIMER32_CONTROL_ENABLE;
}

uint32_t timer_msp432::getCounter() {
	return (_period_load - _timer->VALUE) / _factor;
}

void timer_msp432::resetCounter() {
	_timer->LOAD = _period_load;
}

void timer_msp432::setNanoPeriod(uint32_t ns, TIMER::timer_mode mode) {
    _period_ns = ns;
    // set load register
    _timer->LOAD = _period_load = (ns * _factor) / 1000;
    // set onshot
    if (mode == TIMER::ONE_SHOT) {
        _timer->CONTROL |=  TIMER32_CONTROL_ONESHOT;
    } else {
        _timer->CONTROL &= ~TIMER32_CONTROL_ONESHOT;
    }
}

uint32_t timer_msp432::getNanoPeriod() {
    return _period_ns;
}

// Interrupt handler
////////////////////
extern "C" {

void T32_INT1_IRQHandler(void) {
    // clear the interrupt
    TIMER32_1->INTCLR = 1;
    // disable timer if one-shot was selected
    if (TIMER32_1->CONTROL & TIMER32_CONTROL_ONESHOT)
        TIMER32_1->CONTROL &= ~TIMER32_CONTROL_ENABLE;
    // call the user handler
    if (timer_msp432::_intHandler1) {
        timer_msp432::_intHandler1(timer_msp432::_arg1);
    }
}
void T32_INT2_IRQHandler(void) {
    // clear the interrupt
    TIMER32_2->INTCLR = 1;
    // disable timer if one-shot was selected
    if (TIMER32_2->CONTROL & TIMER32_CONTROL_ONESHOT)
        TIMER32_2->CONTROL &= ~TIMER32_CONTROL_ENABLE;
    // call the user handler
    if (timer_msp432::_intHandler2) {
        timer_msp432::_intHandler2(timer_msp432::_arg2);
    }
}

} // extern "C"
