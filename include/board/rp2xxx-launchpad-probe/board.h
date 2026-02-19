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
// This file defines the hardware components
// on the RP2xxx Launchpad Probe.
//
#ifndef RP2xxx_LAUNCHPAD_PROBE_BOARD_H
#define RP2xxx_LAUNCHPAD_PROBE_BOARD_H

#define YAHAL_BOARD_RP2xxx_LAUNCHPAD_PROBE

// The BC UART is available on a (non-populated) header.
#define BC_UART_TX      0
#define BC_UART_RX      1

// The LEDs for UART RX/TX and SWD activity
#define LED_RED_GPIO    4
#define LED_GREEN_GPIO  3
#define LED_BLUE_GPIO   2

// The SWD signals
#define SWCLK_GPIO      6
#define SWDIO_GPIO      7

// The UART interface to the target MCU
#define TARGET_UART_TX  8
#define TARGET_UART_RX  9

// Generic defines
#define COPY_TO_RAM     __attribute__((section(".move_to_ram")))
#define NO_INLINE       __attribute__((__noinline__))
#define FORCE_INLINE    __attribute__((always_inline))
#define CONSTRUCTOR     __attribute__((constructor))

#endif // RP2xxx_LAUNCHPAD_PROBE_BOARD_H
