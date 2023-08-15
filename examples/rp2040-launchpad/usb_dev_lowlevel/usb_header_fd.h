#ifndef _USB_HEADER_FD_H
#define _USB_HEADER_FD_H

#include "usb_cdc_common.h"
#include "usb_functional_descriptor.h"

class usb_header_fd : public usb_functional_descriptor {
public:
    usb_header_fd();

    inline void set_bcdCDC(uint16_t val) {
        descriptor.bcdCDC = val;
    }

    USB::CDC::func_desc_header_t    descriptor;
};


#endif //USB_DEV_LOWLEVEL_USB_HEADER_FD_H
