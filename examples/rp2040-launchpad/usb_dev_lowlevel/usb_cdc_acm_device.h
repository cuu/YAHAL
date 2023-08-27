//    _   _             _    _  _____ ____
//   | | (_)           | |  | |/ ____|  _ \   _     _
//   | |_ _ _ __  _   _| |  | | (___ | |_) |_| |_ _| |_
//   | __| | '_ \| | | | |  | |\___ \|  _ < _   _|_   _|
//   | |_| | | | | |_| | |__| |____) | |_) | |_|   |_|
//    \__|_|_| |_|\__, |\____/|_____/|____/
//                __/ |
//               |___/
//
// This file is part of tinyUSB++, C++ based and easy to
// use library for USB host/device functionality.
// (c) 2023 A. Terstegge  (Andreas.Terstegge@gmail.com)
//
#ifndef TUPP_USB_CDC_ACM_DEVICE_H
#define TUPP_USB_CDC_ACM_DEVICE_H

#include "usb_cdc_common.h"
#include "usb_configuration.h"
#include "usb_device_controller.h"

#include "usb_interface.h"
#include "usb_interface_association.h"

#include "usb_fd_header.h"
#include "usb_fd_call_mgmt.h"
#include "usb_fd_acm.h"
#include "usb_fd_union.h"
#include <functional>
#include <utility>

class usb_cdc_acm_device {
public:
    usb_cdc_acm_device(usb_device_controller & controller,
                       usb_configuration & configuration);

    inline void set_receive_handler(std::function<void(uint8_t *,uint16_t)> h) {
        _receive_handler = std::move(h);
    }
    inline void set_line_coding_handler(std::function<void(uint8_t *,uint16_t)> h) {
        _line_coding_handler = std::move(h);
    }
    inline void set_control_line_handler(std::function<void(bool dtr, bool rts)> h) {
        _control_line_handler = std::move(h);
    }
    inline void set_break_handler(std::function<void(uint16_t)> h) {
        _break_handler = std::move(h);
    }

    inline void transmit(uint8_t *buf, uint16_t len) {
        _ep_data_in->start_transfer(buf, len);
    }

    // Read only version of line coding information
    const CDC::line_coding_t & line_coding;

private:
    // CDC ACM descriptor tree
    usb_configuration &         _configuration;
    usb_interface_association   _assoc       {_configuration};
    usb_interface               _if_ctrl     {_assoc};
    usb_interface               _if_data     {_assoc};
    usb_fd_header               _header_fd   {_if_ctrl};
    usb_fd_call_mgmt            _call_mgmt_fd{_if_ctrl};
    usb_fd_acm                  _acm_fd      {_if_ctrl};
    usb_fd_union                _union_fd    {_if_ctrl};
public:
    // USB endpoints
    usb_endpoint_interface *    _ep_ctrl_in  { nullptr };
    usb_endpoint_interface *    _ep_data_in  { nullptr };
    usb_endpoint_interface *    _ep_data_out { nullptr };
private:
    // Callback handlers
    std::function<void(uint8_t *,uint16_t)> _receive_handler;
    std::function<void(uint8_t *,uint16_t)> _line_coding_handler;
    std::function<void(bool dtr, bool rts)> _control_line_handler;
    std::function<void(uint16_t millis)> _break_handler;

    // Line coding information
    CDC::line_coding_t          _line_coding;

    // Internal data buffer
    uint8_t                     _buffer[64];
};

#endif  // TUPP_USB_CDC_ACM_DEVICE_H
