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
// This example demonstrates the new extended system
// startup file (system_ext_msp432_gcc.c).
// It allows a more detailed configuration of the clock
// system, especially the usage of the HFXT as a source
// for the MCLK signal.
// The application code is the same as example_blink_timer.
// If you compare the blinking of the LEDs of the original
// example_blink_timer (MCLK driven by 3MHz DCO) and this
// example (MCLK driven by 48MHz XTAL), you will notice that
// the blinking is more precise (compare with the seconds-
// tick of a wristwatch for example).

#include <cstdio>

#include "gpio_msp432.h"
#include "uart_msp432.h"
#include "timer_msp432.h"
#include "posix_io.h"

extern uint32_t SystemCoreClock;
extern uint32_t SubsystemMasterClock;

void delay(int us) {
    bool expired = false;
    timer_msp432 timer2(TIMER32_2);
    timer2.setPeriod(us, TIMER::ONE_SHOT);
    timer2.setCallback([&]() { expired = true; });
    timer2.start();
    // Now wait until the callback method
    // has changed the 'expired' variable...
    while(!expired) ;
}

int main(void)
{
    // Setup backchannel UART for stdout
    uart_msp432 uart;
    posix_io::inst.register_stdout(uart);

    printf("************ DCO configuration ************\n");
    const char * dco_f = "";
    printf("DCO force on:        %ld\n", (CS->CTL0 & CS_CTL0_DCOEN)  >> CS_CTL0_DCOEN_OFS  );
    printf("DCO ext. resistor:   %ld\n", (CS->CTL0 & CS_CTL0_DCORES) >> CS_CTL0_DCORES_OFS );
    switch ((CS->CTL0 & CS_CTL0_DCORSEL_MASK) >> CS_CTL0_DCORSEL_OFS) {
        case 0: dco_f = "1.5"; break;
        case 1: dco_f = "3.0"; break;
        case 2: dco_f = "6.0"; break;
        case 3: dco_f = "12.0"; break;
        case 4: dco_f = "24.0"; break;
        case 5: dco_f = "48.0"; break;
        case 6: dco_f = "??6"; break;
        case 7: dco_f = "??7"; break;
    }
    printf("DCO center freq.:    %s MHz\n", dco_f);
    int16_t tune = CS->CTL0 & CS_CTL0_DCOTUNE_MASK;
    if (tune & BIT9) tune |= 0xfc00;
    printf("DCO tune:            %d\n", tune);
    printf("DCO bias on:         %ld\n",  (CS->STAT & CS_STAT_DCOBIAS_ON) >> CS_STAT_DCOBIAS_ON_OFS);
    printf("DCO on:              %ld\n",  (CS->STAT & CS_STAT_DCO_ON) >> CS_STAT_DCO_ON_OFS);

    printf("************ HFXT configuration ************\n");
    printf("HFXT bypass:         %ld\n", (CS->CTL2 & CS_CTL2_HFXTBYPASS) >> CS_CTL2_HFXTBYPASS_OFS);
    printf("HFXT force enable:   %ld\n", (CS->CTL2 & CS_CTL2_HFXT_EN)    >> CS_CTL2_HFXT_EN_OFS);

    const char * hfxt_freq = "";
    switch((CS->CTL2 & CS_CTL2_HFXTFREQ_MASK) >> CS_CTL2_HFXTFREQ_OFS) {
        case 0: hfxt_freq = "1 to 4"; break;
        case 1: hfxt_freq = "4 to 8"; break;
        case 2: hfxt_freq = "8 to 16"; break;
        case 3: hfxt_freq = "16 to 24"; break;
        case 4: hfxt_freq = "24 to 32"; break;
        case 5: hfxt_freq = "32 to 40"; break;
        case 6: hfxt_freq = "40 to 48"; break;
        default: hfxt_freq = "??"; break;
    }
    printf("HFXT freq. sel.:     %s MHz\n", hfxt_freq);
    printf("HFXT drive:          %ld\n", (CS->CTL2 & CS_CTL2_HFXTDRIVE) >> CS_CTL2_HFXTDRIVE_OFS);
    printf("HFXT on:             %ld\n",  (CS->STAT & CS_STAT_HFXT_ON) >> CS_STAT_HFXT_ON_OFS);

    printf("************ LFXT configuration ************\n");
    printf("LFXT bypass:         %ld\n", (CS->CTL2 & CS_CTL2_LFXTBYPASS) >> CS_CTL2_LFXTBYPASS_OFS);
    printf("LFXT force enable:   %ld\n", (CS->CTL2 & CS_CTL2_LFXT_EN)    >> CS_CTL2_LFXT_EN_OFS);
    const char * lfxt_drv = "";
    switch((CS->CTL2 & CS_CTL2_LFXTDRIVE_MASK) >> CS_CTL2_LFXTDRIVE_OFS) {
        case 0: lfxt_drv = "low (0)"; break;
        case 1: lfxt_drv = "medium (1)"; break;
        case 2: lfxt_drv = "medium (2)"; break;
        case 3: lfxt_drv = "strong (3)"; break;
        default: lfxt_drv = "??"; break;
    }
    printf("LFXT drive:          %s\n", lfxt_drv);
    printf("LFXT on:             %ld\n",  (CS->STAT & CS_STAT_LFXT_ON) >> CS_STAT_LFXT_ON_OFS);

    printf("************ REFO configuration ************\n");
    printf("REFO select:         %s kHz\n", CS->CLKEN & CS_CLKEN_REFOFSEL ? "128" : "32.768" );
    printf("REFO force enable:   %ld\n",  (CS->CLKEN  & CS_CLKEN_REFO_EN) >> CS_CLKEN_REFO_EN_OFS);
    printf("REFO on:             %ld\n",  (CS->STAT   & CS_STAT_REFO_ON)  >> CS_STAT_REFO_ON_OFS);

    printf("************ VLO configuration ************\n");
    printf("VLO force enable:    %ld\n", (CS->CLKEN & CS_CLKEN_VLO_EN) >> CS_CLKEN_VLO_EN_OFS);
    printf("VLO on:              %ld\n", (CS->STAT  & CS_STAT_VLO_ON)  >> CS_STAT_VLO_ON_OFS);

    printf("************ MODOSC configuration ************\n");
    printf("MODOSC force enable: %ld\n",  (CS->CLKEN & CS_CLKEN_MODOSC_EN) >> CS_CLKEN_MODOSC_EN_OFS);
    printf("MODOSC on:           %ld\n",  (CS->STAT & CS_STAT_MODOSC_ON) >> CS_STAT_MODOSC_ON_OFS);

    printf("************ MCLK signal ************\n");
    const char * selm = "";
    switch((CS->CTL1 & CS_CTL1_SELM_MASK) >> CS_CTL1_SELM_OFS) {
        case 0: selm = "LFXTCLK"; break;
        case 1: selm = "VLOCLK"; break;
        case 2: selm = "REFOCLK"; break;
        case 3: selm = "DCOCLK"; break;
        case 4: selm = "MODOSC"; break;
        case 5: selm = "HFXTCLK"; break;
        default: selm = "??"; break;
    }
    printf("MCLK select:         %s\n", selm);
    printf("MCLK divider:        %d\n", 1 << ((CS->CTL1 & CS_CTL1_DIVM_MASK)  >> CS_CTL1_DIVM_OFS));
    printf("MCLK cond. on:       %ld\n", (CS->CLKEN & CS_CLKEN_MCLK_EN)   >> CS_CLKEN_MCLK_EN_OFS);
    printf("MCLK ready:          %ld\n", (CS->STAT  & CS_STAT_MCLK_READY) >> CS_STAT_MCLK_READY_OFS);
    printf("MCLK on:             %ld\n", (CS->STAT  & CS_STAT_MCLK_ON)    >> CS_STAT_MCLK_ON_OFS);

    printf("************ SMCLK/HSMCLK signal ************\n");
    const char * sels = "";
    switch((CS->CTL1 & CS_CTL1_SELS_MASK) >> CS_CTL1_SELS_OFS) {
        case 0: sels = "LFXTCLK"; break;
        case 1: sels = "VLOCLK"; break;
        case 2: sels = "REFOCLK"; break;
        case 3: sels = "DCOCLK"; break;
        case 4: sels = "MODOSC"; break;
        case 5: sels = "HFXTCLK"; break;
        default: sels = "??"; break;
    }
    printf("(H)SMCLK select:     %s\n", sels);
    printf("HSMCLK divider:      %d\n", 1 << ((CS->CTL1 & CS_CTL1_DIVHS_MASK) >> CS_CTL1_DIVHS_OFS));
    printf("HSMCLK cond. on:     %ld\n", (CS->CLKEN & CS_CLKEN_HSMCLK_EN) >> CS_CLKEN_HSMCLK_EN_OFS);
    printf("HSMCLK ready:        %ld\n",  (CS->STAT & CS_STAT_HSMCLK_READY) >> CS_STAT_HSMCLK_READY_OFS);
    printf("HSMCLK on:           %ld\n", (CS->STAT  & CS_STAT_HSMCLK_ON)  >> CS_STAT_HSMCLK_ON_OFS);
    printf("SMCLK divider:       %d\n", 1 << ((CS->CTL1 & CS_CTL1_DIVS_MASK)  >> CS_CTL1_DIVS_OFS));
    printf("SMCLK cond. on:      %ld\n", (CS->CLKEN & CS_CLKEN_SMCLK_EN) >> CS_CLKEN_SMCLK_EN_OFS);
    printf("SMCLK ready:         %ld\n",  (CS->STAT & CS_STAT_SMCLK_READY) >> CS_STAT_SMCLK_READY_OFS);
    printf("SMCLK on:            %ld\n", (CS->STAT  & CS_STAT_SMCLK_ON)  >> CS_STAT_SMCLK_ON_OFS);

    printf("************ ACLK signal ************\n");
    const char * sela = "";
    switch((CS->CTL1 & CS_CTL1_SELA_MASK) >> CS_CTL1_SELA_OFS) {
        case 0: sela = "LFXTCLK"; break;
        case 1: sela = "VLOCLK"; break;
        case 2: sela = "REFOCLK"; break;
        default: sela = "??"; break;
    }
    printf("ACLK select:         %s\n", sela);
    printf("ACLK divider:        %d\n", 1 << ((CS->CTL1 & CS_CTL1_DIVA_MASK)  >> CS_CTL1_DIVA_OFS));
    printf("ACLK cond. on:       %ld\n", (CS->CLKEN & CS_CLKEN_ACLK_EN)  >> CS_CLKEN_ACLK_EN_OFS);
    printf("ACLK ready:          %ld\n", (CS->STAT & CS_STAT_ACLK_READY) >> CS_STAT_ACLK_READY_OFS);
    printf("ACLK on:             %ld\n", (CS->STAT & CS_STAT_ACLK_ON)    >> CS_STAT_ACLK_ON_OFS);

    printf("************ BCLK signal ************\n");
    printf("BCLK select:         %s\n",  (CS->CTL1 & CS_CTL1_SELB) ? "REFOCLK" : "LFXTCLK" );
    printf("BCLK ready:          %ld\n", (CS->STAT & CS_STAT_BCLK_READY) >> CS_STAT_BCLK_READY_OFS);

    printf("************ Other signals ************\n");
    printf("REFOCLK on:          %ld\n", (CS->STAT & CS_STAT_REFOCLK_ON) >> CS_STAT_REFOCLK_ON_OFS);
    printf("LFXTCLK on:          %ld\n", (CS->STAT & CS_STAT_LFXTCLK_ON) >> CS_STAT_LFXTCLK_ON_OFS);
    printf("VLOCLK on:           %ld\n", (CS->STAT & CS_STAT_VLOCLK_ON) >> CS_STAT_VLOCLK_ON_OFS);
    printf("MODCLK on:           %ld\n", (CS->STAT & CS_STAT_MODCLK_ON) >> CS_STAT_MODCLK_ON_OFS);

    printf("\n");
    printf("SystemCoreClock:      %ld Hz\n", SystemCoreClock);
    printf("SubsystemMasterClock: %ld Hz\n", SubsystemMasterClock);

    // Setup two LEDs on the launchpad for blinking
    gpio_msp432_pin led1( PORT_PIN(1,0) ); // Left red LED
    gpio_msp432_pin led2( PORT_PIN(2,0) ); // red RGB LED
    led1.gpioMode( GPIO::OUTPUT );
    led2.gpioMode( GPIO::OUTPUT );

    // Setup the first timer with a timeout
    // of 500ms. As an example, a pointer to the
    // gpio_pin is passed as the callback argument.
    // When a timer is e.g. used within a class, the
    // this-pointer could be passed to the callback
    // method, so it can call methods of the class.
    timer_msp432 timer1;
    timer1.setPeriod(500000, TIMER::PERIODIC);
    timer1.setCallback([&]() { led1.gpioToggle(); });
    timer1.start();

    // The second timer is used within the
    // delay-method, which is now very precise
    // and has a high resolution (1 microsecond).
    //
    // After observing the 2 blinking LEDs you
    // will notice, that the second LED (on the
    // right, code below) will blink a _little_
    // bit slower, because calling the toggle()
    // method and calling delay() adds some small
    // time to the 500ms. Since the first LED is
    // running in PERIODC mode, the interval is
    // exactly 500ms!
    while(true) {
        delay(500000);      // wait 500ms
        led2.gpioToggle();  // toggle the LED
    }
}
