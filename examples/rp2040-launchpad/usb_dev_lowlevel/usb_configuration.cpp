#include "usb_configuration.h"
#include "usb_strings.h"
#include <cassert>

using namespace USB;

usb_configuration::usb_configuration()
: descriptor{}, interfaces{nullptr}, associations{nullptr} {
    descriptor.bLength         = sizeof(configuration_descriptor_t);
    descriptor.bDescriptorType = bDescriptorType_t::DESC_CONFIGURATION;
    set_total_length();
}

void usb_configuration::set_Description(const char * n) {
    descriptor.iConfiguration = usb_strings::inst.add_string(n);
}

void usb_configuration::set_total_length() {
    // Start with our own descriptor
    uint16_t len = sizeof(configuration_descriptor_t);
    // Add all interface associations
    for (usb_interface_association *assoc : associations) {
        // Add all interface associations which are in use
        if (assoc && assoc->descriptor.bInterfaceCount) {
            len += sizeof(interface_association_descriptor_t);
        }
    }
    // Add all interfaces and their endpoints
    for (usb_interface *interf : interfaces) {
        if (interf) {
            len += interf->get_totalLength();
        }
    }
    descriptor.wTotalLength = len;
}

uint8_t usb_configuration::add_interface(usb_interface & interface) {
    int i = 0;
    for (i = 0; i < 5; ++i) {
        if (!interfaces[i]) {
            interfaces[i] = &interface;
            break;
        }
    }
    assert(i != 5);
    interface.set_parent(this);
    // Set the interface number in the interface
    interface.descriptor.bInterfaceNumber = i;
    // Set our own descriptor accordingly
    descriptor.bNumInterfaces = i + 1;
    set_total_length();
    return i;
}

void usb_configuration::add_interface_association(usb_interface_association &assoc) {
    int i = 0;
    for (i = 0; i < 5; ++i) {
        if (!associations[i]) {
            associations[i] = &assoc;
            break;
        }
    }
    assert(i != 5);
    assoc.set_parent(this);
    set_total_length();
}

void usb_configuration::activate_endpoints(bool b) {
    for (usb_interface *uif: interfaces) {
        if (uif) uif->activate_endpoints(b);
    }
}
