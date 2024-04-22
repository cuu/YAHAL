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
// A simple blink example using the red LED on
// GPIO 13. The first delay is implemented with
// task:sleep_ms(uint32_t ms), which pauses the
// execution by the given number of milliseconds.
// The second delay uses the method task::millis(),
// which returns the number of milliseconds since
// the start of the system.

#include "gpio_rp2040.h"
#include "task.h"

// Build-in red LED on rp2040-launchpad
#define RED_LED 13

int main()
{
    // Use GPIO 13 (buildin LED) as output
    gpio_rp2040_pin led( RED_LED );
    led.gpioMode( GPIO::OUTPUT );

    // This loop will never end ...
    while(true) {
        // switch on the LED
        led = HIGH;
        // Delay with the sleep() method
        task::sleep_ms(500);
        // switch off the LED
        led = LOW;
        // Delay by using the millis() method
        uint64_t until = task::millis() + 500;
        while (task::millis() < until) ;
    }
}
