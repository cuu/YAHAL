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
// A simple blink example using both cores
// of the RP2350 MCU.
//
#include "board.h"
#include "gpio_rp2350.h"
#include "multicore_rp2350.h"
#include "task.h"
#include "task_monitor.h"
#include "ws2812_rp2350.h"

int main() {

    // Start work on core 1
    multicore_rp2350::reset_core1();
    multicore_rp2350::start_on_core1([]() {
        gpio_rp2350 led(LED_RED_GPIO);
        led.gpioMode(GPIO::OUTPUT);
        while (true) {
            led.gpioToggle();
            task::sleep_ms(500);
        }
    });

    // Start work on core 0
    ws2812_rp2350 leds(LED_RGB_GPIO, LED_RGB_COUNT);
    while (true) {
        leds[0].toggle();
        task::sleep_ms(500);
    }

}
