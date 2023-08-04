#ifndef _USB_DEVICE_RP2040_H_
#define _USB_DEVICE_RP2040_H_

#include "usb_device_interface.h"

class usb_device_rp2040 : public usb_device_interface {
public:

    usb_device_rp2040(const usb_device_descriptor & desc) : usb_device_interface(desc) {
    }

    void init() override;
    void pullup_enable() override;
    void pullup_disable() override;
    void irq_enable() override;
    void irq_disable() override;
    void set_address(uint8_t addr) override;
};

#endif
