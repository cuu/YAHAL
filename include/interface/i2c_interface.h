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
//  This file defines a generic and abstract C++
//  interface for a I2C interface.

#ifndef _I2C_INTERFACE_H_
#define _I2C_INTERFACE_H_

#include <stdint.h>

class i2c_interface {
public:
    // Read max. len bytes from the I2C interface.
    // The number of bytes read is returned, or -1
    // case of errors. The last parameter specifies
    // if a I2C STOP condition is generated at the end.
    virtual int16_t i2cRead (uint16_t addr,
                             uint8_t *rxbuf, uint8_t len,
                             bool sendStop = true) = 0;

    // Write len bytes from txbuf to the I2C interface.
    // The number of bytes written is returned, or -1
    // in case of errors. The last parameter specifies
    // if a I2C STOP condition is generated at the end.
    virtual int16_t i2cWrite(uint16_t addr,
                             uint8_t *txbuf, uint8_t len,
                             bool sendStop = true) = 0;

    // Set the speed in Hz. Typical values are
    //  100000 (100 kHz),
    //  400000 (400 KHz) or
    // 1000000 (1 MHz)
    virtual void setSpeed(uint32_t Hz) = 0;

protected:
    virtual ~i2c_interface() = default;
};

#endif // _I2C_INTERFACE_H_

