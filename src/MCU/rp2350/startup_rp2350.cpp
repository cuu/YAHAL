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
// Startup code for RP2350.
//
#include "boot/boot_blocks.h"
#include "system_rp2350.h"
#include "RP2350.h"
using namespace _PPB_;

#ifdef __cplusplus
extern "C" {
#endif

// Macro Definitions
#define WEAK_FUNC(FUN) \
void FUN(void) __attribute__ ((weak));
#define WEAK_INT_FUNC(FUN) \
int FUN() __attribute__ ((weak));
#define WEAK_ALIAS_FUNC(FUN, FUN_ALIAS) \
void FUN(void) __attribute__ ((weak, alias(#FUN_ALIAS)));
#define WEAK_ALIAS_INT_FUNC(FUN, FUN_ALIAS) \
int FUN() __attribute__ ((weak, alias(#FUN_ALIAS)));

// External variables and functions
extern void     __cmsis_start(void);
extern uint32_t __StackTop;

typedef void (*pFunc)(void);

// Forward declaration of the implemented handlers.
WEAK_FUNC(Default_Handler)
WEAK_FUNC(Reset_Handler)
WEAK_INT_FUNC(return_0)

// Cortex-M33 Processor Exceptions
WEAK_ALIAS_FUNC(NMI_Handler,                Default_Handler)
WEAK_ALIAS_FUNC(HardFault_Handler,          Default_Handler)
WEAK_ALIAS_FUNC(MemoryManagement_Handler,   Default_Handler)
WEAK_ALIAS_FUNC(BusFault_Handler,           Default_Handler)
WEAK_ALIAS_FUNC(UsageFault_Handler,         Default_Handler)
WEAK_ALIAS_FUNC(SecureFault_Handler,        Default_Handler)
WEAK_ALIAS_FUNC(SVC_Handler,                Default_Handler)
WEAK_ALIAS_FUNC(DebugMonitor_Handler,       Default_Handler)
WEAK_ALIAS_FUNC(PendSV_Handler,             Default_Handler)
WEAK_ALIAS_FUNC(SysTick_Handler,            Default_Handler)

// Device specific interrupt handler

WEAK_ALIAS_FUNC(TIMER0_IRQ_0_Handler,       Default_Handler)
WEAK_ALIAS_FUNC(TIMER0_IRQ_1_Handler,       Default_Handler)
WEAK_ALIAS_FUNC(TIMER0_IRQ_2_Handler,       Default_Handler)
WEAK_ALIAS_FUNC(TIMER0_IRQ_3_Handler,       Default_Handler)
WEAK_ALIAS_FUNC(TIMER1_IRQ_0_Handler,       Default_Handler)
WEAK_ALIAS_FUNC(TIMER1_IRQ_1_Handler,       Default_Handler)
WEAK_ALIAS_FUNC(TIMER1_IRQ_2_Handler,       Default_Handler)
WEAK_ALIAS_FUNC(TIMER1_IRQ_3_Handler,       Default_Handler)
WEAK_ALIAS_FUNC(PWM_IRQ_WRAP_0_Handler,     Default_Handler)
WEAK_ALIAS_FUNC(PWM_IRQ_WRAP_1_Handler,     Default_Handler)
WEAK_ALIAS_FUNC(DMA_IRQ_0_Handler,          Default_Handler)
WEAK_ALIAS_FUNC(DMA_IRQ_1_Handler,          Default_Handler)
WEAK_ALIAS_FUNC(DMA_IRQ_2_Handler,          Default_Handler)
WEAK_ALIAS_FUNC(DMA_IRQ_3_Handler,          Default_Handler)
WEAK_ALIAS_FUNC(USBCTRL_IRQ_Handler,        Default_Handler)
WEAK_ALIAS_FUNC(PIO0_IRQ_0_Handler,         Default_Handler)
WEAK_ALIAS_FUNC(PIO0_IRQ_1_Handler,         Default_Handler)
WEAK_ALIAS_FUNC(PIO1_IRQ_0_Handler,         Default_Handler)
WEAK_ALIAS_FUNC(PIO1_IRQ_1_Handler,         Default_Handler)
WEAK_ALIAS_FUNC(PIO2_IRQ_0_Handler,         Default_Handler)
WEAK_ALIAS_FUNC(PIO2_IRQ_1_Handler,         Default_Handler)
WEAK_ALIAS_FUNC(IO_IRQ_BANK0_Handler,       Default_Handler)
WEAK_ALIAS_FUNC(IO_IRQ_BANK0_NS_Handler,    Default_Handler)
WEAK_ALIAS_FUNC(IO_IRQ_QSPI_Handler,        Default_Handler)
WEAK_ALIAS_FUNC(IO_IRQ_QSPI_NS_Handler,     Default_Handler)
WEAK_ALIAS_FUNC(SIO_IRQ_FIFO_Handler,       Default_Handler)
WEAK_ALIAS_FUNC(SIO_IRQ_BELL_Handler,       Default_Handler)
WEAK_ALIAS_FUNC(SIO_IRQ_FIFO_NS_Handler,    Default_Handler)
WEAK_ALIAS_FUNC(SIO_IRQ_BELL_NS_Handler,    Default_Handler)
WEAK_ALIAS_FUNC(SIO_IRQ_MTIMECMP_Handler,   Default_Handler)
WEAK_ALIAS_FUNC(CLOCKS_IRQ_Handler,         Default_Handler)
WEAK_ALIAS_FUNC(SPI0_IRQ_Handler,           Default_Handler)
WEAK_ALIAS_FUNC(SPI1_IRQ_Handler,           Default_Handler)
WEAK_ALIAS_FUNC(UART0_IRQ_Handler,          Default_Handler)
WEAK_ALIAS_FUNC(UART1_IRQ_Handler,          Default_Handler)
WEAK_ALIAS_FUNC(ADC_IRQ_FIFO_Handler,       Default_Handler)
WEAK_ALIAS_FUNC(I2C0_IRQ_Handler,           Default_Handler)
WEAK_ALIAS_FUNC(I2C1_IRQ_Handler,           Default_Handler)
WEAK_ALIAS_FUNC(OTP_IRQ_Handler,            Default_Handler)
WEAK_ALIAS_FUNC(TRNG_IRQ_Handler,           Default_Handler)
WEAK_ALIAS_FUNC(PLL_SYS_IRQ_Handler,        Default_Handler)
WEAK_ALIAS_FUNC(PLL_USB_IRQ_Handler,        Default_Handler)
WEAK_ALIAS_FUNC(POWMAN_IRQ_POW_Handler,     Default_Handler)
WEAK_ALIAS_FUNC(POWMAN_IRQ_TIMER_Handler,   Default_Handler)

// The interrupt vector table.
void (* const isr_vector[])(void) __attribute__((section(".isr_vector"), used)) = {
    (pFunc) &__StackTop,            // The initial stack pointer

    Reset_Handler,                  // -15 The reset handler
    NMI_Handler,                    // -14 The NMI handler
    HardFault_Handler,              // -13 The hard fault handler
    MemoryManagement_Handler,       // -12 The Memory Management handler
    BusFault_Handler,               // -11 The Bus Fault handler
    UsageFault_Handler,             // -10 The Usage Fault handler
    SecureFault_Handler,            //  -9 The Secure Fault handler
    nullptr,                        //  -8 Reserved
    nullptr,                        //  -7 Reserved
    nullptr,                        //  -6 Reserved
    SVC_Handler,                    //  -5 SVCall handler
    DebugMonitor_Handler,           //  -4 The Debug Monitor handler
    nullptr,                        //  -3 Reserved
    PendSV_Handler,                 //  -2 The PendSV handler
    SysTick_Handler,                //  -1 The SysTick handler

    TIMER0_IRQ_0_Handler,           //  0 TIMER0_IRQ_0
    TIMER0_IRQ_1_Handler,           //  1 TIMER0_IRQ_1
    TIMER0_IRQ_2_Handler,           //  2 TIMER0_IRQ_2
    TIMER0_IRQ_3_Handler,           //  3 TIMER0_IRQ_3
    TIMER1_IRQ_0_Handler,           //  4 TIMER1_IRQ_0
    TIMER1_IRQ_1_Handler,           //  5 TIMER1_IRQ_1
    TIMER1_IRQ_2_Handler,           //  6 TIMER1_IRQ_2
    TIMER1_IRQ_3_Handler,           //  7 TIMER1_IRQ_3
    PWM_IRQ_WRAP_0_Handler,         //  8 PWM_IRQ_WRAP_0
    PWM_IRQ_WRAP_1_Handler,         //  9 PWM_IRQ_WRAP_1
    DMA_IRQ_0_Handler,              // 10 DMA_IRQ_0
    DMA_IRQ_1_Handler,              // 11 DMA_IRQ_1
    DMA_IRQ_2_Handler,              // 12 DMA_IRQ_2
    DMA_IRQ_3_Handler,              // 13 DMA_IRQ_3
    USBCTRL_IRQ_Handler,            // 14 USBCTRL_IRQ
    PIO0_IRQ_0_Handler,             // 15 PIO0_IRQ_0
    PIO0_IRQ_1_Handler,             // 16 PIO0_IRQ_1
    PIO1_IRQ_0_Handler,             // 17 PIO1_IRQ_0
    PIO1_IRQ_1_Handler,             // 18 PIO1_IRQ_1
    PIO2_IRQ_0_Handler,             // 19 PIO2_IRQ_0
    PIO2_IRQ_1_Handler,             // 20 PIO2_IRQ_1
    IO_IRQ_BANK0_Handler,           // 21 IO_IRQ_BANK0
    IO_IRQ_BANK0_NS_Handler,        // 22 IO_IRQ_BANK0_NS
    IO_IRQ_QSPI_Handler,            // 23 IO_IRQ_QSPI
    IO_IRQ_QSPI_NS_Handler,         // 24 IO_IRQ_QSPI_NS
    SIO_IRQ_FIFO_Handler,           // 25 SIO_IRQ_FIFO
    SIO_IRQ_BELL_Handler,           // 26 SIO_IRQ_BELL
    SIO_IRQ_FIFO_NS_Handler,        // 27 SIO_IRQ_FIFO_NS
    SIO_IRQ_BELL_NS_Handler,        // 28 SIO_IRQ_BELL_NS
    SIO_IRQ_MTIMECMP_Handler,       // 29 SIO_IRQ_MTIMECMP
    CLOCKS_IRQ_Handler,             // 30 CLOCKS_IRQ
    SPI0_IRQ_Handler,               // 31 SPI0_IRQ
    SPI1_IRQ_Handler,               // 32 SPI1_IRQ
    UART0_IRQ_Handler,              // 33 UART0_IRQ
    UART1_IRQ_Handler,              // 34 UART1_IRQ
    ADC_IRQ_FIFO_Handler,           // 35 ADC_IRQ_FIFO
    I2C0_IRQ_Handler,               // 36 I2C0_IRQ
    I2C1_IRQ_Handler,               // 37 I2C1_IRQ
    OTP_IRQ_Handler,                // 38 OTP_IRQ
    TRNG_IRQ_Handler,               // 39 TRNG_IRQ
    PLL_SYS_IRQ_Handler,            // 42 PLL_SYS_IRQ
    PLL_USB_IRQ_Handler,            // 43 PLL_USB_IRQ
    POWMAN_IRQ_POW_Handler,         // 44 POWMAN_IRQ_POW
    POWMAN_IRQ_TIMER_Handler        // 45 POWMAN_IRQ_TIMER
};

#define MAJOR_VER 1
#define MINOR_VER 0

namespace BLOCKS {

    constexpr blocks<0> start;
    constexpr auto header   = HEADER    (start);
    constexpr auto image    = IMAGE_DEF (header,
                                         image_type::TYPE_EXE,
                                         exe_security::SEC_S,
                                         exe_cpu::CPU_ARM,
                                         exe_chip::CHIP_RP2350);
    constexpr auto version  = VERSION   (image, MAJOR_VER, MINOR_VER);
    constexpr auto last     = LAST_ITEM (version, version.size() - header.size());
    constexpr auto link     = LINK      (last, 0);
    constexpr auto footer   = FOOTER    (link);
};

// Put the calculated boot blocks into the correct section during compile/link-time
const auto boot_blocks __attribute__((section(".boot_blocks"), used)) = BLOCKS::footer;


// The ELF entry point. This code first checks if the CPU
// is running a flash image or a ram image (flash is located
// at 0x10xxxxxx, ram is located at 0x20xxxxxx).
// flash image: Use the ISR vector table of the bootrom
//              at address 0x0. Jump to the reset handler
//              and let the bootrom initialize the XIP and
//              find (and run) a flash image.
// ram image:   After downloading a UF2 ram image, the bootrom
//              will jump to 0x20000001. So the _elf_entry_point
//              is located at 0x20000000, and will use the
//              ISR vector table of the ram image, located at
//              __vector_start__.
void _elf_entry_point() __attribute__((section(".reset"), naked, used));
void _elf_entry_point() {
    asm volatile(
    "       .syntax unified             @ \n"
    "       movs    r0, #0              @ R0 is pointer to the isr vector.\n"
    "                                   @ Default is bootrom at 0x0.      \n"
    "       mov     r3, pc              @ Get the most significant byte   \n"
    "       lsrs    r3, r3, 24          @ of the PC.                      \n"
    "       cmp     r3, #0x10           @ Are we running a FLASH image?   \n"
    "       beq     _do_reset           @ If yes, branch to reset routine \n"
    "       ldr     r0, =__vector_start__ @ Load vector table start       \n"
    "_do_reset:                         @                                 \n"
    "       ldr     r1, =0xe000ed08     @ Load VTOR register address ...  \n"
    "       str     r0, [r1]            @ ... and store value             \n"
    "       ldmia   r0!, {r1, r2}       @ R1=initial SP, R2=reset handler \n"
    "       msr     msp, r1             @ set the master stack pointer... \n"
    "       bx      r2                  @ ...and jump to reset handler.   \n");
}

// The reset irq handler
void Reset_Handler(void) {
    // Initialize the hardware
    SystemInit();
    // Let CMSIS code do the initialization of the C++ runtime and jump to main.
    __cmsis_start();
}

// This is the code that gets called when the processor receives an unexpected
// interrupt. This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
void Default_Handler(void) {
    // Enter an infinite loop.
    while (true) { }
}

// Dummy Posix File IO functions to suppress linker warnings
WEAK_ALIAS_INT_FUNC( _read,   return_0 );
WEAK_ALIAS_INT_FUNC( _write,  return_0 );
WEAK_ALIAS_INT_FUNC( _open,   return_0 );
WEAK_ALIAS_INT_FUNC( _close,  return_0 );
WEAK_ALIAS_INT_FUNC( _link,   return_0 );
WEAK_ALIAS_INT_FUNC( _unlink, return_0 );
WEAK_ALIAS_INT_FUNC( _stat,   return_0 );
WEAK_ALIAS_INT_FUNC( _fstat,  return_0 );
WEAK_ALIAS_INT_FUNC( _lseek,  return_0 );
WEAK_ALIAS_INT_FUNC( _isatty, return_0 );
WEAK_ALIAS_INT_FUNC( _kill,   return_0 );
WEAK_ALIAS_INT_FUNC( _getpid, return_0 );

int return_0() {
    return 0;
}

#ifdef __cplusplus
}
#endif
