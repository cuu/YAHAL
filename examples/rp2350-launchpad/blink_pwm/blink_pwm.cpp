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
// A simple blink example using a PWM channel.
// The PWM frequency is 50Hz, and the duty cycle
// is used to control the brightness of the LED.
//
#include "board.h"
#include "gpio_rp2350.h"
#include "RP2350.h"
#include "system_rp2350.h"
#include "task.h"

#define PWM_FREQ_HZ 50

using namespace _PWM_;

int main(void)
{
    // Use GPIO 38 (buildin LED) as output and select PWM mode
    gpio_rp2350 led( LED_RED_GPIO );
    led.setSEL(_IO_BANK0_::GPIO_CTRL_FUNCSEL__pwm);

    // Calculate the divider. Because the PWM module uses a
    // 8.4 divider (8 bits integer part, 4 bits fractional part),
    // we calculate the divider 16 times to large, so we can more
    // easily extract the fractional part.
    // div is the number of system clock cycles per PWM counter tick,
    // assuming that the PWM counter should count to the maximum
    // value of 65535. Therefore, div could be calculated by
    // div = 200000000Hz / 50Hz / 65536 ticks. But since the div
    // value should be factored 16 too high, we only divide by 4096:
    uint32_t div = CLK_SYS / PWM_FREQ_HZ / 4096;
    // Set the integer and fractional part of the divider
    PWM.CH11_DIV.INT  = div / 16;
    PWM.CH11_DIV.FRAC = div % 16;
    // GPIO 38 is connected to PWM 11A. So set the
    // PWM 11A values (TOP and A compare count value)
    PWM.CH11_TOP  = 65535;
    // Finally enable the PWM module
    PWM.CH11_CSR.EN = 1;

    // This loop will never end ...
    while(true) {
        // Increase brightness of LED for one second
        for(int i=0; i<100; ++i) {
            PWM.CH11_CC.A = i*600;
            task::sleep_ms(10);
        }
        // Decrease brightness of LED for one second
        for(int i=99; i>=0; --i) {
            PWM.CH11_CC.A = i*600;
            task::sleep_ms(10);
        }
    }
}
