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
// Small example to demonstrate running code on
// core 1 of the RP2350 MCU. The code on core 1
// is blinking the red LED on the RP2350 Launchpad,
// the code on core 0 is blinking one WS2812 RGB
// LED.
//
#include "board.h"
#include "gpio_rp2350.h"
#include "multicore_rp2350.h"
#include "task.h"
#include "ws2812_rp2350.h"

void core1_code() {
    gpio_rp2350 led( LED_RED_GPIO );
    led.gpioMode( GPIO::OUTPUT );
    while(true) {
        led.gpioToggle();
        task::sleep_ms(500);
    }
}

int main()
{
    multicore_rp2350::reset_core1();
    multicore_rp2350::start_on_core1( core1_code );

    ws2812_rp2350 leds(LED_RGB_GPIO, LED_RGB_COUNT);
    // This loop will never end ...
    while(true) {
        // switch on the LED
        leds[0].toggle();
        // Delay with the sleep() method
        task::sleep_ms(500);
        // switch off the LED
    }
}
