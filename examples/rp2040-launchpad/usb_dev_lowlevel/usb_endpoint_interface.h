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
#ifndef TUPP_USB_ENDPOINT_INTERFACE_H_
#define TUPP_USB_ENDPOINT_INTERFACE_H_

#include "usb_interface.h"
#include "usb_endpoint_base.h"
#include <cstdint>

class usb_endpoint_interface : public usb_endpoint_base {
public:
    usb_endpoint_interface(usb_interface * interface) {
        if (interface) interface->add_endpoint(this);
    }

    // Start a transfer on this endpoint (data stage).
    virtual bool start_transfer(uint8_t * buffer, uint16_t len, bool blocking=true) = 0;

    // (De-)Activate this endpoint
    virtual void enable_endpoint(bool b) = 0;

    // Send a stall
    virtual void send_stall() = 0;

    // Send ZLP with DATA1
    virtual void send_zlp_data1() = 0;

    // PID used for next transfer
    uint8_t next_pid;

protected:
    virtual ~usb_endpoint_interface() = default;
};

#endif  // TUPP_USB_ENDPOINT_INTERFACE_H_
