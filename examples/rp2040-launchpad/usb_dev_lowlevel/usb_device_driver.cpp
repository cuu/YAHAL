#include "usb_device_driver.h"
#include "usb_common.h"
#include "usb_strings.h"
#include <cstring>
#include <cstdio>
#include <cassert>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

usb_device_driver::usb_device_driver(usb_dcd_interface & driver)
    : _dcd(driver), _new_addr(0), _should_set_address(false), _configured(false) {

    EP0_IN  = usb_endpoint_ctrl::inst.create_endpoint(0x80, USB_TRANSFER_TYPE_CONTROL, 64, 0);
    EP0_OUT = usb_endpoint_ctrl::inst.create_endpoint(0x00, USB_TRANSFER_TYPE_CONTROL, 64, 0);

    EP0_IN->set_handler([&](uint8_t *, uint16_t) {
        if (_should_set_address) {
            _dcd.set_address(_new_addr);
            _should_set_address = false;
        } else {
            EP0_OUT->start_transfer(nullptr, 0);
        }
    });

    EP0_OUT->set_handler([](uint8_t *, uint16_t) {
    });

    _dcd.set_bus_reset_handler([&]() {
        printf("Bus reset\n");
        _new_addr = 0;
        _should_set_address = false;
        _dcd.set_address(0);
        _configured = false;
    });

    _dcd.set_setup_handler([&](usb_setup_packet * pkt) {
        uint8_t req_direction = pkt->bmRequestType;
        uint8_t req           = pkt->bRequest;

        // Reset PID to 1 for EP0_IN
        EP0_IN->next_pid = 1;

        if (req_direction == USB_DIR_OUT) {
            if (req == USB_REQUEST_SET_ADDRESS) {
                printf("Set address %d\n", pkt->wValue & 0xff);
                _should_set_address = true;
                _new_addr = pkt->wValue & 0xff;
                // Send back ACK
                EP0_IN->start_transfer(nullptr, 0);
            } else if (req == USB_REQUEST_SET_CONFIGURATION) {
                printf("Device configured\n");
                // Send back ACK
                EP0_IN->start_transfer(nullptr, 0);
                _configured = true;
            } else {
                EP0_IN->start_transfer(nullptr, 0);
                printf("Other OUT request (0x%x)\r\n", pkt->bRequest);
            }
        } else if (req_direction == USB_DIR_IN) {
            if (req == USB_REQUEST_GET_DESCRIPTOR) {
                uint16_t descriptor_type = pkt->wValue >> 8;

                switch (descriptor_type) {
                    case USB_DT_DEVICE:
                        printf("GET DEVICE DESCRIPTOR\r\n");
                        usb_handle_device_descriptor(pkt);
                        break;

                    case USB_DT_CONFIG:
                        printf("GET CONFIG DESCRIPTOR\r\n");
                        usb_handle_config_descriptor(pkt);
                        break;

                    case USB_DT_STRING:
                        printf("GET STRING DESCRIPTOR\r\n");
                        usb_handle_string_descriptor(pkt);
                        break;

                    default:
                        printf("Unhandled GET_DESCRIPTOR type 0x%x\r\n", descriptor_type);
                }
            } else {
                printf("Other IN request (0x%x)\r\n", pkt->bRequest);
            }
        }
    });
}

void usb_device_driver::usb_handle_device_descriptor(usb_setup_packet * pkt) {
    // Always respond with pid 1
    EP0_IN->next_pid = 1;
    assert(_dcd.descriptor.bLength <= pkt->wLength);
    EP0_IN->start_transfer((uint8_t *)&_dcd.descriptor, _dcd.descriptor.bLength);
}

void usb_device_driver::usb_handle_config_descriptor(usb_setup_packet * pkt) {
    uint8_t ep0_buf[64];
    uint8_t *buf = ep0_buf;

    // First request will want just the config descriptor
    const usb_configuration * conf  = _dcd.configurations[0];
    const usb_interface     * inter = conf->interfaces[0];

    const usb_configuration_descriptor *d = &_dcd.configurations[0]->descriptor;
    memcpy((void *) buf, &conf->descriptor, sizeof(usb_configuration_descriptor));
    buf += sizeof(struct usb_configuration_descriptor);

    // If we want more than just the config descriptor copy it all
    if (pkt->wLength >= d->wTotalLength) {
        memcpy((void *) buf, &inter->descriptor, sizeof(usb_interface_descriptor));
        buf += sizeof(struct usb_interface_descriptor);
        for(usb_endpoint_interface * ep : inter->endpoints) {
            if (ep) {
                memcpy((void *) buf, &ep->descriptor, sizeof(struct usb_endpoint_descriptor));
                buf += sizeof(struct usb_endpoint_descriptor);
            }
        }
    }

    // Send data
    // Get len by working out end of buffer subtract start of buffer
    uint32_t len = (uint32_t) buf - (uint32_t) ep0_buf;
    assert(len <= pkt->wLength);
    EP0_IN->start_transfer(&ep0_buf[0],MIN(len, pkt->wLength));
}

void usb_device_driver::usb_handle_string_descriptor(usb_setup_packet * pkt) {
    uint8_t ep0_buf[64];
    uint8_t i = pkt->wValue & 0xff;
    uint8_t len = 0;

    len = usb_strings::inst.prepare_buffer(i, ep0_buf);
    assert(len <= pkt->wLength);
    EP0_IN->start_transfer(ep0_buf, len);
}
