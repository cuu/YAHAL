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
//
#include "board.h"
#include "gpio_rp2350.h"
#include "ws2812_rp2350.h"
#include "RP2350.h"

int main()
{
    // Set up the LEDs
    ws2812_rp2350 leds(LED_RGB_GPIO, LED_RGB_COUNT);
    leds[0].set_on_color(0x080000);	// left  LED is red
    leds[7].set_on_color(0x000600);	// right LED is green

    // GPIO pins with buttons
    gpio_rp2350 button_S1(S1_GPIO); // left button
    gpio_rp2350 button_S2(S2_GPIO); // right button

    // Setup GPIO modes
    button_S1.gpioMode(GPIO::INPUT | GPIO::PULLUP);
    button_S2.gpioMode(GPIO::INPUT | GPIO::PULLUP);

    // Attach a IRQ handler to every button. Both handlers
    // are lambda expressions in this case. The parameter
    // is a std::function<void()>, so the handler can also
    // be a functor or a simple C function...
    //
    // The left  LED will change its status when S1 is _pressed_!
    // (pressing the button sets the gpio to LOW, so this is
    // a falling edge!)
    // The right LED will change its status when S2 is _released_!
    button_S1.gpioAttachIrq(GPIO::FALLING, [&]() {
        leds[0].toggle();
    });
    button_S2.gpioAttachIrq(GPIO::RISING, [&]() {
        leds[7].toggle();
    });

    // Endless loop, which is only 'interrupted' by
    // our HW-interrupts. __WFE() maps to an assembly
    // command waiting for an 'event', e.g. an interrupt.
    // The CPU will enter a sleep state (power save state)
    // in the meantime! So the loop is not running all the
    // time.
    while(true) __WFE();
}
