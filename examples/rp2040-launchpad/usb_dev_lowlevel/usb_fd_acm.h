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
#ifndef TUPP_USB_FD_ACM_H
#define TUPP_USB_FD_ACM_H

#include "usb_cdc_common.h"
#include "usb_fd_base.h"

class usb_fd_acm : public usb_fd_base {
public:
    explicit usb_fd_acm(usb_interface & i);

    // No copy, no assignment
    usb_fd_acm (const usb_fd_acm&) = delete;
    usb_fd_acm& operator= (const usb_fd_acm&) = delete;

    inline void set_bmCapabilities(USB::CDC::bmAcmCapabilities_t val) {
        _descriptor.bmCapabilities = val;
    }

private:
    USB::CDC::func_desc_acm_t _descriptor;
};

#endif // TUPP_USB_FD_ACM_H
