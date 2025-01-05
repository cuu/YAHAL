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
// Complete CPU and peripheral register
// definitions for the RP2350 MCU. This
// file only covers the ARM Cortex-M33
// CPUs, not the RISCV-processors!
//
#ifndef _RP2350_H_
#define _RP2350_H_

// ======================================================
// ===========  Interrupt Number Definition  ============
// ======================================================
typedef enum {
    // ====  ARM Cortex-M33 Specific Interrupt Numbers  =====
    Reset_IRQn              = -15,
    NonMaskableInt_IRQn     = -14,
    HardFault_IRQn          = -13,
    MemoryManagement_IRQn   = -12,
    BusFault_IRQn           = -11,
    UsageFault_IRQn         = -10,
    SecureFault_IRQn        = -9,
    SVCall_IRQn             = -5,
    DebugMonitor_IRQn       = -4,
    PendSV_IRQn             = -2,
    SysTick_IRQn            = -1,

    // ========  RP2350 Specific Interrupt Numbers  =========
    TIMER0_IRQ_0_IRQn       = 0,
    TIMER0_IRQ_1_IRQn       = 1,
    TIMER0_IRQ_2_IRQn       = 2,
    TIMER0_IRQ_3_IRQn       = 3,
    TIMER1_IRQ_0_IRQn       = 4,
    TIMER1_IRQ_1_IRQn       = 5,
    TIMER1_IRQ_2_IRQn       = 6,
    TIMER1_IRQ_3_IRQn       = 7,
    PWM_IRQ_WRAP_0_IRQn     = 8,
    PWM_IRQ_WRAP_1_IRQn     = 9,
    DMA_IRQ_0_IRQn          = 10,
    DMA_IRQ_1_IRQn          = 11,
    DMA_IRQ_2_IRQn          = 12,
    DMA_IRQ_3_IRQn          = 13,
    USBCTRL_IRQ_IRQn        = 14,
    PIO0_IRQ_0_IRQn         = 15,
    PIO0_IRQ_1_IRQn         = 16,
    PIO1_IRQ_0_IRQn         = 17,
    PIO1_IRQ_1_IRQn         = 18,
    PIO2_IRQ_0_IRQn         = 19,
    PIO2_IRQ_1_IRQn         = 20,
    IO_IRQ_BANK0_IRQn       = 21,
    IO_IRQ_BANK0_NS_IRQn    = 22,
    IO_IRQ_QSPI_IRQn        = 23,
    IO_IRQ_QSPI_NS_IRQn     = 24,
    SIO_IRQ_FIFO_IRQn       = 25,
    SIO_IRQ_BELL_IRQn       = 26,
    SIO_IRQ_FIFO_NS_IRQn    = 27,
    SIO_IRQ_BELL_NS_IRQn    = 28,
    SIO_IRQ_MTIMECMP_IRQn   = 29,
    CLOCKS_IRQ_IRQn         = 30,
    SPI0_IRQ_IRQn           = 31,
    SPI1_IRQ_IRQn           = 32,
    UART0_IRQ_IRQn          = 33,
    UART1_IRQ_IRQn          = 34,
    ADC_IRQ_FIFO_IRQn       = 35,
    I2C0_IRQ_IRQn           = 36,
    I2C1_IRQ_IRQn           = 37,
    OTP_IRQ_IRQn            = 38,
    TRNG_IRQ_IRQn           = 39,
    PLL_SYS_IRQ_IRQn        = 42,
    PLL_USB_IRQ_IRQn        = 43,
    POWMAN_IRQ_POW_IRQn     = 44,
    POWMAN_IRQ_TIMER_IRQn   = 45
} IRQn_Type;

// ======================================================
// ======  Processor and Core Peripheral Section  =======
// ======================================================

//==  Configuration of the ARM Cortex-M33 Processor and Core Peripherals  ==
#define __CM33_REV                0x0100U       // CM33 Core Revision
#define __NVIC_PRIO_BITS               4        // Number of Bits used for Priority Levels
#define __Vendor_SysTickConfig         0        // Set to 1 if different SysTick Config is used
#define __VTOR_PRESENT                 1        // Set to 1 if CPU supports Vector Table Offset Register
#define __MPU_PRESENT                  1        // MPU present
#define __FPU_PRESENT                  1        // FPU present
#define __FPU_DP                       0        // Double Precision FPU
#define __DSP_PRESENT                  1        // DSP extension present
#define __SAUREGION_PRESENT            1        // SAU region present

#include "core_cm33.h"   // ARM Cortex-M33 processor and core peripherals

// Additional CPU defines are placed here
#define EXC_RETURN_BASE 0xffffff80UL
#define EXC_RETURN_NON_SECURE_STACK_FRAME   (0UL << 6)
#define EXC_RETURN_SECURE_STACK_FRAME       (1UL << 6)
#define EXC_RETURN_CALLEE_STACKING_SKIPPED  (0UL << 5)
#define EXC_RETURN_NORMAL_CALLEE_STACKING   (1UL << 5)
#define EXC_RETURN_EXTENDED_STACK_FRAME     (0UL << 4)
#define EXC_RETURN_INT_ONLY_STACK_FRAME     (1UL << 4)
#define EXC_RETURN_HANDLER_MODE             (0UL << 3)
#define EXC_RETURN_THREAD_MODE              (1UL << 3)
#define EXC_RETURN_MAIN_STACK_POINTER       (0UL << 2)
#define EXC_RETURN_PROCESS_STACK_POINTER    (1UL << 2)
#define EXC_RETURN_EXCEPTION_NON_SECURE     (0UL << 0)
#define EXC_RETURN_EXCEPTION_SECURE         (1UL << 0)

#define EXC_RETURN_THREAD_PSP_NOFP          (EXC_RETURN_BASE | \
                                            EXC_RETURN_SECURE_STACK_FRAME | \
                                            EXC_RETURN_EXCEPTION_SECURE | \
                                            EXC_RETURN_NORMAL_CALLEE_STACKING | \
                                            EXC_RETURN_INT_ONLY_STACK_FRAME | \
                                            EXC_RETURN_THREAD_MODE | \
                                            EXC_RETURN_PROCESS_STACK_POINTER )

#define EXC_RETURN_THREAD_PSP_NOFP_NS       (EXC_RETURN_BASE | \
                                            EXC_RETURN_NON_SECURE_STACK_FRAME | \
                                            EXC_RETURN_EXCEPTION_NON_SECURE | \
                                            EXC_RETURN_NORMAL_CALLEE_STACKING | \
                                            EXC_RETURN_INT_ONLY_STACK_FRAME | \
                                            EXC_RETURN_THREAD_MODE | \
                                            EXC_RETURN_PROCESS_STACK_POINTER )

#define CONTROL_SPSEL_PSP   CONTROL_SPSEL_Msk
#define CONTROL_SPSEL_MSP   0
#define CONTROL_NOT_PRIV    CONTROL_nPRIV_Msk
#define CONTROL_PRIV        0

// ======================================================
// =============  MCU Peripheral Section ================
// ======================================================

// necessary because some register fields
// in the RP2350 are called 'DEBUG'...
#undef DEBUG
#include "RP2350_regs.h"    // RP2350 peripherals and registers

#endif // _RP2350_H
