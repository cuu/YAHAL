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
// This example shows how to control a WS2812-based LED stripe
// with the MSP432.
// The WS2812 codes a binary 0 or 1 with a high/low pulse, e.g.:
//
//  send binary 0:   signal is 400ns high, 850ns low
//  send binary 1:   signal is 800ns high, 450ns low
//
// The sum of the high and low pulse is 1250ns, which results
// in a 'bit'-frequency of 800kHz. Typically the high/low times
// have a tolerance of about 150ns, so timing is not that critical.
// The idea now is the following: To produce fast sequences of
// high-low pulses, we can use a SPI interface with a four-times
// higher frequency, e.g. 3MHz, which will mean that sending a
// single bits lasts 333ns. If we now send the bit pattern 1000
// or 1110 via this SPI interface, we get the following timing:
//
//  pattern 1000:   MOSI is  333ns high and 999ns low
//  pattern 1110:   MOSI is  999ns high and 333ns low
//
// The resulting timings are within the tolerance of the WS2812,
// so by sending a nibble 0x8 or 0xe, we can send a single bit
// to the WS2812. For a single LED we have to send 24 bits
// (3 bytes for red, green, blue), which means we have to store
// 24 nibbles = 12 bytes per LED. The following class manages
// the byte arrays needed for the SPI transmission.

#include <cstdlib>
#include "gpio_msp432.h"
#include "spi_msp432.h"
#include "yahal_assert.h"
#include "task.h"

class WS2812 {
public:
    // Create a WS2812 object for 'size' LEDs.
    // Use the SPI interface _spi
    WS2812(spi_interface & spi, int size)
        : _spi(spi), _size(size)
    {
        // Set clock speed of SPI interface
        _spi.setSpeed(3000000);
        // Do not generate CS signals (we don't need them...)
        _spi.setCS(true);
        // Allocate SPI send buffer
        _txbuff = new uint8_t[size * 12];
        // Initialize colors (set all LEDs to black)
        for (int i = 0; i < size; ++i) {
            setRGB(i, 0, 0, 0);
        }
        sendData();
    }

    // Set the color of LED with index 'i' (0 < i < size)
    // Color is specified with one byte for R, G and B.
    void setRGB(int led, int r, int g, int b)
    {
        yahal_assert(led < _size);
        // SPI values for  '00'  '01'  '10'  '11'
        char values[] = { 0x88, 0x8e, 0xe8, 0xee };
        for (int i = 0; i < 4; ++i)
        {
            _txbuff[3 - i + led * 12] = values[g & 0x3];
            _txbuff[7 - i + led * 12] = values[r & 0x3];
            _txbuff[11- i + led * 12] = values[b & 0x3];
            g >>= 2;
            r >>= 2;
            b >>= 2;
        }
    }

    void sendData() {
        // Send out data via SPI to control all LEDs!
        _spi.spiTx(_txbuff, _size * 12);
        // Make sure MOSI is low after transmission!
        uint8_t c = 0;
        _spi.spiTx(&c, 1);
    }

private:
    spi_interface & _spi;
    int             _size;
    uint8_t *       _txbuff;
};

int main() {
    // Define a CS pin for SPI
    // (this is only a dummy and not needed)
    gpio_msp432_pin cs(PORT_PIN(2,0));

    // Define the SPI interface
    // Here are the GPIO pins for the MOSI signal:
    //
    // Interface     MOSI
    // -------------+-----
    // EUSCI_A0_SPI  P1.3
    // EUSCI_A1_SPI  P2.3
    // EUSCI_A2_SPI  P3.3
    // EUSCI_A3_SPI  P9.7
    // EUSCI_B0_SPI  P1.6
    // EUSCI_B1_SPI  P6.4
    // EUSCI_B2_SPI  P3.6
    // EUSCI_B3_SPI  P10.2
    //
    // MOSI has to be connected to the IN signal
    // of the first LED
    spi_msp432 spi(EUSCI_B1_SPI, cs);

    // Create a new WS2812 controller
    WS2812 leds(spi, 11);

    int bright = 0;
    while (true)
    {
        // Get a random color
        int r = rand() % 50;
        int g = rand() % 50;
        int b = rand() % 50;
        // Set color of all LEDs
        for (int i=0; i < 11; ++i) {
            if (i == bright) {
                leds.setRGB(i, 255, 0, 0);
            } else {
                leds.setRGB(i, r, g, b);
            }
        }
        // Move bright LED
        bright++;
        if (bright == 11) bright = 0;
        // Send out data to LEDs
        leds.sendData();
        // Wait a while
        task::sleep_ms(200);
    }
}
