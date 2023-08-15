#ifndef _USB_CALL_MGMT_FD_H_
#define _USB_CALL_MGMT_FD_H_

#include "usb_cdc_common.h"
#include "usb_functional_descriptor.h"

class usb_call_mgmt_fd : public usb_functional_descriptor {
public:
    usb_call_mgmt_fd();

    inline void set_bmCapabilities(USB::CDC::bmCmCapabilities_t val) {
        descriptor.bmCapabilities = val;
    }

    inline void set_bDataInterface(uint8_t val) {
        descriptor.bDataInterface = val;
    }

    USB::CDC::func_desc_cm_t    descriptor;
};


#endif //USB_DEV_LOWLEVEL_USB_HEADER_FD_H
