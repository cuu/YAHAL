/*
 * i2c_interface.h
 *
 *  Created on: 28.02.2016
 *      Author: Andreas Terstegge
 */

// generic interface for I2C communication


#ifndef _I2C_INTERFACE_H_
#define _I2C_INTERFACE_H_

#include <stdint.h>

namespace I2C {
enum i2c_mode { READ = 0x01, WRITE = 0x00 };
}

class i2c_interface {

  public:
    // Write len bytes from txbuf to I2C interface.
    // The number of bytes written is returned,
    // otherwise -1 in case of errors
    virtual int16_t write(uint8_t addr, uint8_t *txbuf, uint8_t len) = 0;

    // Read max. len bytes from I2C interface
    // The number of bytes read is returned,
    // otherwise -1 in case of errors
    virtual int16_t read (uint8_t addr, uint8_t *rxbuf, uint8_t len) = 0;

    // Perform 2 I2C opertions with only one 'stop'
    virtual void twice(uint8_t addr,
                       I2C::i2c_mode m1, uint8_t *buf1, uint8_t len1,
                       I2C::i2c_mode m2, uint8_t *buf2, uint8_t len2) = 0;

};

#endif // _I2C_INTERFACE_H_

