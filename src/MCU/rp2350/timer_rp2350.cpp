/*
 * timer_rp2040.cpp
 *
 *  Created on: 01.11.2022
 *      Author: aterstegge
 */

#include "timer_rp2350.h"
#include "system_rp2350.h"
#include <cassert>

timer_rp2350 *   timer_rp2350::_timerinst[4];
function<void()> timer_rp2350::_callback[4];

timer_rp2350::timer_rp2350(int8_t index) {
    if (index == -1) {
        // Find next free timer
        for (index=0; index < 4; ++index) {
            if (!_timerinst[index]) break;
        }
    }
    assert(index < 4);
    assert(_timerinst[index] == nullptr);
    // Initialize members
    _index      = index;
    _mask       = 1 << index;
    _alarm      = &(_TIMER0_::TIMER0.ALARM[index]);
    _mode       = TIMER::ONE_SHOT;
    _period     = 0;
    // Use the system clock for higher accuracy
    _TIMER0_::TIMER0.SOURCE = _TIMER0_::SOURCE_CLK_SYS__CLK_SYS;
    // Calculate factor for 1 us
    _tick_factor= CLK_SYS / 1000000;
    // Register timer instance pointer
    _timerinst[index] = this;
    // Enable timer interrupt
    _TIMER0_::TIMER0_SET.INTE = _mask;
    // enable IRQ in NVIC. Default priority is 0 (highest).
    NVIC_EnableIRQ(IRQn_Type(TIMER0_IRQ_0_IRQn + index));
}

timer_rp2350::~timer_rp2350() {
    stop();
    _timerinst[_index] = nullptr;
}

void timer_rp2350::setPeriod(uint32_t us, TIMER::timer_mode mode) {
    _period = us * _tick_factor;
    _mode   = mode;
}

void timer_rp2350::setPeriod_ns(uint32_t ns, TIMER::timer_mode mode) {
    _period = (ns * _tick_factor) / 1000;
    _mode   = mode;
}

uint32_t timer_rp2350::getPeriod() {
    return _period / _tick_factor;
}

void timer_rp2350::setCallback(function<void()> f) {
    timer_rp2350::_callback[_index] = f;
}

void timer_rp2350::start() {
    *_alarm = _TIMER0_::TIMER0.TIMERAWL + _period;
}

void timer_rp2350::stop() {
    if (isRunning()) {
        // Clear 'armed'-bit
        _TIMER0_::TIMER0.ARMED = _mask;
    }
}

bool timer_rp2350::isRunning() {
    return _TIMER0_::TIMER0.ARMED & _mask;
}

void timer_rp2350::reset() {
    // If timer is running, immediately
    // trigger a re-start.
    if (isRunning()) start();
}

void timer_rp2350::irqHandler() {
    // Clear interrupt
    _TIMER0_::TIMER0.INTR = _mask;
    // Re-trigger timer if periodic
    if (_mode == TIMER::PERIODIC) {
        *_alarm += _period;
    }
    // Call the user-provided handler
    _callback[_index]();
}

// Interrupt handler
////////////////////
extern "C" {

void TIMER0_IRQ_0_Handler(void) {
    timer_rp2350::_timerinst[0]->irqHandler();
}

void TIMER0_IRQ_1_Handler(void) {
    timer_rp2350::_timerinst[1]->irqHandler();
}

void TIMER0_IRQ_2_Handler(void) {
    timer_rp2350::_timerinst[2]->irqHandler();
}

void TIMER0_IRQ_3_Handler(void) {
    timer_rp2350::_timerinst[3]->irqHandler();
}

} // extern "C"
