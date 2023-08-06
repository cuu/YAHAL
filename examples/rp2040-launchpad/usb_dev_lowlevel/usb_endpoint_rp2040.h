#ifndef _USB_ENDPOINT_RP2040_H_
#define _USB_ENDPOINT_RP2040_H_

#include "usb_endpoint_interface.h"

#include "RP2040.h"
using namespace _USBCTRL_DPRAM_;
using namespace _USBCTRL_REGS_;
using namespace _RESETS_;

class usb_endpoint_rp2040 : public usb_endpoint_interface {
public:
    usb_endpoint_rp2040(uint8_t  addr,
                        uint8_t  type,
                        uint16_t packet_size = 64,
                        uint8_t  interval    = 0);
    
    void process_buffer() override;
    void start_transfer(uint8_t * buffer, uint16_t len) override;

    void set_handler(function<void(uint8_t * buffer, uint16_t len)>) override;

    friend class usb_endpoint_ctrl;

private:
    EP_CONTROL_t *        _endp_ctrl;
    EP_BUFFER_CONTROL_t * _buff_ctrl;

    uint8_t *             _buffer;
    uint16_t              _buffer_size;
    static uint8_t *      _next_free_buffer;

    function<void(uint8_t * buffer, uint16_t len)> _handler;

    static usb_endpoint_interface * endpoints[16][2];
};

#endif
