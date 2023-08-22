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

#include "usb_endpoint_base.h"
#include "usb_interface.h"

usb_endpoint_base::usb_endpoint_base() : descriptor(_descriptor)
{
    // Set descriptor length
    _descriptor.bLength = sizeof(USB::endpoint_descriptor_t);
    // Set descriptor type
    _descriptor.bDescriptorType = USB::bDescriptorType_t::DESC_ENDPOINT;
}
