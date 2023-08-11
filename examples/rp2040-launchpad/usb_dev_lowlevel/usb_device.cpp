#include "usb_configuration.h"
#include "usb_device.h"
#include "usb_strings.h"
#include <cassert>

usb_device::usb_device() : descriptor{}, configurations{nullptr} {
    descriptor.bLength         = sizeof(USB::device_descriptor_t);
    descriptor.bDescriptorType = USB::bDescriptorType_t::DESC_DEVICE;
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

usb_configuration * usb_device::find_configuration(uint8_t i) {
    for (usb_configuration * config : configurations) {
        if (config && config->descriptor.bConfigurationValue == i)
            return config;
    }
    assert(false);
    return nullptr;
}
