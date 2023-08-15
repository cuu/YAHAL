#ifndef _USB_INTERFACE_ASSOCIATION_H_
#define _USB_INTERFACE_ASSOCIATION_H_

//#include "usb_configuration.h"

class usb_configuration;
#include "usb_interface.h"
#include "usb_common.h"
#include <array>

class usb_interface_association {
public:
    usb_interface_association();

    inline void set_bFunctionClass(USB::bInterfaceClass_t n) {
        descriptor.bFunctionClass = n;
    }
    inline void set_bFunctionSubClass(USB::bInterfaceSubClass_t  n) {
        descriptor.bFunctionSubClass = n;
    }
    inline void set_bFunctionProtocol(USB::bInterfaceProtocol_t n) {
        descriptor.bFunctionProtocol = n;
    }
    void set_FunctionName(const char *);

    uint8_t add_interface(usb_interface & interface);

    // The interface association descriptor
    USB::interface_association_descriptor_t descriptor;

    void set_parent(usb_configuration * p);

private:
    usb_configuration * _parent;
};

#endif
