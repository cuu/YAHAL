#ifndef _USB_INTERFACE_H_
#define _USB_INTERFACE_H_

#include "usb_endpoint_interface.h"
#include "usb_common.h"
#include <cassert>

class usb_interface {
public:
    // The Interface descriptor
    usb_interface_descriptor descriptor;

    usb_interface(const usb_interface_descriptor & desc) : _endpoints{ nullptr} {
        descriptor = desc;
    }
    
    void add_endpoint(usb_endpoint_interface & ep);
    
private:
    usb_endpoint_interface * _endpoints[5];
};

#endif
