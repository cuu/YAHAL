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

#include <audio_output.h>

audio_output * audio_output::_this = nullptr;

// The audio output uses the buzzer GPIO (P2.7), which
// is operated by the Timer TA0.4. The idea is the
// following: The Timer generates a high-frequency
// PWM signal (in this case the frequency is 44100Hz).
// According to the Nyquist Theorm, we can produce
// audio frequencies with a maximum frequency of 22050Hz.
// This is already HiFi quality! The PWM duty cycle
// varies around 50% with the frequencies which should
// be generated.
// A single sample lasts 1/44100Hz = 22,67us.
// The Timer A is operated with 24MHz, so it counts up
// to a value of 22,67us * 24000000Hz = 544.
// So the PWM signal can have a resolution of 9 bits
// (values from 0...511).

audio_output::audio_output() :
    _buzz(PORT_PIN(2,7)),
    _pcm_fifo (PCM_FIFO_SIZE)
{
    // Set up buzzer GPIO (Output, and driven by TA0.4)
    _buzz.gpioMode(GPIO::OUTPUT);
    _buzz.setSEL(1);
    TIMER_A0->CTL     = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP;
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE;
    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[0]  = SubsystemMasterClock / 44100;
    TIMER_A0->CCR[4]  = SubsystemMasterClock / 44100 / 2;
    NVIC_EnableIRQ(TA0_0_IRQn);
    _this = this;
}

extern "C" {
    void TA0_0_IRQHandler()
    {
        // Reset the CCR0 IRQ flag
        TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;

        if (audio_output::_this) {
            audio_output * _this = audio_output::_this;
            if (_this->_pcm_fifo.get(_this->_pcm_value)) {
                // The PCM values have a resolution of 14 bits.
                // We have to scale them down to 9 bits, so we
                // shift them accordingly!
                TIMER_A0->CCR[4] = _this->_pcm_value >> 5;
            }
        }
    }
}
