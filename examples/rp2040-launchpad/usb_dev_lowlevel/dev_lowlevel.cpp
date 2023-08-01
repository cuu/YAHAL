/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h> // for memcpy
#include <assert.h>

#include "uart_rp2040.h"
#include "posix_io.h"
// Include descriptors
#include "usb_common.h"
#include "dev_lowlevel.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

// Function prototypes for our device specific endpoint handlers defined
// later on
void ep0_in_handler (uint8_t *buf, uint16_t len);
void ep0_out_handler(uint8_t *buf, uint16_t len);
void ep1_out_handler(uint8_t *buf, uint16_t len);
void ep2_in_handler (uint8_t *buf, uint16_t len);

// Global device address
static bool should_set_address  = false;
static uint8_t dev_addr         = 0;
static volatile bool configured = false;

// Global data buffer for EP0
static uint8_t ep0_buf[64];

// Struct defining the device configuration
static struct usb_device_configuration dev_config = {
        .device_descriptor    = &device_descriptor,
        .interface_descriptor = &interface_descriptor,
        .config_descriptor    = &config_descriptor,
        .lang_descriptor      = lang_descriptor,
        .descriptor_strings   = descriptor_strings,
        .endpoints = {
                {
                        .descriptor       = &ep0_out,
                        .handler          = &ep0_out_handler,
                        .endpoint_control = nullptr, // NA for EP0
                        .buffer_control   = &USBCTRL_DPRAM.EP0_OUT_BUFFER_CONTROL, // &usb_dpram->ep_buf_ctrl[0].out,
                        // EP0 in and out share a data buffer
                        .data_buffer      = (uint8_t *) &USBCTRL_DPRAM + 0x100, // . &usb_dpram->ep0_buf_a[0],
                        .next_pid         = 0
                },
                {
                        .descriptor       = &ep0_in,
                        .handler          = &ep0_in_handler,
                        .endpoint_control = nullptr, // NA for EP0,
                        .buffer_control   = &USBCTRL_DPRAM.EP0_IN_BUFFER_CONTROL, //usb_dpram->ep_buf_ctrl[0].in,
                        // EP0 in and out share a data buffer
                        .data_buffer      = (uint8_t *) &USBCTRL_DPRAM + 0x100, //&usb_dpram->ep0_buf_a[0],
                        .next_pid         = 0
                },
                {
                        .descriptor       = &ep1_out,
                        .handler          = &ep1_out_handler,
                        // EP1 starts at offset 0 for endpoint control
                        .endpoint_control = &USBCTRL_DPRAM.EP1_OUT_CONTROL, //usb_dpram->ep_ctrl[0].out,
                        .buffer_control   = &USBCTRL_DPRAM.EP1_OUT_BUFFER_CONTROL, //usb_dpram->ep_buf_ctrl[1].out,
                        // First free EPX buffer
                        .data_buffer      = (uint8_t *) &USBCTRL_DPRAM + 0x180, //&usb_dpram->epx_data[0 * 64],
                        .next_pid         = 0
                },
                {
                        .descriptor       = &ep2_in,
                        .handler          = &ep2_in_handler,
                        .endpoint_control = &USBCTRL_DPRAM.EP2_IN_CONTROL, //usb_dpram->ep_ctrl[1].in,
                        .buffer_control   = &USBCTRL_DPRAM.EP2_IN_BUFFER_CONTROL, //usb_dpram->ep_buf_ctrl[2].in,
                        // Second free EPX buffer
                        .data_buffer      = (uint8_t *) &USBCTRL_DPRAM + 0x1c0, //&usb_dpram->epx_data[1 * 64],
                        .next_pid         = 0
                }
        }
};

/**
 * @brief Given an endpoint address, return the usb_endpoint_configuration of that endpoint. Returns NULL
 * if an endpoint of that address is not found.
 *
 * @param addr
 * @return struct usb_endpoint_configuration*
 */
struct usb_endpoint_configuration *usb_get_endpoint_configuration(uint8_t addr) {
    struct usb_endpoint_configuration *endpoints = dev_config.endpoints;
    for (int i = 0; i < USB_NUM_ENDPOINTS; i++) {
        if (endpoints[i].descriptor && (endpoints[i].descriptor->bEndpointAddress == addr)) {
            return &endpoints[i];
        }
    }
    return nullptr;
}

/**
 * @brief Given a C string, fill the EP0 data buf with a USB string descriptor for that string.
 *
 * @param C string you would like to send to the USB host
 * @return the length of the string descriptor in EP0 buf
 */
uint8_t usb_prepare_string_descriptor(const unsigned char *str) {
    // 2 for bLength + bDescriptorType + strlen * 2 because string is unicode. i.e. other byte will be 0
    uint8_t bLength = 2 + (strlen((const char *) str) * 2);
    static const uint8_t bDescriptorType = 0x03;

    volatile uint8_t *buf = &ep0_buf[0];
    *buf++ = bLength;
    *buf++ = bDescriptorType;

    uint8_t c;

    do {
        c = *str++;
        *buf++ = c;
        *buf++ = 0;
    } while (c != '\0');

    return bLength;
}

/**
 * @brief Take a buffer pointer located in the USB RAM and return as an offset of the RAM.
 *
 * @param buf
 * @return uint32_t
 */
static inline uint32_t usb_buffer_offset(volatile uint8_t *buf) {
    return (uint32_t) buf ^ (uint32_t) &USBCTRL_DPRAM;
}

/**
 * @brief Set up the endpoint control register for an endpoint (if applicable. Not valid for EP0).
 *
 * @param ep
 */
void usb_setup_endpoint(const struct usb_endpoint_configuration *ep) {
    printf("Set up endpoint 0x%x with buffer address 0x%p\n", ep->descriptor->bEndpointAddress, ep->data_buffer);

    // EP0 doesn't have one so return if that is the case
    if (!ep->endpoint_control) {
        return;
    }

    ep->endpoint_control->INTERRUPT_PER_BUFF = 1;
    ep->endpoint_control->BUFFER_ADDRESS = usb_buffer_offset(ep->data_buffer);
    ep->endpoint_control->ENDPOINT_TYPE = ep->descriptor->bmAttributes;
    ep->endpoint_control->ENABLE = 1;
}

/**
 * @brief Set up the endpoint control register for each endpoint.
 *
 */
void usb_setup_endpoints() {
    const struct usb_endpoint_configuration *endpoints = dev_config.endpoints;
    for (int i = 0; i < USB_NUM_ENDPOINTS; i++) {
        if (endpoints[i].descriptor && endpoints[i].handler) {
            usb_setup_endpoint(&endpoints[i]);
        }
    }
}

/**
 * @brief Set up the USB controller in device mode, clearing any previous state.
 *
 */
void usb_device_init() {
    // Reset usb controller
    RESETS_SET.RESET.usbctrl <<= 1;
    RESETS_CLR.RESET.usbctrl <<= 1;
    while (!RESETS.RESET_DONE.usbctrl);

    // Clear any previous state in dpram just in case
    memset(&USBCTRL_DPRAM, 0, 4096); // <1>

    // Enable USB interrupt at processor
    NVIC_ClearPendingIRQ(USBCTRL_IRQ_IRQn);
    NVIC_EnableIRQ(USBCTRL_IRQ_IRQn);

    // Mux the controller to the onboard usb phy
    USBCTRL_REGS_SET.USB_MUXING.SOFTCON <<= 1;
    USBCTRL_REGS_SET.USB_MUXING.TO_PHY <<= 1;

    // Force VBUS detect so the device thinks it is plugged into a host
    USBCTRL_REGS_SET.USB_PWR.VBUS_DETECT_OVERRIDE_EN <<= 1;
    USBCTRL_REGS_SET.USB_PWR.VBUS_DETECT <<= 1;

    // Enable the USB controller in device mode.
    USBCTRL_REGS_SET.MAIN_CTRL.CONTROLLER_EN <<= 1;

    // Enable an interrupt per EP0 transaction
    USBCTRL_REGS_SET.SIE_CTRL.EP0_INT_1BUF <<= 1;

    // Enable interrupts for when a buffer is done, when the bus is reset,
    // and when a setup packet is received
    USBCTRL_REGS_SET.INTE.SETUP_REQ <<= 1;
    USBCTRL_REGS_SET.INTE.BUS_RESET <<= 1;
    USBCTRL_REGS_SET.INTE.BUFF_STATUS <<= 1;

    // Set up endpoints (endpoint control registers)
    // described by device configuration
    usb_setup_endpoints();

    // Present full speed device by enabling pull up on DP
    USBCTRL_REGS_SET.SIE_CTRL.PULLUP_EN <<= 1;
}

/**
 * @brief Given an endpoint configuration, returns true if the endpoint
 * is transmitting data to the host (i.e. is an IN endpoint)
 *
 * @param ep, the endpoint configuration
 * @return true
 * @return false
 */
static inline bool ep_is_tx(struct usb_endpoint_configuration *ep) {
    return ep->descriptor->bEndpointAddress & USB_DIR_IN;
}

/**
 * @brief Starts a transfer on a given endpoint.
 *
 * @param ep, the endpoint configuration.
 * @param buf, the data buffer to send. Only applicable if the endpoint is TX
 * @param len, the length of the data in buf (this example limits max len to one packet - 64 bytes)
 */
void usb_start_transfer(struct usb_endpoint_configuration *ep, uint8_t *buf, uint16_t len) {
    // We are asserting that the length is <= 64 bytes for simplicity of the example.
    // For multi packet transfers see the tinyusb port.
    assert(len <= 64);

    printf("Start transfer of len %d on ep addr 0x%x PID %d\n", len, ep->descriptor->bEndpointAddress, ep->next_pid);

    if (ep_is_tx(ep)) {
        // Need to copy the data from the user buffer to the usb memory
        memcpy((void *) ep->data_buffer, (void *) buf, len);
    }

    // Set pid and flip for next transfer
    ep->buffer_control->PID_0 = (bool) ep->next_pid;
    ep->buffer_control->FULL_0 = ep_is_tx(ep);
    ep->buffer_control->LENGTH_0 = len;
    ep->buffer_control->AVAILABLE_0 = 1;
    ep->next_pid ^= 1u;
}

/**
 * @brief Send device descriptor to host
 *
 */
void usb_handle_device_descriptor() {
    const struct usb_device_descriptor *d = dev_config.device_descriptor;
    // EP0 in
    struct usb_endpoint_configuration *ep = usb_get_endpoint_configuration(EP0_IN_ADDR);
    // Always respond with pid 1
    ep->next_pid = 1;
    usb_start_transfer(ep, (uint8_t *) d,
                       MIN(sizeof(struct usb_device_descriptor), USBCTRL_DPRAM.SETUP_PACKET_HIGH.WLENGTH));
}

/**
 * @brief Send the configuration descriptor (and potentially the configuration and endpoint descriptors) to the host.
 *
 * @param pkt, the setup packet received from the host.
 */
void usb_handle_config_descriptor() {
    uint8_t *buf = ep0_buf;

    // First request will want just the config descriptor
    const struct usb_configuration_descriptor *d = dev_config.config_descriptor;
    memcpy((void *) buf, d, sizeof(struct usb_configuration_descriptor));
    buf += sizeof(struct usb_configuration_descriptor);

    // If we more than just the config descriptor copy it all
    if (USBCTRL_DPRAM.SETUP_PACKET_HIGH.WLENGTH >= d->wTotalLength) {
        memcpy((void *) buf, dev_config.interface_descriptor, sizeof(struct usb_interface_descriptor));
        buf += sizeof(struct usb_interface_descriptor);
        const struct usb_endpoint_configuration *ep = dev_config.endpoints;

        // Copy all the endpoint descriptors starting from EP1
        for (uint8_t i = 2; i < USB_NUM_ENDPOINTS; i++) {
            if (ep[i].descriptor) {
                memcpy((void *) buf, ep[i].descriptor, sizeof(struct usb_endpoint_descriptor));
                buf += sizeof(struct usb_endpoint_descriptor);
            }
        }

    }

    // Send data
    // Get len by working out end of buffer subtract start of buffer
    uint32_t len = (uint32_t) buf - (uint32_t) ep0_buf;
    usb_start_transfer(usb_get_endpoint_configuration(EP0_IN_ADDR), &ep0_buf[0],
                       MIN(len, USBCTRL_DPRAM.SETUP_PACKET_HIGH.WLENGTH));
}

/**
 * @brief Handle a BUS RESET from the host by setting the device address back to 0.
 *
 */
void usb_bus_reset(void) {
    printf("BUS RESET\n");
    // Set address back to 0
    dev_addr = 0;
    should_set_address = false;
    USBCTRL_REGS.ADDR_ENDP = 0;
    configured = false;
}

/**
 * @brief Send the requested string descriptor to the host.
 *
 * @param pkt, the setup packet from the host.
 */
void usb_handle_string_descriptor() {
    uint8_t i = USBCTRL_DPRAM.SETUP_PACKET_LOW.WVALUE & 0xff;
    uint8_t len = 0;

    if (i == 0) {
        len = 4;
        memcpy(&ep0_buf[0], dev_config.lang_descriptor, len);
    } else {
        // Prepare fills in ep0_buf
        len = usb_prepare_string_descriptor(dev_config.descriptor_strings[i - 1]);
    }

    usb_start_transfer(usb_get_endpoint_configuration(EP0_IN_ADDR), &ep0_buf[0],
                       MIN(len, USBCTRL_DPRAM.SETUP_PACKET_HIGH.WLENGTH));
}

/**
 * @brief Sends a zero length status packet back to the host.
 */
void usb_acknowledge_out_request(void) {
    usb_start_transfer(usb_get_endpoint_configuration(EP0_IN_ADDR), nullptr, 0);
}

/**
 * @brief Handles a SET_ADDR request from the host. The actual setting of the device address in
 * hardware is done in ep0_in_handler. This is because we have to acknowledge the request first
 * as a device with address zero.
 *
 * @param pkt, the setup packet from the host.
 */
void usb_set_device_address() {
    // Set address is a bit of a strange case because we have to send a 0 length status packet first with
    // address 0
    dev_addr = USBCTRL_DPRAM.SETUP_PACKET_LOW.WVALUE & 0xff;
    printf("Set address %d\r\n", dev_addr);
    // Will set address in the callback phase
    should_set_address = true;
    usb_acknowledge_out_request();

}

/**
 * @brief Handles a SET_CONFIGRUATION request from the host. Assumes one configuration so simply
 * sends a zero length status packet back to the host.
 *
 * @param pkt, the setup packet from the host.
 */
void usb_set_device_configuration() {
    // Only one configuration so just acknowledge the request
    printf("Device Enumerated\r\n");
    usb_acknowledge_out_request();
    configured = true;
}



/**
 * @brief Notify an endpoint that a transfer has completed.
 *
 * @param ep, the endpoint to notify.
 */
static void usb_handle_ep_buff_done(struct usb_endpoint_configuration *ep) {
//    uint32_t buffer_control = *ep->buffer_control;
    // Get the transfer length for this endpoint
    //uint16_t len = ep->buffer_control->LENGTH_0;   //buffer_control & USB_BUF_CTRL_LEN_MASK;

    // Call that endpoints buffer done handler
    ep->handler((uint8_t *) ep->data_buffer, ep->buffer_control->LENGTH_0);
}

/**
 * @brief Find the endpoint configuration for a specified endpoint number and
 * direction and notify it that a transfer has completed.
 *
 * @param ep_num
 * @param in
 */
static void usb_handle_buff_done(uint8_t ep_num, bool in) {
    uint8_t ep_addr = ep_num | (in ? USB_DIR_IN : 0);
    printf("EP %d (in = %d) done\n", ep_num, in);
    for (uint32_t i = 0; i < USB_NUM_ENDPOINTS; i++) {
        struct usb_endpoint_configuration *ep = &dev_config.endpoints[i];
        if (ep->descriptor && ep->handler) {
            if (ep->descriptor->bEndpointAddress == ep_addr) {
                usb_handle_ep_buff_done(ep);
                return;
            }
        }
    }
}

/**
 * @brief Handle a "buffer status" irq. This means that one or more
 * buffers have been sent / received. Notify each endpoint where this
 * is the case.
 */
static void usb_handle_buff_status() {
//    uint32_t buffers = USBCTRL_REGS.BUFF_STATUS;
    uint32_t remaining_buffers = USBCTRL_REGS.BUFF_STATUS;

    uint32_t bit = 1u;
    for (uint32_t i = 0; remaining_buffers && i < USB_NUM_ENDPOINTS * 2; i++) {
        if (remaining_buffers & bit) {
            // clear this in advance
            USBCTRL_REGS_CLR.BUFF_STATUS = bit;
            // IN transfer for even i, OUT transfer for odd i
            usb_handle_buff_done(i >> 1u, !(i & 1u));
            remaining_buffers &= ~bit;
        }
        bit <<= 1u;
    }
}

/**
 * @brief EP0 in transfer complete. Either finish the SET_ADDRESS process, or receive a zero
 * length status packet from the host.
 *
 * @param buf the data that was sent
 * @param len the length that was sent
 */
void ep0_in_handler(uint8_t *buf, uint16_t len) {
    if (should_set_address) {
        // Set actual device address in hardware
        USBCTRL_REGS.ADDR_ENDP.ADDRESS = dev_addr;
        should_set_address = false;
    } else {
        // Receive a zero length status packet from the host on EP0 OUT
        struct usb_endpoint_configuration *ep = usb_get_endpoint_configuration(EP0_OUT_ADDR);
        usb_start_transfer(ep, nullptr, 0);
    }
}

void ep0_out_handler(uint8_t *buf, uint16_t len) {
    ;
}

// Device specific functions
void ep1_out_handler(uint8_t *buf, uint16_t len) {
    printf("RX %d bytes from host\n", len);
    // Send data back to host
    struct usb_endpoint_configuration *ep = usb_get_endpoint_configuration(EP2_IN_ADDR);
    usb_start_transfer(ep, buf, len);
}

void ep2_in_handler(uint8_t *buf, uint16_t len) {
    printf("Sent %d bytes to host\n", len);
    // Get ready to rx again from host
    usb_start_transfer(usb_get_endpoint_configuration(EP1_OUT_ADDR), NULL, 64);
}



/**
 * @brief Respond to a setup packet from the host.
 *
 */
void usb_handle_setup_packet(void) {
//    volatile struct usb_setup_packet *pkt = (volatile struct usb_setup_packet *) &USBCTRL_DPRAM; //.SETUP_PACKET_LOW;
    uint8_t req_direction = USBCTRL_DPRAM.SETUP_PACKET_LOW.BMREQUESTTYPE;
    uint8_t req = USBCTRL_DPRAM.SETUP_PACKET_LOW.BREQUEST;

    // Reset PID to 1 for EP0 IN
    usb_get_endpoint_configuration(EP0_IN_ADDR)->next_pid = 1u;

    if (req_direction == USB_DIR_OUT) {
        if (req == USB_REQUEST_SET_ADDRESS) {
            usb_set_device_address();
        } else if (req == USB_REQUEST_SET_CONFIGURATION) {
            usb_set_device_configuration();
        } else {
            usb_acknowledge_out_request();
            printf("Other OUT request (0x%x)\r\n", USBCTRL_DPRAM.SETUP_PACKET_LOW.BREQUEST);
        }
    } else if (req_direction == USB_DIR_IN) {
        if (req == USB_REQUEST_GET_DESCRIPTOR) {
            uint16_t descriptor_type = USBCTRL_DPRAM.SETUP_PACKET_LOW.WVALUE >> 8;

            switch (descriptor_type) {
                case USB_DT_DEVICE:
                    printf("GET DEVICE DESCRIPTOR\r\n");
                    usb_handle_device_descriptor();
                    break;

                case USB_DT_CONFIG:
                    printf("GET CONFIG DESCRIPTOR\r\n");
                    usb_handle_config_descriptor();
                    break;

                case USB_DT_STRING:
                    printf("GET STRING DESCRIPTOR\r\n");
                    usb_handle_string_descriptor();
                    break;

                default:
                    printf("Unhandled GET_DESCRIPTOR type 0x%x\r\n", descriptor_type);
            }
        } else {
            printf("Other IN request (0x%x)\r\n", USBCTRL_DPRAM.SETUP_PACKET_LOW.BREQUEST);
        }
    }
}

extern "C" {
    void USBCTRL_IRQ_Handler(void) {
        // Setup packet received
        if (USBCTRL_REGS.INTS.SETUP_REQ) {
            USBCTRL_REGS_CLR.SIE_STATUS.SETUP_REC = 1;
            usb_handle_setup_packet();
        }
        // Buffer status, one or more buffers have completed
        if (USBCTRL_REGS.INTS.BUFF_STATUS) {
            usb_handle_buff_status();
        }
        // Bus is reset
        if (USBCTRL_REGS.INTS.BUS_RESET) {
            USBCTRL_REGS_CLR.SIE_STATUS.BUS_RESET = 1;
            usb_bus_reset();
        }
    }
}

int main(void) {
    uart_rp2040 uart; // default is backchannel UART!

    posix_io::inst.register_stdin(uart);
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    printf("USB Device Low-Level hardware example\n");
    usb_device_init();

    // Wait until configured
    while (!configured) ;

    // Get ready to rx from host
    usb_start_transfer(usb_get_endpoint_configuration(EP1_OUT_ADDR), NULL, 64);

    // Everything is interrupt driven so just loop here
    while (1) ;

    return 0;
}
