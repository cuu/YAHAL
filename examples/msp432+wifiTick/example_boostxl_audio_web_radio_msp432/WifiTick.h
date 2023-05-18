

#ifndef _WIFI_TICK_H_
#define _WIFI_TICK_H_

#include <cstdint>
#include <functional>
#include "gpio_msp432.h"

class WifiTick
{
public:
    WifiTick();

    // Set the LED on the WifiTick-board
    inline void led(bool v) {
        _led.gpioWrite(v);
    }

    // Set the PU line of the ESP8266
    inline void power_up(bool v) {
        _powerUp.gpioWrite(v);
    }

    // Perform a reset sequence. When the
    // parameter is true, the ESP8266 is
    // booting from UART
    void reset(bool boot_from_uart = false);

private:
    gpio_msp432_pin _gpio0;
    gpio_msp432_pin _gpio2;
    gpio_msp432_pin _gpio15;
    gpio_msp432_pin _reset;
    gpio_msp432_pin _powerUp;
    gpio_msp432_pin _led;
};

#endif // _WIFI_TICK_H_
