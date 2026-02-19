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
// This is an example program for the MFRC522
// driver in YAHAL. The original driver and
// documentation can be found here:
//
//   https://github.com/miguelbalboa/rfid
//
// There are also more examples in this project,
// which are written for the Arduino IDE (*.ino files).
// These examples can be easily converted to a real
// C/C++ program by copying all code in setup() to
// the beginning of main(), and putting the loop()
// code in an endless while(true) { ... } loop.
//
// The following code is the adapted version of the
// DumpInfo example (follow the above link and then
// -> Examples->DumpInfo).
// This program will print out the card information
// and contents when a tag or card is held near the
// reader.
// Further hints:
// After downloading the program, the reader is
// sometimes not propperly initialized. You might
// have to do a reset. The message from the UART
// should be someting like:
//
//    Firmware Version: 0x92 = v2.0
//
// Only if a propper firmware is detected, the card
// will work!
//
// Hardware configuration: The pins on the RFID-RC522
// module have the following names. The numbers are
// the RP2350 GPIO pins which have to be connected to
// the Launchpad (lower horizontal connector)!

#define SDA_PIN     5
#define SCK_PIN     6
#define MOSI_PIN    3
#define MISO_PIN    4
#define IRQ_PIN     18  // Currently not used
//      GND         -> connect to GND on the Launchpad
#define RST_PIN     7
//      3.3V        -> connect to 3V3 on the RP2350 Lauchpad
#include <cstdio>

#include "board.h"
#include "gpio_rp2350.h"
#include "task.h"
#include "posix_io.h"
#include "spi_rp2350.h"
#include "uart_rp2350.h"
#include "mfrc522_drv.h"

int main()
{
    // Set up UART
    uart_rp2350 uart;
    posix_io::inst.register_stdio(uart);

    // Set up a blinky LED
    gpio_rp2350 led(LED_RED_GPIO);
    led.gpioMode(GPIO::OUTPUT);

    // Set up the driver stack for the RFID board
    gpio_rp2350 cs ( SDA_PIN );
    spi_rp2350  spi( MISO_PIN, MOSI_PIN, SCK_PIN, cs);
    gpio_rp2350 rst( RST_PIN );
    mfrc522_drv mfrc522(spi, rst);

    // Initialize the RFID reader
    task::sleep_ms(100);
    mfrc522.PCD_Init();
    task::sleep_ms(100);
    // Show details of PCD - MFRC522 Card Reader details
    mfrc522.PCD_DumpVersionToSerial();

    printf("Scan PICC to see UID, SAK, type, and data blocks...");
    while(true) {
        // Skip if there is no card near
        if (!mfrc522.PICC_IsNewCardPresent()) continue;
        // Skip if we can not read the card
        if (!mfrc522.PICC_ReadCardSerial())   continue;
        // Dump debug info about the card
        // PICC_HaltA() is automatically called
        led = 1;
        mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
        led = 0;
    }
}
