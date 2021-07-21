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
// A simple blink example using a 16-bit timer
// (the msp432 CPU contains 4 TIMER_A units,
//  TIMER_A0 to TIMER_A3).
//
// Note that the 16-bit Timers have a restricted
// period time: The maximum clock divider for those
// timers is 8*8=64. So if your CPU clock is 3MHz,
// the timers will be clocked with 3MHz/64, resulting
// in a MAXIMUM period time of 1,39s. But if the
// CPU clock is 48MHz, the maximum period is only
// 87,38ms!
// The necessary clock dividers will be automatically
// calculated by this driver!
//
// This example shows 2 applications of the timer:
// One timer uses the callback method to toggle the
// LED. The other timer is used to implement a delay-
// method, which can be used in the user application.

#include "gpio_msp432.h"
#include "timerA_msp432.h"

void delay(int us) {
    // Setup the second time in ONE_SHOT mode
    // and simply wait until the callback
    // method has changed the 'expired' variable.
    // The interrupt handler is realized as a
    // lambda expression, which can access this
    // variable (capture [&]).
    bool expired = false;
    timerA_msp432 timer1(TIMER_A1);
    timer1.setPeriod(us, TIMER::ONE_SHOT);
    timer1.setCallback([&]() { expired = true; });
    timer1.start();
    // Now (actively) wait until the callback
    // method has changed the 'expired' variable...
    while(!expired) ;
}

int main(void)
{
    // Setup two LEDs on the launchpad for blinking
    gpio_msp432_pin led1( PORT_PIN(1,0) ); // Left red LED
    gpio_msp432_pin led2( PORT_PIN(2,0) ); // red RGB LED
    led1.gpioMode( GPIO::OUTPUT );
    led2.gpioMode( GPIO::OUTPUT );

    // Setup the first timer with a timeout of 500ms
    // in periodic mode
    timerA_msp432 timer0;
    timer0.setPeriod(500000, TIMER::PERIODIC);
    // Set the callback method to toggle the LED
    timer0.setCallback([&]() { led1.gpioToggle(); });
    timer0.start();

    // The second timer is used within the
    // delay-method, which is now very precise
    // and has a high resolution (1 microsecond).
    //
    // After observing the 2 blinking LEDs you
    // will notice, that the second LED (on the
    // right, code below) will blink a _little_
    // bit slower, because calling the toggle()
    // method and calling delay() adds some small
    // time to the 500ms. Since the first LED is
    // running in PERIODC mode, the interval is
    // exactly 500ms!
    while(true) {
        delay(500000);      // wait 500ms
        led2.gpioToggle();  // toggle the LED
    }
}
