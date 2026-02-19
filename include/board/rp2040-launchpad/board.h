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
// on the RP2040 Launchpad.
//
#ifndef RP2040_LAUNCHPAD_BOARD_H
#define RP2040_LAUNCHPAD_BOARD_H

#define YAHAL_BOARD_RP2040_LAUNCHPAD

#define BC_UART_TX      0
#define BC_UART_RX      1

#define S1_GPIO         16
#define S2_GPIO         17

#define LED_RED_GPIO    13
#define LED_RGB_GPIO    29
#define LED_RGB_COUNT   8

#define ADC_MUX_GPIO    18

#define BATT_ADC        5

// Generic defines
#define COPY_TO_RAM     __attribute__((section(".move_to_ram")))
#define NO_INLINE       __attribute__((__noinline__))
#define FORCE_INLINE    __attribute__((always_inline))
#define CONSTRUCTOR     __attribute__((constructor))

#endif // RP2040_LAUNCHPAD_BOARD_H
