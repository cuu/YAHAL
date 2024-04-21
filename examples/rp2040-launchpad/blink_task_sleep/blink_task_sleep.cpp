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
// A simple blink example using two WS2812 LEDs on
// the rp2040-launchpad.
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

#include "gpio_rp2040.h"
#include "uart_rp2040.h"
#include "ws2812_rp2040.h"
#include "posix_io.h"
#include "task.h"
#include "task_monitor.h"

// WS2812 GPIO mumber
#define WS2812_PIN  29  // GPIO Pin controlling the WS2812 LEDs
#define WS2812_COUNT 8  // Number of WS2812 LEDs

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
    blink_task(const char * name, led_interface & led, int delay)
    : task(name), _led(led), _delay(delay) { }

    // This is the task code, which is
    // run by the multitasking kernel
    void run() override {
        // Endless loop toggling the LED
        while(1) {
            sleep_ms( _delay );
            _led.toggle();
        }
    }

private:
    led_interface & _led;
    int             _delay;
};


int main(void)
{
    // Set up the LEDs
    ws2812_rp2040 leds(WS2812_PIN, WS2812_COUNT);

    leds[0].set_on_color(0x080000);	// LED0 is red
    leds[1].set_on_color(0x000600);	// LED1 is green

    // Redirect stdout and stderr to our backchannel UART,
    // so we can see the output of the task monitor
    uart_rp2040 uart;
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    // Instantiate the tasks to blink the red LED.
    // The class is derived from task (see above).
    // Blink the red LED with a delay of 300 ms!
    blink_task t1("t1 blinker", leds[0], 300 );

    // Instantiate the tasks to blink the green LED.
    // Here the code is provided as the first parameter
    // (in this case a lambda expression) to task.
    // The LED (leds[1]) is defined outside of task to
    // demonstrate the capture of external variables.
    // Toggle the green LED with a delay of 500 ms!

    task t2([&]() {
        // Endless loop
        while(true) {
            leds[1].toggle();
            task::sleep_ms(500);
        }
    }, "t2 blinker");

    // Start both tasks. This means that the tasks are put into a circular
    // list for scheduling and marked as 'ready' to run. But the kernel is
    // not yet started, so no task code is run after the two next lines!
    t1.start();
    t2.start();

    // Start the task monitor. When a terminal is connected to /dev/ttyACM0,
    // then the task status can be seen!
    task_monitor monitor;
    monitor.start();

    // Start the multitasking kernel.
    // This call is blocking (it will never return ...)!
    task::start_scheduler();
}
