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
// A small demo for using the adc_rp2040 class.
// No ADC interrupts or ADC scanning is used, just
// simple reading of single ADC conversions.
//
// The program will switch on the green/red LED on the
// Launchpad when the Joystick is moved to left/right.
// The raw ADC values are shown on the backchannel UART.

#include "adc_rp2040.h"
#include "uart_rp2040.h"
#include "posix_io.h"
#include "ws2812_rp2040.h"
#include <cstdio>

int main() {
    // Redirect stdout so printf is working
    uart_rp2040 uart;
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    // LEDs
    ws2812_rp2040 leds(29, 8);
    led_rgb_interface & led_red   = leds[0];
    led_rgb_interface & led_green = leds[7];
    led_red.set_on_color(0x080000);     // Dark red
    led_green.set_on_color(0x000800);   // Dark green

    // ADC channel 1 is joystick X-movement.
    // The voltage from the joystick (range 0...3,3V) to
    // is converted to a 12-bit integer (0...4095)
    adc_rp2040_channel joy_X(1);

    // Store the offset (the value at the center position)
    uint16_t offset = joy_X.adcReadRaw();

    while (true) {
        // read in a new ADC value
        uint16_t val = joy_X.adcReadRaw();
        // switch on red LED when Joystick is moved to the left
        led_red  = (val - offset) < -1000;
        // switch on green LED when Joystick is moved to the right
        led_green = (val - offset) > 1000;

        // Calculate the voltage with integer arithmetic
        printf("%d millivolt\n", val * 3300 / 4095);
    }
}
