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
#ifndef ELF2UF2_CRC32_H
#define ELF2UF2_CRC32_H

#include <cstdint>
#include <memory>

class crc32 {
public:
    crc32() = delete;

    static uint32_t calculate(const uint8_t *data, size_t len);

private:
    static uint8_t rev_8(uint8_t b);

    static uint32_t rev_32(uint32_t b);

    static uint32_t poly8_lookup[256];
};

#endif //ELF2UF2_CRC32_H
