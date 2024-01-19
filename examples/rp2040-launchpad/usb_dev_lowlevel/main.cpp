#include "usb_msc_bot_device.h"
#include "usb_device.h"
#include "usb_configuration.h"

#include "usb_dcd_rp2040.h"
#include "usb_device_controller.h"

#include "usb_bos.h"
#include "usb_bos_dev_cap_platform_ms.h"
#include "usb_bos_dev_cap_webusb_ms.h"

#include "usb_ms_header.h"
#include "usb_ms_config_subset.h"
#include "usb_ms_func_subset.h"
#include "usb_ms_compatible_ID.h"
#include "usb_ms_registry_property.h"

#include "uart_rp2040.h"
#include "gpio_rp2040.h"
#include "task.h"
#include "task_monitor.h"
#include "posix_io.h"
#include "ws2812_rp2040.h"
#include <cstdio>
#include <cstring>

#include "sd_spi_drv.h"
#include "spi_rp2040.h"

// Hardware configuration.
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
    led_rgb_interface & led_red   = leds[0];
    led_rgb_interface & led_green = leds[1];
    led_red.set_on_color(0x040000);
    led_green.set_on_color(0x000500);

    // Set up the driver stack for the SD card
    gpio_rp2040_pin cs ( CS_PIN );     // CS Line of SPI interface
    spi_rp2040      spi( SPI1, MISO_PIN, MOSI_PIN, SCLK_PIN, cs );
    sd_spi_drv      sd ( spi );        // SD card low level driver

    // USB Device driver
    usb_dcd_rp2040 & driver = usb_dcd_rp2040::inst();
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
    device.set_idProduct      (0x0111);
    device.set_Manufacturer   ("FH Aachen");
    device.set_Product        ("MSC test device");

    ////////////////////////
    // USB BOS descriptor //
    ////////////////////////
    // {3408b638-09a9-47a0-8bfd-a0768815b665}
    uint8_t uuid1[16] = { 0x38, 0xB6, 0x08, 0x34, 0xA9, 0x09, 0xA0, 0x47,
                          0x8B, 0xFD, 0xA0, 0x76, 0x88, 0x15, 0xB6, 0x65 };

    // {d8dd60df-4589-4cc7-9cd2-659d9e648a9f}
    uint8_t uuid2[16] = { 0xDF, 0x60, 0xDD, 0xD8, 0x89, 0x45, 0xC7, 0x4C,
                          0x9C, 0xD2, 0x65, 0x9D, 0x9E, 0x64, 0x8A, 0x9F };

    uint32_t win_version    = 0x06030000;

    usb_bos bos(device);

    usb_bos_dev_cap_webusb_ms web_platform(bos);
    web_platform.set_PlatformCapabilityUUID ( uuid1 );
    web_platform.set_bcdVersion             ( 0x0100 );
    web_platform.set_bVendorCode            ( USB::bRequest_t::REQ_GET_STATUS );
    web_platform.set_iLandingPage           ( "\x01" "fh-aachen.de");

    usb_bos_dev_cap_platform_ms cap_platform(bos);
    cap_platform.set_PlatformCapabilityUUID ( uuid2 );
    cap_platform.set_dwWindowsVersion       ( win_version );
    cap_platform.set_bMS_VendorCode         ( USB::bRequest_t::REQ_GET_DESCRIPTOR );
    cap_platform.set_bAltEnumCode           ( 0 );

    usb_ms_header ms_header                 ( cap_platform );
    ms_header.set_dwWindowsVersion          ( win_version );

    usb_ms_config_subset ms_config_subset   ( ms_header );

    usb_ms_func_subset ms_func_subset       ( ms_config_subset );

    usb_ms_compatible_ID ms_compat_id       ( ms_func_subset );
    ms_compat_id.set_compatible_id          ( "WINUSB" );
    ms_compat_id.set_sub_compatible_id      ( "" );

    usb_ms_registry_property ms_reg_prop    ( ms_func_subset );
    ms_reg_prop.add_property_name           ( "DeviceInterfaceGUIDs\0" );
    ms_reg_prop.add_property_value          ( "{CDB3B5AD-293B-4663-AA36-1AAE46463776}" );

//    printf("Header len %04x\n", ms_header.descriptor.wLength);
//    printf("Header ttl %04x\n", ms_header.descriptor.wTotalLength);
//    printf("Config len %04x\n", ms_config_subset.descriptor.wLength);
//    printf("Config ttl %04x\n", ms_config_subset.descriptor.wTotalLength);
//    printf("Func   len %04x\n", ms_func_subset.descriptor.wLength);
//    printf("Func   sub %04x\n", ms_func_subset.descriptor.wSubsetLength);
//    printf("Compat len %04x\n", ms_compat_id.descriptor.wLength);
//    printf("Prop   len %04x\n", ms_reg_prop.get_length());

    uint8_t buff[256];
    uint8_t buff_url[32] {};
    uint8_t * tmp_ptr = buff;

    auto * ptr = &ms_header.descriptor;
    auto   len =  ms_header.descriptor.wLength;
    memcpy(tmp_ptr, ptr, len);
    tmp_ptr += len;
    for (uint16_t c=0; c < ms_header._config_subsets.size(); ++c) {
        auto * ptr = &ms_header._config_subsets[c]->descriptor;
        auto   len =  ms_header._config_subsets[c]->descriptor.wLength;
        memcpy(tmp_ptr, ptr, len);
        tmp_ptr += len;
        for (uint16_t f=0; f < ms_header._config_subsets[c]->_func_subsets.size(); ++f) {
            auto  ptr = &ms_header._config_subsets[c]->_func_subsets[f]->descriptor;
            auto  len  = ms_header._config_subsets[c]->_func_subsets[f]->descriptor.wLength;
            memcpy(tmp_ptr, ptr, len);
            tmp_ptr += len;
            if (ms_header._config_subsets[c]->_func_subsets[f]->_compat_id) {
                auto ptr = &ms_header._config_subsets[c]->_func_subsets[f]->_compat_id->descriptor;
                auto len =  ms_header._config_subsets[c]->_func_subsets[f]->_compat_id->descriptor.wLength;
                memcpy(tmp_ptr, ptr, len);
                tmp_ptr += len;
            }
            for (uint16_t p=0; p < ms_header._config_subsets[c]->_func_subsets[f]->_reg_props.size(); ++p) {
                auto ptr = ms_header._config_subsets[c]->_func_subsets[f]->_reg_props[p]->descriptor();
                auto len = ms_header._config_subsets[c]->_func_subsets[f]->_reg_props[p]->get_length();
                memcpy(tmp_ptr, ptr, len);
                tmp_ptr += len;
            }
        }
    }

    device.setup_handler = [&] (USB::setup_packet_t * pkt) {
        printf("In device vendor handler! %d\n", pkt->wLength);
        if ( (pkt->bRequest == USB::bRequest_t::REQ_GET_STATUS) &&
             (pkt->wIndex == 2) ) {
            // URL
            uint8_t len = usb_strings::inst.prepare_buffer_utf8(pkt->wValue, buff_url);
            if (len > pkt->wLength) len = pkt->wLength;
            controller._ep0_in->start_transfer(buff_url, len);
        } else if ( (pkt->bRequest == USB::bRequest_t::REQ_GET_DESCRIPTOR) &&
                    (pkt->wValue   == 0) && (pkt->wIndex == 7) ) {
            // Header
            controller._ep0_in->start_transfer(buff, tmp_ptr-buff);
        } else {
            controller._ep0_in->send_stall(true);
            controller._ep0_out->send_stall(true);
        }
    };

    ///////////////////////////////
    // USB configuration descriptor
    ///////////////////////////////
    usb_configuration config(device);
    config.set_bConfigurationValue(1);
    config.set_bmAttributes( { .remote_wakeup = 0,
                               .self_powered  = 0,
                               .bus_powered   = 1 } );
    config.set_bMaxPower_mA(100);

    /////////////////////
    // USB CDC ACM device
    /////////////////////
    usb_msc_bot_device msc_device(controller, config);

    // Set callback handlers
    msc_device.capacity_handler = [&](uint16_t & block_size,
                                      uint32_t & block_count) {
        block_size  = 512;
        block_count = sd.getBlockCount();
    };
    msc_device.read_handler = [&](uint8_t * buff, uint32_t block) {
        sd.readBlock(buff, block, 1);
    };
    msc_device.write_handler = [&](uint8_t * buff, uint32_t block) {
        sd.writeBlock(buff, block, 1);
    };
    msc_device.activity_handler = [&](bool r, bool w) {
        led_green = r;
        led_red   = w;
    };

    //////////////////////
    // Activate USB device
    //////////////////////
    driver.pullup_enable(true);

    //////////////////////////////////////////
    // Wait until USB enumeration has finished
    //////////////////////////////////////////
    printf("Waiting for USB connection on USB TARGET..\n");
    while (!controller.active_configuration) {
        task::sleep(100);
    }

    printf("Entering endless loop...\n");

    while (1) {
        msc_device.handle_request();
    }
}
