#ifndef _USB_ENDPOINT_INTERFACE_H_
#define _USB_ENDPOINT_INTERFACE_H_

#include <cstdint>
#include <functional>
using std::function;

#include "usb_common.h"
using namespace USB;


class usb_endpoint_interface {
public:
    // The USB endpoint descriptor
    USB::endpoint_descriptor_t descriptor;

    // Start a transfer on this endpoint (data and status stage).
    // including data and status phases.
    virtual void start_transfer(uint8_t * buffer, uint16_t len) = 0;

    // Set the data handler associated to this endpoint
    virtual void set_handler(function<void(uint8_t * buffer, uint16_t len)>) = 0;

    virtual void enable_endpoint(bool b) = 0;

    virtual void send_stall() = 0;

    inline bool is_EP_IN() const {
        return descriptor.bEndpointAddress & 0x80;
    }

    // PID used for next transfer
    uint8_t next_pid;

protected:
    virtual ~usb_endpoint_interface() = default;
};

#endif
