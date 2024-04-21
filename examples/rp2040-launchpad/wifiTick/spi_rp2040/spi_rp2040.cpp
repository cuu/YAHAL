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
// This is a demo for SPI communication between
// the WifiTick board (ESP8266) and the RP2040 launchpad.
// The program does 2 things:
//
// - Forward any char which is received from the
//   ESP8266 uart to our backchannel uart, so we
//   can see messages from the ESP8266 on our terminal.
//
// - Send a message via a SPI interface to the ESP8266.
//   The mesage will be returned by the ESP8266 program.
//
//////////////////////// IMPORTANT //////////////////////////
// General hint:
// Make sure this program is running at 48MHz, because with
// lower frequencies, the SPI communication might loose data.
// The ESP8266 is the SPI master, and has a SPI clock rate
// of 1MHz. If the MSP is e.g. only running at 3MHz, it is
// too slow the get all the data via SPI!
/////////////////////////////////////////////////////////////

#include <cstring>
#include <cstdio>

#include "uart_rp2040.h"
#include "posix_io.h"
#include "gpio_rp2040.h"
#include "spi_rp2040.h"
#include "task.h"

int main(void)
{
    uart_rp2040 uart; // default is backchannel UART!
    posix_io::inst.register_stdin ( uart );
    posix_io::inst.register_stdout( uart );

    gpio_rp2040_pin esp_reset(6);
    esp_reset.gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);

    // Initialize the UART which is connected to the ESP8266
    // and handle all incoming chars via an interrupt routine
    uart_rp2040 uart_esp(1, 20, 21, 115200);

    // Forward any chars from the ESP8266 UART to the back channel UART
    // so we can see the debug messages from the ESP8266!
    uart_esp.uartAttachIrq([&](char c) { uart.putc(c); });

    // Initialize the SPI interface which is connected to the
    // ESP8266 and use the client mode on RP2040 side
    gpio_rp2040_pin cs (3);
    spi_rp2040 spi( 1, 8, 11, 10, cs);
    spi.setSpeed(250000);
    spi.generateCS(false);

    esp_reset.gpioWrite( HIGH );
    while (true) {
        uint8_t rxbuf[60];
        uint8_t txbuf[60];

        uint8_t minibuf[2];
        minibuf[0] = 0x03;
        minibuf[1] = 0x00;

        strcpy((char *)txbuf, "Hello from RP2040!! :)");
        // Send the message to the WifiTick-board
        cs.gpioWrite(LOW);
        spi.spiTx(minibuf, 2);
//        spi.spiTx(txbuf, 30);
        spi.spiRx(0, rxbuf, 10);
        cs.gpioWrite(HIGH);
        // Print out what has been received from the ESP8266.
        // Due to the 1500ms delay in the ESP8266 sketch, the
        // message from the ESP8266 serial port is printed
        // 1500ms later, so the messages are not garbled.
        printf("RP2040  received: %s\n", (char*)rxbuf);
        task::sleep_ms(2000);
    }
    return 0;
}
