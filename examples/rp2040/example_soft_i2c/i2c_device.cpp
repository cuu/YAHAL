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

#include <i2c_device.h>
#include <cstddef>

i2c_device::i2c_device(gpio_pin & sda, gpio_pin & scl,
                       uint8_t i2c_addr, bool pullup)
: _slave(sda, scl, pullup), _reg_index(0)
{
    // Set the I2C address, This will also
    // initialize the slave (GPIOs etc,)
    _slave.setI2cAddress(i2c_addr);

    // Allocate space for I2C registers
    for (size_t i=0; i < sizeof(_reg)/sizeof(i2c_reg); ++i) {
        _reg[i].data = new uint8_t[ _reg[i].length];
    }

    // Set a magic value in the ID register (reg 0)
    _reg[0].data[0] = 0xAB;
    _reg[0].data[1] = 0xCD;

    // Callback methods
    _receive = [this](uint16_t index, uint8_t data) -> bool {
        // process register address
        if (index == 0) {
            if (data < sizeof(_reg)/sizeof(i2c_reg)) {
                _reg_index = data;
                return true;
            } else {
                return false;
            }
        } else {
            // Check register index
            if (_reg_index >= sizeof(_reg)/sizeof(i2c_reg)) {
                return false;
            }
            // Check write access
            if (!_reg[_reg_index].writeable) {
                return false;
            }
            // Check data index
            if (index > _reg[_reg_index].length) {
                return false;
            }
            // Write the byte to register
            _reg[_reg_index].data[index-1] = data;
            return true;
        }
    };

    _transmit = [this](uint16_t index) -> uint8_t {
        if (_reg_index < sizeof(_reg)/sizeof(i2c_reg)  &&
            index < _reg[_reg_index].length) {
            return  _reg[_reg_index].data[index];
        }
        return 0;
    };

    _stop = [this]() -> void {
        // STOP condition is ignored. So we don't care if
        // communication uses I2C RESTART conditions, or
        // regular START-STOP sequences.
    };

    _slave.set_callbacks(_receive, _transmit, _stop);
}

i2c_device::~i2c_device() {
    // Free I2C registers space
    for (size_t i=0; i < sizeof(_reg)/sizeof(i2c_reg); ++i) {
        delete [] _reg[i].data;
    }
}
