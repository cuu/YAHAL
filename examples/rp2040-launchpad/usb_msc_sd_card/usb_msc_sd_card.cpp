#include "usb_dcd_rp2040.h"
#include "usb_device_controller.h"
#include "usb_ms_compat_descriptor.h"
#include "usb_msc_bot_device.h"

#include "posix_io.h"
#include "uart_rp2040.h"
#include "gpio_rp2040.h"
#include "spi_rp2040.h"
#include "sd_spi_drv.h"
#include "ws2812_rp2040.h"
#include "task.h"
#include <cstdio>

// SD card hardware configuration.
#define MISO_PIN  8
#define MOSI_PIN 11
#define SCLK_PIN 10
#define CS_PIN    3
#define SPI1      1

int main() {
    uart_rp2040 uart; // default is backchannel UART!

    posix_io::inst.register_stdin(uart);
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    // Set up LEDs
    gpio_rp2040_pin led(13);
    led.gpioMode(GPIO::OUTPUT);

    // Setup two LEDs on the launchpad for blinking
    ws2812_rp2040 leds(29, 8);
    led_rgb_interface &led_red   = leds[0];
    led_rgb_interface &led_green = leds[1];
    led_red.set_on_color(0x040000);
    led_green.set_on_color(0x000500);
    bool read_active, write_active;

    // Set up the driver stack for the SD card
    gpio_rp2040_pin cs(CS_PIN);     // CS Line of SPI interface
    spi_rp2040     spi(SPI1, MISO_PIN, MOSI_PIN, SCLK_PIN, cs);
    sd_spi_drv      sd(spi);        // SD card low level driver

    // Switch on USB logging
    usb_log::inst.setLevel(LOG_INFO);
    // USB Device driver
    usb_dcd_rp2040 &driver = usb_dcd_rp2040::inst();
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
    // USB CDC ACM device
    /////////////////////
    usb_msc_bot_device msc_device(controller, config);
    msc_device.set_vendor_id  ("FH AC");
    msc_device.set_product_id ("MSC Test Device");
    msc_device.set_product_rev("1.0");

    // Set callback handlers
    msc_device.capacity_handler = [&](uint16_t &block_size,
                                      uint32_t &block_count) {
        block_size = 512;
        block_count = sd.getBlockCount();
    };
    msc_device.read_handler = [&](uint8_t *buff, uint32_t block) {
        auto res = sd.readBlock(buff, block, 1);
        if (res != BLOCKIO::result_t::OK) {
            TUPP_LOG(LOG_ERROR, "Reading SD card failed (%d)", res);
        }
        read_active = true;
    };
    msc_device.write_handler = [&](uint8_t *buff, uint32_t block) {
        auto res = sd.writeBlock(buff, block, 1);
        if (res != BLOCKIO::result_t::OK) {
            TUPP_LOG(LOG_ERROR, "Writing SD card failed (%d)", res);
        }
        write_active = true;
    };
    msc_device.is_writeable_handler = [&]() {
        return true;
    };

    // Activate USB device
    driver.pullup_enable(true);

    // Wait until USB enumeration has finished
    printf("Waiting for USB connection on USB TARGET..\n");
    while (!controller.active_configuration) {
        task::sleep_ms(100);
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
                task::sleep_ms(5);
            }
            if (led_red.is_on() != write_active) {
                led_red = write_active;
                task::sleep_ms(5);
            }
        }
    }, "LED reset");
    led_reset.start();

    task::start_scheduler();
}
