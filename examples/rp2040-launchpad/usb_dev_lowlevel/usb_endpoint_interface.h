#ifndef _USB_ENDPOINT_INTERFACE_H_
#define _USB_ENDPOINT_INTERFACE_H_

#include <stdint.h>
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

    inline bool is_EP_IN() { return descriptor.bEndpointAddress & 0x80; }

    static usb_endpoint_interface * addr_to_ep(uint8_t addr);

protected:
    virtual ~usb_endpoint_interface() = default;
};

#endif
