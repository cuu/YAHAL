#ifndef _USB_ENDPOINT_INTERFACE_H_
#define _USB_ENDPOINT_INTERFACE_H_

#include <cstdint>
#include <functional>
using std::function;

#include "usb_common.h"

class usb_endpoint_interface {
public:
    // The Endpoint descriptor
    usb_endpoint_descriptor descriptor;

    virtual void process_buffer() = 0;
    virtual void start_transfer(uint8_t * buffer, uint16_t len) = 0;

    virtual void set_handler(function<void(uint8_t * buffer, uint16_t len)>) = 0;

    inline bool is_EP_IN() const { return descriptor.bEndpointAddress & 0x80; }

    uint8_t next_pid;

protected:
    virtual ~usb_endpoint_interface() = default;
};

class usb_endpoint_ctrl {
public:
    static usb_endpoint_ctrl inst;

    usb_endpoint_interface * addr_to_ep(uint8_t addr);

    usb_endpoint_interface * create_endpoint(uint8_t  addr,
                                             uint8_t  type,
                                             uint16_t packet_size,
                                             uint8_t  interval);
private:
    usb_endpoint_ctrl() { }
};

#endif
