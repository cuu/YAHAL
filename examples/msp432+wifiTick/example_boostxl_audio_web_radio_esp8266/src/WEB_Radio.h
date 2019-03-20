#ifndef _WEB_RADIO_H_
#define _WEB_RADIO_H_

// I2C command definitions
#include "i2c_commands.h"

// Arduino includes
#include <WiFiClient.h>

// YAHAL includes
#include "gpio_esp8266.h"
#include "soft_i2c_slave.h"
//#include "lock_base_esp8266.h"
//#include "mutex.h"
#include "FIFO.h"

#define I2C_SLAVE_ADDR 0x55
#define TMP_BUFF_SIZE 1024
#define FIFO_SIZE (32*1024)

class WEB_Radio {
public:

    WEB_Radio();
    ~WEB_Radio();

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
//    bool    spiBufferFilled;
//    mutex<lock_base_esp8266> spiBufferMutex;
    void      setSpiBuffer();

    ////////////////
    // GPIO stuff //
    ////////////////
    gpio_esp8266_pin oneQuarter;
    gpio_esp8266_pin twoQuarters;
    gpio_esp8266_pin threeQuarters;
    inline void setGpios();

    ///////////////
    // I2C stuff //
    ///////////////
    gpio_esp8266_pin sda;
    gpio_esp8266_pin scl;
    soft_i2c_slave   i2c;

    struct i2c_cmd_struct {
        uint8_t len;
        char *  data;
    } i2c_cmd_data[I2C_COMMAND_SIZE];
    uint8_t  i2c_cmd;  // current command
    uint16_t sendSize; // nuber of byte to send

    // String getter
    inline char* ssid()     { return i2c_cmd_data[WLAN_SSID  ].data; }
    inline char* passwd()   { return i2c_cmd_data[WLAN_PASSWD].data; }
    inline char* httpHost() { return i2c_cmd_data[HTTP_HOST  ].data; }
    inline char* httpPath() { return i2c_cmd_data[HTTP_PATH  ].data; }

    // Integer getter
    inline int   httpPort() { return i2c_cmd_data[HTTP_PORT].data[0] * 256
                                   + i2c_cmd_data[HTTP_PORT].data[1]; }
    inline int   dataSize() { return i2c_cmd_data[DATA_SIZE].data[0] * 256
                                   + i2c_cmd_data[DATA_SIZE].data[1]; }
    // Boolean getter/setter
    inline char connectWLAN()   { return i2c_cmd_data[CONN_WLAN].data[0];     }
    inline void connectWLAN(uint8_t v) { i2c_cmd_data[CONN_WLAN].data[0] = v; }
    inline char connectSRV()    { return i2c_cmd_data[CONN_SRV ].data[0];     }
    inline void connectSRV(uint8_t v)  { i2c_cmd_data[CONN_SRV ].data[0] = v; }

    // I2C callback methods
    static bool    i2c_receive (uint16_t index, uint8_t data, void * ptr);
    static uint8_t i2c_transmit(uint16_t index, void * ptr);
    static void    i2c_stop    (void * ptr);
};

#endif // _WEB_RADIO_H_
