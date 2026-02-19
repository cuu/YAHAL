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
#ifndef RPI_PICO_BOARD_H
#define RPI_PICO_BOARD_H

#define YAHAL_BOARD_RPI_PICO


#define BC_UART_TX      0
#define BC_UART_RX      1

// Generic defines
#define COPY_TO_RAM     __attribute__((section(".move_to_ram")))
#define NO_INLINE       __attribute__((__noinline__))
#define FORCE_INLINE    __attribute__((always_inline))
#define CONSTRUCTOR     __attribute__((constructor))

#endif // RPI_PICO_BOARD_H
