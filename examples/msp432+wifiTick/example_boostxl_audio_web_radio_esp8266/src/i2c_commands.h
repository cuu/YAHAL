#ifndef _I2C_COMMANDS_H_
#define _I2C_COMMANDS_H_

#include <cstdint>

const uint8_t I2C_COMMAND_SIZE = 8;

enum i2c_command {
    WLAN_SSID   = 0,
    WLAN_PASSWD = 1,
    HTTP_HOST   = 2,
    HTTP_PORT   = 3,
    HTTP_PATH   = 4,
    CONN_WLAN   = 5,
    CONN_SRV    = 6,
    DATA_SIZE   = 7
};

#endif // _I2C_COMMANDS_H_

