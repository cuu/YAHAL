#include "usb_endpoint_rp2040.h"
#include <cstring>
#include <cassert>
#include <cstdio>

uint8_t * usb_endpoint_rp2040::_next_free_buffer = (uint8_t *)&USBCTRL_DPRAM + 0x100;
usb_endpoint_interface * usb_endpoint_rp2040::endpoints[16][2] = { nullptr };

usb_endpoint_rp2040::usb_endpoint_rp2040(uint8_t  addr,
                                         uint8_t  transfer_type,
                                         uint16_t packet_size,
                                         uint8_t  interval) {

    // Align packet size to multiples of 64 byte
    if (packet_size & 0x3f) packet_size += 64;
    packet_size &= 0xffc0;

    // Set up descriptor
    descriptor.bLength          = sizeof(usb_endpoint_descriptor);
    descriptor.bDescriptorType  = USB_DT_ENDPOINT;
    descriptor.bEndpointAddress = addr;
    descriptor.bmAttributes     = transfer_type;
    descriptor.wMaxPacketSize   = packet_size;
    descriptor.bInterval        = interval;

    // Set Hardware registers
    uint8_t offset = (addr & 0x7f) << 1;
    bool    is_in  =  addr & 0x80;
    
    if (offset) {
        _endp_ctrl = (EP_CONTROL_t *)&USBCTRL_DPRAM + offset;
        if (!is_in) _endp_ctrl++;
    } else {
        _endp_ctrl = nullptr;
    }
    _buff_ctrl = (EP_BUFFER_CONTROL_t *)&USBCTRL_DPRAM.EP0_IN_BUFFER_CONTROL + offset;
    if (!is_in) _buff_ctrl++;

    // Set buffer address in DPRAM
    _buffer = _next_free_buffer;
    _next_free_buffer += packet_size;
    _buffer_size = packet_size;

    assert(_next_free_buffer <= (uint8_t *)&USBCTRL_DPRAM + 0x1000);
    // Set endpoint control register
    if (_endp_ctrl) {
        _endp_ctrl->BUFFER_ADDRESS     = (uint32_t)_buffer & 0xffff;
        _endp_ctrl->INTERRUPT_PER_BUFF = 1;
        _endp_ctrl->ENDPOINT_TYPE      = descriptor.bmAttributes;
        _endp_ctrl->ENABLE             = 1;
    }

    // Initial PID value
    _next_pid = 0;
    
    // Store this endpoint in lookup table
    usb_endpoint_rp2040::endpoints[addr & 0x0f][addr >> 7] = this;
}
    
void usb_endpoint_rp2040::process_buffer() {
    // Call user handler
    if (_handler) {
        _handler(_buffer, _buff_ctrl->LENGTH_0);
    }
}

void usb_endpoint_rp2040::start_transfer(uint8_t * buffer, uint16_t len) {

    assert(len <= _buffer_size);

    if (is_EP_IN()) {
        // Need to copy the data from the user buffer to the usb memory
        memcpy((void *) _buffer, (void *) buffer, len);
    }

    // Set pid and flip for next transfer
    _buff_ctrl->PID_0       = _next_pid;
    _buff_ctrl->FULL_0      = is_EP_IN();
    _buff_ctrl->LENGTH_0    = len;
    _buff_ctrl->AVAILABLE_0 = 1;
    _next_pid ^= 1;
}

void usb_endpoint_rp2040::set_handler(function<void(uint8_t * buffer, uint16_t len)> handler) {
    _handler = handler;
}

usb_endpoint_interface * usb_endpoint_rp2040::addr_to_ep(uint8_t addr) {
    return endpoints[addr & 0x0f][addr >> 7];
}

