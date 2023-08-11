#include "usb_configuration.h"
#include "usb_interface.h"
#include "usb_strings.h"
#include "usb_endpoint_interface.h"
#include <cassert>

using namespace USB;

usb_interface::usb_interface() : descriptor{}, function(nullptr), endpoints{nullptr} {
    descriptor.bLength = sizeof(interface_descriptor_t);
    descriptor.bDescriptorType = bDescriptorType_t::DESC_INTERFACE;
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
    if (_parent) _parent->set_total_length();
}

uint16_t usb_interface::get_totalLength() {
    uint16_t len = descriptor.bLength;
    for (usb_endpoint_interface * ep : endpoints) {
        if (ep) len += ep->descriptor.bLength;
    }
    return len;
}

void usb_interface::activate_endpoints(bool b) {
    for (usb_endpoint_interface * ep : endpoints) {
        if (ep) ep->enable_endpoint(b);
    }
}

void usb_interface::set_parent(usb_configuration *p) {
    _parent = p;
}

