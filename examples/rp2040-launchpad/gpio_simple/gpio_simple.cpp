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

#include "gpio_rp2040.h"

#define LED_RED   2  // left  red LED
#define LED_BLUE  3  // right blue LED
#define SWITCH1   16 // left  S1 button
#define SWITCH2   17 // right S2 button

int main()
{
    // GPIO pins with LEDs
    gpio_rp2040_pin red_led (LED_RED);
    gpio_rp2040_pin blue_led(LED_BLUE);

    // GPIO pins with buttons
    gpio_rp2040_pin s1(SWITCH1); // left button
    gpio_rp2040_pin s2(SWITCH2); // right button

    // Setup GPIO modes. The PULLUP mode is necessary
    // because there are no external pullup resistors
    // on the launchpad
    red_led. gpioMode(GPIO::OUTPUT);
    blue_led.gpioMode(GPIO::OUTPUT);
    s1.gpioMode(GPIO::INPUT | GPIO::PULLUP);
    s2.gpioMode(GPIO::INPUT | GPIO::PULLUP);

    while(true) {
        // Set the red and blue LEDs to the
        // inverted values of button s1 and s2
        // using the YAHAL gpio methods:
        red_led.gpioWrite ( ! s1.gpioRead() );
        blue_led.gpioWrite( ! s2.gpioRead() );

        // Same as above, but using
        // (syntactic sugar) C++ operators:
        red_led  = !s1;
        blue_led = !s2;
    }
}
