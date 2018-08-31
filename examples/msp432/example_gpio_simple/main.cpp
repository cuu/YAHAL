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
// This program is a small example for gpio usage.
// It uses the two buttons S1 and S2 on the launchpad
// to switch on a red and blue LED on the launchpad.

#include "gpio_msp432.h"

#define LED_RED   PORT_PIN(1, 0)  // left  red LED
#define LED_BLUE  PORT_PIN(2, 2)  // right blue LED
#define SWITCH1   PORT_PIN(1, 1)  // left  S1 button
#define SWITCH2   PORT_PIN(1, 4)  // right S2 button

int main()
{
    // GPIO pins with LEDs
    gpio_msp432_pin red_led (LED_RED);
    gpio_msp432_pin blue_led(LED_BLUE);

    // GPIO pins with buttons
    gpio_msp432_pin s1(SWITCH1); // left button
    gpio_msp432_pin s2(SWITCH2); // right button

    // Setup GPIO modes. The PULLUP mode is necessary
    // because there are no external pullup resistors
    // on the launchpad
    red_led. gpioMode(GPIO::OUTPUT);
    blue_led.gpioMode(GPIO::OUTPUT);
    s1.gpioMode(GPIO::INPUT | GPIO::PULLUP);
    s2.gpioMode(GPIO::INPUT | GPIO::PULLUP);

    while(true) {
        red_led.gpioWrite ( ! s1.gpioRead() );
        blue_led.gpioWrite( ! s2.gpioRead() );
    }
}
