#ifndef _USB_INTERFACE_H_
#define _USB_INTERFACE_H_

#include "usb_endpoint_interface.h"
#include "usb_common.h"
#include <array>

class usb_interface {
public:
    usb_interface();

    inline void set_bInterfaceNumber  (uint8_t n) {
        descriptor.bInterfaceNumber   = n;
    }
    inline void set_bAlternateSetting (uint8_t n) {
        descriptor.bAlternateSetting  = n;
    }
    inline void set_bInterfaceClass   (uint8_t n) {
        descriptor.bInterfaceClass    = n;
    }
    inline void set_bInterfaceSubClass(uint8_t n) {
        descriptor.bInterfaceSubClass = n;
    }
    inline void set_bInterfaceProtocol(uint8_t n) {
        descriptor.bInterfaceProtocol = n;
    }

    void set_InterfaceName(const char * n);

    uint16_t get_totalLength();

    // The Interface descriptor
    usb_interface_descriptor descriptor;

    void add_endpoint(usb_endpoint_interface & ep);
    std::array<usb_endpoint_interface *, 5> endpoints;
};

#endif
