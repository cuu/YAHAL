//
// Created by andreas on 30.12.25.
//

#ifndef CONFIG_H
#define CONFIG_H

#include "usb_config.h"

// General
//#define START_TASK_MONITOR          true

// USB device configuration
///////////////////////////
#define USB_DEV_bcdUSB              0x210       // USB version in BCD
#define USB_DEV_bMaxPacketSize0     TUPP_DEFAULT_PAKET_SIZE
#define USB_DEV_VID                 0x2e8a      // Raspberry Pi (Trading) Limited
#define USB_DEV_PID                 0x1089      // RP2040 Lauchpad (see https://github.com/raspberrypi/usb-pid)
#define USB_DEV_Manufacturer        "FH Aachen"
#define USB_DEV_Produt              "RP2xxx Lauchpad Debug Probe"
#define USB_DEV_bcdDevice           0x0100      // Product version

// CMSIS DAP configuration
//////////////////////////
#define DAP_USB_IF_NAME             "CMSIS-DAP v2 Interface"
#define DAP_PROTOCOL_VERSION        "2.1.1"

// Vendor Name and Product Name. If these values are set to empty
// strings, the USB Device Information is used to obtain these values!
#define DAP_VENDOR_NAME             USB_DEV_Manufacturer
#define DAP_PRODUCT_NAME            USB_DEV_Produt
#define DAP_FIRMWARE_VERSION        "1.0"

// Device/Board information if debug probe is fixed to a dev board.
// Use empty strings if the chip device and board are not know.
#define DAP_DEVICE_VENDOR           "Raspberry Pi"
#define DAP_DEVICE_NAME             "RP2040"
#define DAP_BOARD_VENDOR            "FH Aachen"
#define DAP_BOARD_NAME              "RP2040 Launchpad"

// Maximum Package Buffers for Command and Response data.
// This configuration settings is used to optimize the communication
// performance with the debugger and depends on the USB peripheral.
#define DAP_MAX_PACKET_COUNT        10

// Maximum Package Size for Command and Response data.
// This configuration settings is used to optimize the communication
// performance with the debugger and depends on the USB peripheral.
// Typical vales are 64 for Full-speed USB HID or WinUSB,
// 1024 for High-speed USB HID and 512 for High-speed USB WinUSB.
#define DAP_MAX_PACKET_SIZE         TUPP_DEFAULT_PAKET_SIZE

// CMSIS DAP Protocol support
#define DAP_CAP_SWD_SUPPORT         true
#define DAP_CAP_JTAG_SUPPORT        false
#define DAP_DEFAULT_PORT            PORT_SWD
#define DAP_DEFAULT_CLOCK           1000000

// SWO settings
#define DAP_CAP_SWO_UART            false
#define DAP_CAP_SWO_MANCHESTER      false
#define DAP_CAP_SWO_STREAMING_TRACE false
#define DAP_SWO_BUFFER_SIZE         0

// DAP UART settings
#define DAP_CAP_UART_COM_PORT       false
#define DAP_CAP_USB_COM_PORT        false
#define DAP_UART_RX_SIZE            0
#define DAP_UART_TX_SIZE            0


#define JTAG_DEV_COUNT              8
#define JTAG_IR_LENGTH              4

// SWD/JTAG Hardware configuration
#define GPIO_SWCLK                  6
#define GPIO_SWDIO                  7


// USB UART configuration
/////////////////////////
#define UART_TARGET_TX_GPIO         8           // probe to target
#define UART_TARGET_RX_GPIO         9           // target to probe
#define UART_TARGET_BUFFER_SIZE     1024

// Debug UART configuration
///////////////////////////
#define UART_DEBUG_TX_GPIO          0           // Same as back channel UART
#define UART_DEBUG_RX_GPIO          1           // on RP2xxx Launchpads

#endif // CONFIG_H

