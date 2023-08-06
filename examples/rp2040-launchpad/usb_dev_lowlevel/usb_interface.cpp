#include "usb_interface.h"
#include "usb_strings.h"
#include <cassert>

usb_interface::usb_interface() : descriptor{}, endpoints{nullptr} {
    descriptor.bLength = sizeof(usb_interface_descriptor);
    descriptor.bDescriptorType = USB_DT_INTERFACE;
}

void usb_interface::set_InterfaceName(const char * n) {
    descriptor.iInterface = usb_strings::inst.add_string(n);
}

void usb_interface::add_endpoint(usb_endpoint_interface & ep) {
    int i=0;
    for (i=0; i < 5; ++i) {
        if (!endpoints[i]) {
             endpoints[i] = &ep;
            break;
        }
    }
    assert(i != 5);
    descriptor.bNumEndpoints = i+1;
}

uint16_t usb_interface::get_totalLength() {
    uint16_t len = descriptor.bLength;
    for (usb_endpoint_interface * ep : endpoints) {
        if (ep) len += ep->descriptor.bLength;
    }
    return len;
}
