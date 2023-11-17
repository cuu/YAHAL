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
// A simple example using a I2C interface of
// the MSP432. The I2C interface is used to
// directly read/write data to the OPT3001
// light sensor. The raw light value is printed
// on the backchannel uart.

#include "uart_rp2040.h"
#include "posix_io.h"
#include "i2c_rp2040.h"
#include "task.h"
#include <cstdio>

int main()
{
    // Initialize backchannel UART
    uart_rp2040 uart;
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    // Initialize I2C port
    i2c_rp2040 i2c(0, 24, 25, 0);
    i2c.setSpeed(400000); // Set speed to 100kHz

    uint8_t txbuf[3];
    uint8_t rxbuf[2];

    // Write the configuration register
    // of the OPT3001
    txbuf[0] = 0x01; // 0x01 = config register
    txbuf[1] = 0xce; // MSB (see data sheet)
    txbuf[2] = 0x10; // LSB (see data sheet)
    i2c.i2cWrite(0x44, txbuf, 3);

    // Set the register value to 0 (='Result')
    txbuf[0] = 0x00;
    i2c.i2cWrite(0x44, txbuf, 1);

    // Loop forever
    while(1) {
        // Read the current 'Result' value ...
        i2c.i2cRead(0x44, rxbuf, 2);
        uint16_t raw = (rxbuf[0] << 8) + rxbuf[1];
        // and show it on the console
        printf("Raw light value: %x\n", raw);
        task::sleep(500);
    }
}









