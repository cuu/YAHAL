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

typedef uint8_t blockio_status_t;

namespace BLOCKIO {
    // Enum for return value of blockio operations
    enum result_t {
        OK     = 0, // 0: Successful
        ERROR  = 1, // 1: R/W Error
        WRPRT  = 2, // 2: Write Protected
        NOTRDY = 3, // 3: Not Ready
        PARERR = 4  // 4: Invalid Parameter
    };
    // Bit masks for device status
    const blockio_status_t NOINIT  = 0x01;
    const blockio_status_t NODISK  = 0x02;
    const blockio_status_t PROTECT = 0x04;
}

class block_io_interface {
public:
    // Initialize device and return status
    virtual blockio_status_t initialize() = 0;

    // Get current device status
    virtual blockio_status_t status() = 0;

    // Read in 'count' 512-byte blocks. Start reading at 'start_block'.
    // Store the data in buff, which has to point to a memory buffer
    // with at least 512 * count bytes size.
    virtual BLOCKIO::result_t readBlock(uint8_t* buff, uint32_t start_block,
                                        uint16_t count) = 0;

    // Write 'count' 512-byte blocks. Start storing at 'start_block'.
    // Read the data from buff, which has to point to a memory buffer
    // with at least 512 * count bytes size.
    virtual BLOCKIO::result_t writeBlock(const uint8_t* buff, uint32_t start_block,
                                         uint16_t count) = 0;

    // Get the block count (total size of device is 512 * count bytes)
    virtual uint32_t getBlockCount() = 0;

    // Sync the IO device (dirty buffers are written)
    virtual BLOCKIO::result_t sync() = 0;

protected:
    virtual ~block_io_interface() = default;
};

#endif // _BLOCK_IO_INTERFACE_H_

