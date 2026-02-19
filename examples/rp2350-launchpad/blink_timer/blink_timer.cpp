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
// A simple blink example using two of the eight
// 64-bit timers on the RP2350, which can be used
// to measure time or to run some code in specified
// intervals. The timers have a resolution of one
// microsecond!
// The timers operate in a ONE_SHOT or PERIODIC
// mode (see timer_interface.h). In ONE_SHOT mode,
// the timer is stopped after the time has expired,
// and calls the callback method. In PERIODIC mode,
// the timer is automatically reloaded so that the
// callback method is called in constant intervals
// until someone calls stop() on the timer instance.
//
// This example shows 2 applications of the timer:
// One timer uses the callback method to toggle the
// LED. The other timer is used to implement a delay-
// method, which can be used in the user application.

#include "board.h"
#include "ws2812_rp2350.h"
#include "timer_rp2350.h"
#include "RP2350.h"

// A microsecond delay method based on a timer.
// The timer_rp2350 constructor takes one integer
// argument in the range of 0..7 to select one
// specific timer. When there is no parameter,
// the next available timer is used!
void delay(int us) {
    // Set up the second time in ONE_SHOT mode
    // and simply wait until the callback
    // method has changed the 'expired' variable.
    // The interrupt handler is realized as a
    // lambda expression, which can access this
    // variable (capture [&]).
    bool expired = false;
    timer_rp2350 timer1(1);
    timer1.setPeriod(us, TIMER::ONE_SHOT);
    timer1.setCallback([&]() { expired = true; });
    timer1.start();
    // Now (actively) wait until the callback
    // method has changed the 'expired' variable...
    while(!expired) ;
}

int main()
{
    // Setup two LEDs on the launchpad for blinking
    ws2812_rp2350 leds(LED_RGB_GPIO, LED_RGB_COUNT);
    leds[0].set_on_color(0x200000); // red
    leds[1].set_on_color(0x000040); // blue

    // Set up the first timer with a timeout of 500ms
    // in periodic mode. This will let the red LED
    // blink with a delay of _exactly_ 500 ms!
    timer_rp2350 timer0(0);
    timer0.setPeriod(500000, TIMER::PERIODIC);
    // Set the callback method to toggle the LED
    timer0.setCallback([&]() { leds[0].toggle(); });
    timer0.start();

    // After observing the 2 blinking LEDs for a
    // longer time, you will notice, that the blue
    // LED (see code below) will blink a _little_
    // bit slower, because calling the toggle()
    // method and calling delay() adds some extra
    // time to the 500ms. Since the first (red) LED
    // is running in PERIODIC mode, the blink interval
    // is _exactly_ 500ms!
    while(true) {
        __WFE();
        delay(500000);      // wait 500ms
        leds[1].toggle();   // toggle the blue LED
    }
}
