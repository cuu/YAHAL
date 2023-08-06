#ifndef _USB_DEVICE_DRIVER_H_
#define _USB_DEVICE_DRIVER_H_

#include "usb_dcd_interface.h"
#include "usb_endpoint_interface.h"

class usb_device_driver {
public:
    explicit usb_device_driver(usb_dcd_interface & driver);

    inline bool configured() { return _configured; }

private:

    usb_endpoint_interface * EP0_IN;
    usb_endpoint_interface * EP0_OUT;

    void usb_handle_device_descriptor(usb_setup_packet * pkt);
    void usb_handle_config_descriptor(usb_setup_packet * pkt);
    void usb_handle_string_descriptor(usb_setup_packet * pkt);

    usb_dcd_interface & _dcd;
    uint8_t _new_addr;
    bool    _should_set_address;
    volatile bool    _configured;
};


#endif
