#include "gpio_rp2040.h"
#include "RP2040.h"

// Build-in red LED on rp2040-launchpad
#define RED_LED 13

using namespace _PWM_;

int main(void)
{
    // Use GPIO 13 (buildin LED) as output and select PWM mode
    gpio_rp2040_pin led( RED_LED );
    led.setSEL(_IO_BANK0_::GPIO_CTRL_FUNCSEL__pwm);

    // Calculate the divider. Because the PWM module uses a
    // 8.4 divider (8 bits integer part, 4 bits fractional part),
    // we calculate the diver 16 times to large, so we can more
    // easily extract the fractional part.
    // div is the number of system clock cycles per PWM counter tick,
    // assuming that the PWM counter should count to the maximum
    // value of 65535. Therefore div could be calcualted by
    // div = 125000000Hz / 10Hz / 65536 ticks. But since the div
    // value should be factor 16 too high, we only divide by 4096:
    uint32_t div = 125000000 / 10 / 4096;
    // Set the integer and fractional part of the divider
    PWM.CH6_DIV.INT  = div / 16;
    PWM.CH6_DIV.FRAC = div % 16;
    // GPIO 13 is connected to PWM 6B. So set the
    // PWM 6B values (TOP and B compare count value)
    PWM.CH6_TOP  = 65535;
    PWM.CH6_CC.B = 30000;
    // Finally enable the PWM 6 module
    PWM.CH6_CSR.EN = 1;

    // This loop will never end ...
    while(1) {
        // WFE() will set the CPU to sleep and wait
        // for the next interrupt. The PWM module will
        // not generate any interrupts, because they
        // were not enabled :)
//        _WFE();
    }
}
