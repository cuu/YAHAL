// ---------------------------------------------
//           This file is part of
//      _  _   __    _   _    __    __
//     ( \/ ) /__\  ( )_( )  /__\  (  )
//      \  / /(__)\  ) _ (  /(__)\  )(__
//      (__)(__)(__)(_) (_)(__)(__)(____)
//
//     Yet Another HW Abstraction Library
//      Copyright (C) Andreas Terstegge
//      BSD Licensed (see file LICENSE)
//
// ---------------------------------------------
//
#include "board.h"
#include "usb_dcd.h"
#include "usb_device_controller.h"
#include "usb_ms_compat_descriptor.h"
#include "usb_msc_bot_device.h"

#include "block_io_interface.h"
#include "posix_io.h"
#include "task.h"
#include "uart_rp2350.h"
#include "ws2812_rp2350.h"

#include <cstdio>
#include <cstring>

#include "unzipLIB.h"
#include "image.h"

// Use the full 8MB of PSRAM as a USB mass storage device.
// The PSRAM will not be initialized during startup!
uint8_t psram[16384][512] PSRAM;

int main() {
    uart_rp2350 uart; // default is back-channel UART!
    posix_io::inst.register_stdin(uart);
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    // Open the ZIP image ...
    UNZIP zip;
    uint8_t buff[512];
    int res = zip.openZIP(image, sizeof(image));
    res = zip.gotoFirstFile();
    res = zip.openCurrentFile();
    // ... and read the first sector
    res = zip.readCurrentFile(buff, 512);
    // Check if the PSRAM contains this sector already
    bool mismatch=false;
    for(int i=0; i < 512; ++i) {
        if (buff[i] != psram[0][i]) mismatch=true;
        // Copy data in any case!
        psram[0][i] = buff[i];
    }
    if (mismatch) {
        puts("No valid image in PSRAM. Initialize ...");
        // The PSRAM seems to be not initialized.
        // Copy all data from the ZIP file
        int count = 1; // First sector was read already
        do {
            res = zip.readCurrentFile(psram[count], 512);
            if (res) count++;
        } while(res > 0);
        printf("%d blocks written\n", count);
    } else {
        puts("Valid image found in PSRAM!");
    }
    res = zip.closeZIP();

    // Setup two LEDs on the launchpad for blinking
    ws2812_rp2350 leds(LED_RGB_GPIO, LED_RGB_COUNT);
    led_rgb_interface &led_red   = leds[0];
    led_rgb_interface &led_green = leds[1];
    led_rgb_interface &led_rem   = leds[4];
    led_red.set_on_color(0x040000);
    led_green.set_on_color(0x000500);
//    led_rem.set_on_color(0x444400);
    bool read_active, write_active;

    // Switch on USB logging
    usb_log::inst.setLevel(LOG_INFO);
    // USB Device driver
    usb_dcd &driver = usb_dcd::inst();
    // USB device: Root object of USB descriptor tree
    usb_device device;
    // Generic USB Device Controller on top
    usb_device_controller controller(driver, device);

    ////////////////////////
    // USB device descriptor
    ////////////////////////
    device.set_bcdUSB         (0x0210);
    device.set_bMaxPacketSize0(64);
    device.set_idVendor       (0x2e8a);
    device.set_idProduct      (0x0151);
    device.set_Manufacturer   ("FH Aachen");
    device.set_Product        ("MSC Test Device");

    ////////////////////////
    // USB BOS descriptor //
    ////////////////////////
    usb_ms_compat_descriptor webusb(controller, device);

    ///////////////////////////////
    // USB configuration descriptor
    ///////////////////////////////
    usb_configuration config(device);
    config.set_bConfigurationValue(1);
    config.set_bmAttributes({.remote_wakeup = 0,
                             .self_powered  = 0,
                             .bus_powered   = 1});
    config.set_bMaxPower_mA(100);

    /////////////////////
    // USB MSC BOT device
    /////////////////////
    usb_msc_bot_device msc_device(controller, config);
    msc_device.set_vendor_id  ("FH AC");
    msc_device.set_product_id ("MSC Test Device");
    msc_device.set_product_rev("1.0");

    // Set callback handlers
    msc_device.capacity_handler = [&](uint16_t &block_size,
                                      uint32_t &block_count) {
        block_size  = 512;
        block_count = 8192 * 2;
    };
    msc_device.read_handler = [&](uint8_t *buff, uint32_t block) {
        memcpy(buff, psram[block], 512);
        read_active = true;
        return BLOCKIO::result_t::OK;
    };
    msc_device.write_handler = [&](uint8_t *buff, uint32_t block) {
        memcpy(psram[block], buff, 512);
        write_active = true;
        return BLOCKIO::result_t::OK;
    };
    msc_device.is_writeable_handler = [&]() {
        return true;
    };
    msc_device.start_stop_handler = [&](uint8_t power_condition, bool start, bool load_eject) {
//        msc_device.set_device_ready(false);
        if ((power_condition == 0) &&load_eject && !start) {
            driver.pullup_enable(false);
        }
    };
    msc_device.remove_handler = [&](bool prevent_removal) {
        led_rem = prevent_removal;
    };

    // Activate USB device
    driver.pullup_enable(true);

    // Wait until USB enumeration has finished
    printf("Waiting for USB connection on USB TARGET..\n");
    while (!controller.active_configuration) {
        task::sleep_ms(10);
    }

    // The first task handles the MSC requests in an endless loop.
    task msc_worker([&]() {
        while(true) {
            msc_device.handle_request();
            task::sleep_ms(5);
        }
    }, "MSC worker");
    msc_worker.sign_up();

    // The second task resets the LEDs to off. Since this task has
    // the same priority as the first task, it will get runtime, but
    // sleep most of the time.
    task led_reset([&]() {
        while(true) {
            // Switch off the LEDs using their related variables
            read_active = false;
            write_active= false;
            // Sleep, and during this sleep the variables above
            // might be set again...
            task::sleep_ms(200);
            // Check if the LEDs reflect the needed state.
            // Change the state if needed, and wait a little
            // bit so the WS2812 do not get confused...
            if (led_green.is_on() != read_active) {
                led_green = read_active;
                //task::sleep_ms(5);
            }
            if (led_red.is_on() != write_active) {
                led_red = write_active;
                //task::sleep_ms(5);
            }
        }
    }, "LED reset");
    led_reset.sign_up();

    puts("Starting scheduler");
    task::start_scheduler();
}
