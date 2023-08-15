//
// Created by andreas on 13.08.23.
//

#ifndef _USB_FUNCTIONAL_DESCRIPTOR_H_
#define _USB_FUNCTIONAL_DESCRIPTOR_H_

#include <cstdint>

class usb_functional_descriptor {
public:
    usb_functional_descriptor(uint8_t * ptr, uint16_t len)
    : descriptor(ptr), descriptor_length(len), next(nullptr) {}

    uint8_t * descriptor;
    uint16_t  descriptor_length;

    usb_functional_descriptor * next;
};


#endif // _USB_FUNCTIONAL_DESCRIPTOR_H_
