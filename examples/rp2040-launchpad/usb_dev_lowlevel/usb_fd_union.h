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
#ifndef TUPP_USB_FD_UNION_H_
#define TUPP_USB_FD_UNION_H_

#include "usb_cdc_common.h"
#include "usb_fd_base.h"

class usb_fd_union : public usb_fd_base {
public:
    explicit usb_fd_union(usb_interface & i);

    inline void set_bControlInterface(uint8_t val) {
        _descriptor.bControlInterface = val;
    }
    inline void set_bSubordinateInterface0(uint8_t val) {
        _descriptor.bSubordinateInterface0 = val;
    }

private:
    USB::CDC::func_desc_union_t _descriptor;
};

#endif // TUPP_USB_FD_UNION_H_
