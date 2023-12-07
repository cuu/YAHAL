//    _   _             _    _  _____ ____
//   | | (_)           | |  | |/ ____|  _ \   _     _
//   | |_ _ _ __  _   _| |  | | (___ | |_) |_| |_ _| |_
//   | __| | '_ \| | | | |  | |\___ \|  _ < _   _|_   _|
//   | |_| | | | | |_| | |__| |____) | |_) | |_|   |_|
//    \__|_|_| |_|\__, |\____/|_____/|____/
//                __/ |
//               |___/
//
// This file is part of tinyUSB++, C++ based and easy to
// use library for USB host/device functionality.
// (c) 2023 A. Terstegge  (Andreas.Terstegge@gmail.com)
//
#include "usb_device.h"
#include "usb_configuration.h"
#include "usb_strings.h"
#include <cassert>

usb_device::usb_device()
: descriptor(_descriptor), _descriptor{}, _configurations{nullptr}, _bos{nullptr}
{
    // Set descriptor length
    _descriptor.bLength = sizeof(USB::device_descriptor_t);
    // Set descriptor type
    _descriptor.bDescriptorType = USB::bDescriptorType_t::DESC_DEVICE;
}

void usb_device::set_Manufacturer(const char * n) {
    _descriptor.iManufacturer = usb_strings::inst.add_string(n);
}

void usb_device::set_Product(const char * n) {
    _descriptor.iProduct = usb_strings::inst.add_string(n);
}

void usb_device::set_SerialNumber(const char * n) {
    _descriptor.iSerialNumber = usb_strings::inst.add_string(n);
}

void usb_device::add_configuration(usb_configuration * config) {
    int i=0;
    // Find an empty slot
    for (i=0; i < TUPP_MAX_CONF_PER_DEVICE; ++i) {
        if (!_configurations[i]) {
             _configurations[i] = config;
            break;
        }
    }
    assert(i != TUPP_MAX_CONF_PER_DEVICE);
    // Set number of configurations in our own descriptor
    _descriptor.bNumConfigurations = i+1;
}

void usb_device::add_bos(usb_bos * bos) {
    // We may only add one BOS
    assert(!_bos);
    _bos = bos;
}

usb_configuration * usb_device::find_configuration(uint8_t i) {
    for (usb_configuration * config : _configurations) {
        if (config && config->descriptor.bConfigurationValue == i)
            return config;
    }
    assert(!"Configuration not found");
    return nullptr;
}
