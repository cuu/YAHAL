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
// to check all GPIO pins of a RP2040 launchpad.
//
#include "gpio_rp2040.h"
#include "i2c_rp2040.h"
#include "uart_rp2040.h"
#include "cy8c95xxa_drv.h"
#include "posix_io.h"
#include "task.h"
#include <cstdio>

struct gpio_pair {
    gpio_pin_t    cy_pin;
    gpio_pin_t    rp_mux_and_pin;
};

#define NC 0xffff
// RP2040 Analog inputs
#define A0 PORT_PIN(0, 26)
#define A1 PORT_PIN(1, 26)
#define A2 PORT_PIN(0, 27)
#define A3 PORT_PIN(1, 27)
#define A4 PORT_PIN(0, 28)
#define A5 PORT_PIN(1, 28)
#define A6 PORT_PIN(0, 29)
#define A7 PORT_PIN(1, 29)
// RP2040 I2C interface
#define SDA 24
#define SCL 25
// CY LED pins
#define LED_RED   PORT_PIN(2, 1)
#define LED_GREEN PORT_PIN(2, 2)
#define LED_BLUE  PORT_PIN(2, 0)

int main(void)
{
    gpio_pair pairs[] = {
    // ---------------- | ---------------
    // ---- CYPRESS --- | --- RP2040 ----
    // ---------------- | ---------------
        { PORT_PIN(0,0), A1 } ,
        { PORT_PIN(0,1), 21 } ,
        { PORT_PIN(0,2), A0 } ,
        { PORT_PIN(0,3), 20 } ,
        { PORT_PIN(0,4), A2 } ,
        { PORT_PIN(0,5), 19 } ,
        { PORT_PIN(0,6), A4 } ,
        { PORT_PIN(0,7), A6 } ,

        { PORT_PIN(1,0), 14 } ,
        { PORT_PIN(1,1), 13 } ,
        { PORT_PIN(1,2), 12 } ,
        { PORT_PIN(1,3), 10 } ,
        { PORT_PIN(1,4), 11 } ,
        { PORT_PIN(1,5),  8 } ,
        { PORT_PIN(1,6),  9 } ,
        { PORT_PIN(1,7), NC } ,

        { PORT_PIN(3,0), A3 } ,
        { PORT_PIN(3,1), 22 } ,
        { PORT_PIN(3,2), A5 } ,
        { PORT_PIN(3,3), 23 } ,
        { PORT_PIN(3,4), A7 } ,
        { PORT_PIN(3,5), NC } ,
        { PORT_PIN(3,6), NC } ,

        { PORT_PIN(4,0),  7 } ,
        { PORT_PIN(4,1), NC } ,
        { PORT_PIN(4,2),  4 } ,
        { PORT_PIN(4,3),  6 } ,
        { PORT_PIN(4,4),  5 } ,
        { PORT_PIN(4,5), 16 } ,
        { PORT_PIN(4,6), 15 } ,
        { PORT_PIN(4,7), 17 } ,

        { PORT_PIN(5,0),  3 } ,
        { PORT_PIN(5,1),  2 }
    };

    // Use backchannel UART for stdin/stdout
    ////////////////////////////////////////
    uart_rp2040 uart;
    posix_io::inst.register_stdin ( uart );
    posix_io::inst.register_stdout( uart );
    posix_io::inst.register_stderr( uart );

    // Set up I2C connection
    ////////////////////////
    i2c_rp2040 i2c(0, SDA, SCL, 0);
    i2c.setSpeed(100000);

    // The gpio instances
    /////////////////////
    cy8c95xxa_drv   gpio_cy(i2c, 0x20);
    gpio_rp2040 &   gpio_rp = gpio_rp2040::inst;

    // Set up CY LEDs
    /////////////////
    gpio_cy.gpioMode( LED_RED,   GPIO::OUTPUT | GPIO::INIT_LOW);
    gpio_cy.gpioMode( LED_GREEN, GPIO::OUTPUT | GPIO::INIT_LOW);
    gpio_cy.gpioMode( LED_BLUE,  GPIO::OUTPUT | GPIO::INIT_LOW);

    // Set up RP2040 multiplexer ctrl pin
    gpio_rp.gpioMode( 18, GPIO::OUTPUT);

    printf("**** RP2040 Launchpad Tester ****\n");
    printf("=================================\n\n");

    int errors = 0;

    gpio_cy.gpioMode( LED_RED,   GPIO::OUTPUT | GPIO::INIT_LOW);
    gpio_cy.gpioMode( LED_GREEN, GPIO::OUTPUT | GPIO::INIT_LOW);
    gpio_cy.gpioMode( LED_BLUE,  GPIO::OUTPUT | GPIO::INIT_LOW);

    int entries = sizeof(pairs) / sizeof(gpio_pair);
    printf("Checking %d Pins ...\n\n", entries);

    for(int i=0; i < entries; ++i) {
        gpio_pin_t cy_pin     = pairs[i].cy_pin;
        gpio_pin_t rp_mux_pin = pairs[i].rp_mux_and_pin;
        bool res;

        // Check for not connected pins
        if (rp_mux_pin == NC) continue;

        // Set multiplexer pin
        uint8_t rp_pin = PIN(rp_mux_pin);
        uint8_t rp_mux = PORT(rp_mux_pin);
        gpio_rp.gpioWrite(18, rp_mux);

        // Test MSP pin as output
        /////////////////////////
        printf("Testing GPIO %2d (mux %d) as output ... ", rp_pin, rp_mux);
        gpio_cy.gpioMode(cy_pin, GPIO::INPUT );
        gpio_rp.gpioMode(rp_pin, GPIO::OUTPUT);

        gpio_rp.gpioWrite(rp_pin,   true);
        gpio_cy.gpioWrite(LED_RED, true);
        res = gpio_cy.gpioRead(cy_pin);
        if (res != true) {
            errors++;
            printf(" FAIL(H)");
        }

        gpio_rp.gpioWrite(rp_pin,   false);
        gpio_cy.gpioWrite(LED_RED, false);
        res = gpio_cy.gpioRead(cy_pin);
        if (res != false) {
            errors++;
            printf(" FAIL(L)");
        }
        printf("\n");

        // Test MSP pin as input
        /////////////////////////
        printf("Testing GPIO %2d (mux %d) as input ... ", rp_pin, rp_mux);
        gpio_rp.gpioMode(rp_pin, GPIO::INPUT);
        gpio_cy.gpioMode(cy_pin, GPIO::OUTPUT);

        gpio_cy.gpioWrite(cy_pin,   true);
        gpio_cy.gpioWrite(LED_GREEN, true);
        res = gpio_rp.gpioRead(rp_pin);
        if (res != true) {
            errors++;
            printf(" FAIL(H)");
        }

        gpio_cy.gpioWrite(cy_pin,   false);
        gpio_cy.gpioWrite(LED_GREEN, false);
        res = gpio_rp.gpioRead(rp_pin);
        if (res != false) {
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

