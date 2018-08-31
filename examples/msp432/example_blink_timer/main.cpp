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
// A simple blink example using a 32-bit timer.
// The msp432 CPU contains 2 high-resolution
// 32-bit timer, which can be used to measure
// time or to run some code in specified intervals.
// The timers have a resolution of 1 microsecond!
// The timers operate in a ONE_SHOT or PERIODIC
// mode (see timer_interface.h). In ONE_SHOT mode,
// the timer is stopped after the time has expired,
// and calls the callback method. In PERIODIC mode,
// the timer is automatically reloaded to that the
// callback method is called until someone calls
// stop() on the timer instance.
//
// This example shows 2 applications of the timer:
// One timer uses the callback method to toggle the
// LED. The other timer is used to implement a delay-
// method, which can be called in the user program.

#include "gpio_msp432.h"
#include "timer_msp432.h"

void callback1(void * arg) {
    // Convert the argument to a gpio pointer
    gpio_msp432_pin * gpio = static_cast<gpio_msp432_pin *>(arg);
    // toggle the LED
    gpio->gpioToggle();
}

void callback2(void * arg) {
    (*static_cast<bool *>(arg)) = true;
}

void delay(int us) {
    // Setup the second time in ONE_SHOT mode
    // and simply wait until the callback
    // method has changed the 'expired' variable.
    // The pointer to this variable (which is
    // located on the stack!) is passed as an
    // argument to the callback method, so the
    // callback method can modify this variable
    // (see above).
    bool expired = false;
    timer_msp432 timer2(TIMER32_2);
    timer2.setPeriod(us, TIMER::ONE_SHOT);
    timer2.setCallback(callback2, &expired);
    timer2.start();

    // Now wait until the callback method
    // has changed the 'expired' variable...
    while(!expired) ;
}

int main(void)
{
    // Setup two LEDs on the launchpad for blinking
    gpio_msp432_pin led1( PORT_PIN(1,0) ); // Left red LED
    gpio_msp432_pin led2( PORT_PIN(2,0) ); // red RGB LED
    led1.gpioMode( GPIO::OUTPUT );
    led2.gpioMode( GPIO::OUTPUT );

    // Setup the first timer with a timeout
    // of 500ms. As an example, a pointer to the
    // gpio_pin is passed as the callback argument.
    // When a timer is e.g. used within a class, the
    // this-pointer could be passed to the callback
    // method, so it can call methods of the class.
    timer_msp432 timer1;
    timer1.setPeriod(500000, TIMER::PERIODIC);
    timer1.setCallback(callback1, &led1);
    timer1.start();

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
