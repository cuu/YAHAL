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
#ifndef TUPP_USB_ENDPOINT_BASE_H
#define TUPP_USB_ENDPOINT_BASE_H

#include "usb_common.h"
#include <functional>

class usb_endpoint_base {
public:
    usb_endpoint_base();

    // No copy, no assignment
    usb_endpoint_base(const usb_endpoint_base &) = delete;
    usb_endpoint_base & operator= (const usb_endpoint_base &) = delete;

    // Methods to set the descriptor elements
    inline void set_bEndpointAddress(uint8_t n) {
        _descriptor.bEndpointAddress = n;
    }
    inline void set_bmAttributes(USB::ep_attributes_t n) {
        _descriptor.bmAttributes = n;
    }
    inline void set_wMaxPacketSize(uint16_t n) {
        _descriptor.wMaxPacketSize = n;
    }
    inline void set_bInterval(uint8_t n) {
        _descriptor.bInterval = n;
    }

    // Return true if this endpoint is an IN-endpoint
    inline bool is_IN() const {
        return descriptor.bEndpointAddress & 0x80;
    }

    // Read-only version of our descriptor
    const USB::endpoint_descriptor_t & descriptor;

    // The data handler which is called when data from
    // the host has arrived or data was sent to the host
    std::function<void(uint8_t * buffer, uint16_t len)> data_handler;

    // The setup message handler which handles all
    // commands directed to this endpoint. Will be
    // called by the usb_device_controller.
    std::function<void(USB::setup_packet_t * packet)> setup_handler;

private:
    // The configuration descriptor
    USB::endpoint_descriptor_t _descriptor;
};

#endif // TUPP_USB_ENDPOINT_BASE_H
