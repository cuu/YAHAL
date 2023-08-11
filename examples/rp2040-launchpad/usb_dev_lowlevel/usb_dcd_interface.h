
#ifndef _USB_DCD_INTERFACE_H_
#define _USB_DCD_INTERFACE_H_

#include <functional>
using std::function;

#include "usb_common.h"

class usb_dcd_interface {
public:

    virtual void init() = 0;
    virtual void pullup_enable() = 0;
    virtual void pullup_disable() = 0;
    virtual void irq_enable() = 0;
    virtual void irq_disable() = 0;
    virtual void set_address(uint8_t addr) = 0;

    virtual void set_setup_handler(function<void(USB::setup_packet_t * packet)>) = 0;
    virtual void set_bus_reset_handler(function<void()>) = 0;

protected:
    virtual ~usb_dcd_interface() = default;
};

#endif // _USB_DCD_INTERFACE_H_
