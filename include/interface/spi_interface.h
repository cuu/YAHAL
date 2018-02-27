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
//  interface for a simple SPI interface.
//  Currently only 8-bit transfers are supported.

#ifndef _SPI_INTERFACE_H_
#define _SPI_INTERFACE_H_

#include <stdint.h>

class spi_interface {
public:
    // Perform a combines read/write operation.
    // len bytes from txbuf are sent via SPI, and at
    // the same time rxbuf is filled with len bytes.
    // The number of bytes read/written is returned,
    // otherwise -1 in case of errors
    virtual int16_t transfer(uint8_t *txbuf, uint8_t *rxbuf, uint16_t len) = 0;

protected:
    virtual ~spi_interface() { }
};

#endif // _SPI_INTERFACE_H_

