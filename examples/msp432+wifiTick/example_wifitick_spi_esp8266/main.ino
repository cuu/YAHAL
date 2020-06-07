////////////////////////////////////////////////////////////
// This is the test program which is running on the ESP8266.
// Use the WifiTick-Programmer to download this program
// to the WifiTick board!
////////////////////////////////////////////////////////

#include "Arduino.h"
#include "SPI.h"

void setup() {
    // Initialize the serial port
    Serial.begin(115200);

    // Initialize the SPI interface.
    // The ESP is the SPI master,
    // and running the SPI interface with 1MHz
    SPI.begin();
    SPI.setDataMode(SPI_MODE0);
    SPI.setBitOrder(MSBFIRST);
    SPI.setHwCs(true);
    SPI.setFrequency(250000);
}

void loop() {

    // Send/Receive buffers
    uint8_t txbuf[60];
    uint8_t rxbuf[60];

    // Fill in some data to send
    strcpy((char*)txbuf, "This is data from ESP8266!!");

    // Perform duplex SPI transfer
    SPI.transferBytes( txbuf, rxbuf, 60 );

    // Short delay so the printf message below
    // is not interfering with the MSP432 debug
    // output!
    delay(1500);

    // Print out received data
    Serial.print  ("ESP8266 received: ");
    Serial.println((const char *)rxbuf);

    delay(1500);
}

