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
// Implementation of LEDs for the RP2040-based debug
// probe on the RP2040 or RP2350 Launchpad boards.
//
#ifndef DAP_LED_RP2XX0_LP_PROBE_H
#define DAP_LED_RP2XX0_LP_PROBE_H

#include <cstdint>
#include "board.h"
#include "DAP_led_interface.h"
#include "gpio_rp2040.h"
#include "system_rp2040.h"
#include "task_timer.h"

#include "RP2040.h"
using namespace _IO_BANK0_;
using namespace _PWM_;

// LED configuration
#define LED_FOLLOW_UP_TIME_MS 20

class DAP_led_rp2xxx_launchpad_probe : public DAP_led_interface, task_timer {
public:

    DAP_led_rp2xxx_launchpad_probe() : task_timer("LED timer task") {
        // Set GPIOs to output
        _red.gpioMode  (GPIO::OUTPUT | GPIO::INIT_LOW);
        _green.gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
        _blue.gpioMode (GPIO::OUTPUT | GPIO::INIT_LOW);

        // The timer will switch off the RX/TX LEDs
        setCallback([&] () {
            _red   = false;
            _green = false;
        });

        // Set up PWM for blue LED
        _blue.setSEL(_IO_BANK0_::GPIO_CTRL_FUNCSEL__pwm);
        uint32_t div = CLK_SYS / 10 / 4096;
        PWM.CH1_DIV.INT  = div / 16;
        PWM.CH1_DIV.FRAC = div % 16;
        PWM.CH1_TOP  = 65535;
        PWM.CH1_CC.A = 0; // OFF
        PWM.CH1_CSR.EN = 1;
    }

    // Switch on the LED signalling UART TX
    // activity from the target. After the
    // follow-up time, the LED is switched
    // off automatically.
    void trigger_uart_tx_led() override {
        _red = true;
        if (isRunning()) {
            reset();
        } else {
            setPeriod(LED_FOLLOW_UP_TIME_MS * 1000, TIMER::ONE_SHOT);
            start();
        }
    }

    // Switch on the LED signalling UART RX
    // activity to the target. After the
    // follow-up time, the LED is switched
    // off automatically.
    void trigger_uart_rx_led() override {
        _green = true;
        if (isRunning()) {
            reset();
        } else {
            setPeriod(LED_FOLLOW_UP_TIME_MS * 1000, TIMER::ONE_SHOT);
            start();
        }
    }

    // Switch on/off the LED signalling the
    // connection status between debugger and target.
    inline void set_connected_led(bool val) override {
        if (val) _just_connected = true;
        PWM.CH1_CC.A = val ? 65535 : 0;
    }

    // Switch on/off the LED signalling the
    // 'target running' status
    inline void set_running_led(bool val) override {
        if (_just_connected) {
            // Ignore the first switch-on from openocd...
            _just_connected = false;
        } else {
            // Only blink when we are connected
            if (PWM.CH1_CC.A) {
                PWM.CH1_CC.A = val ? 30000 : 65535;
            }
        }
    }

    void welcome() override {
        for(int i=1; i < 7; ++i) {
            _red   = (bool)(i % 2);
            _green = (bool)(i % 2);
            task::sleep_ms(100);
        }
    }

    using task::sign_up;
    using task::setPriority;

private:
    gpio_rp2040 _red   {LED_RED_GPIO};   // UART TX (data from target)
    gpio_rp2040 _green {LED_GREEN_GPIO}; // UART RX (data to target)
    gpio_rp2040 _blue  {LED_BLUE_GPIO};

    bool        _just_connected {false};
};

#endif // DAP_LED_RP2XX0_LP_PROBE_H
