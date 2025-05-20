//#include "board.h"

#include "usb_dcd.h"
#include "usb_device_controller.h"
#include "usb_ms_compat_descriptor.h"
#include "usb_msc_bot_device.h"

#include "posix_io.h"
#include "uart_rp2350.h"
#include "gpio_rp2350.h"
#include "pio_rp2350.h"
#include "timer_rp2350.h"

#include "task.h"
#include "mutex.h"
#include "lock_base_rp2350.h"
#include <cstdio>
#include <cstring>

#include "mfm.pio.h"

#include "floppy_mfm_reader.h"
#include "floppy_logger.h"

#include "floppy_drv.h"

using namespace _TIMER0_;
using namespace FLOPPY;

int main() {
    uart_rp2350 uart; // default is back-channel UART!

    posix_io::inst.register_stdin(uart);
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    // Floppy adapter GPIOs
    gpio_rp2350 index           (20);
    gpio_rp2350 drive_select    (18);
    gpio_rp2350 motor_on        (17);
    gpio_rp2350 direction_select(11);
    gpio_rp2350 step            (16);
    gpio_rp2350 write_data      (12);
    gpio_rp2350 write_gate      (15);
    gpio_rp2350 track_00        (13);
    gpio_rp2350 write_protect   (10);
    gpio_rp2350 read_data       (14);
    gpio_rp2350 side_one_select (2);
    gpio_rp2350 disk_change     (1);

    timer_rp2350 motor_timer;

    floppy_pins pin_config = {
            .index              = index,
            .drive_select       = drive_select,
            .motor_on           = motor_on,
            .direction_select   = direction_select,
            .step               = step,
            .write_data         = write_data,
            .write_gate         = write_gate,
            .track_00           = track_00,
            .write_protect      = write_protect,
            .read_data          = read_data,
            .side_one_select    = side_one_select,
            .disk_change        = disk_change
    };

    LOG_LEVEL(FLOPPY::LOG_INFO);

    // The Floppy driver
    uint8_t * data;
    ret_t res;

    floppy_drv fd(pin_config, FLOPPY::TEAC_FD_235HF, motor_timer);

    res = fd.init();
    printf("Code %d, Field %d\n", res.code, res.field);
    floppy_statistics::inst().reset();

    for (int track=0; track < 10; ++track) {
        printf("track %d: ", track);
        for(int head=0; head <= fd.format->double_sided; ++head) {
            printf(" head %d: ", head);
            for(int sector=1; sector <= fd.format->sectors_per_track; ++sector) {
                res = fd.read_sector(track,head,sector, data);
                if (res == RET_CODE::SUCCESS) printf(".");
                else printf("Code %d, Field %d\n", res.code, res.field);
            }
        }
        puts("");
    }
    puts("");
    printf("Code %d, Field %d\n", res.code, res.field);

    floppy_statistics::inst().show();

    while(true) { __WFE(); }


    // Switch on USB logging
    usb_log::inst.setLevel(::LOG_INFO);
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
        block_count = 8192 * 2; //sd.getBlockCount();
    };
    msc_device.read_handler = [&](uint8_t *buff, uint32_t block) {
//        memcpy(buff, psram + (block << 9), 512);
//        auto res = sd.readBlock(buff, block, 1);
//        if (res != BLOCKIO::result_t::OK) {
//            TUPP_LOG(LOG_ERROR, "Reading SD card failed (%d)", res);
//        }
//        read_active = true;
        return BLOCKIO::result_t::OK;
    };
    msc_device.write_handler = [&](uint8_t *buff, uint32_t block) {
//        memcpy(psram + (block << 9), buff, 512);
//        auto res = sd.writeBlock(buff, block, 1);
//        if (res != BLOCKIO::result_t::OK) {
//            TUPP_LOG(LOG_ERROR, "Writing SD card failed (%d)", res);
//        }
//        write_active = true;
        return BLOCKIO::result_t::OK;
    };
    msc_device.is_writeable_handler = [&]() {
        return true;
    };
    msc_device.start_stop_handler = [&](bool start, bool load_eject) {
        if (load_eject && !start) {
//            driver.pullup_enable(false);
        }
    };
    msc_device.remove_handler = [&](bool prevent_removal) {
//        led_rem = prevent_removal;
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
        while(true) msc_device.handle_request();
    }, "MSC worker");
    msc_worker.start();

    // The second task resets the LEDs to off. Since this task has
    // the same priority as the first task, it will get runtime, but
    // sleep most of the time.
    task led_reset([&]() {
        while(true) {
            // Switch off the LEDs using their related variables
//            read_active = false;
//            write_active= false;
            // Sleep, and during this sleep the variables above
            // might be set again...
            task::sleep_ms(200);
            // Check if the LEDs reflect the needed state.
            // Change the state if needed, and wait a little
            // bit so the WS2812 do not get confused...
//            if (led_green.is_on() != read_active) {
//                led_green = read_active;
                //task::sleep_ms(5);
//            }
//            if (led_red.is_on() != write_active) {
//                led_red = write_active;
                //task::sleep_ms(5);
//            }
        }
    }, "LED reset");
//    led_reset.start();

    task::start_scheduler();
}
