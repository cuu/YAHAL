/*
 * timer_rp2040.cpp
 *
 *  Created on: 01.11.2022
 *      Author: aterstegge
 */

#include "timer_rp2040.h"
#include "system_rp2040.h"
#include <cassert>

timer_rp2040 *   timer_rp2040::_timerinst[4];
function<void()> timer_rp2040::_callback[4];

timer_rp2040::timer_rp2040(int8_t index) {
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
    _ALARM      = &(_TIMER_::TIMER.ALARM0) + index;
    _mode       = TIMER::ONE_SHOT;
    _period     = 0;
    // Calculate factor
    _tick_factor= CLK_TICK / 1000000;
    // Register timer instance pointer
    _timerinst[index] = this;
    // Enable timer interrupt
    _TIMER_::TIMER_SET.INTE = _mask;
    // enable IRQ in NVIC
    NVIC_EnableIRQ(IRQn_Type(TIMER_IRQ_0_IRQn + index));
}

timer_rp2040::~timer_rp2040() {
    stop();
    _timerinst[_index] = nullptr;
}

void timer_rp2040::setPeriod(uint32_t us, TIMER::timer_mode mode) {
    _period = us * _tick_factor;
    _mode   = mode;
}

void timer_rp2040::setPeriod_ns(uint32_t ns, TIMER::timer_mode mode) {
    _period = (ns * _tick_factor) / 1000;
    _mode   = mode;
}

uint32_t timer_rp2040::getPeriod() {
    return _period / _tick_factor;
}

void timer_rp2040::setCallback(function<void()> f) {
    timer_rp2040::_callback[_index] = f;
}

void timer_rp2040::start() {
    *_ALARM = _TIMER_::TIMER.TIMERAWL + _period;
}

void timer_rp2040::stop() {
    if (isRunning()) {
        // Clear 'armed'-bit
        _TIMER_::TIMER.ARMED = _mask;
    }
}

bool timer_rp2040::isRunning() {
    return _TIMER_::TIMER.ARMED & _mask;
}

void timer_rp2040::reset() {
    // If timer is running, immediately
    // trigger a re-start.
    if (isRunning()) start();
}

void timer_rp2040::irqHandler() {
    // Clear interrupt
    _TIMER_::TIMER.INTR = _mask;
    // Re-trigger timer if periodic
    if (_mode == TIMER::PERIODIC) {
        *_ALARM += _period;
    }
    // Call the user-provided handler
    _callback[_index]();
}

// Interrupt handler
////////////////////
extern "C" {

void TIMER_IRQ_0_Handler(void) {
    timer_rp2040::_timerinst[0]->irqHandler();
}

void TIMER_IRQ_1_Handler(void) {
    timer_rp2040::_timerinst[1]->irqHandler();
}

void TIMER_IRQ_2_Handler(void) {
    timer_rp2040::_timerinst[2]->irqHandler();
}

void TIMER_IRQ_3_Handler(void) {
    timer_rp2040::_timerinst[3]->irqHandler();
}

} // extern "C"
