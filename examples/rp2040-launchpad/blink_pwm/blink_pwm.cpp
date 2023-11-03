#include "gpio_rp2040.h"
#include "task.h"
#include "RP2040.h"

// Build-in red LED on rp2040-launchpad
#define RED_LED 13

using namespace _PWM_;

int main(void)
{
    // Use GPIO 13 (buildin LED) as output
    gpio_rp2040_pin led( RED_LED );
    led.setSEL(_IO_BANK0_::GPIO_CTRL_FUNCSEL__pwm);

    uint32_t div = 125000000 / 10 / 4096;
    PWM.CH6_DIV.INT  = div / 16;
    PWM.CH6_DIV.FRAC = div % 16;
    PWM.CH6_TOP = 65535;
    PWM.CH6_CC.B = 30000;
    PWM.CH6_CSR.EN = 1;

    // This loop will never end ...
    while(1) {

    }
}
