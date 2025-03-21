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
// This is a demo for UART communication between
// the WifiTick board (ESP8266) and the MSP432 launchpad.
// The program does 2 things:
//
// - Send a messages via a the EUSCI_A3 UART, which is
//   connected to the ESP UART. The messages will have
//   lower-case letters, which in turn are converted to
//   upper case on the ESP side and sent back.
//
// - Implement a interrupt-driven message receiver, which
//   will receive all chars from the ESP UART until a '\n' is
//   received. The message is then printed to the
//   backchannel UART of the MSP432.
//

#include "posix_io.h"
#include "uart_msp432.h"
#include "gpio_msp432.h"
#include "task.h"
#include "yahal_String.h"
#include <cstdio>

int main(void)
{
    // The backchannel UART (default 115200 baud)
    uart_msp432 uart;
    // Register backchannel UART for printf etc.
    posix_io::inst.register_stdout( uart );

    // UART which is connected to the ESP8266
    uart_msp432 uart_esp(EUSCI_A3,115200);

    // Receive message handler:
    // All received chars are collected in a String.
    // When '\n' is received, the whole message is
    // printed out.
    String msg;
    uart_esp.uartAttachIrq([&](char c) {
        if (c == '\n') {
            printf("I received a message from ESP8266: %s\n", msg.c_str());
            msg.clear();
        } else {
            msg += c; // Add char to message
        }
    });

    // Reset the ESP8266
    gpio_msp432_pin esp_reset( PORT_PIN(10, 5) );
    esp_reset.gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
    task::sleep_ms(200);
    esp_reset.gpioWrite( HIGH );
    task::sleep_ms(200);

    // Endless loop which sends lower-case messages
    // to the ESP8266. The answers from ESP8266 are
    // printed in the receive message handler above!
    while (true) {
        uart_esp.puts("hello world!\n");
        task::sleep_ms(1000);
    }
    return 0;
}
