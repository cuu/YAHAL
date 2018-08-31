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
// A small demo for using the adc14_msp432 class.
// No ADC interrupts or ADC scanning is used, just
// simple reading of single ADC conversions.
//
// The program will switch on the green/red LED on the
// Launchpad when the Joystick is moved to left/right

#include "gpio_msp432.h"
#include "adc14_msp432.h"

int main()
{
    // GPIO Pins with LEDs
    gpio_msp432_pin red_led  (PORT_PIN(2, 0));
    gpio_msp432_pin green_led(PORT_PIN(2, 1));
    red_led.  gpioMode(GPIO::OUTPUT);
    green_led.gpioMode(GPIO::OUTPUT);

    // ADC channel 15 is joystick X-movement.
    // Convert voltage to with 10 bits resolution.
	adc14_msp432_channel joy_X(15);
	joy_X.adcMode(ADC::ADC_10_BIT);

	// Store the offset (the value at the center position)
	uint16_t offset = joy_X.adcReadRaw();

	while(true) {
	    // read in a new ADC value
	    uint16_t val = joy_X.adcReadRaw();
	    // switch on green LED when Joystick is moved to the left
	    bool left  = (val - offset) < -200;
	    green_led.gpioWrite( left );
	    // switch on red LED when Joystick is moved to the right
	    bool right = (val - offset) > 200;
	    red_led.  gpioWrite( right );
	}
}
