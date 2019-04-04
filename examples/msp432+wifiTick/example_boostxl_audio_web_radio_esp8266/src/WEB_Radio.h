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

#ifndef _WEB_RADIO_H_
#define _WEB_RADIO_H_

// I2C deivce
#include "i2c_device.h"

// YAHAL includes
#include "gpio_esp8266.h"
#include "FIFO.h"

// Arduino includes
#include <WiFiClient.h>

#define I2C_SLAVE_ADDR 0x55
#define TMP_BUFF_SIZE 1024
#define FIFO_SIZE (32*1024)

class WEB_Radio {
public:

    WEB_Radio();

    void setup( void );
    void loop ( void );

private:
    //////////////////////
    // WiFiClient stuff //
    //////////////////////
    WiFiClient    _client;
    FIFO<uint8_t> _fifo;
    unsigned char _buffer[TMP_BUFF_SIZE];
    bool          _inHeader;
    int           _metaInt;
    int           _receivedBytes;

    /////////////////////
    // SPI Slave stuff //
    /////////////////////
    uint8_t   _spiBuffer[4096];
    uint8_t * _spiBufferPtr;
    void      setSpiBuffer();

    ///////////////
    // I2C stuff //
    ///////////////
    gpio_esp8266_pin _sda;
    gpio_esp8266_pin _scl;
    i2c_device       _i2c;
    uint16_t         _sendSize;  // number of byte to send

    void connect_to_WLAN();
    void connect_to_server();
    void stop_server();
};

#endif // _WEB_RADIO_H_
