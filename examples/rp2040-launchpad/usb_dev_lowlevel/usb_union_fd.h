//
// Created by andreas on 13.08.23.
//

#ifndef USB_DEV_LOWLEVEL_USB_UNION_FD_H
#define USB_DEV_LOWLEVEL_USB_UNION_FD_H

#include "usb_cdc_common.h"
#include "usb_functional_descriptor.h"

class usb_union_fd : public usb_functional_descriptor {
public:
    usb_union_fd();

    inline void set_bControlInterface(uint8_t val) {
        descriptor.bControlInterface = val;
    }

    inline void set_bSubordinateInterface0(uint8_t val) {
        descriptor.bSubordinateInterface0 = val;
    }

    USB::CDC::func_desc_union_t   descriptor;
};


#endif //USB_DEV_LOWLEVEL_USB_UNION_FD_H
