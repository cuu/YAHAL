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

#define LED_RED   13  // left  red LED
#define SWITCH1   16 // left  S1 button
#define SWITCH2   17 // right S2 button

int main()
{
    // GPIO pins with LEDs
    gpio_rp2040_pin red_led (LED_RED);

    // GPIO pins with buttons
    gpio_rp2040_pin s1(SWITCH1); // left button
    gpio_rp2040_pin s2(SWITCH2); // left button

    // Setup GPIO modes. The PULLUP mode is necessary
    // because there are NO external pullup resistors
    // on the launchpad. S1 is automatically inverted,
    // S2 not.
    red_led. gpioMode(GPIO::OUTPUT);
    s1.gpioMode(GPIO::INPUT_INVERT | GPIO::PULLUP);
    s2.gpioMode(GPIO::INPUT        | GPIO::PULLUP);

    while(true) {
        // Switch on the red LED if either S1 or S2 is pressed.
        // Due to operator overloading, the gpio_rp2040_pin object
        // can be used as a boolean expression (and calls the gpioRead()
        // method internally).
        red_led.gpioWrite ( s1.gpioRead() || !s2 );

        // Same as above, but using the object to assign a boolean value
        // (and call the gpioWrite() method internally)
        red_led  = s1 || !s2;
    }
}
