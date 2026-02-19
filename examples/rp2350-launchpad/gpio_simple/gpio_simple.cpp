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
// to switch on a red LED and the RGB LEDs on the launchpad.
//
#include "board.h"
#include "gpio_rp2350.h"
#include "ws2812_rp2350.h"

int main()
{
    // GPIO pins with LEDs
    gpio_rp2350 red_led(LED_RED_GPIO);

    // RGB LED
    ws2812_rp2350 rgb_leds(LED_RGB_GPIO, LED_RGB_COUNT);
    rgb_leds[0].set_on_color(0x100000);
    rgb_leds[1].set_on_color(0x001000);
    rgb_leds[2].set_on_color(0x000020);

    // GPIO pins with buttons
    gpio_rp2350 s1(S1_GPIO);    // left button
    gpio_rp2350 s2(S2_GPIO);    // right button

    // Setup GPIO modes. The PULLUP mode is necessary
    // because there are NO external pullup resistors
    // on the launchpad. S1 is automatically inverted,
    // S2 not.
    red_led.gpioMode(GPIO::OUTPUT);
    s1.gpioMode(GPIO::INPUT_INVERT | GPIO::PULLUP);
    s2.gpioMode(GPIO::INPUT        | GPIO::PULLUP);

    while(true) {
        // Switch on the red LED if S1 is pressed.
        // The switch is HIGH when NOT pressed, but the
        // value is INVERTED (see above).
        // Due to operator overloading, the gpio_rp2350 object
        // can be used as a boolean expression (calling the
        // gpioRead() method internally). So an alternative is:
        // red_led = s1;
        red_led.gpioWrite ( s1.gpioRead() );

        // Use the RGB LEDs to show some logical functions.
        // s1 and s2 are used as boolean expressions, calling
        // gpioRead() internally. In the last code line the
        // cast to bool is important, because there is also
        // an assignment operator for int values (RGB).
        rgb_leds[0] = s1 || !s2;
        rgb_leds[1] = s1 && !s2;
        rgb_leds[2] = (bool)(s1 ^  !s2);
    }
}
