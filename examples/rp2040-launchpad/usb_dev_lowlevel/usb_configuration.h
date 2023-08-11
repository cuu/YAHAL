#ifndef _USB_CONFIGURATION_H_
#define _USB_CONFIGURATION_H_

#include "usb_device.h"
#include "usb_interface.h"
#include "usb_interface_association.h"
#include "usb_common.h"
#include <array>

class usb_configuration {
public:
    usb_configuration();

    // Methods to modify the device descriptor
    inline void set_bConfigurationValue(uint8_t n) {
        descriptor.bConfigurationValue = n;
    }
    inline void set_bmAttributes(USB::conf_attr_t n) {
        descriptor.bmAttributes = n;
    }
    inline void set_bMaxPower_mA(uint8_t n) {
        descriptor.bMaxPower = n/2;
    }
    void set_Description(const char *);

    void set_total_length();

    // The configuration descriptor
    USB::configuration_descriptor_t descriptor;

    // Storage for interfaces
    uint8_t add_interface(usb_interface & interface);
    std::array<usb_interface *, 5> interfaces;

    // Storage for interface associations
    void add_interface_association(usb_interface_association & function);
    std::array<usb_interface_association *, 5> associations;

    void activate_endpoints(bool b);
};

#endif
