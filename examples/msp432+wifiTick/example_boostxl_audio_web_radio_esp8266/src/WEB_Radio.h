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
#define FIFO_SIZE (40*1024)

class WEB_Radio {
public:

    WEB_Radio();

    void setup( void );
    void loop ( void );

private:
    //////////////////////
    // WiFiClient stuff //
    //////////////////////
    WiFiClient    client;
    FIFO<uint8_t> fifo;
    unsigned char buffer[TMP_BUFF_SIZE];

    /////////////////////
    // SPI Slave stuff //
    /////////////////////
    uint8_t   spiBuffer[4096];
    uint8_t * spiBufferPtr;
    void      setSpiBuffer();

    ///////////////
    // I2C stuff //
    ///////////////
    gpio_esp8266_pin sda;
    gpio_esp8266_pin scl;
    i2c_device       i2c;

    uint16_t sendSize;  // number of byte to send
//    char metaData[320]; // ICY metadata buffer
};

#endif // _WEB_RADIO_H_
