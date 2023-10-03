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
#include "usb_msc_bot_device.h"
#include "usb_common.h"
#include <cstdio>
#include <cassert>
#include <cstring>
#include "machine/endian.h"

using namespace USB;
using enum USB::bInterfaceClass_t;
using enum USB::bInterfaceSubClass_t;
using enum USB::bInterfaceProtocol_t;
using enum USB::ep_attributes_t;
using enum USB::direction_t;
using enum SCSI::peripheral_device_type_t;
using enum SCSI::peripheral_qualifier_type_t;

usb_msc_bot_device::usb_msc_bot_device(
        usb_device_controller & controller,
        usb_configuration     & configuration)
:  _configuration(configuration), _max_lun(0), _state(state_t::RECEIVE_CBW), _buffer_out_len(0)
{
    // USB interface descriptor config
    //////////////////////////////////
    _interface.set_bInterfaceClass   (IF_CLASS_MSC);
    _interface.set_bInterfaceSubClass(IF_SUBCLASS_SCSI_TRANSPARENT);
    _interface.set_bInterfaceProtocol(IF_PROTOCOL_MSC_BOT);

    // USB endpoints
    ////////////////
    _ep_in  = controller.create_endpoint(_interface, DIR_IN,  TRANS_BULK);
    _ep_out = controller.create_endpoint(_interface, DIR_OUT, TRANS_BULK);

    // Prepare new request to receive data
    //////////////////////////////////////
    _ep_out->start_transfer(_buffer_out, 512);

    // Endpoint handlers
    ////////////////////
    _ep_out->data_handler = [&](uint8_t *, uint16_t len) {
//        printf("Data handler out %d\n", len);
        if (len) {
            // Stop incoming data
            _ep_out->send_NAK(true);
            // Sent length to signal new data
            _buffer_out_len = len;
        }
        // Trigger a new receive
        _ep_out->start_transfer(_buffer_out, 512);
    };

    _ep_in->data_handler = [&](uint8_t *, uint16_t len) {
//        printf("Data handler in %d\n", len);
        // Check if we have more data to send
//        for(len = 0; len < _ep_in->descriptor.wMaxPacketSize; ++len) {
//            if (!_transmit.get(_buffer_in[len])) {
//                break;
//            }
//        }
        // Trigger a new transmit
//        if (len) {
//            _ep_in->start_transfer(_data_in, len);
//        }
    };

    // Handler for CDC ACM specific requests
    ////////////////////////////////////////
    _interface.setup_handler = [&](USB::setup_packet_t *pkt) {
        switch(pkt->bRequest) {
            case bRequest_t::REQ_MSC_BOT_RESET: {
                printf("MSC_BBB_RESET\n");
                assert(pkt->wValue  == 0);
                assert(pkt->wLength == 0);
                break;
            }
            case bRequest_t::REQ_MSC_GET_MAX_LUN: {
                printf("GET_MAX_LUN\n");
                assert(pkt->wValue  == 0);
                assert(pkt->wLength == 1);
                controller._ep0_in->start_transfer(&_max_lun, 1);
                // Status stage
                controller._ep0_out->send_zlp_data1();
                break;
            }
            default: {
                printf("Unsupported MSC command 0x%02x\n", (int)pkt->bRequest);
            }
        }
    };

    // Initialize SCSI inquiry response
    ///////////////////////////////////
    _inquiry_response.peripheral_device    = SBC_4_DIRECT_ACCESS;
    _inquiry_response.peripheral_qualifier = DEVICE_CONNECTED_TO_LUN;
    _inquiry_response.removable_media      = 1;
    _inquiry_response.version              = SCSI::version_t::NO_STANDARD;
    _inquiry_response.response_data_format = 2;
    _inquiry_response.hierarchical_support = 0;
    _inquiry_response.normal_aca_support   = 0;
    _inquiry_response.additional_length    = sizeof(SCSI::inquiry_response_t) - 5;
    _inquiry_response.protect              = 0;
    _inquiry_response.third_party_copy     = 0;
    _inquiry_response.access_controls_coordinator = 0;
    _inquiry_response.scc_support          = 0;
    _inquiry_response.multi_port           = 0;
    _inquiry_response.enclosure_services   = 0;
    _inquiry_response.command_queuing      = 0;
    std::strcpy((char *)_inquiry_response.vendor_id,   "FH AC");
    std::strcpy((char *)_inquiry_response.product_id,  "MSC DEVICE");
    std::strcpy((char *)_inquiry_response.product_rev, "1.0");
}

void usb_msc_bot_device::handle_request() {
    switch(_state) {
        case state_t::RECEIVE_CBW: {
            // Did we receive some data?
            if (_buffer_out_len) {
                // Create pointer to CBW
                MSC::cbw_t *cbw = (MSC::cbw_t *) _buffer_out;

//                printf("*** NEW COMMAND ***\n");
//                printf("tag: %d\n", cbw->dCBWTag);
//                printf("len: %d\n", cbw->dCBWDataTransferLength);
//                printf("dir: %d\n", cbw->direction);
//                printf("cb len: %d\n",cbw->bCBWCBLength);
//                for(int i=0; i < cbw->bCBWCBLength; ++i) {
//                    printf("%02x ", cbw->CBWCB[i]);
//                }
//                printf("\n*******************\n");

                // Prepare the command status wrapper
                _csw.dCSWSignature   = MSC::csw_signature;
                _csw.dCSWTag         = cbw->dCBWTag;
                _csw.dCSWDataResidue = 0;
                _csw.bCSWStatus      = MSC::csw_status_t::CMD_PASSED;

                // Check size of data
                if ((_buffer_out_len    != sizeof(MSC::cbw_t)) ||
                    (cbw->dCBWSignature != MSC::cbw_signature)) {
                    // Prepare the command status wrapper
                    _csw.dCSWSignature   = MSC::csw_signature;
                    _csw.dCSWTag         = cbw->dCBWTag;
                    _csw.dCSWDataResidue = 0;
                    _csw.bCSWStatus      = MSC::csw_status_t::PHASE_ERROR;

                    _ep_out->send_NAK(false);
                    // Signal that data has been processed
                    _buffer_out_len = 0;
                    // Continue with sending the CSW
                    _state = state_t::SEND_CSW;
                    return;
                }

                process_scsi_command();

                _ep_out->send_NAK(false);
                // Signal that data has been processed
                _buffer_out_len = 0;
                // Continue with sending the CSW
                _state = state_t::SEND_CSW;
            }
            break;
        }
        case state_t::SEND_CSW: {
            printf("STATE: SEND_CSW\n");
            while (_ep_in->is_active()) ;
            _ep_in->start_transfer((uint8_t *)&_csw, sizeof(_csw));
            _state = state_t::RECEIVE_CBW;
            break;
        }
    }
}

void usb_msc_bot_device::process_scsi_command() {
    MSC::cbw_t       * cbw = (MSC::cbw_t *) _buffer_out;
    SCSI::scsi_cmd_t * cmd = (SCSI::scsi_cmd_t *)&cbw->CBWCB;

    switch(*cmd) {
        case SCSI::scsi_cmd_t::TEST_UNIT_READY: {
            printf("CMD: TEST UNIT READY\n");
            assert(cbw->bCBWCBLength           == sizeof(SCSI::test_unit_ready_t));
            assert(cbw->dCBWDataTransferLength == 0);
            break;
        }
        case SCSI::scsi_cmd_t::INQUIRY: {
            printf("CMD: INQUIRY\n");
            assert(cbw->bCBWCBLength           == sizeof(SCSI::inquiry_t));
            assert(cbw->dCBWDataTransferLength == sizeof(SCSI::inquiry_response_t));
            // Send the response
            while(_ep_in->is_active()) ;
            _ep_in->start_transfer((uint8_t *)&_inquiry_response, sizeof(SCSI::inquiry_response_t));
            break;
        }
        case SCSI::scsi_cmd_t::MODE_SENSE_6: {
            assert(cbw->bCBWCBLength           == sizeof(SCSI::mode_sense_6_t));
            _mode_sense_6_response.mode_data_length = 3;
            _mode_sense_6_response.medium_type      = 0;
            _mode_sense_6_response.write_protect    = 0;
            _mode_sense_6_response.block_descriptor_length = 0;
            // Send the response
            while(_ep_in->is_active()) ;
            _ep_in->start_transfer((uint8_t *)&_mode_sense_6_response, sizeof(SCSI::mode_sense_6_response_t));
            break;
        }
        case SCSI::scsi_cmd_t::READ_CAPACITY_10: {
            printf("CMD: READ CAPACITY 10\n");
            assert(cbw->bCBWCBLength           == sizeof(SCSI::read_capacity_10_t));
            assert(cbw->dCBWDataTransferLength == sizeof(SCSI::read_capacity_10_response_t));
            _read_capacity_10_response.logical_block_address = __htonl(capacity_handler());
            _read_capacity_10_response.block_length          = __htonl(512);
            // Send the response
            while(_ep_in->is_active()) ;
            _ep_in->start_transfer((uint8_t *)&_read_capacity_10_response, sizeof(SCSI::read_capacity_10_response_t));
            break;
        }
        case SCSI::scsi_cmd_t::READ_10: {
            printf("CMD: READ 10\n");
            assert(cbw->bCBWCBLength           == sizeof(SCSI::read_10_t));
            SCSI::read_10_t * read_cmd = (SCSI::read_10_t *)&cbw->CBWCB;
            uint16_t count = __ntohs(read_cmd->transfer_length);
            uint32_t block = __ntohl(read_cmd->logical_block_address);
            for (uint16_t i=0; i < count; ++i) {
                // Read data from device
                read_handler(_data_in, block+i);
                // Send the response
                while(_ep_in->is_active()) ;
                _ep_in->start_transfer(_data_in, 512);
            }
            break;
        }
        case SCSI::scsi_cmd_t::WRITE_10: {
            _buffer_out_len = 0;
            printf("CMD: WRITE 10\n");
            assert(cbw->bCBWCBLength == sizeof(SCSI::write_10_t));
            SCSI::read_10_t * write_cmd = (SCSI::read_10_t *)&cbw->CBWCB;
            uint16_t count = __ntohs(write_cmd->transfer_length);
            uint32_t block = __ntohl(write_cmd->logical_block_address);

            _ep_out->send_NAK(false);
//            _ep_out->start_transfer(_buffer_out, 512);

            for (uint16_t i=0; i < count; ++i) {
                while(_buffer_out_len == 0) ;
//                printf("_buffer_out_len %d\n", _buffer_out_len);
                assert(_buffer_out_len == 512);
                _buffer_out_len = 0;
                // Write data to device
                write_handler(_buffer_out, block+i);
                _ep_out->send_NAK(false);
            }
            break;
        }
    }
}



#if 0
printf("Data handler out %d\n", len);
MSC::cbw_t * cbw = (MSC::cbw_t *)buf;
printf("sig: %08x\n", cbw->dCBWSignature);
printf("tag: %08x\n", cbw->dCBWTag);
printf("len: %08x\n", cbw->dCBWDataTransferLength);
printf("dir: %d\n",   cbw->direction);
printf("lun: %d\n",   cbw->bCBWLUN);
printf("cb len: %d\n",cbw->bCBWCBLength);
for(int i=0; i < cbw->bCBWCBLength; ++i) {
printf("%02x ", cbw->CBWCB[i]);
}
printf("\n");
#endif
