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
// Port 1 pin 0 and the green LED on Port 2 pin 1.
// This program uses the multitasking kernel of YAHAL.
// A task can be defined by deriving a class from
// class 'task'. This class has an abstract method
// run(), which will contain the code to execute.
// So the derived class has to implement run().
// When run() ends, the task is removed from the
// scheduling process.
// The base class task_msp432 also provides functions
// like sleep() to delay the execution (parameter is
// the delay time in milliseconds).
// This program also redirects stdout to the backchannel
// UART and start a task monitor, so task statistics
// can be seen on the terminal.

#include "gpio_msp432.h"
#include "uart_msp432.h"
#include "std_io.h"
#include "task.h"
#include "task_monitor.h"

// Use macros to define the ports
// and pins of the LEDs to use
#define RED_LED   PORT_PIN(1,0)
#define GREEN_LED PORT_PIN(2,1)

// This class defines a new task class. The task
// code in run() only toggles a gpio with a delay
// in between. The name of the task, the specific
// gpio and the amount of delay in milliseconds
// are passed as parameters to the constructor.
class blink_task : public task {
public:

    // The base class task_msp432 has to be called with
    // the name of the task, and optionally (as the second
    // parameter) the stack size of the task.
    blink_task(const char * name, gpio_pin_t gpio, int delay)
    : task(name), _delay(delay) {
        // Initialize the gpio as output
        _led.setGpio ( gpio );
        _led.gpioMode( GPIO::OUTPUT );
    }

    // This is the task code, which is
    // run by the multitasking kernel
    void run() override {
        // Endless loop
        while(1) {
            _led.gpioToggle();
            sleep( _delay );
        }
    }

private:
    gpio_msp432_pin _led;
    int             _delay;
};


int main(void)
{
    // Redirect stdout to our backchannel UART,
    // so we can see the output of the task monitor
    uart_msp432 uart;
    std_io::inst.redirect_stdout(uart);

    // Instantiate two tasks with two
    // different delays (500ms and 300ms).
    blink_task t1("red blinker",   RED_LED,   500 );
    blink_task t2("green blinker", GREEN_LED, 300 );

    // Start both tasks. This means that
    // the tasks are put into a circular
    // list for scheduling and marked as
    // 'ready' to run. But the kernel is
    // not yet started, so no task code
    // is run after the two next lines!
    t1.start();
    t2.start();

    // Start the task monitor. When a terminal
    // is connected to /dev/ttyACM0, then the
    // task status can be seen!
    task_monitor monitor;
    monitor.start();

    // Start the multitasking kernel.
    // This call is blocking (it will
    // never return ...).
    task::start_scheduler();
}
