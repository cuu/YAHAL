#ifndef _USB_CONFIGURATION_H_
#define _USB_CONFIGURATION_H_

#include "usb_interface.h"
#include "usb_common.h"
#include <array>

class usb_configuration {
public:
    usb_configuration();

    inline void set_bConfigurationValue(uint8_t n) {
        descriptor.bConfigurationValue = n;
    }
    inline void set_bmAttributes(uint8_t n) {
        descriptor.bmAttributes = n;
    }
    inline void set_bMaxPower_mA(uint8_t n) {
        descriptor.bMaxPower = n/2;
    }

    void set_ConfigurationName(const char *);

    // The configuration descriptor
    usb_configuration_descriptor descriptor;

    void add_interface(usb_interface & interface);
    std::array<usb_interface *, 5> interfaces;
};

#endif
