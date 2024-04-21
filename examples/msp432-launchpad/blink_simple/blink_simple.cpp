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
// Port 1 pin 0. The delay is implemented with
// a simple for-loop.

#include "gpio_msp432.h"
#include "task.h"

int main(void)
{
    // Use P1.0 as output
    gpio_msp432_pin led( PORT_PIN(1,0) );
    led.gpioMode( GPIO::OUTPUT );

    // This loop will never end ...
    while(1) {
        // switch on the LED
        led = HIGH;
        // Simple delay using an empty loop.
        // This will only work if the compiler does
        // not optimize away this code ...
        for(int i=0; i < 100000; ++i) ;
        // switch off the LED
        led = LOW;
        // Delay using the non-multitasking version
        // of sleep. This delay uses the SysTick timer,
        // and is independent from the CPU clock
        // frequency and compiler optimizations!
        task::sleep_ms(500);
    }
}
