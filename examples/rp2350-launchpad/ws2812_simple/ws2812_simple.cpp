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
// A small example showing the usage of the WS2812
// RGB LEDs on the RP2350 Launchpad.

#include "ws2812_rp2350.h"
#include "board.h"
#include "task.h"

int main() {
    // Create the WS2812 object
    ws2812_rp2350 leds(LED_RGB_GPIO, LED_RGB_COUNT);
    // Set the LED colors when they are used as
    // normal 'binary' LEDs (only on/off).
    // The parameter is a 24-bit RGB values,
    // so 2 hex digits per color red/green/blue.
    // Default is a dark red (used here by leds[0]).
    leds[1].set_on_color(0x000800);  // dark green
    leds[2].set_on_color(0x000020);  // dark blue

    // LEDs can be set with boolean values
    leds[0] = HIGH;
    leds[1] = LOW;
    leds[2] = HIGH;

    // An RGB-LED can also be directly set with its RGB Value:
    leds[3] = 0x101010; // white

    // Endless loop toggling the first 3 LEDs
    while (true) {
        leds[0].toggle();
        leds[1].toggle();
        leds[2].toggle();
        task::sleep_ms(500);
    }
}



