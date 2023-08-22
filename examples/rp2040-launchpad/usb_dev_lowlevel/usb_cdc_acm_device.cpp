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
#include "usb_cdc_acm_device.h"
#include "usb_common.h"
#include "usb_cdc_acm_device.h"
#include "usb_interface.h"
#include <cstdio>
#include <cassert>

using namespace USB;
using enum USB::bInterfaceClass_t;
using enum USB::bInterfaceSubClass_t;
using enum USB::bInterfaceProtocol_t;
using enum USB::ep_attributes_t;
using enum USB::direction_t;

usb_cdc_acm_device::usb_cdc_acm_device(
        usb_device_controller & controller,
        usb_configuration & configuration)
:   line_coding(_line_coding),
    _configuration(configuration)
{
    // USB interface association descriptor config
    //////////////////////////////////////////////
    _assoc.set_bFunctionClass   (CLASS_CDC);
    _assoc.set_bFunctionSubClass(CLASS_ABSTRACT_CONTROL_MODEL);
    _assoc.set_bFunctionProtocol(PROTOCOL_NONE);

    // USB interface descriptors config
    ///////////////////////////////////
    _if_ctrl.set_bInterfaceClass   (CLASS_CDC);
    _if_ctrl.set_bInterfaceSubClass(CLASS_ABSTRACT_CONTROL_MODEL);
    _if_ctrl.set_bInterfaceProtocol(PROTOCOL_NONE);

    _if_data.set_bInterfaceClass   (CLASS_CDC_DATA);
    _if_data.set_bInterfaceProtocol(PROTOCOL_NONE);

    // USB Functional Descriptors config
    ////////////////////////////////////
    _header_fd.set_bcdCDC(0x0120);

    _call_mgmt_fd.set_bmCapabilities({
        .handle_call_management         = 0,
        .call_management_via_data_class = 0,
        .reserved                       = 0
    });
    _call_mgmt_fd.set_bDataInterface(_if_data.descriptor.bInterfaceNumber);

    _acm_fd.set_bmCapabilities({
        .comm_feature_support           = 0,
        .line_coding_support            = 1,
        .send_break_support             = 1,
        .network_connection_support     = 0,
        .reserved                       = 0
    });

    _union_fd.set_bControlInterface     (_if_ctrl.descriptor.bInterfaceNumber);
    _union_fd.set_bSubordinateInterface0(_if_data.descriptor.bInterfaceNumber);

    // USB endpoints
    ////////////////
    _ep_ctrl_in  = controller.create_endpoint(_if_ctrl, DIR_IN,  TRANS_INTERRUPT, 64, 10);
    _ep_data_in  = controller.create_endpoint(_if_data, DIR_IN,  TRANS_BULK, 64, 0);
    _ep_data_out = controller.create_endpoint(_if_data, DIR_OUT, TRANS_BULK, 64, 0);

    // Prepare new request to receive data
    //////////////////////////////////////
    _ep_data_out->start_transfer(_buffer, 64, false);

    // Endpoint handler
    ///////////////////
    _ep_data_out->data_handler = [&](uint8_t *buf, uint16_t len){
        // Call user handler
        if (_receive_handler) _receive_handler(buf, len);
        // Trigger a new receive
        _ep_data_out->start_transfer(_buffer, 64, false);
    };

    // Handler for CDC ACM specific requests
    ////////////////////////////////////////
    _if_ctrl.setup_handler = [&](USB::setup_packet_t *pkt) {
        printf("Received CDC command 0x%02x\n", (int)pkt->bRequest);
        switch(pkt->bRequest) {
            case USB::bRequest_t::CDC_REQ_SET_LINE_CODING: {
                assert(pkt->wLength == sizeof(_line_coding) );
                controller._ep0_out->start_transfer((uint8_t *)&_line_coding, sizeof(_line_coding));
                // Call user handler
                if (_line_coding_handler) _line_coding_handler(_line_coding);
                // Status stage
                controller._ep0_in->send_zlp_data1();
                break;
            }
            case USB::bRequest_t::CDC_REQ_GET_LINE_CODING: {
                assert(pkt->wLength == sizeof(_line_coding) );
                controller._ep0_in->start_transfer((uint8_t *)&_line_coding, sizeof(_line_coding));
                // Status stage
                controller._ep0_out->send_zlp_data1();
                break;
            }
            case USB::bRequest_t::CDC_REQ_SET_CONTROL_LINE_STATE: {
                // Call user handler
                if (_control_line_handler) {
                    _control_line_handler(pkt->wValue & 0x0001,
                                          pkt->wValue & 0x0002);
                }
                // Status stage
                controller._ep0_in->send_zlp_data1();
                break;
            }
            case USB::bRequest_t::CDC_REQ_SEND_BREAK: {
                // Call user handler
                if (_break_handler) _break_handler(pkt->wValue);
                // Status stage
                controller._ep0_in->send_zlp_data1();
                break;
            }
            default: {
                printf("Unsupported CDC command 0x%02x\n", (int)pkt->bRequest);
            }
        }
    };
}
