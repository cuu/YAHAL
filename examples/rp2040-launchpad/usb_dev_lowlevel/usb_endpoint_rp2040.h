#ifndef _USB_ENDPOINT_RP2040_H_
#define _USB_ENDPOINT_RP2040_H_

#include "usb_endpoint_interface.h"

#include "RP2040.h"
using namespace _USBCTRL_DPRAM_;
using namespace _USBCTRL_REGS_;
using namespace _RESETS_;

extern "C" {
void USBCTRL_IRQ_Handler(void);
};

class usb_endpoint_rp2040 : public usb_endpoint_interface {
public:
    friend class usb_dcd_rp2040;
    friend void USBCTRL_IRQ_Handler(void);

    void start_transfer(uint8_t * buffer, uint16_t len) override;

    void set_handler(function<void(uint8_t * buffer, uint16_t len)>) override;

    void enable_endpoint(bool b) override;

    void send_stall() override;

    friend class usb_device_rp2040;
    friend class usb_endpoint_interface;

private:
    usb_endpoint_rp2040(uint8_t  addr,
                        USB::ep_attributes_t  type,
                        uint16_t packet_size = 64,
                        uint8_t  interval    = 0);

    EP_CONTROL_t *        _endp_ctrl;
    EP_BUFFER_CONTROL_t * _buff_ctrl;

    void process_buffer();

    uint8_t *             _buffer;
    uint16_t              _buffer_size;
    static uint8_t *      _next_free_buffer;

    void _process_buffer();

    function<void(uint8_t * buffer, uint16_t len)> _handler;
};

#endif
