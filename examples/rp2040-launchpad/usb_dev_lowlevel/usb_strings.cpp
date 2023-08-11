//
// Created by andreas on 05.08.23.
//

#include "usb_strings.h"
#include "usb_common.h"
#include <cassert>
#include <cstring>

using namespace USB;

usb_strings usb_strings::inst;

// Add a new entry and return the index
// where the pointer was stored.
uint8_t usb_strings::add_string(const char * str) {
    int i=0;
    for (i=0; i < MAX_STRINGS; ++i) {
        if (!_strings[i]) {
            _strings[i] = str;
            return i;
        }
    }
    assert(i < MAX_STRINGS);
    return 0;
}

uint8_t usb_strings::prepare_buffer(uint8_t index, uint8_t * buffer) {
    assert(_strings[index]);
    // Every ascii char takes 2 bytes plus bLength and bDescriptorType
    uint8_t bLength = strlen(_strings[index]);
    if (index) bLength *= 2;
    bLength += 2;
    *buffer++ = bLength;
    *buffer++ = (uint8_t)bDescriptorType_t::DESC_STRING;
    const char *str = _strings[index];
    while (*str) {
        *buffer++ = *str++;
        if (index) *buffer++ = 0;
    }
    return bLength;
}
