#include "usb_device_rp2040.h"
#include "usb_device_driver.h"
#include "usb_endpoint_rp2040.h"

#include "uart_rp2040.h"
#include "posix_io.h"
#include <cstdio>

int main() {
    uart_rp2040 uart; // default is backchannel UART!

    posix_io::inst.register_stdin(uart);
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    // USB classes
    usb_device_rp2040 device;
    usb_configuration config;
    usb_interface     interface;
    device.init();

    // Configure USB endpoints
    usb_endpoint_rp2040 EP1_OUT(0x01, USB_TRANSFER_TYPE_BULK);
    usb_endpoint_rp2040 EP2_IN (0x82, USB_TRANSFER_TYPE_BULK);

    EP1_OUT.set_handler([&](uint8_t *buf, uint16_t len){
        printf("RX %d bytes from host\n", len);
        EP2_IN.start_transfer(buf, len);
    });

    EP2_IN.set_handler([&](uint8_t *, uint16_t len){
        printf("TX %d bytes to host\n", len);
        EP1_OUT.start_transfer(nullptr, 64);
    });

    // Configure USB interface
    interface.set_bInterfaceClass(0xff);
    interface.add_endpoint(EP1_OUT);
    interface.add_endpoint(EP2_IN);

    // Configure USB configuration
    config.set_bConfigurationValue(1);
    config.set_bmAttributes(0xc0);
    config.set_bMaxPower_mA(100);
    config.add_interface(interface);

    // Configure USB device
    device.set_bcdUSB         (0x0110);
    device.set_bMaxPacketSize0(64);
    device.set_idVendor       (0x0000);
    device.set_idProduct      (0x0001);
    device.set_Manufacturer   ("Raspberry Pi");
    device.set_Product        ("Pico Test Device");
    device.add_configuration(config);

    // Create the generic USB driver
    usb_device_driver driver(device);

    // Activate USB device
    device.pullup_enable();

    // Wait until USB enumeration has finished
    while (!driver.configured()) ;

    // Get ready to receive message from host
    EP1_OUT.start_transfer(NULL, 64);

    // Endless loop
    while(1) ;
}
