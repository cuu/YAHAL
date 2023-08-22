#include "usb_dcd_rp2040.h"
#include "usb_endpoint_rp2040.h"
#include <cstring>
#include <cassert>
#include <cstdio>

using namespace USB;

uint8_t * usb_endpoint_rp2040::_next_free_buffer = (uint8_t *)&USBCTRL_DPRAM + 0x180;

usb_endpoint_rp2040::usb_endpoint_rp2040(uint8_t  addr,
                                         ep_attributes_t transfer_type,
                                         uint16_t packet_size,
                                         uint8_t  interval,
                                         usb_interface * interface)
: usb_endpoint_interface(interface)
{
    // Align packet size to multiples of 64 byte
    if (packet_size & 0x3f) packet_size += 64;
    packet_size &= 0xffc0;

    // Set up descriptor
    set_bEndpointAddress(addr);
    set_bmAttributes    (transfer_type);
    set_wMaxPacketSize  (packet_size);
    set_bInterval       (interval);

    // Set Hardware registers
    uint8_t offset = (addr & 0x7f) << 1;

    if (offset) {
        _endp_ctrl = (EP_CONTROL_t *)&USBCTRL_DPRAM + offset;
        if (!is_IN()) _endp_ctrl++;
        // Set buffer address in DPRAM
        _hw_buffer = _next_free_buffer;
        _next_free_buffer += packet_size;
        _hw_buffer_size = packet_size;
        assert(_next_free_buffer <= (uint8_t *)&USBCTRL_DPRAM + 0x1000);
    } else {
        // Handle special case EP0
        _endp_ctrl = nullptr;
        _hw_buffer = (uint8_t *)&USBCTRL_DPRAM + 0x100;
        _hw_buffer_size = packet_size;
        assert(_hw_buffer_size == 64);
    }
    _buff_ctrl = (EP_BUFFER_CONTROL_t *)&USBCTRL_DPRAM.EP0_IN_BUFFER_CONTROL + offset;
    if (!is_IN()) _buff_ctrl++;

    // Set endpoint control register
    if (_endp_ctrl) {
        _endp_ctrl->BUFFER_ADDRESS     = (uint32_t)_hw_buffer & 0xffff;
        _endp_ctrl->INTERRUPT_PER_BUFF = 1;
        _endp_ctrl->ENDPOINT_TYPE      = (uint32_t)descriptor.bmAttributes;
        _endp_ctrl->ENABLE             = 0;
    }

    // Initial PID value
    next_pid = 0;

    // Store this endpoint in lookup table
    usb_dcd_rp2040::inst()._endpoints[addr & 0x0f][addr >> 7] = this;
}

bool usb_endpoint_rp2040::start_transfer(uint8_t * buffer, uint16_t len, bool blocking) {
    printf("Start transfer EP %02x len %d\n", descriptor.bEndpointAddress, len);
    // Mark this endpoint as active
    _active = true;
    // Store transfer parameters
    _data_ptr    = buffer;
    _data_len    = len;
    _current_ptr = buffer;
    _bytes_left  = len;
    // Trigger the transfer (in or out).
    // Limit size to max packet size.
    _current_len = len > descriptor.wMaxPacketSize ?
                   descriptor.wMaxPacketSize : len;
    // Trigger the transfer in HW.
    if (is_IN() && _current_len) {
        // Copy the data from user buffer to the HW buffer
        memcpy(_hw_buffer, _current_ptr, _current_len);
        // Update transfer parameters
        _bytes_left  -= _current_len;
        _current_ptr += _current_len;
    }
    trigger_transfer(_current_len);
    return true;
}

void usb_endpoint_rp2040::enable_endpoint(bool b) {
    printf("EP %2x enabled: %d\n", descriptor.bEndpointAddress, b);
    _endp_ctrl->ENABLE = b;
}

void usb_endpoint_rp2040::send_stall() {
    _buff_ctrl->STALL = 1;
}

void usb_endpoint_rp2040::send_zlp_data1() {
//    next_pid = 1;
    assert (next_pid == 1);
    start_transfer(nullptr, 0);
}

void usb_endpoint_rp2040::handle_buffer_in() {
    // Entering this method means that the hw controller
    // has sent a packet of data to the host.
    // Check if we need to change the hw address
    usb_dcd_rp2040::inst().check_address();
    // Check if the last packet has been sent
    if (!_bytes_left) {
        // Call user handler which will report the complete
        // data which was sent to the host. Deactivate the
        // endpoint before, because the handler might be used
        // to trigger a new transfer!
        _active = false;
        if (data_handler) {
            data_handler(_data_ptr, _data_len);
        }
        return;
    }
    // We need to send more data to the host. So prepare
    // a consecutive transfer. Limit the transfer size to
    // the maximum packet size.
    _current_len = _bytes_left > descriptor.wMaxPacketSize ?
                   descriptor.wMaxPacketSize : _bytes_left;
    // Copy the data from user buffer to the HW buffer
    memcpy(_hw_buffer, _current_ptr, _current_len);
    // Update transfer parameters
    _bytes_left  -= _current_len;
    _current_ptr += _current_len;
    // Finally trigger the transfer
    trigger_transfer(_current_len);
}

void usb_endpoint_rp2040::handle_buffer_out() {
    printf("EP %02x handle buffer out\n", descriptor.bEndpointAddress);

    // Entering this method means that the host has sent us a
    // new data packet. Copy all received bytes to the user buffer.
    uint16_t received_len = _buff_ctrl->LENGTH_0;
    memcpy(_current_ptr, _hw_buffer, received_len);
    // Update transfer parameters
    _bytes_left  -= received_len;
    _current_ptr += received_len;
    // We terminate the transfer if we either have received
    // all bytes or received a 'short' packet, which returned
    // fewer bytes as expected.
    if ((_bytes_left == 0) || (received_len < _current_len)) {
        // Let the user handler consume the complete
        // received data set.
        if (data_handler) {
            data_handler(_data_ptr, _data_len - _bytes_left);
        }
        _active = false;
        return;
    }
    // More bytes to receive, so trigger a new transfer.
    // Limit the transfer size to the maximum packet size.
    _current_len = _bytes_left > descriptor.wMaxPacketSize ?
                   descriptor.wMaxPacketSize : _bytes_left;
    // Finally trigger the transfer
    trigger_transfer(_current_len);
}

void usb_endpoint_rp2040::trigger_transfer(uint16_t len) {
//    printf("Trigger transfer EP %2x, len %d, next_pid %d\n",
//           descriptor.bEndpointAddress,len, next_pid);
    // Set pid and flip for next transfer
    _buff_ctrl->PID_0       = next_pid;
    _buff_ctrl->FULL_0      = is_IN();
    _buff_ctrl->LENGTH_0    = len;
    _buff_ctrl->AVAILABLE_0 = 1;
    next_pid ^= 1;
}

