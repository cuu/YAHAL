#include "usb_device_rp2040.h"
#include "usb_endpoint_rp2040.h"

#include <cstring>
#include <cassert>
#include <cstdio>

#include "RP2040.h"
using namespace _USBCTRL_DPRAM_;
using namespace _USBCTRL_REGS_;
using namespace _RESETS_;

function<void(usb_setup_packet * packet)> usb_device_rp2040::_setup_handler;
function<void()> usb_device_rp2040::_bus_reset_handler;

void usb_device_rp2040::init() {
    // Reset usb controller
    RESETS_SET.RESET.usbctrl <<= 1;
    RESETS_CLR.RESET.usbctrl <<= 1;
    while (!RESETS.RESET_DONE.usbctrl);

    // Clear any previous state in dpram just in case
    memset(&USBCTRL_DPRAM, 0, 4096);

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
    USBCTRL_REGS_SET.INTE.SETUP_REQ   <<= 1;
    USBCTRL_REGS_SET.INTE.BUS_RESET   <<= 1;
    USBCTRL_REGS_SET.INTE.BUFF_STATUS <<= 1;
}

void usb_device_rp2040::pullup_enable() {
    USBCTRL_REGS_SET.SIE_CTRL.PULLUP_EN <<= 1;
}

void usb_device_rp2040::pullup_disable() {
    USBCTRL_REGS_SET.SIE_CTRL.PULLUP_EN <<= 0;
}

void usb_device_rp2040::irq_enable() {
    NVIC_EnableIRQ(USBCTRL_IRQ_IRQn);
}

void usb_device_rp2040::irq_disable() {
    NVIC_DisableIRQ(USBCTRL_IRQ_IRQn);
}

void usb_device_rp2040::set_address(uint8_t addr) {
    USBCTRL_REGS.ADDR_ENDP.ADDRESS = addr;
}



extern "C" {
    void USBCTRL_IRQ_Handler(void) {
        // Setup packet received
        if (USBCTRL_REGS.INTS.SETUP_REQ) {
            USBCTRL_REGS_CLR.SIE_STATUS.SETUP_REC = 1;
            usb_device_rp2040::_setup_handler((usb_setup_packet *)&USBCTRL_DPRAM);
        }
        // Buffer status, one or more buffers have completed
        if (USBCTRL_REGS.INTS.BUFF_STATUS) {
            uint32_t buffs = USBCTRL_REGS.BUFF_STATUS;
            uint32_t bit = 1;
            for(uint32_t i=0; buffs && (i < 32); ++i) {
                if (buffs & bit) {
                    // Clear bits
                    USBCTRL_REGS_CLR.BUFF_STATUS = bit;
                    buffs ^= bit;
                    // Get endpoint and call handler
                    uint8_t ep_addr = (i >> 1);
                    if (!(i & 1)) ep_addr |= 0x80;
                    usb_endpoint_interface * ep = usb_endpoint_ctrl::inst.addr_to_ep(ep_addr);
                    if (ep) ep->process_buffer();
                }
                bit <<= 1;
            }
        }
        // Bus is reset
        if (USBCTRL_REGS.INTS.BUS_RESET) {
            USBCTRL_REGS_CLR.SIE_STATUS.BUS_RESET = 1;
            usb_device_rp2040::_bus_reset_handler();
        }
    }
}
