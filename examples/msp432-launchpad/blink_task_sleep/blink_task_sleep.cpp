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
// A task can be defined in two different ways:
//
// 1.) You specify the code to run as the first
//     parameter (a std::function) in the task constructor.
//     The second and third parameters are the task name
//     and the optional stack size in bytes.
//
// 2.) You can derive from class task and implement
//     the task code in the virtual method void run().
//     The (base class) constructor of task has to be
//     called with the task name as the first parameter
//     and the optional stack size as the second parameter.
//
// When the task code ends, the task is automatically
// removed from the list of active tasks and deleted.
// The class 'task' also provides functions like sleep_ms()
// to delay the execution (parameter is the delay time
// in milliseconds). See file task.h for more details.
// This program also redirects stdout to the backchannel
// UART and start a task monitor, so task statistics
// can be seen on the terminal.

#include "gpio_msp432.h"
#include "uart_msp432.h"
#include "posix_io.h"
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

    // The base class 'task' has to be called with
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
            sleep_ms( _delay );
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
    posix_io::inst.register_stdout(uart);

    // Instantiate the tasks to blink the red LED.
    // The class is derived from task.
    blink_task t1("red blinker", RED_LED, 500 );

    // Instantiate the tasks to blink the green LED.
    // Here the code is provided as the first parameter
    // (in this case a lambda expression) to task.
    // The GPIO is defined outside of task to
    // demonstrate the capture of external variables.
    gpio_msp432_pin led( PORT_PIN(2,1) );
    led.gpioMode( GPIO::OUTPUT );

    task t2([&]() {
        // Endless loop
        while(true) {
            led.gpioToggle();
            task::sleep_ms(500);
        }
    }, "green blinker");

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
