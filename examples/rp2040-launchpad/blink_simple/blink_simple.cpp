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
// GPIO 13. The delays are implemented with
// task:sleep(uint32_t ms), which pauses the
// execution by the given number of milliseconds.
// In a non-multitasking environment (as in this
// example), the sysTick-Timer is used internally
// for sleep(), resulting in a precise delay. 

#include "gpio_rp2040.h"
#include "task.h"

// Build-in red LED on rp2040-launchpad
#define RED_LED 13

int main(void)
{
    // Use GPIO 13 (buildin LED) as output
    gpio_rp2040_pin led( RED_LED );
    led.gpioMode( GPIO::OUTPUT );

    // This loop will never end ...
    while(1) {
        // switch on the LED
        led = HIGH;
        task::sleep(500);
        // switch off the LED
        led = LOW;
        task::sleep(500);
    }
}
