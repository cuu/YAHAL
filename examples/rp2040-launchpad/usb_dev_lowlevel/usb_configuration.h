#ifndef _USB_CONFIGURATION_H_
#define _USB_CONFIGURATION_H_

#include "usb_interface.h"
#include "usb_common.h"

class usb_configuration {
public:
    // The configuration descriptor
    usb_configuration_descriptor descriptor;

    usb_configuration(const usb_configuration_descriptor & desc) : _interfaces{ nullptr} {
        descriptor = desc;
    }

    void add_interface(usb_interface & interface);
    
private:
    usb_interface * _interfaces[5];
};

#endif
