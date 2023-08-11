#ifndef _USB_INTERFACE_H_
#define _USB_INTERFACE_H_

class usb_interface_association;
class usb_configuration;
class usb_endpoint_interface;

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
    inline void set_bInterfaceClass   (USB::bDeviceClass_t n) {
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

    void activate_endpoints(bool b);

    // The Interface descriptor
    USB::interface_descriptor_t descriptor;

    usb_interface_association * function;

    void add_endpoint(usb_endpoint_interface & ep);
    std::array<usb_endpoint_interface *, 5> endpoints;

    void set_parent(usb_configuration * p);

private:
    usb_configuration * _parent;
};

#endif
