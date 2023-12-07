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
#ifndef TUPP_USB_BOS_DEV_CAP_H_
#define TUPP_USB_BOS_DEV_CAP_H_

// Forward declarations (to prevent
// mutual inclusions of header files)
class usb_bos;

#include "usb_common.h"

class usb_bos_dev_cap {
public:
    explicit usb_bos_dev_cap(usb_bos & bos)
    : _bos{bos} { }

    // No copy, no assignment
    usb_bos_dev_cap(const usb_bos_dev_cap &) = delete;
    usb_bos_dev_cap & operator= (const usb_bos_dev_cap &) = delete;

    virtual uint16_t    get_bLength()  = 0;
    virtual uint8_t *   get_desc_ptr() = 0;

protected:

    // The binary object store (BOS) descriptor
    usb_bos &               _bos;
};

#endif  // TUPP_USB_BOS_DEV_CAP_H_
