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
//  This class models a simple I2C device with
//  various registers. It uses the soft_i2c_slave
//  class for communication with a I2c master.

#ifndef _I2C_DEVICE_H_
#define _I2C_DEVICE_H_

#include "gpio_msp432.h"
#include "soft_i2c_slave.h"

class i2c_device
{
public:
    i2c_device(gpio_pin & sda, gpio_pin & scl, uint8_t i2c_addr, bool pullup);
    virtual ~i2c_device();

private:
    soft_i2c_slave  _slave;

    struct i2c_reg {
        bool        writeable;
        uint16_t    length;     // size of the register in bytes
        uint8_t *   data;
    };

    //////////////////
    // I2C register //
    //////////////////

    i2c_reg _reg[2] = { {false,  2, nullptr},    // small read-only id register
                        {true, 256, nullptr}  }; // data register


    // current register index
    uint8_t _reg_index;

    // soft_i2c_slave callback methods
    static bool    _receive (uint16_t index, uint8_t data, void * ptr);
    static uint8_t _transmit(uint16_t index, void * ptr);
    static void    _stop(void * ptr);
};

#endif // _I2C_DEVICE_H_
