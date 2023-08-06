#include "usb_configuration.h"
#include "usb_strings.h"
#include <cassert>

usb_configuration::usb_configuration() : descriptor{}, interfaces{nullptr} {
    descriptor.bLength         = sizeof(usb_configuration_descriptor);
    descriptor.bDescriptorType = USB_DT_CONFIG;
    descriptor.wTotalLength    = sizeof(usb_configuration_descriptor);
}

void usb_configuration::set_ConfigurationName(const char * n) {
    descriptor.iConfiguration = usb_strings::inst.add_string(n);
}

void usb_configuration::add_interface(usb_interface & interface) {
    int i = 0;
    for (i = 0; i < 5; ++i) {
        if (!interfaces[i]) {
            interfaces[i] = &interface;
            break;
        }
    }
    assert(i != 5);
    descriptor.bNumInterfaces = i + 1;
    descriptor.wTotalLength = sizeof(usb_configuration_descriptor);
    for (usb_interface *uif: interfaces) {
        if (uif) descriptor.wTotalLength += uif->get_totalLength();
    }
}
