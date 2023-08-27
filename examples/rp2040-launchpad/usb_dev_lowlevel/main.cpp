#include "usb_cdc_acm_device.h"
#include "usb_device.h"
#include "usb_configuration.h"

#include "usb_dcd_rp2040.h"
#include "usb_device_controller.h"

#include "uart_rp2040.h"
#include "task.h"
#include "posix_io.h"
#include <cstdio>

#include "FIFO.h"

int main() {
    uart_rp2040 uart; // default is backchannel UART!

    posix_io::inst.register_stdin(uart);
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    printf("Simple USB example\n");

    // USB Device driver
    usb_dcd_rp2040 & driver = usb_dcd_rp2040::inst();
    // USB device: Root object of USB descriptor tree
    usb_device device;
    // Generic USB Device Controller on top
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
    usb_configuration config(device);
    config.set_bConfigurationValue(1);
    config.set_bmAttributes( { .reserved      = 0,
                               .remote_wakeup = 0,
                               .self_powered  = 0,
                               .bus_powered   = 1 } );
    config.set_bMaxPower_mA(100);

    /////////////////////
    // USB CDC ACM device
    /////////////////////
    usb_cdc_acm_device acm_device(controller, config);

    FIFO<uint8_t> fifo(10000);

    acm_device.set_receive_handler([&](uint8_t *buf, uint16_t len) {
        // Check if we need to stop incoming data
        if (fifo.available_put() < 500) {
            acm_device._ep_data_out->send_NAK(true);
        }
        // Copy all available bytes to the FIFO
        for(int i=0; i<len; ++i) {
            fifo.put(buf[i]);
        }
    });


    acm_device.set_line_coding_handler([&](uint8_t *,uint16_t) {
        const char * parity[5] = {"N", "O", "E", "M", "S"};
        const char * stop[3]   = {"1", "1.5", "2"};
        printf("Line coding set to %d baud %d%s%s\n",
               (int)acm_device.line_coding.dwDTERate,
               (int)acm_device.line_coding.bDataBits,
               parity[(int)acm_device.line_coding.bParityType],
               stop[(int)acm_device.line_coding.bCharFormat]);
    });

    acm_device.set_control_line_handler([](bool dtr, bool rts) {
        printf("Control signals DTR=%d, RTS=%d\n", dtr, rts);
    });

    acm_device.set_break_handler([](uint16_t millis) {
        printf("Send break for 0x%04x milliseconds\n", millis);
    });

    //////////////////////
    // Activate USB device
    //////////////////////
    driver.pullup_enable(true);

    //////////////////////////////////////////
    // Wait until USB enumeration has finished
    //////////////////////////////////////////
    while (!controller.active_configuration) {
        task::sleep(100);
    }

    printf("Entering endless loop...\n");

    uint8_t buf[64], val;
    int i=0;
    while (1) {
        // Check if we need to enable incoming data
        if (fifo.available_put() > 1000) {
            acm_device._ep_data_out->send_NAK(false);
        }
        // Check if there is some data in the FIFO for sending
        if (fifo.available_get()) {
            for (i = 0; i < 64; ++i) {
                if (fifo.get(val)) {
                    buf[i] = val;
                } else {
                    break;
                }
            }
            // Transmit the data, if existing
            if (i)  {
                acm_device._ep_data_in->start_transfer(buf, i);
                while(acm_device._ep_data_in->is_active()) ;
//                task::sleep(20);
            }
        }
    }
}
