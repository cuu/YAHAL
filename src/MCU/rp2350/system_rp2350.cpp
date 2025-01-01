#include "system_rp2350.h"

#include "RP2350.h"
using namespace _CLOCKS_;
using namespace _PLL_SYS_;
using namespace _PLL_USB_;
using namespace _RESETS_;
using namespace _SIO_;
using namespace _WATCHDOG_;
using namespace _XOSC_;
using namespace _TICKS_;

// XOSC configuration (depends on HW)
/////////////////////////////////////
#ifndef XOSC_FREQ
#define XOSC_FREQ 12000000
#endif
#ifndef XOSC_STARTUP_MS
#define XOSC_STARTUP_MS 64
#endif
#define XOSC_STARTUP    ((XOSC_FREQ * XOSC_STARTUP_MS / 1000) / 256)

// Clock configurations
///////////////////////
#ifndef SYS_CLK_FREQ
#define SYS_CLK_FREQ 200
#endif


#ifdef __cplusplus
extern "C" {
#endif

// Global RP2350 clocks frequencies
uint32_t CLK_REF  = 0;
uint32_t CLK_SYS  = 0;
uint32_t CLK_PERI = 0;
uint32_t CLK_HSTX = 0;
uint32_t CLK_USB  = 0;
uint32_t CLK_ADC  = 0;

/*---------------------------------------------------------------------------
  System initialization function
 *---------------------------------------------------------------------------*/
void SystemInit (void)
{
    // Reset peripherals
    RESETS_SET.RESET.UART0 <<= 1;
    RESETS_SET.RESET.UART1 <<= 1;

    // Check if core 1 is executing
    // this code and let it sleep here
    if (SIO.CPUID != 0) {
        while(1) ;
    }

    // Start the crystal oscillator (XOSC)
    XOSC.CTRL.FREQ_RANGE              = CTRL_FREQ_RANGE__1_15MHZ;
    XOSC.STARTUP                      = XOSC_STARTUP;
    XOSC.CTRL.ENABLE                  = CTRL_ENABLE__ENABLE;
    while (XOSC.STATUS.ENABLED == 0) {}

    // Set default clock configuration: Run system from ROSC
    CLOCKS.CLK_REF_CTRL.SRC           = CLK_REF_CTRL_SRC__rosc_clksrc_ph;
    while (CLOCKS.CLK_REF_SELECTED != (1 << CLK_REF_CTRL_SRC__rosc_clksrc_ph)) {}
    CLOCKS.CLK_SYS_CTRL.SRC           = CLK_SYS_CTRL_SRC__clk_ref;
    while (CLOCKS.CLK_SYS_SELECTED != (1 << CLK_SYS_CTRL_SRC__clk_ref)) {}

    // Set up PLL_SYS
    // The reference frequency is XOSC / REFDIV = 6 MHz
    // The output frequency (200*6 MHz=1200 MHz) is divided by 3*2=6,
    // which results in a final frequency of 200 MHz, which is the same
    // as the feedback divider FBDIV.
    RESETS_SET.RESET.PLL_SYS        <<= 1;
    RESETS_CLR.RESET.PLL_SYS        <<= 1;
    while (RESETS.RESET_DONE.PLL_SYS == 0) {}
    PLL_SYS.CS.REFDIV                 = 2;
    PLL_SYS.FBDIV_INT                 = SYS_CLK_FREQ;
    PLL_SYS_CLR.PWR.VCOPD           <<= 1;
    PLL_SYS_CLR.PWR.PD              <<= 1;
    while (PLL_SYS.CS.LOCK != 1) {}
    PLL_SYS.PRIM.POSTDIV1             = 3;
    PLL_SYS.PRIM.POSTDIV2             = 2;
    PLL_SYS_CLR.PWR.POSTDIVPD       <<= 1;

    // Set up PLL_USB
    // The reference frequency is 12 MHz
    // The output frequency (100*12 MHz=1200 MHz) is divided by 5*5=25,
    // which results in a final frequency of 48 MHz.
    RESETS_SET.RESET.PLL_USB        <<= 1;
    RESETS_CLR.RESET.PLL_USB        <<= 1;
    while (RESETS.RESET_DONE.PLL_USB == 0) {}
    PLL_USB.CS.REFDIV                 = 1;
    PLL_USB.FBDIV_INT                 = 100;
    PLL_USB_CLR.PWR.VCOPD           <<= 1;
    PLL_USB_CLR.PWR.PD              <<= 1;
    while (PLL_USB.CS.LOCK != 1) {}
    PLL_USB.PRIM.POSTDIV1             = 5;
    PLL_USB.PRIM.POSTDIV2             = 5;
    PLL_USB_CLR.PWR.POSTDIVPD       <<= 1;

    // Configure CLK_REF
    CLOCKS.CLK_REF_CTRL.AUXSRC        = CLK_REF_CTRL_AUXSRC__clksrc_pll_usb;
    CLOCKS.CLK_REF_CTRL.SRC           = CLK_REF_CTRL_SRC__clksrc_clk_ref_aux;
    CLOCKS.CLK_REF_DIV.INT            = 1;

    // Configure CLK_SYS
    CLOCKS.CLK_SYS_CTRL.AUXSRC        = CLK_SYS_CTRL_AUXSRC__clksrc_pll_sys;
    CLOCKS.CLK_SYS_CTRL.SRC           = CLK_SYS_CTRL_SRC__clksrc_clk_sys_aux;
    CLOCKS.CLK_SYS_DIV.INT            = 1;
    CLOCKS.CLK_SYS_DIV.FRAC           = 0;

    // Configure CLK_PERI
    CLOCKS_CLR.CLK_PERI_CTRL.ENABLE <<= 1;
    CLOCKS.CLK_PERI_CTRL.AUXSRC       = CLK_PERI_CTRL_AUXSRC__clksrc_pll_usb;
    CLOCKS.CLK_PERI_DIV.INT           = 1;
    CLOCKS_SET.CLK_PERI_CTRL.ENABLE <<= 1;

    // Configure CLK_HSTX
    CLOCKS_CLR.CLK_HSTX_CTRL.ENABLE <<= 1;
    CLOCKS.CLK_HSTX_CTRL.AUXSRC       = CLK_HSTX_CTRL_AUXSRC__clksrc_pll_usb;
    CLOCKS.CLK_HSTX_DIV.INT           = 1;
    CLOCKS_SET.CLK_HSTX_CTRL.ENABLE <<= 1;

    // Configure CLK_USB
    CLOCKS_CLR.CLK_USB_CTRL.ENABLE  <<= 1;
    CLOCKS.CLK_USB_CTRL.AUXSRC        = CLK_USB_CTRL_AUXSRC__clksrc_pll_usb;
    CLOCKS.CLK_USB_DIV.INT            = 1;
    CLOCKS_SET.CLK_USB_CTRL.ENABLE  <<= 1;

    // Configure CLK_ADC
    CLOCKS_CLR.CLK_ADC_CTRL.ENABLE  <<= 1;
    CLOCKS.CLK_ADC_CTRL.AUXSRC        = CLK_ADC_CTRL_AUXSRC__clksrc_pll_usb;
    CLOCKS.CLK_ADC_DIV.INT            = 1;
    CLOCKS_SET.CLK_ADC_CTRL.ENABLE  <<= 1;

    ClockUpdate();
}

// Updates the system clocks with current
// settings from hardware registers.
void __attribute__((constructor)) ClockUpdate (void) {
    // Calculate PLL frequencies
    uint32_t pll_sys = XOSC_FREQ;
    pll_sys /= PLL_SYS.CS.REFDIV;
    pll_sys *= PLL_SYS.FBDIV_INT;
    pll_sys /= PLL_SYS.PRIM.POSTDIV1;
    pll_sys /= PLL_SYS.PRIM.POSTDIV2;

    uint32_t pll_usb = XOSC_FREQ;
    pll_usb /= PLL_USB.CS.REFDIV;
    pll_usb *= PLL_USB.FBDIV_INT;
    pll_usb /= PLL_USB.PRIM.POSTDIV1;
    pll_usb /= PLL_USB.PRIM.POSTDIV2;

    // Set the global clock frequencies
    CLK_REF  = pll_usb / CLOCKS.CLK_REF_DIV.INT;
    CLK_SYS  = pll_sys / CLOCKS.CLK_SYS_DIV.INT;
    CLK_PERI = pll_usb / CLOCKS.CLK_PERI_DIV.INT;
    CLK_HSTX = pll_usb / CLOCKS.CLK_HSTX_DIV.INT;
    CLK_USB  = pll_usb / CLOCKS.CLK_USB_DIV.INT;
    CLK_ADC  = pll_usb / CLOCKS.CLK_ADC_DIV.INT;

    // Configure Tick Generators for 1 MHz
    TICKS.PROC0_CYCLES                = CLK_REF / 1000000;
    TICKS_SET.PROC0_CTRL.ENABLE     <<= 1;
    TICKS.TIMER0_CYCLES               = CLK_REF / 1000000;
    TICKS_SET.TIMER0_CTRL.ENABLE    <<= 1;
}

#ifdef __cplusplus
}
#endif
