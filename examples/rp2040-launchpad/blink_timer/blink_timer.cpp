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
// A simple blink example using two of the four
// 64-bit timers on the RP2040, which can be used
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

#include "ws2812_rp2040.h"
#include "timer_rp2040.h"

#define WS2812_PIN  29
#define WS2812_COUNT 8

// A microsecond delay method based on a timer.
// The second timer is used here (constructor
// parameter 1, range is 0..3).
void delay(int us) {
    // Set up the second time in ONE_SHOT mode
    // and simply wait until the callback
    // method has changed the 'expired' variable.
    // The interrupt handler is realized as a
    // lambda expression, which can access this
    // variable (capture [&]).
    bool expired = false;
    timer_rp2040 timer1(1);
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
    ws2812_rp2040 leds(WS2812_PIN, WS2812_COUNT);
    led_rgb_interface & led_red = leds[0];
    led_rgb_interface & led_blue = leds[1];
    led_red.set_on_color(0x040000);
    led_blue.set_on_color(0x000010);

    // Set up the first timer with a timeout of 500ms
    // in periodic mode. This will let the red LED
    // blink with a delay of _exactly_ 500 ms!
    timer_rp2040 timer0(0);
    timer0.setPeriod(500000, TIMER::PERIODIC);
    // Set the callback method to toggle the LED
    timer0.setCallback([&]() { led_red.toggle(); });
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
        delay(500000);        // wait 500ms
        led_blue.toggle();    // toggle the blue LED
    }
}
