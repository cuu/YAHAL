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
//  This class models a I2C device with various registers.
//  It uses the soft_i2c_slave class for communication with
//  a I2C master. The registers control the ESP8266 part of
//  the WEB Radio. There are registers for the WLAN connection,
//  for the URL of the MP3 stream and command registers.

#ifndef _I2C_DEVICE_H_
#define _I2C_DEVICE_H_

#include "i2c_commands.h"
#include "gpio_interface.h"
#include "soft_i2c_slave.h"


class i2c_device
{
private:
    ///////////////////////
    // I2C register data //
    ///////////////////////
    struct i2c_reg {
        bool        writeable;  // true if register is writable
        uint16_t    size;       // size of the register in bytes
        uint8_t *   data;       // pointer to register data
    } _reg[I2C_COMMAND_SIZE] =
            {
             /* WLAN_SSID   */ { true,  80, nullptr }, // SSID of WLAN
             /* WLAN_PASSWD */ { true,  80, nullptr }, // Password of WLAN
             /* HTTP_HOST   */ { true,  80, nullptr }, // Host part of URL
             /* HTTP_PORT   */ { true,   2, nullptr }, // Port (typically 80)
             /* HTTP_PATH   */ { true,  80, nullptr }, // Path part of URL
             /* CONN_WLAN   */ { true ,  1, nullptr }, // Command to connect to WLAN
             /* CONN_SRV    */ { true,   1, nullptr }, // Command to connect to server
             /* READ_DATA   */ { true,   2, nullptr }, // Command to read a block of data
             /* FIFO_SIZE   */ { false,  2, nullptr }  // Return the current size of FIFO
            };
public:

    i2c_device( gpio_pin & sda,     // SDA gpio line
                gpio_pin & scl,     // SCL gpio line
                uint8_t i2c_addr,   // the I2C address
                bool pullup=false );// true to enable pullups on client side
    virtual ~i2c_device();

    // String getter
    ////////////////
    inline char* ssid()     { return (char *)_reg[WLAN_SSID  ].data; }
    inline char* passwd()   { return (char *)_reg[WLAN_PASSWD].data; }
    inline char* httpHost() { return (char *)_reg[HTTP_HOST  ].data; }
    inline char* httpPath() { return (char *)_reg[HTTP_PATH  ].data; }

    // Integer getter
    /////////////////
    inline int   httpPort() { return   _reg[HTTP_PORT].data[0] * 256
                                     + _reg[HTTP_PORT].data[1]; }
    inline int   readData() { return   _reg[READ_DATA].data[0] * 256
                                     + _reg[READ_DATA].data[1]; }
    // Integer setter
    /////////////////
    inline void  readData(uint16_t v){ _reg[READ_DATA].data[0] = v / 256;
                                       _reg[READ_DATA].data[1] = v % 256; }
    inline void  fifoSize(uint16_t v){ _reg[FIFO_SIZE].data[0] = v / 256;
                                       _reg[FIFO_SIZE].data[1] = v % 256; }
    // Boolean getter
    /////////////////
    inline char connectWLAN() { return _reg[CONN_WLAN].data[0]; }
    inline char connectSRV()  { return _reg[CONN_SRV ].data[0]; }

    // Boolean setter
    /////////////////
    inline void connectWLAN(uint8_t v) { _reg[CONN_WLAN].data[0] = v; }
    inline void connectSRV (uint8_t v) { _reg[CONN_SRV ].data[0] = v; }

private:
    // The I2C slave instance
    soft_i2c_slave _slave;

    // current register index
    uint8_t _reg_index;

    // soft_i2c_slave callback methods
    static bool    _receive (uint16_t index, uint8_t data, void * ptr);
    static uint8_t _transmit(uint16_t index, void * ptr);
    static void    _stop(void * ptr);
};

#endif // _I2C_DEVICE_H_
