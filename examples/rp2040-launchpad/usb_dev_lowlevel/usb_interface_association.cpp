#include "usb_configuration.h"
#include "usb_interface_association.h"
#include "usb_strings.h"
#include <cassert>

using namespace USB;

usb_interface_association::usb_interface_association()
: descriptor{}, _parent(nullptr)  {
    descriptor.bLength         = sizeof(interface_association_descriptor_t);
    descriptor.bDescriptorType = bDescriptorType_t::DESC_INTERFACE_ASSOCIATION;
}

void usb_interface_association::set_FunctionName(const char * n) {
    descriptor.iFunction = usb_strings::inst.add_string(n);
}

void usb_interface_association::add_interface(usb_interface & interface) {
    uint8_t index = _parent->add_interface(interface);
    if (!descriptor.bInterfaceCount) {
        // First interface for this association
        descriptor.bFirstInterface = index;
        interface.function = this;
    }
    descriptor.bInterfaceCount++;
}

void usb_interface_association::set_parent(usb_configuration *p) {
    _parent = p;
}
