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
// This file defines a generic and abstract C++
// interface for reading a bit stream. This
// functionality is e.g. used in drivers for
// graphic displays, when displaying characters
// from a specific font.

#ifndef _BITSTREAM_INTERFACE_H_
#define _BITSTREAM_INTERFACE_H_

class bitstream_interface {
public:
    // Get the next n bits out of a bit stream.
    // If n is 0 (or not given), the implementation
    // might return a default number of bits.
    // A maximum of 16 bits is return, which are
    // 'shifted in' from the LSB side.
    virtual uint16_t getNext(uint8_t n = 0) = 0;

protected:
    virtual ~bitstream_interface() { }
};

#endif // _BITSTREAM_INTERFACE_H_
