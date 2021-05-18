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
// Example showing how to operate the OPT3001
// with interrupts. GPIO 4.6 is connected to
// the (open drain) IRQ output of the OPT3001.
// GPIO 4.6 is configured to generate a interrupt
// on falling edges. The handler then reads and
// prints the raw light value, and resets the
// IRQ line by reading the config register.
// Find details of the OPT3001 IRQ generation
// in the OPT3001 data sheet.

#include "gpio_msp432.h"
#include "uart_msp432.h"
#include "posix_io.h"
#include "i2c_msp432.h"
#include <cstdio>

int main(void)
{
    i2c_msp432      opt3001( EUSCI_B1 );
    gpio_msp432_pin opt_irq( PORT_PIN(4,6) );

    uint8_t rxbuf[2];
    uint8_t txbuf[3];

    // Initialize backchannel UART
    uart_msp432 uart;
    posix_io::inst.register_stdout( uart );

    // Initialize GPIOs
    opt_irq.gpioMode(GPIO::INPUT);
    // Interrupt handler
    opt_irq.gpioAttachIrq(GPIO::FALLING, [&]() {
        // Read the Result register
        txbuf[0] = 0x00;
        opt3001.i2cWrite(0x44, txbuf, 1);
        opt3001.i2cRead (0x44, rxbuf, 2);
        uint16_t raw = (rxbuf[0] << 8) + rxbuf[1];
        printf("Raw light value: %x\n", raw);
        // Read the Configuration register
        // to reset the IRQ line
        txbuf[0] = 0x01;
        opt3001.i2cWrite(0x44, txbuf, 1);
        opt3001.i2cRead (0x44, rxbuf, 2);
    });

    // Reset OPT3001
    txbuf[0] = 0x06;
    opt3001.i2cWrite(0x00, txbuf, 1);

    // Write the 'Configuration'
    // (default is 0xc819)
    txbuf[0] = 0x01;
    txbuf[1] = 0xce; // MSB
    txbuf[2] = 0x10; // LSB
    opt3001.i2cWrite(0x44, txbuf, 3);

    // Write the 'LOW' register
    txbuf[0] = 0x02;
    txbuf[1] = 0xff;
    txbuf[2] = 0xff;
    opt3001.i2cWrite(0x44, txbuf, 3);

    while (1) {
        // Sleep until we receive a interrupt
        __WFE();
    }
}
