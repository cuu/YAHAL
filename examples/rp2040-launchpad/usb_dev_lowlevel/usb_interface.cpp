#include "usb_configuration.h"
#include "usb_interface.h"
#include "usb_strings.h"
#include "usb_endpoint_interface.h"
#include <cassert>

using namespace USB;

usb_interface::usb_interface()
: descriptor{}, function(nullptr), endpoints{nullptr},
  _func_desc(nullptr), _parent(nullptr) {
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
    // Start with size of own descriptor
    uint16_t len = descriptor.bLength;
    // Add size of all functional descriptors
    usb_functional_descriptor * fd = _func_desc;
    while (fd) {
        len += fd->descriptor_length;
        fd = fd->next;
    }
    // Add size of all endpoint descriptors
    for (usb_endpoint_interface * ep : endpoints) {
        if (ep) {
            len += ep->descriptor.bLength;
        }
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

void usb_interface::add_func_descriptor(usb_functional_descriptor & desc) {
     if (!_func_desc) {
         // First entry
         _func_desc = &desc;
     } else {
         usb_functional_descriptor *ptr = _func_desc;
         while (ptr->next) ptr = ptr->next;
         ptr->next = &desc;
     }
    if (_parent) _parent->set_total_length();
}
