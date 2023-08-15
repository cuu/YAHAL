//
// Created by andreas on 13.08.23.
//

#ifndef USB_DEV_LOWLEVEL_USB_ACM_FD_H
#define USB_DEV_LOWLEVEL_USB_ACM_FD_H

#include "usb_cdc_common.h"
#include "usb_functional_descriptor.h"

class usb_acm_fd : public usb_functional_descriptor {
public:
    usb_acm_fd();

    inline void set_bmCapabilities(USB::CDC::bmAcmCapabilities_t val) {
        descriptor.bmCapabilities = val;
    }

    USB::CDC::func_desc_acm_t   descriptor;
};



#endif //USB_DEV_LOWLEVEL_USB_ACM_FD_H
