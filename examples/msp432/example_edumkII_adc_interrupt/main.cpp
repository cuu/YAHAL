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
// A demo for using the adc14_msp432 class with
// interrupts. Interrupts on ADC channels can
// only be used 'on top of' the ADC scan mode,
// which will repeatedly convert new values.
// There are two types of interrupts:
//
//   - attachScanIrq(handler): After every ADC
//     conversion, the handler is called
//
//   - attachWinIrq (handler,low, high, mode):
//     The handler is called, when the last conversion
//     result is either below the lower, above the
//     higher or between the lower and higher window
//     values. The 'mode' parameter controls this
//     behavior. The window interrupt is disabled
//     before the handler is called. So this interrupt
//     has a 'one shot' characteristic. But a new
//     window interrupt can be attached in the
//     interupt handler function (see below).
//

#include <cstdio>
#include "gpio_msp432.h"
#include "adc14_msp432.h"

// create ADC channels
adc14_msp432_channel joy_X(15);
adc14_msp432_channel joy_Y( 9);
uint16_t offset_X, offset_Y;

// GPIO Pins with LEDs
gpio_msp432_pin red_led  (PORT_PIN(2, 0));
gpio_msp432_pin green_led(PORT_PIN(2, 1));
gpio_msp432_pin blue_led (PORT_PIN(2, 2));

void delay() {
    for(int i=0; i < 5000; ++i) ;
}

void handler_X(uint16_t, uint16_t value) {
    // This handler is called after EVERY conversion
    // of a new ADC value.
    //
    // Switch on/off the red LED if the joystick
    // is moved left/right
    if ( (value-offset_X) >  200 ) red_led.gpioWrite(HIGH);
    if ( (value-offset_X) < -200 ) red_led.gpioWrite(LOW);
}

void handler_Y(uint16_t, uint16_t irq_mode) {
    // This handler is only called, when the
    // configured window mode is met.
    // Before this handler is called, the window
    // interrupts are disabled. So you need to
    // make another call to attachWinIrq(...),
    // if the handler should be called again.
    // Of course the window values can be changed
    // if desired.
    //
    // Flash the red/green/blue LED when the joystick
    // is within a defined window.
    if ( irq_mode == ADC::ABOVE_HIGH ) {
        green_led.gpioWrite(HIGH);
        // Set a new window so the handler is called
        // again, when the Y joystick is near the middle
        joy_Y.attachWinIrq (handler_Y,
                            offset_Y-40, offset_Y+40,
                            ADC::WITHIN_WIN);
        delay();
        green_led.gpioWrite(LOW);
    }
    if ( irq_mode == ADC::BELOW_LOW  ) {
        red_led.gpioWrite(HIGH);
        // Set a new window so the handler is called
        // again, when the Y joystick is near the middle
        joy_Y.attachWinIrq (handler_Y,
                            offset_Y-40, offset_Y+40,
                            ADC::WITHIN_WIN);
        delay();
        red_led.gpioWrite(LOW);
    }
    if ( irq_mode == ADC::WITHIN_WIN) {
        // okay, we are in the middle again. Set a new
        // window for LED on/off function.
        // Also flash the blue LED!
        blue_led.gpioWrite(HIGH);
        joy_Y.attachWinIrq (handler_Y,
                            offset_Y-400, offset_Y+400,
                            ADC::BELOW_LOW | ADC::ABOVE_HIGH);
        delay();
        blue_led.gpioWrite(LOW);
    }
}

int main()
{
    // set the modes
    red_led.  gpioMode(GPIO::OUTPUT);
    green_led.gpioMode(GPIO::OUTPUT);
    blue_led.gpioMode (GPIO::OUTPUT);
    joy_X.adcMode(ADC::ADC_10_BIT);
    joy_Y.adcMode(ADC::ADC_10_BIT);

    // read the initial value (middle position)
    offset_X = joy_X.adcReadRaw();
    offset_Y = joy_Y.adcReadRaw();

    // attach irq handlers
    joy_X.attachScanIrq(handler_X);
    joy_Y.attachWinIrq (handler_Y,
                        offset_Y-400, offset_Y+400,
                        ADC::ABOVE_HIGH | ADC::BELOW_LOW);

    // shortcut for adc instance
    adc14_msp432 & adc = adc14_msp432::inst;

    // setup and start the scan process
    adc.adcSetupScan(ADC::ADC_10_BIT);
    adc.adcStartScan(9, 15);

    while(true) {
        // nothing to do in the main loop,
        // because everything is handled by
        // the interrupt handlers!
    }
}
