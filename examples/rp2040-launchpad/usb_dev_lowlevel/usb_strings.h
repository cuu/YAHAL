//    _   _             _    _  _____ ____
//   | | (_)           | |  | |/ ____|  _ \   _     _
//   | |_ _ _ __  _   _| |  | | (___ | |_) |_| |_ _| |_
//   | __| | '_ \| | | | |  | |\___ \|  _ < _   _|_   _|
//   | |_| | | | | |_| | |__| |____) | |_) | |_|   |_|
//    \__|_|_| |_|\__, |\____/|_____/|____/
//                __/ |
//               |___/
//
// This file is part of tinyUSB++, C++ based and easy to
// use library for USB host/device functionality.
// (c) 2023 A. Terstegge  (Andreas.Terstegge@gmail.com)
//
#ifndef TUPP_USB_STRINGS_H_
#define TUPP_USB_STRINGS_H_

#include "usb_config.h"
#include <cstdint>
#include <array>

class usb_strings {
public:
    // This class is a simple singleton
    static usb_strings inst;

    // No copy, no assignment
    usb_strings (const usb_strings&) = delete;
    usb_strings& operator= (const usb_strings&) = delete;

    // Add a new string entry and return the index where the
    // pointer was stored. Index 0 is the language id (see
    // CTOR). The pointer should point to a static string,
    // e.g. a string literal.
    uint8_t add_string(const char * str);

    // Set up a USB buffer so that it conforms to a USB
    // string descriptor. The string to process is selected
    // by the index parameter. buffer has to point to an
    // allocated buffer, which has to have a minimum size
    // of strlen(string)*2+2. Two bytes are needed for
    // the descriptor length and type. Two bytes are needed
    // for every character (USB strings are UTF16).
    // Returns the total length of the constructed descriptor.
    uint8_t prepare_buffer(uint8_t index, uint8_t * buffer);

private:
    // Standard CTOR. It adds a default entry (index 0)
    // with the language descriptor (US english).
    usb_strings() : _strings{nullptr} {
        add_string("\x09\x04");
    }

    // Array to store pointers to the (static) strings
    std::array<const char *, TUPP_MAX_STRINGS> _strings;
};

#endif // TUPP_USB_STRINGS_H_
