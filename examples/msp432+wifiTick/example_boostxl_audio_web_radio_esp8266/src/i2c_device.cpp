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

#include "i2c_device.h"
#include <cstddef>
#include <cstring>

i2c_device::i2c_device(gpio_pin & sda, gpio_pin & scl, uint8_t i2c_addr, bool pullup)
: _slave(sda, scl, _receive, _transmit, _stop, this, pullup),
  _reg_index(0)
{
    // set the I2C address, This will also
    // initialize the slave (GPIOs etc,)
    _slave.setI2cAddress(i2c_addr);

    // Allocate and clear space for I2C registers
    for (size_t i=0; i < I2C_COMMAND_SIZE; ++i) {
        _reg[i].data = new uint8_t[ _reg[i].size ];
        memset(_reg[i].data, 0, _reg[i].size);
    }
}

i2c_device::~i2c_device() {
    // free I2C registers space
    for (size_t i=0; i < I2C_COMMAND_SIZE; ++i) {
        delete [] _reg[i].data;
    }
}

// Callback methods
///////////////////
bool i2c_device::_receive (uint16_t index, uint8_t data, void * ptr) {
    static uint8_t tmp[2];
    i2c_device * _this = (i2c_device *)ptr;
    // process first byte (register index)
    if (index == 0) {
        if (data < I2C_COMMAND_SIZE) {
            _this->_reg_index = data;
            return true;
        } else {
            return false;
        }
    } else {
        // Check register index
        if (_this->_reg_index < I2C_COMMAND_SIZE) {
            i2c_reg & reg = _this->_reg[_this->_reg_index];
            // Check write access and index size
            if (reg.writeable && index <= reg.size) {
                if (_this->_reg_index != READ_DATA) {
                    // Write the byte to register
                    reg.data[index-1] = data;
                } else {
                    // Make sure both bytes are written together, so the
                    // main loop does not get a wrong value
                    tmp[index-1] = data;
                    if (index == 2) {
                        reg.data[0] = tmp[0];
                        reg.data[1] = tmp[1];
                    }
                }
                return true;
            }
        }
    }
    return false;
}

uint8_t i2c_device::_transmit(uint16_t index, void * ptr) {
    i2c_device * _this = (i2c_device *)ptr;
    if (_this->_reg_index < I2C_COMMAND_SIZE) {
        i2c_reg & reg = _this->_reg[_this->_reg_index];
        if (index < reg.size) return reg.data[index];
    }
    return 0;
}

void i2c_device::_stop(void * ptr) {
    // STOP condition is ignored. So we don't care if
    // communication uses I2C RESTART conditions, or
    // regular START-STOP sequences.
}

