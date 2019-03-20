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
//  This example demonstrates the software-based
//  implementations of a I2C master and a I2C slave
//  (soft_i2c_master and soft_i2c_slave).
//  To successfully run the example, you have to
//  connect the following GPIOs with two jumpers:
//
//     - P6.4 and P5.5 (the SDA lines)
//     - P6.5 and P5.4 (the SCL lines)
//
//  P6.4 and P6.5 are used by the I2C master, and
//  P5.5 and P5.4 by the I2C client.
//  Alternatively, the HW implementation of a I2C
//  master (EUSCI_B1) can be used to talk to the
//  soft_i2c_slave (it also uses P6.4 and P6.5).
//

#include <cstdint>
#include <cstring>
#include "uart_msp432.h"
#include "gpio_msp432.h"
#include "i2c_msp432.h"
#include "soft_i2c_master.h"
#include "i2c_device.h"
#include "String.h"

// Simple us-delay (assuming 48MHz clock)
void delay(uint32_t us) {
    for (uint32_t i=0; i < 2*us; ++i);
}

int main(void)
{
    // Use UART for text output
    uart_msp432 uart;

    uart.puts("\r\n\n");
    uart.puts("Software I2C master/slave test\r\n");
    uart.puts("==============================\r\n");
    uart.puts("Press Button S1 during startup to select HW I2C master!\r\n");

    // set up GPIOs for button and I2C master/slave
    gpio_msp432_pin button1( PORT_PIN(1,1));
    button1.gpioMode(GPIO::INPUT | GPIO::PULLUP);
    gpio_msp432_pin m_sda( PORT_PIN(6,4) );
    gpio_msp432_pin m_scl( PORT_PIN(6,5) );
    gpio_msp432_pin s_sda( PORT_PIN(5,5) );
    gpio_msp432_pin s_scl( PORT_PIN(5,4) );

    // create I2C master instance
    /////////////////////////////
    i2c_interface * master = nullptr;
    if (button1.gpioRead() == LOW) {
        // button pressed -> use hardware master
        uart.puts("Using HW I2C master (EUSCI_B1)\r\n");
        master = new i2c_msp432(EUSCI_B1);
        // HW master can operate up to 20kHz
        master->setSpeed(20000);
    } else {
        uart.puts("Using SW I2C master\r\n");
        master = new soft_i2c_master(m_sda, m_scl, delay, true);
        // SW master can run as fast as possible
        master->setSpeed(100000);
    }

    // create I2C slave instance for address 0x55
    /////////////////////////////////////////////
    i2c_device device(s_sda, s_scl, 0x55, true);

    // Check the ID register
    ////////////////////////
    uint8_t buffer_send[257];
    uint8_t buffer_recv[256];
    buffer_send[0] = 0;
    uart.puts("Trying to read ID register... ");
    master->i2cWrite(0x55, buffer_send, 1, false);
    master->i2cRead (0x55, buffer_recv, 2);
    if (buffer_recv[0] != 0xab || buffer_recv[1] != 0xcd) {
        uart.puts("FAILED!\r\n");
        uart.puts("Did you use the jumpers to connect master and slave?");
        while(1);
    }
    uart.puts("OK!\r\n");

    // Send and receive data
    ////////////////////////
    for (uint16_t val=0; val < 256; ++val) {
        // Fill the send buffer
        buffer_send[0] = 1; // Send to register 1
        for(uint16_t i=1; i <= 256; ++i) buffer_send[i] = val;
        // Send the data
        String msg = "Sending 256 bytes (0x" + to_String(val, 16) + ")...";
        uart.puts(msg.c_str());
        master->i2cWrite(0x55, buffer_send, 257);
        // Read back the data
        uart.puts("Reading back...");
        master->i2cRead(0x55, buffer_recv, 256);
        for(uint16_t i=0; i < 256; ++i) {
            if (buffer_recv[i] != val) {
                uart.puts("FAILURE");
                while(1);
            }
        }
        uart.puts(" OK!\r");
    }
    uart.puts("\n\nEnd of Test\r\n");
    return 0;
}
