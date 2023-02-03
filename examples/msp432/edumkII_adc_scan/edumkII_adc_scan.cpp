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
// Small demo for the ADC scan mode:
// Continuously scan the ADC channels 9 to 15, and
// print out the result to the console. Within this
// channel range, there are the 3 accelerometer
// and 2 joystick channels.
//
// The ADC14 will perform this scanning process
// automatically, and save the results in internal
// registers. The method adcReadScan(channel) will
// only read out these internal registers, and is
// therefore very fast. The method adcReadRaw can
// not be used, because it will stop the scanning
// process!

#include <cstdio>

#include "gpio_msp432.h"
#include "adc14_msp432.h"
#include "uart_msp432.h"
#include "posix_io.h"
#include "task.h"

#define CLEAR_SCREEN "%c[H%c[J",27,27

int main()
{
    // Initialize the backchannel UART
    // and redirect stdin and stdout
    uart_msp432 uart;
    posix_io::inst.register_stdin ( uart );
    posix_io::inst.register_stdout( uart );

    // Instantiate ADC channels
    adc14_msp432_channel joy_Y( 9);
    adc14_msp432_channel acc_Z(11);
    adc14_msp432_channel acc_Y(13);
    adc14_msp432_channel acc_X(14);
    adc14_msp432_channel joy_X(15);
    joy_X.adcMode(ADC::ADC_10_BIT);
    joy_Y.adcMode(ADC::ADC_10_BIT);
    acc_X.adcMode(ADC::ADC_10_BIT);
    acc_Y.adcMode(ADC::ADC_10_BIT);
    acc_Z.adcMode(ADC::ADC_10_BIT);

    // shortcut for adc instance
    adc14_msp432 & adc = adc14_msp432::inst;

    // setup and start the scan process
    adc.adcSetupScan(ADC::ADC_10_BIT);
    adc.adcStartScan(9, 15);
    
    while(true) {
        printf(CLEAR_SCREEN);
        printf("joy X: %d\n", joy_X.adcReadScan());
        printf("joy Y: %d\n", joy_Y.adcReadScan());
        printf("acc X: %d\n", acc_X.adcReadScan());
        printf("acc Y: %d\n", acc_Y.adcReadScan());
        printf("acc Z: %d\n", acc_Z.adcReadScan());

        // Small delay
        task::sleep(100);
    }
}
