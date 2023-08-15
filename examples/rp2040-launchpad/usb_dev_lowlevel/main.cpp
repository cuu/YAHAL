#include "usb_cdc_common.h"
#include "usb_device.h"
#include "usb_configuration.h"
#include "usb_interface_association.h"
#include "usb_dcd_rp2040.h"
#include "usb_device_controller.h"
#include "usb_endpoint_rp2040.h"
#include "usb_header_fd.h"
#include "usb_call_mgmt_fd.h"
#include "usb_acm_fd.h"
#include "usb_union_fd.h"

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

    printf("Simple USB example\n");

    // USB Device driver
    usb_dcd_rp2040 &    driver = usb_dcd_rp2040::inst();
    driver.init();
    usb_device          device;
    // Put generic USB Device Controller on top
    usb_device_controller controller(driver, device);

    ////////////////////////
    // USB device descriptor
    ////////////////////////
    device.set_bcdUSB         (0x0110);
    device.set_bMaxPacketSize0(64);
    device.set_idVendor       (0x0000);
    device.set_idProduct      (0x0001);
    device.set_Manufacturer   ("Raspberry Pi");
    device.set_Product        ("Pico Test Device");

    ///////////////////////////////
    // USB configuration descriptor
    ///////////////////////////////
    usb_configuration config;
    config.set_bConfigurationValue(1);
    config.set_bmAttributes( { .reserved      = 0,
                               .remote_wakeup = 0,
                               .self_powered  = 0,
                               .bus_powered   = 1 } );
    config.set_bMaxPower_mA(100);
    device.add_configuration(config);

    ///////////////////////////////////////
    // USB interface association descriptor
    ///////////////////////////////////////
    usb_interface_association assoc;
    assoc.set_bFunctionClass   (USB::bInterfaceClass_t::CLASS_CDC);
    assoc.set_bFunctionSubClass(USB::bInterfaceSubClass_t::CLASS_ABSTRACT_CONTROL_MODEL);
    assoc.set_bFunctionProtocol(USB::bInterfaceProtocol_t::PROTOCOL_NONE);
    config.add_interface_association(assoc);

    ////////////////////////////
    // USB interface descriptors
    ////////////////////////////
    usb_interface interface_ctrl;
    interface_ctrl.set_bInterfaceClass(USB::bInterfaceClass_t::CLASS_CDC);
    interface_ctrl.set_bInterfaceSubClass(USB::bInterfaceSubClass_t::CLASS_ABSTRACT_CONTROL_MODEL);
    interface_ctrl.set_bInterfaceProtocol(USB::bInterfaceProtocol_t::PROTOCOL_NONE);
    uint8_t ctrl_if_index = assoc.add_interface(interface_ctrl);

    usb_interface interface_data;
    interface_data.set_bInterfaceClass(USB::bInterfaceClass_t::CLASS_CDC_DATA);
    interface_data.set_bInterfaceProtocol(USB::bInterfaceProtocol_t::PROTOCOL_NONE);
    uint8_t data_if_index = assoc.add_interface(interface_data);

    /////////////////////////////
    // USB Functional Descriptors
    /////////////////////////////
    usb_header_fd header_fd;
    header_fd.set_bcdCDC(0x0120);
    interface_ctrl.add_func_descriptor(header_fd);

    usb_call_mgmt_fd call_mgmt_fd;
    call_mgmt_fd.set_bmCapabilities({ .handle_call_management         = 0,
                                      .call_management_via_data_class = 0,
                                      .reserved                       = 0 });
    call_mgmt_fd.set_bDataInterface(data_if_index);
    interface_ctrl.add_func_descriptor(call_mgmt_fd);


    usb_acm_fd acm_fd;
    acm_fd.set_bmCapabilities({ .comm_feature_support       = 0,
                                .line_coding_support        = 1,
                                .send_break_support         = 0,
                                .network_connection_support = 0,
                                .reserved                   = 0 });
    interface_ctrl.add_func_descriptor(acm_fd);

    usb_union_fd union_fd;
    union_fd.set_bControlInterface     (ctrl_if_index);
    union_fd.set_bSubordinateInterface0(data_if_index);
    interface_ctrl.add_func_descriptor(union_fd);

    ////////////////
    // USB endpoints
    ////////////////
    usb_endpoint_interface * EP1_IN = driver.create_endpoint(0x81, USB::ep_attributes_t::TRANS_INTERRUPT, 64, 0);
    interface_ctrl.add_endpoint(*EP1_IN);

    usb_endpoint_interface * EP2_OUT = driver.create_endpoint(0x02, USB::ep_attributes_t::TRANS_BULK, 64, 0);
    usb_endpoint_interface * EP3_IN  = driver.create_endpoint(0x83, USB::ep_attributes_t::TRANS_BULK, 64, 0);
    interface_data.add_endpoint(*EP2_OUT);
    interface_data.add_endpoint(*EP3_IN);


#if 0
    EP1_OUT.set_handler([&](uint8_t *buf, uint16_t len){
        printf("Received %d bytes from host\n", len);
        for (int i=0; i < len; ++i) buf[i] = std::toupper(buf[i]);
        EP2_IN.start_transfer(buf, len);
    });

    EP2_IN.set_handler([&](uint8_t *, uint16_t len){
        printf("Sent %d bytes to host\n", len);
        EP1_OUT.start_transfer(nullptr, 64);
    });
#endif

    // Activate USB device
    driver.pullup_enable(true);

    // Wait until USB enumeration has finished
    while (!controller.active_configuration()) {
        task::sleep(100);
    }

    printf("Entering endless loop\n");
#if 0
    printf("Start receive");
    // Get ready to receive message from host
    EP1_OUT.start_transfer(nullptr, 64);
#endif

    // Endless loop
    while(1) {
//        task::sleep(1000);
//        printf("Working\n");
//        EP1_OUT.start_transfer(nullptr, 64);
    }
}

