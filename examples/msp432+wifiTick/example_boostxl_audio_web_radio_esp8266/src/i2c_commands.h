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
// These are the I2C command numbers which
// are processed by the ESP8266 I2C soft slave.

#ifndef _I2C_COMMANDS_H_
#define _I2C_COMMANDS_H_

#include <cstdint>

const uint8_t I2C_COMMAND_SIZE = 9;

enum i2c_command {
    WLAN_SSID   = 0,
    WLAN_PASSWD = 1,
    HTTP_HOST   = 2,
    HTTP_PORT   = 3,
    HTTP_PATH   = 4,
    CONN_WLAN   = 5,
    CONN_SRV    = 6,
    READ_DATA   = 7,
    FIFO_SIZE   = 8
};

#endif // _I2C_COMMANDS_H_

