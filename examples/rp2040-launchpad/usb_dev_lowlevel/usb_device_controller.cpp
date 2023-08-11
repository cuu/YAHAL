#include "usb_common.h"
#include "usb_strings.h"

#include "usb_device.h"
#include "usb_configuration.h"
#include "usb_interface.h"

#include "usb_device_controller.h"
#include <cstring>
#include <cstdio>
#include <cassert>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

using namespace USB;
using enum USB::bRequest_t;
using enum USB::bDescriptorType_t;
using enum USB::recipient_t;

usb_device_controller::usb_device_controller(usb_dcd_interface & driver, usb_device & device)
    : _driver(driver), _device(device), _new_addr(0), _should_set_address(false),
      _active_configuration(0) {

    EP0_IN  = usb_endpoint_ctrl::inst.create_endpoint(0x80, ep_attributes_t::TRANS_CONTROL, 64, 0);
    EP0_OUT = usb_endpoint_ctrl::inst.create_endpoint(0x00, ep_attributes_t::TRANS_CONTROL, 64, 0);

    EP0_IN->set_handler([&](uint8_t *, uint16_t) {
        if (_should_set_address) {
            _driver.set_address(_new_addr);
            _should_set_address = false;
        } else {
            EP0_OUT->start_transfer(nullptr, 0);
        }
    });

    EP0_OUT->set_handler([](uint8_t *, uint16_t) {
    });

    _driver.set_bus_reset_handler([&]() {
        printf("Bus reset\n");
        _new_addr = 0;
        _should_set_address = false;
        _driver.set_address(0);
        _active_configuration = 0;
    });

    _driver.set_setup_handler([&](USB::setup_packet_t *pkt) {
        // Reset PID to 1 for EP0_IN
        EP0_IN->next_pid = 1;
        // Check request type
        if (pkt->bmRequestType.type == type_t::TYPE_CLASS) {
            assert("No class specific requests.." && false);
        }
        if (pkt->bmRequestType.type == type_t::TYPE_VENDOR) {
            assert("No vendor specific requests.." && false);
        }
        // Process standard requests
        assert(pkt->bmRequestType.type == type_t::TYPE_STANDARD);
        switch (pkt->bRequest) {
            // Device requests
            case REQ_SET_ADDRESS:
                printf("SET_ADDRESS\n");
                handle_set_address(pkt);
                break;
            case REQ_GET_DESCRIPTOR:
                printf("GET_DESCRIPTOR\n");
                handle_get_descriptor(pkt);
                break;
            case REQ_SET_DESCRIPTOR:
                printf("SET_DESCRIPTOR\n");
                handle_set_descriptor(pkt);
                break;
            case REQ_GET_CONFIGURATION:
                printf("GET_CONFIGURATION\n");
                handle_get_configuration(pkt);
                break;
            case REQ_SET_CONFIGURATION:
                printf("SET_CONFIGURATION\n");
                handle_set_configuration(pkt);
                break;
            // Interface requests
            case REQ_GET_INTERFACE:
                printf("GET_INTERFACE\n");
                handle_get_interface(pkt);
                break;
            case REQ_SET_INTERFACE:
                printf("SET_INTERFACE\n");
                handle_set_interface(pkt);
                break;
            // Endpoint requests
            case REQ_SYNCH_FRAME:
                printf("SYNCH_FRAME\n");
                handle_synch_frame(pkt);
                break;
            // Requests for different recipients
            case REQ_GET_STATUS:
                printf("GET_STATUS\n");
                handle_get_status(pkt);
                break;
            case REQ_CLEAR_FEATURE:
                printf("CLEAR_FEATURE\n");
                handle_clear_feature(pkt);
                break;
            case REQ_SET_FEATURE:
                printf("SET_FEATURE\n");
                handle_set_feature(pkt);
                break;
            default:
                assert("Unknown setup request" && false);
        }
    });
}

void usb_device_controller::handle_set_address(setup_packet_t * pkt) {
    assert(pkt->bmRequestType.direction == direction_t::DIR_OUT);
    assert(pkt->bmRequestType.recipient == recipient_t::REC_DEVICE);
    _new_addr = pkt->wValue & 0xff;
    printf("Set address %d\n", _new_addr);
    _should_set_address = true;
    // Send back ACK
    EP0_IN->start_transfer(nullptr, 0);
}

void usb_device_controller::handle_get_descriptor(setup_packet_t * pkt) {
    assert(pkt->bmRequestType.direction == direction_t::DIR_IN);
    assert(pkt->bmRequestType.recipient == recipient_t::REC_DEVICE);
    uint8_t desc_index = pkt->wValue & 0xff;
    USB::bDescriptorType_t desc_type = (USB::bDescriptorType_t)(pkt->wValue >> 8);

    uint8_t   tmp_buf[64];
    uint8_t * tmp_ptr = tmp_buf;

    switch (desc_type) {
        case DESC_DEVICE: {
            assert(_device.descriptor.bLength <= pkt->wLength);
            EP0_IN->start_transfer((uint8_t *) &_device.descriptor, _device.descriptor.bLength);
            break;
        }
        case DESC_CONFIGURATION: {
            usb_configuration * conf = _device.configurations[desc_index];
            if (conf) {
                assert(pkt->wLength >= sizeof(configuration_descriptor_t));
                // Copy configuration descriptor first
                memcpy(tmp_ptr, &conf->descriptor, sizeof(configuration_descriptor_t));
                tmp_ptr += sizeof(configuration_descriptor_t);
                if (pkt->wLength >= conf->descriptor.wTotalLength) {
                    // Copy interface and endpoint descriptors
                    for (usb_interface * inter : conf->interfaces) {
                        if (inter) {
                            if (inter->function) {
                                memcpy(tmp_ptr, &inter->function->descriptor, sizeof(interface_association_descriptor_t));
                                tmp_ptr += sizeof(interface_association_descriptor_t);
                            }
                            memcpy(tmp_ptr, &inter->descriptor, sizeof(interface_descriptor_t));
                            tmp_ptr += sizeof(interface_descriptor_t);
                            for (usb_endpoint_interface * ep : inter->endpoints) {
                                if (ep) {
                                    memcpy(tmp_ptr, &ep->descriptor, sizeof(endpoint_descriptor_t));
                                    tmp_ptr += sizeof(endpoint_descriptor_t);
                                }
                            }
                        }
                    }
                }
            }
            uint32_t len = (uint32_t)tmp_ptr - (uint32_t)tmp_buf;
            assert(len <= pkt->wLength);
            EP0_IN->start_transfer(tmp_buf, MIN(len, pkt->wLength));
            break;
        }
        case DESC_STRING: {
            uint8_t index = pkt->wValue & 0xff;
            uint8_t len = usb_strings::inst.prepare_buffer(index, tmp_buf);
            assert(len <= pkt->wLength);
            EP0_IN->start_transfer(tmp_buf, len);
            break;
        }
        case DESC_OTG: {
            break;
        }
        case DESC_DEBUG: {
            EP0_IN->send_stall();
            EP0_IN->start_transfer(tmp_buf, 0);
            break;
        }
        default:
            printf("Unknown GET_DESCRIPTOR %d\n", (int)desc_type);
            assert("Illegal operation" && false);
    }
}

void usb_device_controller::handle_set_descriptor(setup_packet_t * pkt) {
    assert(pkt->bmRequestType.direction == direction_t::DIR_OUT);
    assert(pkt->bmRequestType.recipient == recipient_t::REC_DEVICE);
    assert("Not implemented" && false);
}

void usb_device_controller::handle_get_configuration(USB::setup_packet_t *pkt) {
    assert(pkt->bmRequestType.direction == direction_t::DIR_IN);
    assert(pkt->bmRequestType.recipient == recipient_t::REC_DEVICE);
    EP0_IN->start_transfer(&_active_configuration, 1);
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
            if (conf) conf->activate_endpoints(false);
            else assert("Config not found " && false);
            printf("Disabled configuration %d\n", _active_configuration);
            _active_configuration = 0;
        }
        if (index) {
            conf = _device.find_configuration(index);
            if (conf) conf->activate_endpoints(true);
            else assert("Config not found" && false);
            printf("Enabled configuration %d\n", index);
            _active_configuration = index;
        }
    }
    EP0_IN->start_transfer(nullptr, 0);
}

void usb_device_controller::handle_get_interface(USB::setup_packet_t *pkt) {
    assert(pkt->bmRequestType.direction == direction_t::DIR_IN);
    assert(pkt->bmRequestType.recipient == recipient_t::REC_INTERFACE);
    uint8_t index = pkt->wIndex & 0xff;
    if (_active_configuration) {
        usb_interface * inter = _device.configurations[_active_configuration]->interfaces[index];
        if (inter) {
            EP0_IN->start_transfer(&inter->descriptor.bAlternateSetting, 1);
        } else {
            assert("nullptr error" && false);
        }
    } else {
        assert("No active config" && false);
    }
}

void usb_device_controller::handle_set_interface(USB::setup_packet_t *pkt) {
    assert(pkt->bmRequestType.direction == direction_t::DIR_OUT);
    assert(pkt->bmRequestType.recipient == recipient_t::REC_INTERFACE);
    uint8_t index = pkt->wIndex & 0xff;
    if (_active_configuration) {
        usb_interface * inter = _device.configurations[_active_configuration]->interfaces[index];
        if (inter) {
            inter->descriptor.bAlternateSetting = pkt->wValue & 0xff;
        } else {
            assert("nullptr error" && false);
        }
    } else {
        assert("No active config" && false);
    }
}

void usb_device_controller::handle_synch_frame(USB::setup_packet_t *pkt) {
    assert(pkt->bmRequestType.direction == direction_t::DIR_IN);
    assert(pkt->bmRequestType.recipient == recipient_t::REC_ENDPOINT);
}


void usb_device_controller::handle_get_status(USB::setup_packet_t * pkt) {
    assert(pkt->bmRequestType.direction == direction_t::DIR_IN);
    assert(pkt->wValue  == 0);
    assert(pkt->wLength == 2);

    switch(pkt->bmRequestType.recipient) {
        case REC_DEVICE: {
            break;
        }
        case REC_INTERFACE: {
            break;
        }
        case REC_ENDPOINT: {
            break;
        }
    }
    EP0_IN->send_stall();
    EP0_IN->start_transfer(nullptr, 0);

}

void usb_device_controller::handle_clear_feature(USB::setup_packet_t *pkt) {

}

void usb_device_controller::handle_set_feature(USB::setup_packet_t *pkt) {

}

