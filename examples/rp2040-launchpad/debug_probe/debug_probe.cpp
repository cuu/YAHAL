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
#include "config.h"

#include "usb_dcd.h"
#include "usb_device_controller.h"
#include "usb_ms_compat_descriptor.h"

#include "usb_dap_device.h"
#include "usb_uart_device.h"

#include "DAP_hw_rp2040_pio.h"
#include "DAP_hw_rp2040_gpio.h"
#include "DAP_log.h"

#ifdef YAHAL_BOARD_RP2xxx_LAUNCHPAD_PROBE
#include "DAP_led_rp2xxx_launchpad_probe.h"
#endif
#ifdef YAHAL_BOARD_RP2040_LAUNCHPAD
#include "DAP_led_rp2040_launchpad.h"
#endif

#include "bootrom_rp2040.h"
#include "posix_io.h"
#include "task.h"
#include "task_monitor.h"
#include "uart_rp2040.h"

int main() {
    // Get the unique ID of this board. This involves
    // switching the Flash into a different mode, so
    // do this right at the beginning if main. There
    // should not run any flash-based IRQ-handlers or
    // other flash-based background stuff right now!
    auto id = bootrom_rp2040::read_unique_id_string();

    // Debug UART (same as BC UART during development)
    uart_rp2040 uart(UART_DEBUG_TX_GPIO, UART_DEBUG_RX_GPIO);
    posix_io::inst.register_stdio(uart);

    // Switch on USB logging
    usb_log::inst.setLevel(usb_log::LOG_INFO);
    // USB Device driver
    usb_dcd &driver = usb_dcd::inst();
    // USB device: Root object of USB descriptor tree
    usb_device device;
    // Generic USB Device Controller on top
    usb_device_controller controller(driver, device);

    // USB device descriptor
    device.set_bcdUSB          (USB_DEV_bcdUSB);
    device.set_bMaxPacketSize0 (USB_DEV_bMaxPacketSize0);
    device.set_idVendor        (USB_DEV_VID);
    device.set_idProduct       (USB_DEV_PID);
    device.set_Manufacturer    (USB_DEV_Manufacturer);
    device.set_Product         (USB_DEV_Produt);
    device.set_SerialNumber    (id.data());
    device.set_bcdDevice       (USB_DEV_bcdDevice);

    // USB configuration descriptor
    usb_configuration config(device);
    config.set_bConfigurationValue(1);
    config.set_bmAttributes({ .remote_wakeup = 0,
                              .self_powered  = 0,
                              .bus_powered   = 1});
    config.set_bMaxPower_mA(100);

    // USB BOS descriptor
    usb_ms_compat_descriptor webusb(controller, device);

    //////////////////////////
    // Set up CMSIS DAP device
    //////////////////////////
    // Switch on DAP logging
    DAP_log::inst.setLevel(DAP_log::log_level::LOG_INFO);
    DAP_hw_rp2040_pio dap_hw;
    DAP_Protocol  dap(dap_hw);
    dap.set_serial(id.data());
    usb_dap_device dap_device(controller, config, dap);
    dap_device.sign_up();

    ////////////////////////
    // Set up CDC ACM device
    ////////////////////////
    uart_rp2040 bc_uart(UART_TARGET_TX_GPIO, UART_TARGET_RX_GPIO);
    usb_uart_device bc_uart_device(controller, config, bc_uart);
    bc_uart_device.sign_up();
    bc_uart_device.setPriority(90);

    //////////////
    // LED handler
    //////////////
    #ifdef YAHAL_BOARD_RP2xxx_LAUNCHPAD_PROBE
    DAP_led_rp2xxx_launchpad_probe leds;
    #endif
    #ifdef YAHAL_BOARD_RP2040_LAUNCHPAD
    DAP_led_rp2040_launchpad leds;
    #endif

    // Connect LEDs with USB UART and DAP callbacks
    usb_uart_device::uart_tx_cb = [&]()       { leds.trigger_uart_tx_led(); };
    usb_uart_device::uart_rx_cb = [&]()       { leds.trigger_uart_rx_led(); };
    DAP_Protocol::connected_cb  = [&](bool v) { leds.set_connected_led(v);  };
    DAP_Protocol::running_cb    = [&](bool v) { leds.set_running_led(v);    };
    leds.sign_up();
    leds.setPriority(50);
    leds.welcome();

    // Activate USB device after things have settled
    task::sleep_ms(200);
    driver.pullup_enable(true);

    // Wait until USB enumeration has finished
    TUPP_LOG(LOG_INFO, "Waiting for USB connection ...");
    while (!controller.active_configuration) {
        task::sleep_ms(100);
    }

    // Set DCD and DTR after USB has connected
    bc_uart_device.set_dcd_dtr(true, true);

    // Task Monitor
    #ifdef START_TASK_MONITOR
    task_monitor monitor;
    monitor.sign_up(core_t::CURRENT_CORE, 20);
    #endif

    // Start multitasking kernel
    task::start_scheduler();
}
