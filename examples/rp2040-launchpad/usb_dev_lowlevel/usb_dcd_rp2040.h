//
// Created by andreas on 15.08.23.
//

#ifndef _USB_DCD_RP2040_H
#define _USB_DCD_RP2040_H

#include "usb_dcd_interface.h"
#include "usb_endpoint_rp2040.h"
//class usb_endpoint_rp2040;

#include "RP2040.h"
using namespace _USBCTRL_DPRAM_;
using namespace _USBCTRL_REGS_;
using namespace _RESETS_;

extern "C" {
void USBCTRL_IRQ_Handler(void);
};

class usb_dcd_rp2040 : public usb_dcd_interface {
public:

    friend class usb_endpoint_rp2040;
    friend void USBCTRL_IRQ_Handler(void);

    static usb_dcd_rp2040 & inst() {
        static usb_dcd_rp2040 _inst;
        return _inst;
    }

    void init();

    void pullup_enable(bool e) override;
    void irq_enable(bool e) override;
    void set_address(uint8_t addr) override;
    void reset_address() override;

    virtual void set_setup_handler(function<void(USB::setup_packet_t * packet)> handler) override {
        _setup_handler = handler;
    }

    virtual void set_bus_reset_handler(function<void()> handler) override {
        _bus_reset_handler = handler;
    }

    // Create a new endpoint based on its address.
    usb_endpoint_interface * create_endpoint(
            uint8_t         addr,
            ep_attributes_t type,
            uint16_t        packet_size,
            uint8_t         interval) override;

    // Create a new endpoint based on its direction.
    // The next free available address is used.
    usb_endpoint_interface * create_endpoint(
            direction_t     direction,
            ep_attributes_t type,
            uint16_t        packet_size,
            uint8_t         interval) override;

    inline usb_endpoint_interface * get_ep0_in()  override {
        return _ep0_in;
    }

    inline usb_endpoint_interface * get_ep0_out() override {
        return _ep0_out;
    }

private:
    usb_dcd_rp2040();

    usb_endpoint_rp2040 * _endpoints[16][2];

    usb_endpoint_interface * _ep0_in;
    usb_endpoint_interface * _ep0_out;

    uint8_t             _new_addr;
    bool                _should_set_address;

    function<void(USB::setup_packet_t * packet)> _setup_handler;
    function<void()> _bus_reset_handler;

    inline usb_endpoint_rp2040 * addr_to_ep(uint8_t addr) {
        return _endpoints[addr & 0x0f][addr >> 7];
    }

};

#endif //USB_DEV_LOWLEVEL_USB_DCD_RP2040_H
