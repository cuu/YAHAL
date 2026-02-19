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
// to check all GPIO pins of a RP2350 launchpad.
//
#include "cy8c95xxa_drv.h"
#include "gpio_rp2350.h"
#include "i2c_rp2350.h"
#include "posix_io.h"
#include "uart_rp2350.h"
#include <cstdio>

using namespace _TIMER0_;

struct gpio_pair {
    gpio_pin_t    cy_pin;
    gpio_pin_t    rp_pin;
};
#define NC 0xffff

// RP2350 I2C interface
#define SDA 34
#define SCL 35

// RP2350 analog pins
#define A0  40
#define A1  41
#define A2  42
#define A3  43
#define A4  44
#define A5  45
#define A6  46
#define A7  47

// CY LED pins
#define LED_RED   PORT_PIN(2, 1)
#define LED_GREEN PORT_PIN(2, 2)
#define LED_BLUE  PORT_PIN(2, 0)

int main()
{
    gpio_pair pairs[] = {
    // ---------------- | ---------------
    // ---- CYPRESS --- | --- RP2350 ----
    // ---------------- | ---------------
        { PORT_PIN(0,0), A0 } ,
        { PORT_PIN(0,1), 33 } ,
        { PORT_PIN(0,2), A1 } ,
        { PORT_PIN(0,3), 32 } ,
        { PORT_PIN(0,4), A2 } ,
        { PORT_PIN(0,5), 31 } ,
        { PORT_PIN(0,6), A3 } ,
        { PORT_PIN(0,7), A4 } ,

        { PORT_PIN(1,0), 25 } ,
        { PORT_PIN(1,1), 24 } ,
        { PORT_PIN(1,2), 23 } ,
        { PORT_PIN(1,3), 22 } ,
        { PORT_PIN(1,4), 21 } ,
        { PORT_PIN(1,5), 20 } ,
        { PORT_PIN(1,6), 19 } ,
        { PORT_PIN(1,7), 18 } ,

        { PORT_PIN(3,0), A5 } ,
        { PORT_PIN(3,1), 30 } ,
        { PORT_PIN(3,2), A6 } ,
        { PORT_PIN(3,3), 36 } ,
        { PORT_PIN(3,4), A7 } ,
        { PORT_PIN(3,5), NC } ,
        { PORT_PIN(3,6), NC } ,

        { PORT_PIN(4,0), 11 } ,
        { PORT_PIN(4,1), 17 } ,
        { PORT_PIN(4,2), 12 } ,
        { PORT_PIN(4,3), 16 } ,
        { PORT_PIN(4,4), 13 } ,
        { PORT_PIN(4,5), 15 } ,
        { PORT_PIN(4,6), 14 } ,
        { PORT_PIN(4,7), 10 } ,

        { PORT_PIN(5,0),  1 } ,
        { PORT_PIN(5,1),  2 }
    };

    // Use backchannel UART for stdin/stdout
    ////////////////////////////////////////
    uart_rp2350 uart;
    posix_io::inst.register_stdout( uart );
    posix_io::inst.register_stderr( uart );

    // Set up I2C connection
    ////////////////////////
    i2c_rp2350 i2c(SDA, SCL, 0);
    i2c.setSpeed(100000);

    // The gpio instances
    /////////////////////
    cy8c95xxa_drv   gpio_cy(i2c, 0x20);
    gpio_rp2350     gpio_rp;

    // Set up CY LEDs
    /////////////////
    gpio_cy.gpioMode( LED_RED,   GPIO::OUTPUT | GPIO::INIT_LOW);
    gpio_cy.gpioMode( LED_GREEN, GPIO::OUTPUT | GPIO::INIT_LOW);
    gpio_cy.gpioMode( LED_BLUE,  GPIO::OUTPUT | GPIO::INIT_LOW);

    printf("**** RP2350 Launchpad Tester ****\n");
    printf("=================================\n\n");

    int errors = 0;

    gpio_cy.gpioMode( LED_RED,   GPIO::OUTPUT | GPIO::INIT_LOW);
    gpio_cy.gpioMode( LED_GREEN, GPIO::OUTPUT | GPIO::INIT_LOW);
    gpio_cy.gpioMode( LED_BLUE,  GPIO::OUTPUT | GPIO::INIT_LOW);

    int entries = sizeof(pairs) / sizeof(gpio_pair);
    printf("Checking %d Pins ...\n\n", entries);

    for(int i=0; i < entries; ++i) {
        gpio_pin_t cy_pin = pairs[i].cy_pin;
        gpio_pin_t rp_pin = pairs[i].rp_pin;
        bool res;

        // Check for not connected pins
        if (rp_pin == NC) continue;

        // Test LP pin as output
        ////////////////////////
        printf("Testing GPIO %2d as output ... ", rp_pin);
        gpio_cy.gpioMode(cy_pin, GPIO::INPUT);
        gpio_rp.setGpio(rp_pin);
        gpio_rp.gpioMode(GPIO::OUTPUT);

        gpio_rp.gpioWrite(true);
        gpio_cy.gpioWrite(LED_RED, true);
        res = gpio_cy.gpioRead(cy_pin);
        if (!res) {
            errors++;
            printf(" FAIL(H)");
        }

        gpio_rp.gpioWrite(false);
        gpio_cy.gpioWrite(LED_RED, false);
        res = gpio_cy.gpioRead(cy_pin);
        if (res) {
            errors++;
            printf(" FAIL(L)");
        }
        printf("\n");

        // Test LP pin as input
        ///////////////////////
        printf("Testing GPIO %2d as input ... ", rp_pin);
        gpio_rp.gpioMode(GPIO::INPUT);
        gpio_cy.gpioMode(cy_pin, GPIO::OUTPUT);

        gpio_cy.gpioWrite(cy_pin,   true);
        gpio_cy.gpioWrite(LED_GREEN, true);
        res = gpio_rp.gpioRead();
        if (!res) {
            errors++;
            printf(" FAIL(H)");
        }

        gpio_cy.gpioWrite(cy_pin,   false);
        gpio_cy.gpioWrite(LED_GREEN, false);
        res = gpio_rp.gpioRead();
        if (res) {
            errors++;
            printf(" FAIL(L)");
        }
        printf("\n");

        gpio_cy.gpioMode( cy_pin, GPIO::INPUT);
    }

    printf("Total errors: %d\n", errors);

    gpio_cy.gpioWrite(LED_BLUE,  false);
    gpio_cy.gpioWrite(LED_GREEN, (errors == 0));
    gpio_cy.gpioWrite(LED_RED,   (errors != 0));
}

