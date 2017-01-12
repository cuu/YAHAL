//
// spi_interface.h
//
//  Created on: 28.02.2016
//      Author: Andreas Terstegge
//

#ifndef _SPI_INTERFACE_H_
#define _SPI_INTERFACE_H_

#include <stdint.h>

// generic interface for SPI communication

class spi_interface {

  public:

	// Perform a combines read/write operation.
    // len bytes from txbuf are sent via SPI, and at
    // the same time rxbuf is filled with len bytes.
    // The number of bytes read/written is returned,
    // otherwise -1 in case of errors
    virtual int16_t transfer(uint8_t *txbuf, uint8_t *rxbuf, uint16_t len) = 0;

};

#endif // _SPI_INTERFACE_H_

