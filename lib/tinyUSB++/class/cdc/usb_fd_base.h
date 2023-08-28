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
#ifndef TUPP_USB_FD_BASE_H_
#define TUPP_USB_FD_BASE_H_

class usb_interface;
#include <cstdint>

class usb_fd_base {
public:
    usb_fd_base(usb_interface & i, uint8_t * ptr, uint16_t len)
    : descriptor(ptr), descriptor_length(len), next(nullptr), _parent(i) {}

    // No copy, no assignment
    usb_fd_base (const usb_fd_base &) = delete;
    usb_fd_base & operator= (const usb_fd_base &) = delete;

    uint8_t * descriptor;
    uint16_t  descriptor_length;

    usb_fd_base * next;

protected:
    usb_interface & _parent;
};

#endif // TUPP_USB_FD_BASE_H_
