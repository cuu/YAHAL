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
// Small example to demonstrate multitasking on
// both cores of the RP2350. The class 'blinker'
// is a small class to blink one of the WS2812
// LEDS. For every core two blinkers and a task
// monitor are signed up. Tasks on core 0 are
// started after a delay of 2500ms so that the
// output of the two task monitors does not
// interfere!
//
#include "board.h"
#include "multicore_rp2350.h"
#include "task.h"
#include "task_monitor.h"
#include "ws2812_rp2350.h"
#include "uart_rp2350.h"
#include "posix_io.h"

using enum core_t;

// Small task class to blink a WS2812 LED
class blinker : public task {
public:
    blinker(const char * name, led_rgb_interface & led, int delay_ms)
    : task(name), _led(led), _delay_ms(delay_ms) { }

    [[noreturn]] void run() override {
        while(true) {
            _led.toggle();
            task::sleep_ms(_delay_ms);
        }
    }

private:
    led_rgb_interface & _led;
    int                 _delay_ms;
};


int main() {
    // Set up back channel UART
    uart_rp2350 uart;
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    // Set up four WS2812 LEDs
    ws2812_rp2350 leds(LED_RGB_GPIO, LED_RGB_COUNT);
    leds[0].set_on_color(0x200000); // Red
    leds[1].set_on_color(0x002000); // Green
    leds[6].set_on_color(0x000020); // Blue
    leds[7].set_on_color(0x202000); // Yellow

    // All tasks for core 1
    blinker blue("Blue Blinker", leds[6], 500);
    blue.sign_up(CORE_1);
    blinker yellow("Yellow Blinker", leds[7], 250);
    yellow.sign_up(CORE_1);
    task_monitor m_core1;
    m_core1.sign_up(CORE_1);

    // Start the core 1 multitasking
    multicore_rp2350::reset_core1();
    multicore_rp2350::start_on_core1([]() {
        task::start_scheduler();
    });

    // Delay core 0 tasks so the monitor outputs
    // do not interfere...
    task::sleep_ms(2480);

    // All tasks for core 0
    blinker red("Red Blinker", leds[0], 500);
    red.sign_up();
    blinker green("Green Blinker", leds[1], 250);
    green.sign_up();
    task_monitor m_core0;
    m_core0.sign_up();

    // Start core 0 multitasking
    task::start_scheduler();
}
