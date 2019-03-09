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
// the WifiTick board (ESP8266) and the MSP432 launchpad.
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

#include "uart_msp432.h"
#include "std_io.h"
#include "gpio_msp432.h"
#include "spi_msp432.h"

uart_msp432 uart; // default is backchannel UART!

void uart_esp_rx_handler(char c, void *) {
    // Forward any chars from the ESP8266 UART to the back channel UART
    // so we can see the debug messages from the ESP8266!
    uart.putc(c);
}

int main(void)
{
    std_io::inst.redirect_stdin ( uart );
    std_io::inst.redirect_stdout( uart );

    gpio_msp432_pin esp_reset( PORT_PIN(10, 5) );
    esp_reset.gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);

    // Initialize the UART which is connected to the ESP8266
    // and handle all incoming chars via an interrupt routine
    uart_msp432 uart_esp(EUSCI_A3,115200);
    uart_esp.uartAttachIrq(uart_esp_rx_handler, nullptr);

    // Initialize the SPI interface which is connected to the
    // ESP8266 and use the client mode on MSP432 side
    gpio_msp432_pin lcd_cs (PORT_PIN(10, 0));
    spi_msp432 spi(EUSCI_B3_SPI, lcd_cs, SPI::CLIENT);
    spi.setSpeed(250000);

    esp_reset.gpioWrite( HIGH );
    while (true) {

        uint8_t rxbuf[60];
        uint8_t txbuf[60];

        strcpy((char *)txbuf, "Hello from MSP432!! :)");
        // Send the message to the WifiTick-board
        spi.spiTxRx(txbuf, rxbuf, 60);
        // Print out what has been received from the ESP8266.
        // Due to the 1500ms delay in the ESP8266 sketch, the
        // message from the ESP8266 serial port is printed
        // 1500ms later, so the messages are not garbled.
        printf("MSP432  received: %s\n", (char*)rxbuf);
    }
    return 0;
}
