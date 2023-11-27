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
#ifndef TUPP_USB_MSC_BOT_DEVICE_H
#define TUPP_USB_MSC_BOT_DEVICE_H

#include "usb_msc_common.h"
#include "scsi_common.h"
#include "usb_configuration.h"
#include "usb_interface.h"
#include "usb_endpoint.h"
#include "usb_device_controller.h"
#include "usb_config.h"
#include <array>

class usb_msc_bot_device {
public:
    usb_msc_bot_device(usb_device_controller & controller,
                       usb_configuration     & configuration);

    void handle_request();

    // Callback handlers
    std::function<void(uint16_t & block_size, uint32_t & block_count)> capacity_handler;
    std::function<void(uint8_t * buff, uint32_t block)> read_handler;
    std::function<void(uint8_t * buff, uint32_t block)> write_handler;
    std::function<void(bool read, bool write)> activity_handler;

private:

    enum class state_t : uint8_t {
        RECEIVE_CBW = 0,
        DATA_READ   = 1,
        DATA_WRITE  = 2,
        SEND_CSW    = 3
    };

    // CDC ACM descriptor tree
    usb_configuration &         _configuration;
    usb_interface               _interface  {_configuration};

    // USB endpoints
    usb_endpoint *              _ep_in  {nullptr};
    usb_endpoint *              _ep_out {nullptr};

    uint8_t                     _max_lun;

    state_t                     _state;
    MSC::csw_t                  _csw;

    // Internal data buffers
    volatile uint16_t           _buffer_out_len;
    uint8_t                     _buffer_out[TUPP_MSC_BLOCK_SIZE];
    uint8_t                     _buffer_in [TUPP_MSC_BLOCK_SIZE];

    SCSI::inquiry_response_t    _inquiry_response;
    SCSI::read_capacity_10_response_t _read_capacity_10_response;
    SCSI::read_format_capacity_10_response_t _read_format_capacity_10_response;
    SCSI::mode_sense_6_response_t _mode_sense_6_response;

    void process_scsi_command();

    // Data transfer parameters
    uint16_t                    _blocks_to_transfer;
    uint16_t                    _blocks_transferred;
    uint32_t                    _block_addr;
};

#endif  // TUPP_USB_MSC_BOT_DEVICE_H
