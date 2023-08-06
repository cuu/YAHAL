#ifndef _USB_DEVICE_RP2040_H_
#define _USB_DEVICE_RP2040_H_

#include "usb_dcd_interface.h"
#include "usb_endpoint_rp2040.h"

extern "C" {
void USBCTRL_IRQ_Handler(void);
};

class usb_device_rp2040 : public usb_dcd_interface {
public:

    void init() override;
    void pullup_enable() override;
    void pullup_disable() override;
    void irq_enable() override;
    void irq_disable() override;
    void set_address(uint8_t addr) override;

    void set_setup_handler(function<void(usb_setup_packet * packet)> h) override {
        _setup_handler = h;
    }
    void set_bus_reset_handler(function<void()> h) override {
        _bus_reset_handler = h;
    }

    friend void USBCTRL_IRQ_Handler(void);

private:
    static function<void(usb_setup_packet * packet)> _setup_handler;
    static function<void()> _bus_reset_handler;
};

#endif
