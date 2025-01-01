
#ifndef _CMSIS_SYSTEM_RP2350_H_
#define _CMSIS_SYSTEM_RP2350_H_

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

// The RP2350 system clocks in Hz
extern uint32_t CLK_REF;
extern uint32_t CLK_SYS;
extern uint32_t CLK_PERI;
extern uint32_t CLK_HSTX;
extern uint32_t CLK_USB;
extern uint32_t CLK_ADC;

// Set up the microcontroller system.
// Initialize the System and finally
// update the SystemCoreClock variable
void SystemInit (void);

// Updates the SystemCoreClock with current
// core Clock retrieved from cpu registers.
extern void ClockUpdate (void);

#ifdef __cplusplus
}
#endif

#endif // _CMSIS_SYSTEM_RP2350_H_
