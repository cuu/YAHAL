#include "usb_device.h"
#include "usb_strings.h"
#include <cassert>

usb_device::usb_device() : descriptor{}, configurations{nullptr} {
    descriptor.bLength         = sizeof(usb_device_descriptor);
    descriptor.bDescriptorType = USB_DT_DEVICE;
}

void usb_device::set_Manufacturer(const char * n) {
    descriptor.iManufacturer = usb_strings::inst.add_string(n);
}

void usb_device::set_Product(const char * n) {
    descriptor.iProduct = usb_strings::inst.add_string(n);
}

void usb_device::set_SerialNumber(const char * n) {
    descriptor.iSerialNumber = usb_strings::inst.add_string(n);
}

void usb_device::add_configuration(usb_configuration & config) {
    int i=0;
    for (i=0; i < 5; ++i) {
        if (!configurations[i]) {
            configurations[i] = &config;
            break;
        }
    }
    assert(i != 5);
    descriptor.bNumConfigurations = i+1;
}

