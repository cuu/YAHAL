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
// When loaded on the RP2350, the lower (target)
// USB port has to be used to program the ESP8266!
//
#include <cstdio>

#include "usb_dcd.h"
#include "usb_device_controller.h"
#include "usb_cdc_acm_device.h"
#include "usb_ms_compat_descriptor.h"

#include "posix_io.h"
#include "uart_rp2350.h"
#include "gpio_rp2350.h"
#include "task.h"
#include "task_monitor.h"

#include "board.h"
#include "wifiTick.h"

int main() {
    uart_rp2350 uart; // default is back channel UART!

    posix_io::inst.register_stdin(uart);
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    // LP buttons
    gpio_rp2350 button_s1( S1_GPIO );
    gpio_rp2350 button_s2( S2_GPIO );
    button_s1.gpioMode( GPIO::INPUT | GPIO::PULLUP);
    button_s2.gpioMode( GPIO::INPUT | GPIO::PULLUP);

    // ESP GPIO0 is controlling the boot mode. This line
    // has a pull-up on the Tick (1 = ESP Flash boot),
    // and has to be driven low for an ESP UART boot!
    gpio_rp2350 esp_gpio0( TICK_GPIO0 );
    esp_gpio0.gpioMode( GPIO::OUTPUT_OPEN_DRAIN | GPIO::INIT_HIGH );

    // ESP GPIO2 is controlling the boot mode. This line
    // has a pull-up on the Tick (1 = ESP FLASH/UART boot),
    // and is also used to control a LED on cheap ESP boards.
    // Polarity of the LED is reverse, so 0 -> LED on
    gpio_rp2350 esp_gpio2( TICK_GPIO2 );
    esp_gpio2.gpioMode( GPIO::INPUT);

    // The ESP reset line (active low)
    gpio_rp2350 esp_reset( TICK_nRESET );
    esp_reset.gpioMode( GPIO::INPUT | GPIO::OUTPUT | GPIO::INIT_HIGH );

    // The LED on the WifiTick, controlled by the LP
    gpio_rp2350 esp_led  ( TICK_LED );
    esp_led.gpioMode( GPIO::OUTPUT );

    // ESP8266 UART
    uart_rp2350 uart_esp( TICK_U0RXD, TICK_U0TXD, 115200 );

    printf("WifiTick Programmer\n");

    TUPP_LOG_LEVEL(LOG_INFO);
    // USB Device driver
    usb_dcd & driver = usb_dcd::inst();
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

    // Handler called when line code changed
    bool line_code_updated = false;
    acm_device.line_coding_handler = [&](const CDC::line_coding_t &) {
        line_code_updated = true;
    };

    // Handler called when control signals changed. Logic need
    // more explanation...
    bool in_prgm_mode = false;
    acm_device.control_line_handler = ([&](bool dtr, bool rts) {
        printf("Control signals DTR=%d, RTS=%d\n", dtr, rts);
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

    // Line break handler
    acm_device.break_handler = ([](uint16_t millis) {
        printf("Send break for 0x%04x milliseconds\n", millis);
    });

    //////////////////////
    // Activate USB device
    //////////////////////
    driver.pullup_enable(false);
    task::sleep_ms(200);
    driver.pullup_enable(true);

    //////////////////////////////////////////
    // Wait until USB enumeration has finished
    //////////////////////////////////////////
    printf("Waiting for USB connection on USB TARGET..\n");

    CDC::bmUartState_t uart_state;
    uart_state.bRxCarrier_DCD = 1;
    uart_state.bTxCarrier_DSR = 1;
    acm_device.notify_serial_state( uart_state );

    // Operate the LED on the Tick just like on
    // cheap ESP8266 boards (reverse polarity!)
    esp_gpio2.gpioAttachIrq(GPIO::RISING | GPIO::FALLING, [&]() {
        esp_led = !esp_gpio2;
    });

    // Forward any characters from ESP to the USB UART
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









//
//
/////////////////////////////////////////////////
////
//// WifiTick programmer
//// (c) 2017 A. Terstegge
////
//// Button S1: Reset line of ESP8266
//// Button S2: GPIO0 line of ESP8266
////
//// To program the ESP8266, S2 has to be pressed
//// while S1 is being released.
//// The back channel uart of the RP2350 lauchpad
//// is used for programming the ESP8266
//// (baud rate is 115200).
////
//// This program features automatic baud rate
//// selection on the ESP8266 side, so the boot
//// messages are also readable!
////
/////////////////////////////////////////////////
//
//#include "board.h"
//#include "wifiTick.h"
//#include "gpio_rp2350.h"
//#include "uart_rp2350.h"
//#include "task.h"
//
///////////////////////////////////
//// Hardware-dependent section. //
///////////////////////////////////
//
//struct HW {
//
//    // HW components
//    ////////////////
//    gpio_rp2350 button_s1;
//    gpio_rp2350 button_s2;
//    gpio_rp2350 esp_gpio0;
//    gpio_rp2350 esp_gpio2;
//    gpio_rp2350 red_led;
//    gpio_rp2350 esp_reset;
//    uart_rp2350 uart_bc;  // back-channel UART
//    uart_rp2350 uart_esp; // ESP8266 UART
//
//    HW() :
//    // HW configuration
//    ///////////////////
//            button_s1( S1_GPIO ),
//            button_s2( S2_GPIO ),
//            esp_gpio0( TICK_I2C_SDA ),
//            esp_gpio2( TICK_I2C_SCL ),
//            red_led  ( TICK_LED ),
//            esp_reset( TICK_nRESET ),
//            uart_bc  ( BC_UART_TX,   BC_UART_RX,   115200 ),
//            uart_esp ( TICK_UART_TX, TICK_UART_RX, 115200 ) {
//    }
//};
//
/////////////////////////////////////
//// Hardware-independent section. //
/////////////////////////////////////
//
//class Main {
//public:
//
//    void main() {
//
//        // Initialize GPIOs
//        hw.button_s1.gpioMode( GPIO::INPUT | GPIO::PULLUP);
//        hw.button_s1.gpioAttachIrq(GPIO::RISING, [this]() {
//            // Small delay for debounce
//            task::sleep_ms(20);
//            // Check the program button (S2)
//            in_prgm_mode   = !hw.button_s2.gpioRead();
//            baud_is_115200 = false;
//            baud_is_set    = false;
//        });
//        hw.button_s2.gpioMode( GPIO::INPUT | GPIO::PULLUP);
//        hw.esp_gpio0.gpioMode( GPIO::OUTPUT_OPEN_DRAIN | GPIO::INIT_HIGH );
//        hw.esp_gpio2.gpioMode( GPIO::INPUT );
//        hw.red_led  .gpioMode( GPIO::OUTPUT | GPIO::INIT_LOW  );
//        hw.esp_reset.gpioMode( GPIO::OUTPUT | GPIO::INIT_HIGH );
//
//        // Initialize UARTs
//        // Forward any chars from the back-channel UART to the ESP
//        hw.uart_bc.uartAttachIrq([this](char c) { hw.uart_esp.putc(c); });
//
//        // Forward any chars from the ESP to the back-channel UART
//        hw.uart_esp.uartAttachIrq([this](char c) {
//            static char magic_prgm[] = "\r\n\r\n";
//            static char magic_run[]  = "~ld\r";
//            static uint8_t cnt  = 0;
//
//            hw.uart_bc.putc(c);
//
//            // No check for magic strings during programming
//            if (in_prgm_mode && baud_is_115200) return;
//
//            // Simple state machine to check magic string
//            const char * magic_ptr = in_prgm_mode ? magic_prgm : magic_run;
//            switch(cnt) {
//                case 0: if (c==magic_ptr[0]) cnt = 1; break;
//                case 1: if (c==magic_ptr[1]) cnt = 2; else cnt = 0; break;
//                case 2: if (c==magic_ptr[2]) cnt = 3; else cnt = 0; break;
//                case 3: if (c==magic_ptr[3]) {
//                        // Change back to 115200 baud...
//                        hw.uart_bc.putc('\r');
//                        baud_is_115200 = true;
//                        baud_is_set    = false;
//                    } else
//                        cnt = 0;
//            }
//        });
//
//        // Put ESP8266 to programming mode as default
//        hw.esp_reset.gpioWrite( LOW );  task::sleep_ms(100);
//        hw.esp_gpio0.gpioWrite( LOW );  task::sleep_ms(100);
//        hw.esp_reset.gpioWrite( HIGH ); task::sleep_ms(100);
//
//        // The never-ending main loop
//        while(true) {
//            // Handle buttons in main loop
//            hw.esp_reset.gpioWrite( hw.button_s1.gpioRead() );
//            hw.esp_gpio0.gpioWrite( hw.button_s2.gpioRead() );
//
//            // Display the inverse of ESP gpio2 on the
//            // red LED. This behavior is similar to the
//            // well-known ESP-12-E module
//            hw.red_led.gpioWrite( !hw.esp_gpio2.gpioRead() );
//
//            // Change the baud-rate if needed
//            if (!baud_is_set) {
//                hw.uart_esp.setBaudrate( baud_is_115200 ? 115200 : 74880);
//                baud_is_set = true;
//            }
//        }
//    }
//
//private:
//
//    HW hw;
//    bool baud_is_115200 = true;
//    bool baud_is_set    = true;
//    bool in_prgm_mode   = false;
//};
//
//int main(void)
//{
//    Main m;
//    m.main();
//    return 0;
//}
//
