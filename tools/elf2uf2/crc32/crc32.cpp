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
#include "crc32.h"

uint32_t crc32::calculate(const uint8_t *data, size_t size) {
    uint32_t generatorPolynomial = 0xEDB88320; // Reverse of 0x04c11db7
    uint32_t remainderPolynomial = 0xFFFFFFFF;

    for (size_t i = 0; i < size; i++) {
        remainderPolynomial ^= rev_8(data[i]);
        for (int j = 0; j < 8; j++) {
            if (remainderPolynomial & 1) {
                remainderPolynomial = (remainderPolynomial >> 1) ^ generatorPolynomial;
            } else {
                remainderPolynomial >>= 1;
            }
        }
    }
    return rev_32(remainderPolynomial);
}

uint8_t crc32::rev_8(uint8_t b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

uint32_t crc32::rev_32(uint32_t b) {
    uint8_t b0 = rev_8(b >> 24);
    uint8_t b1 = rev_8(b >> 16);
    uint8_t b2 = rev_8(b >> 8);
    uint8_t b3 = rev_8(b);
    return (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
}
