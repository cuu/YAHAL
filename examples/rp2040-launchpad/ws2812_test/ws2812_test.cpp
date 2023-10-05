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
// A simple blink example using the WS2812 LEDs on
// the RP2040 Launchpad.

#include "ws2812_rp2040.h"
#include "task.h"

#define WS2812_PIN 29
#define LED_COUNT  8

int main(void) {
    // Create the WS2812 object
    ws2812_rp2040 leds(WS2812_PIN, LED_COUNT);
    // Set the LED colors. Values are
    // 24-bit RGB values, so 2 hex digits per color.
    leds[0].set_on_color(0x080000);  // dark read
    leds[1].set_on_color(0x000800);  // dark green
    leds[2].set_on_color(0x000008);  // dark blue

    leds[0] = HIGH;
    leds[1] = LOW;
    leds[2] = HIGH;
    
    while (1) {
        leds[0].toggle();
        leds[1].toggle();
        leds[2].toggle();
        task::sleep(500);
    }
}

