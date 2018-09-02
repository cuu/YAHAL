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
// This program uses the LaunchpadTester PCB
// to check all GPIO pins of a MSP432 launchpad.
//

#include "gpio_msp432.h"
#include "i2c_msp432.h"
#include "cy8c95xxa_drv.h"
#include "uart_msp432.h"
#include "std_io.h"
#include <cstdio>

struct gpio_pair {
    gpio_pin_t    cy_pin;
    gpio_pin_t    msp_pin;
};

int main(void)
{
    gpio_pair pairs[33] = {
    // ---------------- | ---------------
    // ---- CYPRESS --- | ----- MSP -----
    // ---------------- | ---------------
        { PORT_PIN(0,0), PORT_PIN(6,0) } ,
        { PORT_PIN(0,1), PORT_PIN(3,2) } ,
        { PORT_PIN(0,2), PORT_PIN(6,1) } ,
        { PORT_PIN(0,3), PORT_PIN(3,3) } ,
        { PORT_PIN(0,4), PORT_PIN(4,0) } ,
        { PORT_PIN(0,5), PORT_PIN(4,1) } ,
        { PORT_PIN(0,6), PORT_PIN(4,2) } ,
        { PORT_PIN(0,7), PORT_PIN(4,3) } ,

        { PORT_PIN(1,0), PORT_PIN(2,7) } ,
        { PORT_PIN(1,1), PORT_PIN(2,6) } ,
        { PORT_PIN(1,2), PORT_PIN(2,5) } ,
        { PORT_PIN(1,3), PORT_PIN(2,4) } ,
        { PORT_PIN(1,4), PORT_PIN(3,0) } ,
        { PORT_PIN(1,5), PORT_PIN(5,6) } ,
        { PORT_PIN(1,6), PORT_PIN(5,7) } ,
        { PORT_PIN(1,7), PORT_PIN(6,6) } ,

        { PORT_PIN(3,0), PORT_PIN(4,4) } ,
        { PORT_PIN(3,1), PORT_PIN(1,5) } ,
        { PORT_PIN(3,2), PORT_PIN(4,5) } ,
        { PORT_PIN(3,3), PORT_PIN(4,6) } ,
        { PORT_PIN(3,4), PORT_PIN(4,7) } ,
        { PORT_PIN(3,5), PORT_PIN(5,4) } ,
        { PORT_PIN(3,6), PORT_PIN(5,5) } ,

        { PORT_PIN(4,0), PORT_PIN(1,6) } ,
        { PORT_PIN(4,1), PORT_PIN(6,7) } ,
        { PORT_PIN(4,2), PORT_PIN(1,7) } ,
        { PORT_PIN(4,3), PORT_PIN(2,3) } ,
        { PORT_PIN(4,4), PORT_PIN(5,0) } ,
        { PORT_PIN(4,5), PORT_PIN(5,1) } ,
        { PORT_PIN(4,6), PORT_PIN(5,2) } ,
        { PORT_PIN(4,7), PORT_PIN(3,5) } ,

        { PORT_PIN(5,0), PORT_PIN(3,6) } ,
        { PORT_PIN(5,1), PORT_PIN(3,7) }

    };

    for (int t=0; t < 100000; ++t);

    // Use backchannel UART for stdin/stdout
    ////////////////////////////////////////
    uart_msp432 uart;
    std_io::inst.redirect_stdin ( uart );
    std_io::inst.redirect_stdout( uart );

    // Set up I2C connection
    ////////////////////////
    i2c_msp432 i2c(EUSCI_B1);
    i2c.setSpeed(100000);

    // The gpio instances
    /////////////////////
    cy8c95xxa_drv   gpio_cy(i2c, 0x20);
    gpio_msp432 &   gpio_msp = gpio_msp432::inst;

    gpio_msp432_pin led_red  ( PORT_PIN(2,0) );
    gpio_msp432_pin led_green( PORT_PIN(2,1) );
    gpio_msp432_pin led_blue ( PORT_PIN(2,2) );

    led_red.  gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
    led_green.gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
    led_blue. gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);

    int errors = 0;

    printf("**** Launchpad Tester ****\n");
    printf("==========================\n\n");

//    gpio_cy.gpioMode(PORT_PIN(4,5), GPIO::OUTPUT);
//    while(1) {
//        gpio_cy.gpioWrite(PORT_PIN(4,5), true);
//        gpio_cy.gpioWrite(PORT_PIN(4,5), false);
//    }


    for(int i=0; i < 33; ++i) {
        gpio_pin_t cy_pin  = pairs[i].cy_pin;
        gpio_pin_t msp_pin = pairs[i].msp_pin;
        bool res;

        // Test MSP pin as output
        /////////////////////////
        printf("Testing %d.%d as output ... ", PORT(msp_pin), PIN(msp_pin));
        gpio_cy. gpioMode( cy_pin, GPIO::INPUT );
        gpio_msp.gpioMode(msp_pin, GPIO::OUTPUT);

        gpio_msp.gpioWrite(msp_pin, true);
        led_blue.gpioWrite(true);
        res = gpio_cy.gpioRead(cy_pin);
        if (res != true) {
            errors++;
            printf(" FAIL(H)");
        }

        gpio_msp.gpioWrite(msp_pin, false);
        led_blue.gpioWrite(false);
        res = gpio_cy.gpioRead(cy_pin);
        if (res != false) {
            errors++;
            printf(" FAIL(L)");
        }
        printf("\n");

        // Test MSP pin as input
        /////////////////////////
        printf("Testing %d.%d as input ... ", PORT(msp_pin), PIN(msp_pin));
        gpio_msp.gpioMode(msp_pin, GPIO::INPUT);
        gpio_cy. gpioMode( cy_pin, GPIO::OUTPUT);

        gpio_cy. gpioWrite(cy_pin, true);
        led_blue.gpioWrite(true);
        res = gpio_msp.gpioRead(msp_pin);
        if (res != true) {
            errors++;
            printf(" FAIL(H)");
        }

        gpio_cy. gpioWrite(cy_pin, false);
        led_blue.gpioWrite(false);
        res = gpio_msp.gpioRead(msp_pin);
        if (res != false) {
            errors++;
            printf(" FAIL(L)");
        }
        printf("\n");

        gpio_cy. gpioMode( cy_pin, GPIO::INPUT);
    }

    printf("Total errors: %d\n", errors);

    led_blue.gpioWrite(false);
    led_green.gpioWrite(errors == 0);
    led_red.gpioWrite  (errors != 0);

    while(1) ;
}

