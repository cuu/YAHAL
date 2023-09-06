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
#include "usb_device_controller.h"

#include "usb_device.h"
#include "usb_configuration.h"
#include "usb_interface.h"
#include "usb_interface_association.h"

#include "usb_common.h"
#include "usb_fd_base.h"
#include "usb_strings.h"

#include <cstring>
#include <cstdio>
#include <cassert>

using namespace USB;
using enum USB::bRequest_t;
using enum USB::bDescriptorType_t;
using enum USB::recipient_t;
using enum USB::ep_attributes_t;
using enum USB::direction_t;

usb_device_controller::usb_device_controller(usb_dcd_interface & driver, usb_device & device)
    : active_configuration(_active_configuration), _ep0_in(nullptr), _ep0_out(nullptr),
     _driver(driver), _device(device), _active_configuration(0), _buf{0}
{
    // Create standard endpoints 0. Since these are the first
    // two endpoints, address 0 will be used automatically
    _ep0_in  = _driver.create_endpoint(DIR_IN,  TRANS_CONTROL);
    _ep0_out = _driver.create_endpoint(DIR_OUT, TRANS_CONTROL);

    // These handlers are not necessary - only for debugging
//    _ep0_in->data_handler = [&](uint8_t *, uint16_t) {
//        printf("EP 80 IN handler - %d sent to host!!\n", len);
//    };
//    _ep0_out->data_handler = [](uint8_t *, uint16_t) {
//        printf("EP 00 OUT handler - %d received from host\n", len);
//    };

    ////////////////////////////
    // Handler for USB bus reset
    ////////////////////////////
    _driver.bus_reset_handler = [&]() {
        printf("BUS RESET\n");
        // Reset the USB address
        _driver.reset_address();
        // Deactivate configuration, if existing
        if (_active_configuration) {
            auto conf = _device.find_configuration(_active_configuration);
            if (conf) {
                conf->activate_endpoints(false);
            } else{
                printf("Could not deactivate configuration %d\n", _active_configuration);
            }
        }
        _active_configuration = 0;
    };

    /////////////////////////////
    // Handler for setup requests
    /////////////////////////////
    _driver.setup_handler = [&](USB::setup_packet_t *pkt) {
        // Reset PID to 1 for EP0
        _ep0_in->next_pid  = 1;
        _ep0_out->next_pid = 1;
        // Process standard requests
        if (pkt->bmRequestType.type == type_t::TYPE_STANDARD) {
            switch (pkt->bRequest) {
                // Device requests
                case REQ_SET_ADDRESS:
                    handle_set_address(pkt);
                    break;
                case REQ_GET_DESCRIPTOR:
                    handle_get_descriptor(pkt);
                    break;
                case REQ_SET_DESCRIPTOR:
                    handle_set_descriptor(pkt);
                    break;
                case REQ_GET_CONFIGURATION:
                    handle_get_configuration(pkt);
                    break;
                case REQ_SET_CONFIGURATION:
                    handle_set_configuration(pkt);
                    break;
                    // Interface requests
                case REQ_GET_INTERFACE:
                    handle_get_interface(pkt);
                    break;
                case REQ_SET_INTERFACE:
                    handle_set_interface(pkt);
                    break;
                    // Endpoint requests
                case REQ_SYNCH_FRAME:
                    handle_synch_frame(pkt);
                    break;
                    // Requests for different recipients
                case REQ_GET_STATUS:
                    handle_get_status(pkt);
                    break;
                case REQ_CLEAR_FEATURE:
                    handle_clear_feature(pkt);
                    break;
                case REQ_SET_FEATURE:
                    handle_set_feature(pkt);
                    break;
                default:
                    printf("Unknown standard setup request %d\n", (int)pkt->bmRequestType.type);
            }
        } else {
            // We received a non-standard request.
            // Find the proper destination and forward it.
            switch(pkt->bmRequestType.recipient) {
                case recipient_t::REC_DEVICE: {
                    if (_device.setup_handler) {
                        _device.setup_handler(pkt);
                    }
                    break;
                }
                case recipient_t::REC_INTERFACE: {
                    auto config = _device.find_configuration(_active_configuration);
                    if (config) {
                        auto interface = config->_interfaces[pkt->wIndex];
                        if (interface) {
                            if (interface->setup_handler) {
                                interface->setup_handler(pkt);
                            }
                        }
                    }
                    break;
                }
                case recipient_t::REC_ENDPOINT: {
                    auto ep = _driver.addr_to_ep(pkt->wIndex);
                    if (ep) {
                        if (ep->setup_handler) {
                            ep->setup_handler(pkt);
                        }
                    }
                    break;
                }
                default: {
                    printf("Could not find recipient %d\n", (int)pkt->bmRequestType.recipient);
                }
            }
        }
    };
}

void usb_device_controller::handle_set_address(setup_packet_t * pkt) {
    assert(pkt->bmRequestType.direction == direction_t::DIR_OUT);
    assert(pkt->bmRequestType.recipient == recipient_t::REC_DEVICE);
    assert(pkt->wIndex  == 0);
    assert(pkt->wLength == 0);
    _driver.set_address(pkt->wValue & 0xff);
    // Status stage
    _ep0_in->send_zlp_data1();
}

void usb_device_controller::handle_get_descriptor(setup_packet_t * pkt) {
    assert(pkt->bmRequestType.direction == direction_t::DIR_IN);
    assert(pkt->bmRequestType.recipient == recipient_t::REC_DEVICE);
    // Extract type and index
    uint8_t desc_index = pkt->wValue & 0xff;
    auto desc_type = (USB::bDescriptorType_t)(pkt->wValue >> 8);
    // Initialize data pointer
    uint8_t * tmp_ptr = _buf;
    switch (desc_type) {
        case DESC_DEVICE: {
            printf("DESC_DEVICE\n");
            assert(_device.descriptor.bLength <= pkt->wLength);
            _ep0_in->start_transfer((uint8_t *) &_device.descriptor, _device.descriptor.bLength);
            break;
        }
        case DESC_CONFIGURATION: {
            printf("DESC_CONF %d len %d\n", desc_index, pkt->wLength);
            auto conf = _device._configurations[desc_index];
            if (conf) {
                assert(pkt->wLength >= sizeof(configuration_descriptor_t));
                // Copy configuration descriptor first
                memcpy(tmp_ptr, &conf->descriptor, sizeof(configuration_descriptor_t));
                tmp_ptr += sizeof(configuration_descriptor_t);
                // Check if we need the big stuff
                if (pkt->wLength >= conf->descriptor.wTotalLength) {
                    // Copy interface and endpoint descriptors
                    for (auto interface : conf->_interfaces) {
                        if (interface) {
                            // Process interface association
                            if (interface->_assoc_ptr) {
                                memcpy(tmp_ptr, &interface->_assoc_ptr->descriptor, sizeof(interface_association_descriptor_t));
                                tmp_ptr += sizeof(interface_association_descriptor_t);
                            }
                            // Process interface descriptor
                            memcpy(tmp_ptr, &interface->descriptor, sizeof(interface_descriptor_t));
                            tmp_ptr += sizeof(interface_descriptor_t);
                            // Process functional descriptors
                            if (interface->_fd_ptr) {
                                // Process Functional Descriptors
                                usb_fd_base * fd_ptr = interface->_fd_ptr;
                                while(fd_ptr) {
                                    memcpy(tmp_ptr, fd_ptr->descriptor, fd_ptr->descriptor_length);
                                    tmp_ptr += fd_ptr->descriptor_length;
                                    fd_ptr = fd_ptr->next;
                                }
                            }
                            // Process all endpoint descriptors
                            for (auto ep : interface->_endpoints) {
                                if (ep) {
                                    memcpy(tmp_ptr, &ep->descriptor, sizeof(endpoint_descriptor_t));
                                    tmp_ptr += sizeof(endpoint_descriptor_t);
                                }
                            }
                        }
                    }
                }
            }
            uint32_t len = (uint32_t)tmp_ptr - (uint32_t)_buf;
            assert(len <= pkt->wLength);
            _ep0_in->start_transfer(_buf, len);
            break;
        }
        case DESC_STRING: {
            printf("DESC_STRING\n");
            uint8_t index = pkt->wValue & 0xff;
            uint8_t len = usb_strings::inst.prepare_buffer(index, _buf);
            assert(len <= pkt->wLength);
            _ep0_in->start_transfer(_buf, len);
            break;
        }
        case DESC_OTG: {
            printf("DESC_OTG\n");
            _ep0_in->start_transfer(nullptr, 0);
            break;
        }
        case DESC_DEBUG: {
            printf("DESC_DEBUG\n");
            _ep0_in->start_transfer(nullptr, 0);
            break;
        }
        default:
            printf("Unknown GET_DESCRIPTOR %d\n", (int)desc_type);
            _ep0_in->start_transfer(nullptr, 0);
    }
    // Status stage
    _ep0_out->send_zlp_data1();
}

void usb_device_controller::handle_set_descriptor(setup_packet_t * pkt) {
    assert(pkt->bmRequestType.direction == direction_t::DIR_OUT);
    assert(pkt->bmRequestType.recipient == recipient_t::REC_DEVICE);
    // Status stage
    _ep0_in->send_zlp_data1();
}

void usb_device_controller::handle_get_configuration(USB::setup_packet_t *pkt) {
    assert(pkt->bmRequestType.direction == direction_t::DIR_IN);
    assert(pkt->bmRequestType.recipient == recipient_t::REC_DEVICE);
    _ep0_in->start_transfer((uint8_t *)(&_active_configuration), 1);
    // Status stage
    _ep0_out->send_zlp_data1();
}

void usb_device_controller::handle_set_configuration(USB::setup_packet_t *pkt) {
    assert(pkt->bmRequestType.direction == direction_t::DIR_OUT);
    assert(pkt->bmRequestType.recipient == recipient_t::REC_DEVICE);
    uint8_t index = pkt->wValue & 0xff;
    // Check if we change the configuration
    usb_configuration * conf = nullptr;
    if (_active_configuration != index) {
        // De-activate current configuration
        if (_active_configuration) {
            conf = _device.find_configuration(_active_configuration);
            if (conf) {
                conf->activate_endpoints(false);
                printf("Disabled configuration %d\n", _active_configuration);
            }
            _active_configuration = 0;
        }
        if (index) {
            conf = _device.find_configuration(index);
            if (conf) {
                conf->activate_endpoints(true);
                printf("Enabled configuration %d\n", index);
            }
            _active_configuration = index;
        }
    }
    // Status stage
    _ep0_in->send_zlp_data1();
}

void usb_device_controller::handle_get_interface(USB::setup_packet_t *pkt) {
    assert(pkt->bmRequestType.direction == direction_t::DIR_IN);
    assert(pkt->bmRequestType.recipient == recipient_t::REC_INTERFACE);
    uint8_t index = pkt->wIndex & 0xff;
    if (_active_configuration) {
        auto interface = _device._configurations[_active_configuration]->_interfaces[index];
        if (interface) {
            _ep0_in->start_transfer(&interface->_descriptor.bAlternateSetting, 1);
        }
    }
    // Status stage
    _ep0_out->send_zlp_data1();
}

void usb_device_controller::handle_set_interface(USB::setup_packet_t *pkt) {
    assert(pkt->bmRequestType.direction == direction_t::DIR_OUT);
    assert(pkt->bmRequestType.recipient == recipient_t::REC_INTERFACE);
    uint8_t index = pkt->wIndex & 0xff;
    if (_active_configuration) {
        auto interface = _device._configurations[_active_configuration]->_interfaces[index];
        if (interface) {
            interface->_descriptor.bAlternateSetting = pkt->wValue & 0xff;
        }
    }
    // Status stage
    _ep0_in->send_zlp_data1();
}

void usb_device_controller::handle_synch_frame(USB::setup_packet_t *pkt) {
    assert(pkt->bmRequestType.direction == direction_t::DIR_IN);
    assert(pkt->bmRequestType.recipient == recipient_t::REC_ENDPOINT);
    uint8_t addr = pkt->wIndex & 0xff;
    // Find endpoint and forward request
    auto ep = _driver.addr_to_ep(addr);
    if (ep) {
        if (ep->setup_handler) {
            ep->setup_handler(pkt);
        }
    }
}

void usb_device_controller::handle_get_status(USB::setup_packet_t * pkt) {
    assert(pkt->bmRequestType.direction == direction_t::DIR_IN);
    assert(pkt->wValue  == 0);
    assert(pkt->wLength == 2);
    uint16_t data;
    switch(pkt->bmRequestType.recipient) {
        case REC_DEVICE: {
            data = 0;
            break;
        }
        case REC_INTERFACE: {
            data = 0;
            break;
        }
        case REC_ENDPOINT: {
            data = 0;
            break;
        }
        default:
            printf("Unknown recipient of get status: %d\n", (int)pkt->bmRequestType.recipient);
    }
    // Send status
    _ep0_in->start_transfer((uint8_t *)&data, 2);
    // Status stage
    _ep0_out->send_zlp_data1();
}

void usb_device_controller::handle_clear_feature(USB::setup_packet_t *pkt) {
    assert(pkt->bmRequestType.direction == direction_t::DIR_IN);
    switch(pkt->bmRequestType.recipient) {
        case REC_DEVICE: {
            break;
        }
        case REC_ENDPOINT: {
            break;
        }
        default:
            printf("Unknown recipient of clear feature: %d\n", (int)pkt->bmRequestType.recipient);
    }
    // Status stage
    _ep0_out->send_zlp_data1();
}

void usb_device_controller::handle_set_feature(USB::setup_packet_t *pkt) {
    assert(pkt->bmRequestType.direction == direction_t::DIR_IN);
    switch(pkt->bmRequestType.recipient) {
        case REC_DEVICE: {
            break;
        }
        case REC_ENDPOINT: {
            break;
        }
        default:
            printf("Unknown recipient of set feature: %d\n", (int)pkt->bmRequestType.recipient);
    }
    // Status stage
    _ep0_out->send_zlp_data1();
}
