#include "system_rp2040.h"

#include "RP2040.h"
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

// Cortex-M0+ Processor Exceptions
WEAK_ALIAS_FUNC(NMI_Handler,           Default_Handler)
WEAK_ALIAS_FUNC(HardFault_Handler,     Default_Handler)
WEAK_ALIAS_FUNC(SVC_Handler,           Default_Handler)
WEAK_ALIAS_FUNC(PendSV_Handler,        Default_Handler)
WEAK_ALIAS_FUNC(SysTick_Handler,       Default_Handler)

// Device specific interrupt handler
WEAK_ALIAS_FUNC(TIMER_IRQ_0_Handler,   Default_Handler)
WEAK_ALIAS_FUNC(TIMER_IRQ_1_Handler,   Default_Handler)
WEAK_ALIAS_FUNC(TIMER_IRQ_2_Handler,   Default_Handler)
WEAK_ALIAS_FUNC(TIMER_IRQ_3_Handler,   Default_Handler)
WEAK_ALIAS_FUNC(PWM_IRQ_WRAP_Handler,  Default_Handler)
WEAK_ALIAS_FUNC(USBCTRL_IRQ_Handler,   Default_Handler)
WEAK_ALIAS_FUNC(XIP_IRQ_Handler,       Default_Handler)
WEAK_ALIAS_FUNC(PIO0_IRQ_0_Handler,    Default_Handler)
WEAK_ALIAS_FUNC(PIO0_IRQ_1_Handler,    Default_Handler)
WEAK_ALIAS_FUNC(PIO1_IRQ_0_Handler,    Default_Handler)
WEAK_ALIAS_FUNC(PIO1_IRQ_1_Handler,    Default_Handler)
WEAK_ALIAS_FUNC(DMA_IRQ_0_Handler,     Default_Handler)
WEAK_ALIAS_FUNC(DMA_IRQ_1_Handler,     Default_Handler)
WEAK_ALIAS_FUNC(IO_IRQ_BANK0_Handler,  Default_Handler)
WEAK_ALIAS_FUNC(IO_IRQ_QSPI_Handler,   Default_Handler)
WEAK_ALIAS_FUNC(SIO_IRQ_PROC0_Handler, Default_Handler)
WEAK_ALIAS_FUNC(SIO_IRQ_PROC1_Handler, Default_Handler)
WEAK_ALIAS_FUNC(CLOCKS_IRQ_Handler,    Default_Handler)
WEAK_ALIAS_FUNC(SPI0_IRQ_Handler,      Default_Handler)
WEAK_ALIAS_FUNC(SPI1_IRQ_Handler,      Default_Handler)
WEAK_ALIAS_FUNC(UART0_IRQ_Handler,     Default_Handler)
WEAK_ALIAS_FUNC(UART1_IRQ_Handler,     Default_Handler)
WEAK_ALIAS_FUNC(ADC_IRQ_FIFO_Handler,  Default_Handler)
WEAK_ALIAS_FUNC(I2C0_IRQ_Handler,      Default_Handler)
WEAK_ALIAS_FUNC(I2C1_IRQ_Handler,      Default_Handler)
WEAK_ALIAS_FUNC(RTC_IRQ_Handler,       Default_Handler)

// The interrupt vector table.
void (* const isr_vector[])(void) __attribute__((section(".isr_vector"), used)) = {
    (pFunc) &__StackTop,            // The initial stack pointer

    Reset_Handler,                  // -15 The reset handler
    NMI_Handler,                    // -14 The NMI handler
    HardFault_Handler,              // -13 The hard fault handler
    0,                              // -12 Reserved
    0,                              // -11 Reserved
    0,                              // -10 Reserved
    0,                              //  -9 Reserved
    0,                              //  -8 Reserved
    0,                              //  -7 Reserved
    0,                              //  -6 Reserved
    SVC_Handler,                    //  -5 SVCall handler
    0,                              //  -4 Reserved
    0,                              //  -3 Reserved
    PendSV_Handler,                 //  -2 The PendSV handler
    SysTick_Handler,                //  -1 The SysTick handler

    TIMER_IRQ_0_Handler,            //   0 TIMER_IRQ_0
    TIMER_IRQ_1_Handler,            //   1 TIMER_IRQ_1
    TIMER_IRQ_2_Handler,            //   2 TIMER_IRQ_2
    TIMER_IRQ_3_Handler,            //   3 TIMER_IRQ_3
    PWM_IRQ_WRAP_Handler,           //   4 PWM_IRQ_WRAP
    USBCTRL_IRQ_Handler,            //   5 USBCTRL_IRQ
    XIP_IRQ_Handler,                //   6 XIP_IRQ
    PIO0_IRQ_0_Handler,             //   7 PIO0_IRQ_0
    PIO0_IRQ_1_Handler,             //   8 PIO0_IRQ_1
    PIO1_IRQ_0_Handler,             //   9 PIO1_IRQ_0
    PIO1_IRQ_1_Handler,             //  10 PIO1_IRQ_1
    DMA_IRQ_0_Handler,              //  11 DMA_IRQ_0
    DMA_IRQ_1_Handler,              //  12 DMA_IRQ_1
    IO_IRQ_BANK0_Handler,           //  13 IO_IRQ_BANK0
    IO_IRQ_QSPI_Handler,            //  14 IO_IRQ_QSPI
    SIO_IRQ_PROC0_Handler,          //  15 SIO_IRQ_PROC0
    SIO_IRQ_PROC1_Handler,          //  16 SIO_IRQ_PROC1
    CLOCKS_IRQ_Handler,             //  17 CLOCKS_IRQ
    SPI0_IRQ_Handler,               //  18 SPI0_IRQ
    SPI1_IRQ_Handler,               //  19 SPI1_IRQ
    UART0_IRQ_Handler,              //  20 UART0_IRQ
    UART1_IRQ_Handler,              //  21 UART1_IRQ
    ADC_IRQ_FIFO_Handler,           //  22 ADC_IRQ_FIFO
    I2C0_IRQ_Handler,               //  23 I2C0_IRQ
    I2C1_IRQ_Handler,               //  24 I2C1_IRQ
    RTC_IRQ_Handler                 //  25 RTC_IRQ
};

// The ELF entry point. This code will hand over control to the ROM at 0x0,
// which in turn will check the Flash for a runnable binary.
void _elf_entry_point() {
    PPB.VTOR.TBLOFF = 0;
    uint32_t top_of_stack = *(uint32_t *)0x0;
    uint32_t reset_func   = *(uint32_t *)0x4;
    __set_MSP( top_of_stack );
    ((void (*)())reset_func)();
}

// The reset irq handler
void Reset_Handler(void) {
    // Let CMSIS code do the initialization of the C++ runtime and jump to main.
    // The SystemInit() method is marked as a global constructor, so it will not
    // be called here but after the data and bss regions have been initialized.
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
