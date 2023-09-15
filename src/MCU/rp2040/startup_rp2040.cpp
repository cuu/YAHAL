
#include "RP2040.h"
#include "system_rp2040.h"
#include <stdint.h>

using namespace _CLOCKS_;
using namespace _PLL_SYS_;
using namespace _PLL_USB_;
using namespace _PPB_;
using namespace _RESETS_;
using namespace _SIO_;
using namespace _WATCHDOG_;
using namespace _XOSC_;

#ifdef __cplusplus
extern "C" {
#endif

/*********************/
/* Macro Definitions */
/*********************/
#define WEAK_FUNC(FUN) \
void FUN(void) __attribute__ ((weak));
#define WEAK_INT_FUNC(FUN) \
int FUN() __attribute__ ((weak));
#define WEAK_ALIAS_FUNC(FUN, FUN_ALIAS) \
void FUN(void) __attribute__ ((weak, alias(#FUN_ALIAS)));
#define WEAK_ALIAS_INT_FUNC(FUN, FUN_ALIAS) \
int FUN() __attribute__ ((weak, alias(#FUN_ALIAS)));

/************************************/
/* External variables and functions */
/************************************/
extern void     __cmsis_start(void);
extern uint32_t __StackTop;

/**********************/
/* XOSC configuration */
/**********************/
#define XOSC_FREQUENCY  12000000
#define XOSC_STARTUP_MS 10
#define XOSC_STARTUP    (XOSC_FREQUENCY * XOSC_STARTUP_MS / 1000) / 256

typedef void (*pFunc)(void);

// Forward declaration of the implemented handlers.
WEAK_FUNC(Default_Handler)
WEAK_FUNC(Reset_Handler)
WEAK_INT_FUNC(return_0)

// Cortex-M0+ Processor Exceptions
WEAK_ALIAS_FUNC(NMI_Handler, Default_Handler)
WEAK_ALIAS_FUNC(HardFault_Handler, Default_Handler)
WEAK_ALIAS_FUNC(SVC_Handler, Default_Handler)
WEAK_ALIAS_FUNC(PendSV_Handler, Default_Handler)
WEAK_ALIAS_FUNC(SysTick_Handler, Default_Handler)

// Device specific interrupt handler
WEAK_ALIAS_FUNC(TIMER_IRQ_0_Handler, Default_Handler)
WEAK_ALIAS_FUNC(TIMER_IRQ_1_Handler, Default_Handler)
WEAK_ALIAS_FUNC(TIMER_IRQ_2_Handler, Default_Handler)
WEAK_ALIAS_FUNC(TIMER_IRQ_3_Handler, Default_Handler)
WEAK_ALIAS_FUNC(PWM_IRQ_WRAP_Handler, Default_Handler)
WEAK_ALIAS_FUNC(USBCTRL_IRQ_Handler, Default_Handler)
WEAK_ALIAS_FUNC(XIP_IRQ_Handler, Default_Handler)
WEAK_ALIAS_FUNC(PIO0_IRQ_0_Handler, Default_Handler)
WEAK_ALIAS_FUNC(PIO0_IRQ_1_Handler, Default_Handler)
WEAK_ALIAS_FUNC(PIO1_IRQ_0_Handler, Default_Handler)
WEAK_ALIAS_FUNC(PIO1_IRQ_1_Handler, Default_Handler)
WEAK_ALIAS_FUNC(DMA_IRQ_0_Handler, Default_Handler)
WEAK_ALIAS_FUNC(DMA_IRQ_1_Handler, Default_Handler)
WEAK_ALIAS_FUNC(IO_IRQ_BANK0_Handler, Default_Handler)
WEAK_ALIAS_FUNC(IO_IRQ_QSPI_Handler, Default_Handler)
WEAK_ALIAS_FUNC(SIO_IRQ_PROC0_Handler, Default_Handler)
WEAK_ALIAS_FUNC(SIO_IRQ_PROC1_Handler, Default_Handler)
WEAK_ALIAS_FUNC(CLOCKS_IRQ_Handler, Default_Handler)
WEAK_ALIAS_FUNC(SPI0_IRQ_Handler, Default_Handler)
WEAK_ALIAS_FUNC(SPI1_IRQ_Handler, Default_Handler)
WEAK_ALIAS_FUNC(UART0_IRQ_Handler, Default_Handler)
WEAK_ALIAS_FUNC(UART1_IRQ_Handler, Default_Handler)
WEAK_ALIAS_FUNC(ADC_IRQ_FIFO_Handler, Default_Handler)
WEAK_ALIAS_FUNC(I2C0_IRQ_Handler, Default_Handler)
WEAK_ALIAS_FUNC(I2C1_IRQ_Handler, Default_Handler)
WEAK_ALIAS_FUNC(RTC_IRQ_Handler, Default_Handler)


// Interrupt vector table.
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

void __attribute__((naked, noreturn)) _elf_entry_point() {
    PPB.VTOR.TBLOFF = 0;
    uint32_t top_of_stack = *(uint32_t *)0x0;
    uint32_t reset_func   = *(uint32_t *)0x4;
    __set_MSP( top_of_stack );
    ((void (*)())reset_func)();
}

// The reset irq handler
void __attribute__((naked, noreturn)) Reset_Handler(void)
{
    // Check if core 1 is executing this code
    // and let it sleep in the bootrom
    if (SIO.CPUID != 0) {
        while(1) ;
    }

    SCB->VTOR = 0x10000100;

    // Reset peripherals
    RESETS.RESET = 0xfbcdbf;
    RESETS.RESET = 0xc38001;

    /////////////////////////
    // Set up clock system //
    /////////////////////////

    WATCHDOG.TICK.CYCLES             = 12;
    WATCHDOG_SET.TICK.ENABLE       <<= 1;

    CLOCKS.CLK_SYS_RESUS_CTRL        = 0;

    // Start 12MHz crystal oscillator
    XOSC.CTRL.FREQ_RANGE              = CTRL_FREQ_RANGE__1_15MHZ;
    XOSC.STARTUP                      = XOSC_STARTUP;
    XOSC.CTRL.ENABLE                  = CTRL_ENABLE__ENABLE;
    while (XOSC.STATUS.ENABLED == 0) {}

    CLOCKS.CLK_REF_CTRL.SRC           = CLK_REF_CTRL_SRC__rosc_clksrc_ph;
    while (CLOCKS.CLK_REF_SELECTED != 0x1) {}
    CLOCKS.CLK_SYS_CTRL.SRC           = CLK_SYS_CTRL_SRC__clk_ref;
    while (CLOCKS.CLK_SYS_SELECTED != 0x1) {}

    // Set up PLL_SYS
    RESETS_SET.RESET.pll_sys        <<= 1;
    RESETS_CLR.RESET.pll_sys        <<= 1;
    while (RESETS.RESET_DONE.pll_sys == 0) {}
    PLL_SYS.CS.REFDIV                 = 1;
    PLL_SYS.FBDIV_INT                 = 125;
    PLL_SYS_CLR.PWR.VCOPD           <<= 1;
    PLL_SYS_CLR.PWR.PD              <<= 1;
    while (PLL_SYS.CS.LOCK != 1) {}
    PLL_SYS.PRIM.POSTDIV1             = 6;
    PLL_SYS.PRIM.POSTDIV2             = 2;
    PLL_SYS_CLR.PWR.POSTDIVPD       <<= 1;

    // Set up PLL_USB
    RESETS_SET.RESET.pll_usb        <<= 1;
    RESETS_CLR.RESET.pll_usb        <<= 1;
    while (RESETS.RESET_DONE.pll_usb == 0) {}
    PLL_USB.CS.REFDIV                 = 1;
    PLL_USB.FBDIV_INT                 = 100;
    PLL_USB_CLR.PWR.VCOPD           <<= 1;
    PLL_USB_CLR.PWR.PD              <<= 1;
    while (PLL_USB.CS.LOCK != 1) {}
    PLL_USB.PRIM.POSTDIV1             = 5;
    PLL_USB.PRIM.POSTDIV2             = 5;
    PLL_USB_CLR.PWR.POSTDIVPD       <<= 1;

    CLOCKS.CLK_REF_CTRL.AUXSRC        = CLK_REF_CTRL_AUXSRC__clksrc_pll_usb;
    CLOCKS.CLK_REF_CTRL.SRC           = CLK_REF_CTRL_SRC__xosc_clksrc;
    CLOCKS.CLK_REF_DIV.INT            = 1;

    CLOCKS.CLK_SYS_CTRL.AUXSRC        = CLK_SYS_CTRL_AUXSRC__clksrc_pll_sys;
    CLOCKS.CLK_SYS_CTRL.SRC           = CLK_SYS_CTRL_SRC__clksrc_clk_sys_aux;
    CLOCKS.CLK_SYS_DIV.INT            = 1;
    CLOCKS.CLK_SYS_DIV.FRAC           = 0;

    CLOCKS_CLR.CLK_USB_CTRL.ENABLE  <<= 1;
    CLOCKS.CLK_USB_CTRL.AUXSRC        = CLK_USB_CTRL_AUXSRC__clksrc_pll_usb;
    CLOCKS.CLK_USB_DIV.INT            = 1;
    CLOCKS_SET.CLK_USB_CTRL.PHASE   <<= 1;
    CLOCKS_SET.CLK_USB_CTRL.ENABLE  <<= 1;

    CLOCKS_CLR.CLK_ADC_CTRL.ENABLE  <<= 1;
    CLOCKS.CLK_ADC_CTRL.AUXSRC        = CLK_ADC_CTRL_AUXSRC__clksrc_pll_usb;
    CLOCKS.CLK_ADC_DIV.INT            = 1;
    CLOCKS_SET.CLK_ADC_CTRL.PHASE   <<= 1;
    CLOCKS_SET.CLK_ADC_CTRL.ENABLE  <<= 1;

    CLOCKS_CLR.CLK_RTC_CTRL.ENABLE  <<= 1;
    CLOCKS.CLK_RTC_CTRL.AUXSRC        = CLK_RTC_CTRL_AUXSRC__clksrc_pll_usb;
    CLOCKS.CLK_RTC_DIV.INT            = 1024;
    CLOCKS.CLK_RTC_DIV.FRAC           = 0;
    CLOCKS_SET.CLK_RTC_CTRL.PHASE   <<= 1;
    CLOCKS_SET.CLK_RTC_CTRL.ENABLE  <<= 1;

    CLOCKS_CLR.CLK_PERI_CTRL.ENABLE <<= 1;
    CLOCKS.CLK_PERI_CTRL.AUXSRC       = CLK_PERI_CTRL_AUXSRC__clk_sys;
    CLOCKS_SET.CLK_PERI_CTRL.ENABLE <<= 1;

    RESETS.RESET = 0;

    // Call system initialization routine. Remember that
    // data and bss sections are NOT yet initialized, but
    // copied AFTER this call!
    SystemInit();

    // Let CMSIS code do the initialization of the C++
    // runtime and jump to main
    __cmsis_start();
}

// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
void Default_Handler(void)
{
    // Enter an infinite loop.
    while (1) { }
}

// Dummy Posix File IO functions
// to suppress linker warnings
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
