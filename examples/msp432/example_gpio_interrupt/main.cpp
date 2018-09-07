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
// This program is a small example for gpio interrupts.
// It uses the two buttons S1 and S2 on the launchpad
// to toggle two red LEDs from a interrupt handler.
// The main functions is in a endless loop, doing
// nothing (see below).

#include "gpio_msp432.h"

#define LED_RED1    PORT_PIN(1, 0)  // left  red LED
#define LED_RED2    PORT_PIN(2, 0)  // right red RGB LED
#define BUTTON1     PORT_PIN(1, 1)  // left  S1 button
#define BUTTON2     PORT_PIN(1, 4)  // right S2 button

void gpio_handler(gpio_pin_t gpio, void *) {
    if (gpio == BUTTON1) {
        // Here we use the gpio_msp432 singleton to
        // access the LEDs, because we did not want the
        // gpio_msp432_pin-instances to be global.
        gpio_msp432::inst.gpioToggle(LED_RED1);
    } else
    if (gpio == BUTTON2) {
        gpio_msp432::inst.gpioToggle(LED_RED2);
    }
}

int main()
{
    // GPIO pins with LEDs
    gpio_msp432_pin red_led1 (LED_RED1);
    gpio_msp432_pin red_led2 (LED_RED2);

    // GPIO pins with buttons
    gpio_msp432_pin button_S1(BUTTON1); // left button
    gpio_msp432_pin button_S2(BUTTON2); // right button

    // Setup GPIO modes
    red_led1. gpioMode(GPIO::OUTPUT);
    red_led2. gpioMode(GPIO::OUTPUT);
    button_S1.gpioMode(GPIO::INPUT | GPIO::PULLUP);
    button_S2.gpioMode(GPIO::INPUT | GPIO::PULLUP);

    // Attach a IRQ handler to every button. Both buttons
    // could have a different handler, but in this case
    // they are using the same handler, which can find
    // out the interrupt source by looking at the 'gpio'
    // parameter, which is passed to the interrupt handler
    // (see above).
    //
    // The left  LED will change its status when S1 is _pressed_!
    // (pressing the button sets the gpio to LOW, so this is
    // a falling edge!)
    // The right LED will change its status when S2 is _released_!
    button_S1.gpioAttachIrq(GPIO::FALLING, gpio_handler);
    button_S2.gpioAttachIrq(GPIO::RISING,  gpio_handler);

    // Endless loop, which is only 'interrupted' by
    // our HW-interrupts.
    while(true) ;
}
