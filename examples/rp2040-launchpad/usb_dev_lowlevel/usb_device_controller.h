#ifndef _USB_DEVICE_DRIVER_H_
#define _USB_DEVICE_DRIVER_H_

class usb_device;
#include "usb_dcd_interface.h"
#include "usb_endpoint_interface.h"

class usb_device_controller {
public:
    explicit usb_device_controller(usb_dcd_interface & driver, usb_device & device);

    inline bool active_configuration() { return _active_configuration; }

private:

    usb_endpoint_interface * EP0_IN;
    usb_endpoint_interface * EP0_OUT;

    void handle_set_address(USB::setup_packet_t * pkt);
    void handle_get_descriptor(USB::setup_packet_t * pkt);
    void handle_set_descriptor(USB::setup_packet_t * pkt);
    void handle_get_configuration(USB::setup_packet_t * pkt);
    void handle_set_configuration(USB::setup_packet_t * pkt);
    void handle_get_interface(USB::setup_packet_t * pkt);
    void handle_synch_frame(USB::setup_packet_t * pkt);
    void handle_set_interface(USB::setup_packet_t * pkt);
    void handle_get_status(USB::setup_packet_t * pkt);
    void handle_clear_feature(USB::setup_packet_t * pkt);
    void handle_set_feature(USB::setup_packet_t * pkt);

    usb_dcd_interface & _driver;
    usb_device &        _device;
    uint8_t             _new_addr;
    bool                _should_set_address;
    uint8_t             _active_configuration;
};


#endif
