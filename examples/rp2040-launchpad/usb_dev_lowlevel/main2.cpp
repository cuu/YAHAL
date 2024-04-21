#include "usb_cdc_acm_device.h"
#include "usb_device.h"
#include "usb_configuration.h"

#include "usb_dcd_rp2040.h"
#include "usb_device_controller.h"

#include "uart_rp2040.h"
#include "gpio_rp2040.h"
#include "task.h"
#include "posix_io.h"
#include "fifo.h"

#include <cstdio>

int main() {
    uart_rp2040 uart; // default is backchannel UART!

    posix_io::inst.register_stdin(uart);
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    // ESP8266 UART
    uart_rp2040     uart_esp( 1, 20, 21, 115200 );

    gpio_rp2040_pin button_s1( 16 );
    gpio_rp2040_pin button_s2( 17 );
    gpio_rp2040_pin esp_gpio0( 24 );
    gpio_rp2040_pin esp_gpio2( 25 );
//    gpio_rp2040_pin esp_gpio15( 3 );
    gpio_rp2040_pin esp_reset(  6 );
    gpio_rp2040_pin led(13);

    button_s1.gpioMode( GPIO::INPUT | GPIO::PULLUP);
    button_s2.gpioMode( GPIO::INPUT | GPIO::PULLUP);
    esp_gpio0.gpioMode( GPIO::OUTPUT_OPEN_DRAIN | GPIO::INIT_HIGH );
    esp_gpio2.gpioMode( GPIO::INPUT);
//    esp_gpio15.gpioMode( GPIO::OUTPUT);
    esp_reset.gpioMode( GPIO::OUTPUT | GPIO::DRIVE_12mA | GPIO::INIT_HIGH );
    led.gpioMode( GPIO::OUTPUT );

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
    config.set_bmAttributes( { .remote_wakeup = 0,
                               .self_powered  = 0,
                               .bus_powered   = 1 } );
    config.set_bMaxPower_mA(100);

    /////////////////////
    // USB CDC ACM device
    /////////////////////
    usb_cdc_acm_device acm_device(controller, config);

    acm_device.line_coding_handler = ([&](uint8_t *,uint16_t) {
        const char * parity[5] = {"N", "O", "E", "M", "S"};
        const char * stop[3]   = {"1", "1.5", "2"};
        printf("Line coding set to %d baud %d%s%s\n",
               (int)acm_device.line_coding.dwDTERate,
               (int)acm_device.line_coding.bDataBits,
               parity[(int)acm_device.line_coding.bParityType],
               stop[(int)acm_device.line_coding.bCharFormat]);

        uart_mode_t mode = 0;
        switch((int)acm_device.line_coding.bDataBits) {
            case 7: mode |= UART::BITS_7; break;
            case 8: mode |= UART::BITS_8; break;
            default: printf("Wrong number of bits!!\n");
        }
        switch((int)acm_device.line_coding.bParityType) {
            case (int)CDC::bParityType_t::PARITY_NONE:
                mode |= UART::NO_PARITY; break;
            case (int)CDC::bParityType_t::PARITY_EVEN:
                mode |= UART::EVEN_PARITY; break;
            case (int)CDC::bParityType_t::PARITY_ODD:
                mode |= UART::ODD_PARITY; break;
            default: printf("Wrong parity!\n");
        }
        switch((int)acm_device.line_coding.bCharFormat) {
            case (int)CDC::bCharFormat_t::STOP_BITS_1:
                mode |= UART::STOPBITS_1; break;
            case (int)CDC::bCharFormat_t::STOP_BITS_2:
                mode |= UART::STOPBITS_2; break;
            default: printf("Wrong stop bits!\n");
        }
        uart_esp.uartMode(mode);
        uart_esp.setBaudrate(acm_device.line_coding.dwDTERate);
    });

    acm_device.control_line_handler = ([&](bool dtr, bool rts) {
        printf("Control signals DTR=%d, RTS=%d\n", dtr, rts);
        esp_gpio0 = !dtr;
        esp_reset = !rts;
        task::sleep_ms(200);
    });

    acm_device.break_handler = ([](uint16_t millis) {
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
        task::sleep_ms(100);
    }

    printf("Bevor sending event...\n");

    CDC::bmUartState_t uart_state;
    uart_state.bRxCarrier_DCD = 1;
    uart_state.bTxCarrier_DSR = 1;
    acm_device.notify_serial_state( uart_state );

    printf("Entering endless loop...\n");

    uint8_t buf[64];
    while (1) {
        uint16_t len = acm_device.read(buf, 64);
        if (len) {
//            printf("Before write\n");
            acm_device.write(buf, len);
//            printf("After write\n");
        }
    }
}
