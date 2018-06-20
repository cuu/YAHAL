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
//  interface for all kinds low-level mass storages.
//  Single blocks of 512 bytes can be read and written.

#ifndef _BLOCK_IO_INTERFACE_H_
#define _BLOCK_IO_INTERFACE_H_

#include <stdint.h>

typedef uint8_t blockio_result_t;
typedef uint8_t blockio_status_t;

const blockio_result_t RES_OK     = 0;  // 0: Successful
const blockio_result_t RES_ERROR  = 1;  // 1: R/W Error
const blockio_result_t RES_WRPRT  = 2;  // 2: Write Protected
const blockio_result_t RES_NOTRDY = 3;  // 3: Not Ready
const blockio_result_t RES_PARERR = 4;  // 4: Invalid Parameter

const blockio_status_t STA_NOINIT  = 0x01; // Drive not initialized
const blockio_status_t STA_NODISK  = 0x02; // No medium in the drive
const blockio_status_t STA_PROTECT = 0x04; // Write protected


namespace BLOCKIO {
}

class block_io_interface {
public:

    virtual blockio_status_t initialize() = 0;
    virtual blockio_status_t status    () = 0;

    virtual blockio_result_t readBlock (uint8_t* buff, uint32_t block, uint16_t count) = 0;
    virtual blockio_result_t writeBlock(const uint8_t* buff, uint32_t block, uint16_t count) = 0;

    virtual uint32_t         getBlockCount() = 0;
    virtual blockio_result_t sync() = 0;

protected:
    virtual ~block_io_interface() = default;
};

#endif // _BLOCK_IO_INTERFACE_H_

