#include "usb_device.h"
#include "usb_configuration.h"
#include "usb_device_rp2040.h"
#include "usb_device_controller.h"
#include "usb_endpoint_rp2040.h"

#include "uart_rp2040.h"
#include "task.h"
#include "posix_io.h"
#include <cstdio>
#include <cctype>

using enum USB::bDeviceClass_t;

int main() {
    uart_rp2040 uart; // default is backchannel UART!

    posix_io::inst.register_stdin(uart);
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    // USB Device driver
    usb_device_rp2040 driver;
    driver.init();
    usb_device device;
    // Put generic USB Device Controller on top
    usb_device_controller controller(driver, device);

    // Set up USB device structure
    device.set_bcdUSB         (0x0110);
    device.set_bMaxPacketSize0(64);
    device.set_idVendor       (0x0000);
    device.set_idProduct      (0x0001);
    device.set_Manufacturer   ("Raspberry Pi");
    device.set_Product        ("Pico Test Device");

    // Configure USB configuration
    usb_configuration config;
    config.set_bConfigurationValue(1);
    config.set_bmAttributes( { .reserved      = 0,
                               .remote_wakeup = 0,
                               .self_powered  = 0,
                               .bus_powered   = 1 } );
    config.set_bMaxPower_mA(100);
    device.add_configuration(config);

    usb_interface_association assoc;
    assoc.set_bFunctionClass(CLASS_VENDOR_SPECIFIC);
    config.add_interface_association(assoc);

    // Configure USB interface
    usb_interface interface;
    interface.set_bInterfaceClass(CLASS_VENDOR_SPECIFIC);
    assoc.add_interface(interface);

    // Configure USB endpoints
    usb_endpoint_rp2040 EP1_OUT(0x01, USB::ep_attributes_t::TRANS_BULK);
    usb_endpoint_rp2040 EP2_IN (0x82, USB::ep_attributes_t::TRANS_BULK);
    interface.add_endpoint(EP1_OUT);
    interface.add_endpoint(EP2_IN);

    EP1_OUT.set_handler([&](uint8_t *buf, uint16_t len){
        printf("Received %d bytes from host\n", len);
        for (int i=0; i < len; ++i) buf[i] = std::toupper(buf[i]);
        EP2_IN.start_transfer(buf, len);
    });

    EP2_IN.set_handler([&](uint8_t *, uint16_t len){
        printf("Sent %d bytes to host\n", len);
        EP1_OUT.start_transfer(nullptr, 64);
    });

    // Activate USB device
    driver.pullup_enable();

    // Wait until USB enumeration has finished
    while (!controller.active_configuration()) {
        printf("Waiting\n");
        task::sleep(100);
    }

    printf("Start receive");
    // Get ready to receive message from host
    EP1_OUT.start_transfer(nullptr, 64);

    // Endless loop
    while(1) {
//        task::sleep(1000);
//        printf("Working\n");
//        EP1_OUT.start_transfer(nullptr, 64);
    }
}

