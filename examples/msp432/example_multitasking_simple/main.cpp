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

#include "gpio_msp432.h"
#include "OS.h"

// Simple delay function
void delay(int ms) {
    for(int i=0; i < 1600 * ms; ++i) ;
}

// simple first task: Blink red LED
void task1(void) {
    gpio_msp432_pin red_led(PORT_PIN(1,0));
    red_led.gpioMode(GPIO::OUTPUT);
    while(true) {
        delay(500);
        red_led.gpioToggle();
    }
}

// simple second task: Blink blue LED
void task2(void) {
    gpio_msp432_pin blue_led(PORT_PIN(2,2));
    blue_led.gpioMode(GPIO::OUTPUT);
    while(true) {
        delay(300);
        blue_led.gpioToggle();
    }
}


int main(void)
{
    // Add two tasks to our mini-OS
    OS_add_task(task1);
    OS_add_task(task2);

    // Start the scheduler. This method will never return...
    OS_start_scheduler();
}

