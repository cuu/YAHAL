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
// System startup code RP2350.
//
#ifndef _SYSTEM_RP2350_H_
#define _SYSTEM_RP2350_H_

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

// The global RP2350 system clocks in Hz
extern uint32_t CLK_REF;
extern uint32_t CLK_SYS;
extern uint32_t CLK_PERI;
extern uint32_t CLK_HSTX;
extern uint32_t CLK_USB;
extern uint32_t CLK_ADC;
extern uint32_t systick_ref_ticks_per_ms;
extern uint32_t timer_ticks_per_us;


// Set up the microcontroller system.
// Initialize the System and finally
// update the global clock variables.
void SystemInit (void);

// Calculate and set the global clock
// variables using the current configuration
// retrieved from cpu registers.
extern void ClockUpdate (void);

#ifdef __cplusplus
}
#endif

#endif // _SYSTEM_RP2350_H_
