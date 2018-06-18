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
    // Perform a combines write/read operation.
    // len bytes from txbuf are sent via SPI, and at
    // the same time rxbuf is filled with len bytes.
    // The number of bytes read/written is returned,
    // otherwise -1 in case of errors
    virtual int16_t spiTxRx(const uint8_t *txbuf, uint8_t *rxbuf, uint16_t len) = 0;

    // Perform a write operation. len byte from txbuf are
    // send via SPI, and the received bytes are discarded.
    // The number of bytes written is returned, otherwise
    // -1 in case of errors
    virtual int16_t spiTx(const uint8_t *txbuf, uint16_t len) = 0;

    // Perform a read operation. len bytes with value txbyte
    // are sent, and the received values are stored in rxbuf.
    // The number of bytes read is returned, otherwise -1 in
    // case of errors
    virtual int16_t spiRx(uint8_t txbyte, uint8_t *rxbuf, uint16_t len) = 0;

    // Set the speed in Hz. Typical value is 1000000 (1 MHz)
    virtual void setSpeed(uint32_t Hz) = 0;

    // Enable/Disable hardware control of the CS line.
    virtual void useHwCS(bool val) = 0;

    // Control the CS line in case HwCs is set to false.
    virtual void setCS(bool val) = 0;

    // In SPI client mode, attach a RX handler which
    // is called for every received byte.
    virtual void spiAttachRxIrq(void (*)(uint8_t data)) = 0;

protected:
    virtual ~spi_interface() = default;
};

#endif // _SPI_INTERFACE_H_

