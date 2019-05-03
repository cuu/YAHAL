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
// A simple example demonstrating the use of Timer A.
// The joystick is used to control the brightness of
// the green and blue LED on the EDU-MKII. This is
// done by using the TIMER_A modules, which can e.g.
// control a gpio pin with a PWM signal.

#include "adc14_msp432.h"
#include "gpio_msp432.h"
#include "msp.h" // Needed for TIMER_A stuff

int main(void)
{
    // We do not really use the gpio pins here, but use
    // them to switch the SEL mode with the setSEL() method,
    // which is easier compared to programming the SEL-registers
    // directly. For Timer A operation, SEL1=0 and SEL0=1, which
    // translates to mode 1 in the setSEL() method.
    // Additionally we have to enable the output driver by setting
    // the gpio mode to OUTPUT.
    gpio_msp432_pin green( PORT_PIN(2,4) );
    gpio_msp432_pin blue ( PORT_PIN(5,6) );
    green.gpioMode(GPIO::OUTPUT);
    blue. gpioMode(GPIO::OUTPUT);
    green.setSEL(1);
    blue. setSEL(1);

    // P2.4 (green LED) is now driven by TA0.1 (TIMER_A0, CCR 1)
    // P5.6 (blue LED)  is now driven by TA2.1 (TIMER_A2, CCR 1)
    // Configure TIMER_A0 and TIMER_A2 to use SMCLK as clock
    // source and UP mode. The macros like TIMER_A_CTL_SSEL__SMCLK
    // can be found in the msp432p401r.h file (click right on a macro
    // and select 'Open Declaration'). They make the code more
    // readable.
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP;
    TIMER_A2->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP;

    // Configure the CCR registers TA0.1 and TA2.1 to use output
    // mode 7 (Reset/Set), which will result in a PWM pulse which
    // has a length proportional to the related CCR register.
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A2->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;

    // Configure the frequency of the PWM signals. With 3 MHz,
    // 16384 cycles result in a total PWM cycle time of 5,461ms
    TIMER_A0->CCR[0] = 16384;
    TIMER_A2->CCR[0] = 16384;

    // The registers TIMER_A0->CCR[1] and TIMER_A2->CCR[1] control
    // the width of the PWM pulses. When a CCR register is 0, the
    // PWM pulses also have a length of 0. When a CCR register is
    // 16384 (the same value as in CCR[0]), the pulses have a length
    // of 5,461ms, so the PWM signal will never be LOW.
    // We use ADC14 to control these two CCR values:

    adc14_msp432_channel joy_X(15);
    adc14_msp432_channel joy_Y(9);
    // The ADC will generate raw signals with 14 bits resolution
    // (0...16383 raw-value range)
    joy_X.adcMode(ADC::ADC_14_BIT);
    joy_Y.adcMode(ADC::ADC_14_BIT);

    while(1) {
        // Green LED is controlled by X axis
        TIMER_A0->CCR[1] = joy_X.adcReadRaw();
        // Blue LED is controlled by Y axis
        TIMER_A2->CCR[1] = joy_Y.adcReadRaw();
    }
}

