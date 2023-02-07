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
// This program demonstrates the use of a 28BYJ stepper motor.
// A simple driver class is provided!

#include "gpio_msp432.h"
#include "posix_io.h"
#include "task.h"
#include "uart_msp432.h"

class Stepper_28BYJ {
public:
    // The small PCBs delivered with the 28BJY stepper motor
    // have inputs IN1-IN4. The constructor parameters are
    // 4 gpio pins, which are connected to IN1-IN4. You can
    // use any gpio pins you like...

    Stepper_28BYJ(gpio_pin & m1, gpio_pin & m2, gpio_pin & m3, gpio_pin & m4)
    : _index(0), _m1(m1),_m2(m2),_m3(m3),_m4(m4) {
        // Set output mode
        _m1.gpioMode(GPIO::OUTPUT);
        _m2.gpioMode(GPIO::OUTPUT);
        _m3.gpioMode(GPIO::OUTPUT);
        _m4.gpioMode(GPIO::OUTPUT);
        write();
    }

    // Move the motor a number of steps. Positive values result
    // in clockwise rotation, negative values in counter-clockwise
    // rotation. The steps are written with 1 kHz, which should
    // result in a reliable operation (no missing steps).
    // A value of 4096 results in 360° rotation!
    void move(int steps) {
        bool forward = (steps > 0);
        if (!forward) steps = -steps;
        for (int i=0; i < steps; ++i) {
            if (forward) {
                _index++;
                _index %= sizeof(_pattern);
            } else {
                _index--;
                if (_index < 0) {
                    _index = sizeof(_pattern)-1;
                }
            }
            write();
            task::sleep(1);
        }
    }

    // Write current pattern to GPIOs
    void write() {
        _m1.gpioWrite(_pattern[_index] & 0x01);
        _m2.gpioWrite(_pattern[_index] & 0x02);
        _m3.gpioWrite(_pattern[_index] & 0x04);
        _m4.gpioWrite(_pattern[_index] & 0x08);
    }

    // Switch off motor to save power.
    // The move-method will automatically power the
    // motor on again.
    void off() {
        _m1.gpioWrite(0);
        _m2.gpioWrite(0);
        _m3.gpioWrite(0);
        _m4.gpioWrite(0);
    }

private:
    // Stepping patterns (with micro-steps).
    // One complete sequence (8 steps) is 1/8 rotation of
    // the internal motor. So 8*8 = 64 steps is a full roation.
    // The internal gearbox has a gear ratio of 64:1, so 4096
    // steps is a full 360° turn of the external motor shaft.
    uint8_t _pattern[8] =
        { 0b0001,
          0b0011,
          0b0010,
          0b0110,
          0b0100,
          0b1100,
          0b1000,
          0b1001 };

    int8_t     _index;
    gpio_pin & _m1;
    gpio_pin & _m2;
    gpio_pin & _m3;
    gpio_pin & _m4;
};


int main(void)
{
    gpio_msp432_pin m1(PORT_PIN(7, 4));
    gpio_msp432_pin m2(PORT_PIN(7, 5));
    gpio_msp432_pin m3(PORT_PIN(7, 6));
    gpio_msp432_pin m4(PORT_PIN(7, 7));
    Stepper_28BYJ stepper(m1, m2, m3, m4);

    // Set up UART and enable stdin/stdout
    // using printf/scanf
    //////////////////////////////////////
    uart_msp432 uart; // default is backchannel UART!
    posix_io::inst.register_stdout( uart );
    posix_io::inst.register_stderr( uart );

    while (true) {
        // Step 4 times ( 13 * 68 steps + 2 * 70 ) steps
        // This will result in 4096 steps total.
        // The motor will rotate like a second-hand
        // on a analog clock!
        for (int i=0; i < 4; ++i) {
            // Step 13 times 68 steps
            for (int j=0; j < 13; ++j) {
                stepper.move(68);
                stepper.off();
                task::sleep(100);
            }
            for (int j=0; j < 2; ++j) {
            // Step 2 times 70 steps
                stepper.move(70);
                stepper.off();
                task::sleep(100);
            }
        }
        // Wait 2 seconds and rotate back again
        task::sleep(2000);
        stepper.move(-4096);
        task::sleep(500);
    }
    stepper.off();
    return 0;
}
