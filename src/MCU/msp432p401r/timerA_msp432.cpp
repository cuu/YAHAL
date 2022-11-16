/*
 * timer_msp432.cpp
 *
 *  Created on: 09.07.2016
 *      Author: aterstegge
 */

#include "timerA_msp432.h"
#include "yahal_assert.h"

extern uint32_t SubsystemMasterClock;

function<void()> timerA_msp432::_intHandler0 = 0;
function<void()> timerA_msp432::_intHandler1 = 0;
function<void()> timerA_msp432::_intHandler2 = 0;
function<void()> timerA_msp432::_intHandler3 = 0;

timerA_msp432::timerA_msp432(Timer_A_Type * timer)
   : _timer(timer), _mode(TIMER::ONE_SHOT) {
    // initialize attributes
    _period_us   = 0;
    _ccr0        = 0;
    _divider     = 0;
    // initialize the ctl register
    _timer->CTL = 0;
    // enable IRQ in NVIC
    if (timer == TIMER_A0) NVIC_EnableIRQ(TA0_0_IRQn);
    else if (timer == TIMER_A1) NVIC_EnableIRQ(TA1_0_IRQn);
    else if (timer == TIMER_A2) NVIC_EnableIRQ(TA2_0_IRQn);
    else if (timer == TIMER_A3) NVIC_EnableIRQ(TA3_0_IRQn);
}

timerA_msp432::~timerA_msp432() {
    _timer->CTL = 0; // reset control register to default value
}

void timerA_msp432::setPeriod(uint32_t us, TIMER::timer_mode mode) {
    _mode      = mode;
    _period_us = us;
    // Calculate dividers and CCR0
    uint32_t clock_MHz = SubsystemMasterClock / 1000000;
    clock_MHz *= us;
    uint16_t id, ex0;
    bool found = false;
    for (id = 0; id < 4; id++) {
        for (ex0 = 0; ex0 < 8; ex0++) {
            _divider = (1 << id) * (ex0 + 1);
            _ccr0 = clock_MHz / _divider;
            if (_ccr0 < 0x10000) {
                found = true;
                break;
            }
        }
        if (found) break;
    }
    yahal_assert(found);
    // Set the calculated results
    _timer->CTL   &= ~TIMER_A_CTL_ID_MASK;
    _timer->CTL   |= (id << TIMER_A_CTL_ID_OFS);
    _timer->EX0    = ex0;
    _timer->CCR[0] = _ccr0 - 1;
}

uint32_t timerA_msp432::getPeriod() {
	return _period_us;
}

void timerA_msp432::setCallback(function<void()> f) {
    if (_timer == TIMER_A0) { timerA_msp432::_intHandler0 = f; }
    else if (_timer == TIMER_A1) { timerA_msp432::_intHandler1 = f; }
    else if (_timer == TIMER_A2) { timerA_msp432::_intHandler2 = f; }
    else if (_timer == TIMER_A3) { timerA_msp432::_intHandler3 = f; }
}

void timerA_msp432::start() {
    // Initialize control register
    _timer->CTL     |= TIMER_A_CTL_SSEL__SMCLK | // SMCLK clock source
                       TIMER_A_CTL_CLR;          // Clear timer
    _timer->CCTL[0] |= TIMER_A_CCTLN_CCIE;

    // Set the timer mode to start
    if (_mode == TIMER::ONE_SHOT)
        _timer->CTL |= TIMER_A_CTL_MC__CONTINUOUS;
    else
        _timer->CTL |= TIMER_A_CTL_MC__UP;
}

void timerA_msp432::stop() {
    _timer->CTL = 0;
}

bool timerA_msp432::isRunning() {
	return _timer->CTL & TIMER_A_CTL_MC_MASK;
}

uint32_t timerA_msp432::getCounter() {
	return _timer->R * _divider;
}

void timerA_msp432::resetCounter() {
	_timer->CTL |= TIMER_A_CTL_CLR;
}

// Interrupt handler
////////////////////
extern "C" {

void TA0_0_IRQHandler(void) {
    // clear interrupt
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    // disable timer if one-shot was selected
    if ((TIMER_A0->CTL & TIMER_A_CTL_MC_MASK) == TIMER_A_CTL_MC__CONTINUOUS)
         TIMER_A0->CTL = 0;
    // call the user handler
    if (timerA_msp432::_intHandler0) {
        timerA_msp432::_intHandler0();
    }
}

void TA1_0_IRQHandler(void) {
    // clear interrupt
    TIMER_A1->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    // disable timer if one-shot was selected
    if ((TIMER_A1->CTL & TIMER_A_CTL_MC_MASK) == TIMER_A_CTL_MC__CONTINUOUS)
         TIMER_A1->CTL = 0;
    // call the user handler
    if (timerA_msp432::_intHandler1) {
        timerA_msp432::_intHandler1();
    }
}

void TA2_0_IRQHandler(void) {
    // clear interrupt
    TIMER_A2->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    // disable timer if one-shot was selected
    if ((TIMER_A2->CTL & TIMER_A_CTL_MC_MASK) == TIMER_A_CTL_MC__CONTINUOUS)
         TIMER_A2->CTL = 0;
    // call the user handler
    if (timerA_msp432::_intHandler2) {
        timerA_msp432::_intHandler2();
    }
}

void TA3_0_IRQHandler(void) {
    // clear interrupt
    TIMER_A3->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    // disable timer if one-shot was selected
    if ((TIMER_A3->CTL & TIMER_A_CTL_MC_MASK) == TIMER_A_CTL_MC__CONTINUOUS)
         TIMER_A3->CTL = 0;
    // call the user handler
    if (timerA_msp432::_intHandler3) {
        timerA_msp432::_intHandler3();
    }
}

} // extern "C"
