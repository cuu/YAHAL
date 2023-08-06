
#ifndef _USB_STRINGS_H
#define _USB_STRINGS_H

#include <cstdint>
#include <array>

#define MAX_STRINGS 10

class usb_strings {
public:
    static usb_strings inst;

    // Add a new entry and return the index
    // where the pointer was stored.
    uint8_t add_string(const char * str);

    // Set up a USB buffer with data for string
    uint8_t prepare_buffer(uint8_t index, uint8_t * buffer);

private:
    usb_strings() : _strings{nullptr} {
        // Add the language descriptor at index 0
        // language id = us english
        add_string("\x09\x04");
    }

    std::array<const char *, MAX_STRINGS> _strings;
};

#endif // _USB_STRINGS_H
