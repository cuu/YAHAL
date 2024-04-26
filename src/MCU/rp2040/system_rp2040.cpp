#include "system_rp2040.h"

#include "RP2040.h"
using namespace _CLOCKS_;
using namespace _PLL_SYS_;
using namespace _PLL_USB_;
using namespace _RESETS_;
using namespace _SIO_;
using namespace _WATCHDOG_;
using namespace _XOSC_;

// XOSC configuration
/////////////////////
#define XOSC_FREQ 12000000
#define XOSC_STARTUP_MS 64
#define XOSC_STARTUP    (XOSC_FREQ * XOSC_STARTUP_MS / 1000) / 256

#ifdef __cplusplus
extern "C" {
#endif

// RP2040 clocks
uint32_t CLK_SYS  = 0;
uint32_t CLK_REF  = 0;
uint32_t CLK_PERI = 0;
uint32_t CLK_TICK = 0;
uint32_t CLK_USB  = 0;
uint32_t CLK_ADC  = 0;
uint32_t CLK_RTC  = 0;
uint32_t _ticks_per_millis = 0;

/*---------------------------------------------------------------------------
  System initialization function
 *---------------------------------------------------------------------------*/
void SystemInit (void)
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

    WATCHDOG.TICK.CYCLES              = 12;
    WATCHDOG_SET.TICK.ENABLE        <<= 1;

    CLOCKS.CLK_SYS_RESUS_CTRL         = 0;

    // Start the crystal oscillator (XOSC)
    XOSC.CTRL.FREQ_RANGE              = CTRL_FREQ_RANGE__1_15MHZ;
    XOSC.STARTUP                      = XOSC_STARTUP;
    XOSC.CTRL.ENABLE                  = CTRL_ENABLE__ENABLE;
    while (XOSC.STATUS.ENABLED == 0) {}

    // Set default: Run from ROSC
    CLOCKS.CLK_REF_CTRL.SRC           = CLK_REF_CTRL_SRC__rosc_clksrc_ph;
    while (CLOCKS.CLK_REF_SELECTED != 0x1) {}
    CLOCKS.CLK_SYS_CTRL.SRC           = CLK_SYS_CTRL_SRC__clk_ref;
    while (CLOCKS.CLK_SYS_SELECTED != 0x1) {}

    // Set up PLL_SYS
    RESETS_SET.RESET.pll_sys        <<= 1;
    RESETS_CLR.RESET.pll_sys        <<= 1;
    while (RESETS.RESET_DONE.pll_sys == 0) {}
    PLL_SYS.CS.REFDIV                 = 2;
    PLL_SYS.FBDIV_INT                 = 125;
    PLL_SYS_CLR.PWR.VCOPD           <<= 1;
    PLL_SYS_CLR.PWR.PD              <<= 1;
    while (PLL_SYS.CS.LOCK != 1) {}
    PLL_SYS.PRIM.POSTDIV1             = 3;
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
    CLOCKS_SET.CLK_PERI_CTRL.ENABLE <<= 1;

    // Configure CLK_USB
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

    RESETS.RESET = 0;

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

    // Update the divisor for CLK_TICK
    WATCHDOG_CLR.TICK.ENABLE <<= 1;
    WATCHDOG.TICK.CYCLES = 1;
    WATCHDOG_SET.TICK.ENABLE <<= 1;

    // Set the remaining CLK values
    CLK_REF  = pll_usb / CLOCKS.CLK_REF_DIV.INT;
    CLK_SYS  = pll_sys / CLOCKS.CLK_SYS_DIV.INT;
    CLK_PERI = pll_usb;
    CLK_TICK = CLK_REF / WATCHDOG.TICK.CYCLES;
    CLK_USB  = pll_usb / CLOCKS.CLK_USB_DIV.INT;
    CLK_ADC  = pll_usb / CLOCKS.CLK_ADC_DIV.INT;
    CLK_RTC  = pll_usb / CLOCKS.CLK_RTC_DIV.INT;
    _ticks_per_millis = CLK_TICK / 1000;
}

#ifdef __cplusplus
}
#endif
