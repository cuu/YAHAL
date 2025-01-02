// ---------------------------------------------
//           This file is part of
//      _  _   __    _   _    __    __
//     ( \/ ) /__\  ( )_( )  /__\  (  )
//      \  / /(__)\  ) _ (  /(__)\  )(__
//      (__)(__)(__)(_) (_)(__)(__)(____)
//
//     Yet Another HW Abstraction Library
//      Copyright (C) Andreas Terstegge
//      BSD Licensed (see file LICENSE)
//
// ---------------------------------------------
//
// Timer implementation for RP2350.
//
#include "timer_rp2350.h"
#include "system_rp2350.h"
#include <cassert>

using namespace _TIMER1_;
using namespace _RESETS_;

timer_rp2350 *   timer_rp2350::_timerinst[8];
function<void()> timer_rp2350::_callback[8];

timer_rp2350::timer_rp2350(int8_t index) {
    // Locate a free slot if no index was given
    if (index == -1) {
        // Find next free timer
        for (index=0; index < 7; ++index) {
            if (!_timerinst[index]) break;
        }
    }
    assert(index < 8);
    assert(_timerinst[index] == nullptr);

    // Initialize members
    _index      = index;
    _mask       = 1 << (index % 4);
    _mode       = TIMER::ONE_SHOT;
    _period     = 0;

    // Set the timer pointer and enable IRQs
    if (index < 4) {
        _timer = &TIMER0;
        _alarm = &(TIMER0.ALARM[index]);
        TIMER0_SET.INTE = _mask;
    } else {
        _timer = &TIMER1;
        _alarm = &(TIMER1.ALARM[index-4]);
        TIMER1_SET.INTE = _mask;
    }
    // Register timer instance pointer
    _timerinst[index] = this;
    // enable IRQ in NVIC. Default priority is 0 (highest).
    NVIC_EnableIRQ(IRQn_Type(TIMER0_IRQ_0_IRQn + index));
}

timer_rp2350::~timer_rp2350() {
    if (_timer->ARMED & _mask) {
        _timer->ARMED = _mask;
    }
    _timerinst[_index] = nullptr;
}

void timer_rp2350::setPeriod(uint32_t us, TIMER::timer_mode mode) {
    _period = us * timer_ticks_per_us;
    _mode   = mode;
}

void timer_rp2350::setPeriod_ns(uint32_t ns, TIMER::timer_mode mode) {
    _period = (ns * timer_ticks_per_us) / 1000;
    _mode   = mode;
}

uint32_t timer_rp2350::getPeriod() {
    return _period / timer_ticks_per_us;
}

void timer_rp2350::setCallback(function<void()> f) {
    timer_rp2350::_callback[_index] = f;
}

void timer_rp2350::start() {
    *_alarm = _timer->TIMERAWL + _period;
}

void timer_rp2350::stop() {
    if (isRunning()) {
        // Clear 'armed'-bit
        _timer->ARMED = _mask;
    }
}

bool timer_rp2350::isRunning() {
    return _timer->ARMED & _mask;
}

void timer_rp2350::reset() {
    // If timer is running, immediately
    // trigger a re-start.
    if (isRunning()) start();
}

void timer_rp2350::irqHandler() {
    // Clear interrupt
    _timer->INTR = _mask;
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

void TIMER1_IRQ_0_Handler(void) {
    timer_rp2350::_timerinst[4]->irqHandler();
}

void TIMER1_IRQ_1_Handler(void) {
    timer_rp2350::_timerinst[5]->irqHandler();
}

void TIMER1_IRQ_2_Handler(void) {
    timer_rp2350::_timerinst[6]->irqHandler();
}

void TIMER1_IRQ_3_Handler(void) {
    timer_rp2350::_timerinst[7]->irqHandler();
}

} // extern "C"
