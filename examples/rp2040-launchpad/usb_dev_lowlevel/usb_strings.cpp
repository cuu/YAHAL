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
#include "usb_strings.h"
#include "usb_common.h"
#include <cassert>
#include <cstring>
using namespace USB;

// The static singleton instance
usb_strings usb_strings::inst;

uint8_t usb_strings::add_string(const char * str) {
    int i=0;
    // Find free entry in array
    for (i=0; i < TUPP_MAX_STRINGS; ++i) {
        if (!_strings[i]) {
            // Store the pointer ...
            _strings[i] = str;
            // ... and return the index
            return i;
        }
    }
    // Make sure we found a free entry
    assert(i < TUPP_MAX_STRINGS);
    return 0;
}

uint8_t usb_strings::prepare_buffer(uint8_t index, uint8_t * buffer) {
    assert(_strings[index]);
    // Every ascii char takes 2 bytes plus bLength and bDescriptorType
    uint8_t bLength = strlen(_strings[index]);
    if (index) bLength *= 2;
    bLength += 2;
    // Store the descriptor length
    *buffer++ = bLength;
    // Store the descriptor type
    *buffer++ = (uint8_t)bDescriptorType_t::DESC_STRING;
    // Store the string in UTF16LE (except language id)
    const char *str = _strings[index];
    while (*str) {
        *buffer++ = *str++;
        // Add UTF16 fill-in byte only for index > 0, so
        // the language id is stored without modification.
        if (index) *buffer++ = 0;
    }
    return bLength;
}
