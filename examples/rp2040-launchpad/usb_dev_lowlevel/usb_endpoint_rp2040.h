

#ifndef TUPP_USB_ENDPOINT_RP2040_H_
#define TUPP_USB_ENDPOINT_RP2040_H_

class usb_interface;

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

    bool start_transfer(uint8_t * buffer, uint16_t len, bool blocking = true) override;

    void enable_endpoint(bool b) override;

    void send_stall() override;

    void send_zlp_data1() override;

private:
    usb_endpoint_rp2040(uint8_t  addr,
                        USB::ep_attributes_t  type,
                        uint16_t packet_size = 64,
                        uint8_t  interval    = 0,
                        usb_interface * interface = nullptr);

    EP_CONTROL_t *        _endp_ctrl;
    EP_BUFFER_CONTROL_t * _buff_ctrl;

    uint8_t *             _hw_buffer;
    uint16_t              _hw_buffer_size;
    static uint8_t *      _next_free_buffer;

    uint8_t *             _data_ptr{};
    uint16_t              _data_len{};
    uint8_t *             _current_ptr{};
    uint16_t              _current_len{};
    uint16_t              _bytes_left{};

    bool                  _active{};

    inline void _process_buffer() {
        // Dispatch request according endpoint direction
        if (is_IN()) handle_buffer_in();
        else         handle_buffer_out();
    }
    void handle_buffer_in();
    void handle_buffer_out();
    void trigger_transfer(uint16_t len);
};

#endif  // TUPP_USB_ENDPOINT_RP2040_H_
