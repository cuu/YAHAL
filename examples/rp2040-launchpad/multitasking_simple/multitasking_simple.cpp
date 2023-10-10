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
// This is an example program for a very simple
// multitasking kernel. Two methods are defined
// to blink a red and blue LED with different
// frequencies. Both methods are added as tasks
// to the mini-OS, and the scheduler is started.
//
// The purpose of this project is to demonstrate
// and teach multitasking. If you want to use
// a more complete and fully featured multitasking
// kernel, use YAHAL's task class.

#include "ws2812_rp2040.h"
#include "OS.h"

#define WS2812_PIN 29

ws2812_rp2040 leds(WS2812_PIN, 8);
led_rgb_interface & led_red  = leds[0];
led_rgb_interface & led_blue = leds[1];

// Simple delay function. It is not very
// precise and depends on the CPU clock
// and compiler optimizations.
void delay(int ms) {
    for(int i=0; i < 3167 * ms; ++i) ;
}

// simple first task: Blink red LED
void task1(void) {
    while(true) {
        delay(500);
        led_red.toggle();
    }
}

// simple second task: Blink blue LED
void task2(void) {
    while(true) {
        delay(300);
        led_blue.toggle();
    }
}

int main(void)
{
    // Set LED colors
    led_red.set_on_color (0x040000);
    led_blue.set_on_color(0x000010);
    
    // Add two tasks to our mini-OS
    OS_add_task(task1);
    OS_add_task(task2);

    // Start the scheduler. This method will never return...
    OS_start_scheduler();
}

