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
// This is a programmer for the WiFiTick Board.
// When loaded on the RP2040, the lower (target)
// USB port has to be used to program the ESP8266!
//
#include "usb_dcd_rp2040.h"
#include "usb_device_controller.h"
#include "usb_cdc_acm_device.h"
#include "usb_ms_compat_descriptor.h"

#include "posix_io.h"
#include "uart_rp2040.h"
#include "gpio_rp2040.h"
#include "task.h"
#include "task_monitor.h"

#include <cstdio>

int main() {
    uart_rp2040 uart; // default is backchannel UART!

    posix_io::inst.register_stdin(uart);
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    // ESP8266 UART
    uart_rp2040 uart_esp( 1, 20, 21, 115200 );

    gpio_rp2040_pin button_s1( 16 );
    gpio_rp2040_pin button_s2( 17 );
    gpio_rp2040_pin esp_gpio0( 24 );
    gpio_rp2040_pin esp_gpio2( 25 );
    gpio_rp2040_pin esp_reset(  6 );
    gpio_rp2040_pin led(13);

    button_s1.gpioMode( GPIO::INPUT | GPIO::PULLUP);
    button_s2.gpioMode( GPIO::INPUT | GPIO::PULLUP);
    esp_gpio0.gpioMode( GPIO::OUTPUT_OPEN_DRAIN | GPIO::INIT_HIGH );
    esp_gpio2.gpioMode( GPIO::INPUT);
    esp_reset.gpioMode( GPIO::OUTPUT | GPIO::INIT_HIGH );
    led.gpioMode( GPIO::OUTPUT );

    printf("WifiTick Programmer\n");

    TUPP_LOG_LEVEL(LOG_INFO);
    // USB Device driver
    usb_dcd_rp2040 & driver = usb_dcd_rp2040::inst();
    // USB device: Root object of USB descriptor tree
    usb_device device;
    // Generic USB Device Controller on top
    usb_device_controller controller(driver, device);

    // USB device descriptor
    device.set_bcdUSB         (0x0210);
    device.set_bMaxPacketSize0(64);
    device.set_idVendor       (0x2e8a);
    device.set_idProduct      (0x0110);
    device.set_Manufacturer   ("FH Aachen");
    device.set_Product        ("WifiTick Programmer");

    // USB configuration descriptor
    usb_configuration config(device);
    config.set_bConfigurationValue(1);
    config.set_bmAttributes( { .remote_wakeup = 0,
                               .self_powered  = 0,
                               .bus_powered   = 1 } );
    config.set_bMaxPower_mA(100);

    // BOS descriptor (for Win compatibility)
    usb_ms_compat_descriptor compat(controller, device);

    // USB CDC ACM device and its handlers
    usb_cdc_acm_device acm_device(controller, config);

    bool line_code_updated = false;
    acm_device.line_coding_handler = [&](const CDC::line_coding_t &) {
        line_code_updated = true;
    };

    bool in_prgm_mode = false;
    acm_device.control_line_handler = ([&](bool dtr, bool rts) {
//        printf("Control signals DTR=%d, RTS=%d\n", dtr, rts);
        if (esp_reset == LOW && rts == LOW) {
            if (dtr) {
                // Programming mode
                printf("Program mode\n");
                uart_esp.setBaudrate(115200);
                in_prgm_mode = true;
            } else {
                // Run mode
                printf("Run mode\n");
                uart_esp.setBaudrate(74880);
                in_prgm_mode = false;
            }
        }
        esp_gpio0 = !dtr;
        esp_reset = !rts;
    });

    acm_device.break_handler = ([](uint16_t millis) {
        printf("Send break for 0x%04x milliseconds\n", millis);
    });

    //////////////////////
    // Activate USB device
    //////////////////////
    driver.pullup_enable(true);

    // GPIO3 is connected to ESP8266 GPIO15, which controls the
    // boot-mode of the ESP8266. The WiFiTick-board pulls this
    // pin to LOW, but the EDU-MKII pulls it to HIGH (because it
    // is the READY-line of the temperature sensor). So force
    // this pin to low so the ESP8266 is booting correctly.
    gpio_rp2040_pin gpio3 (3);
    gpio3.gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);

    //////////////////////////////////////////
    // Wait until USB enumeration has finished
    //////////////////////////////////////////
    printf("Waiting for USB connection on USB TARGET..\n");
// No need to wait ...
//    while (!controller.active_configuration) {
//        task::sleep_ms(100);
//    }

    CDC::bmUartState_t uart_state;
    uart_state.bRxCarrier_DCD = 1;
    uart_state.bTxCarrier_DSR = 1;
    acm_device.notify_serial_state( uart_state );

    esp_gpio2.gpioAttachIrq(GPIO::RISING | GPIO::FALLING, [&]() {
        led = !esp_gpio2;
    });

    uart_esp.uartAttachIrq([&](char c) {
        if (!in_prgm_mode && (c == 0xb0)) {
            uart_esp.setBaudrate(115200);
            const char * msg = "\r\n---end of boot messages---\r\n\n";
            acm_device.write((uint8_t *)msg, 31);
        } else {
            acm_device.write((uint8_t *)&c, 1);
        }
    });

    printf("Entering endless loop...\n");

    uint8_t buf[64];
    while (1) {
        if (line_code_updated) {
            TUPP_LOG(LOG_INFO, "Line code changed to %s",
                     acm_device.line_coding_2_str());

            uart_mode_t mode = 0;
            switch ((int) acm_device.line_coding.bDataBits) {
                case 7:
                    mode |= UART::BITS_7;
                    break;
                case 8:
                    mode |= UART::BITS_8;
                    break;
                default:
                    printf("Wrong number of bits!!\n");
            }
            switch ((int) acm_device.line_coding.bParityType) {
                case (int) CDC::bParityType_t::PARITY_NONE:
                    mode |= UART::NO_PARITY;
                    break;
                case (int) CDC::bParityType_t::PARITY_EVEN:
                    mode |= UART::EVEN_PARITY;
                    break;
                case (int) CDC::bParityType_t::PARITY_ODD:
                    mode |= UART::ODD_PARITY;
                    break;
                default:
                    printf("Wrong parity!\n");
            }
            switch ((int) acm_device.line_coding.bCharFormat) {
                case (int) CDC::bCharFormat_t::STOP_BITS_1:
                    mode |= UART::STOPBITS_1;
                    break;
                case (int) CDC::bCharFormat_t::STOP_BITS_2:
                    mode |= UART::STOPBITS_2;
                    break;
                default:
                    printf("Wrong stop bits!\n");
            }
            uart_esp.uartMode(mode);
            uart_esp.setBaudrate(acm_device.line_coding.dwDTERate);
            line_code_updated = false;
        }

        // Handle buttons in main loop
        if (button_s1 == LOW) {
            esp_reset = LOW;
            esp_gpio0 = HIGH;
            uart_esp.setBaudrate(74880);
            in_prgm_mode = false;
            while(!button_s1) ;
            task::sleep_ms(100);
            esp_reset = HIGH;
        }

        // Copy data from host to ESP8266
        uint16_t len = acm_device.read(buf, 64);
        for (int i=0; i < len; ++i) {
            uart_esp.putc(buf[i]);
        }
    }
}
