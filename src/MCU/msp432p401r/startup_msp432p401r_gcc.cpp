#include <msp.h>
#include "system_msp432p401r.h"
#include <stdint.h>

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

typedef void (*pFunc)(void);

// Forward declaration of the implemented handlers.
WEAK_FUNC(Default_Handler)
WEAK_FUNC(Reset_Handler)
WEAK_INT_FUNC(return_0)
/* Cortex-M4 Processor Exceptions */
WEAK_ALIAS_FUNC(NMI_Handler,         Default_Handler)
WEAK_ALIAS_FUNC(HardFault_Handler,   Default_Handler)
WEAK_ALIAS_FUNC(MemManage_Handler,   Default_Handler)
WEAK_ALIAS_FUNC(BusFault_Handler,    Default_Handler)
WEAK_ALIAS_FUNC(UsageFault_Handler,  Default_Handler)
WEAK_ALIAS_FUNC(SVC_Handler,         Default_Handler)
WEAK_ALIAS_FUNC(DebugMon_Handler,    Default_Handler)
WEAK_ALIAS_FUNC(PendSV_Handler,      Default_Handler)
WEAK_ALIAS_FUNC(SysTick_Handler,     Default_Handler)

// Device specific interrupt handler
WEAK_ALIAS_FUNC( PSS_IRQHandler,     Default_Handler)
WEAK_ALIAS_FUNC( CS_IRQHandler,      Default_Handler)
WEAK_ALIAS_FUNC( PCM_IRQHandler,     Default_Handler)
WEAK_ALIAS_FUNC( WDT_A_IRQHandler,   Default_Handler)
WEAK_ALIAS_FUNC( FPU_IRQHandler,     Default_Handler)
WEAK_ALIAS_FUNC( FLCTL_IRQHandler,   Default_Handler)
WEAK_ALIAS_FUNC( COMP_E0_IRQHandler, Default_Handler)
WEAK_ALIAS_FUNC( COMP_E1_IRQHandler, Default_Handler)
WEAK_ALIAS_FUNC( TA0_0_IRQHandler,   Default_Handler)
WEAK_ALIAS_FUNC( TA0_N_IRQHandler,   Default_Handler)
WEAK_ALIAS_FUNC( TA1_0_IRQHandler,   Default_Handler)
WEAK_ALIAS_FUNC( TA1_N_IRQHandler,   Default_Handler)
WEAK_ALIAS_FUNC( TA2_0_IRQHandler,   Default_Handler)
WEAK_ALIAS_FUNC( TA2_N_IRQHandler,   Default_Handler)
WEAK_ALIAS_FUNC( TA3_0_IRQHandler,   Default_Handler)
WEAK_ALIAS_FUNC( TA3_N_IRQHandler,   Default_Handler)
WEAK_ALIAS_FUNC( EUSCIA0_IRQHandler, Default_Handler)
WEAK_ALIAS_FUNC( EUSCIA1_IRQHandler, Default_Handler)
WEAK_ALIAS_FUNC( EUSCIA2_IRQHandler, Default_Handler)
WEAK_ALIAS_FUNC( EUSCIA3_IRQHandler, Default_Handler)
WEAK_ALIAS_FUNC( EUSCIB0_IRQHandler, Default_Handler)
WEAK_ALIAS_FUNC( EUSCIB1_IRQHandler, Default_Handler)
WEAK_ALIAS_FUNC( EUSCIB2_IRQHandler, Default_Handler)
WEAK_ALIAS_FUNC( EUSCIB3_IRQHandler, Default_Handler)
WEAK_ALIAS_FUNC( ADC14_IRQHandler,   Default_Handler)
WEAK_ALIAS_FUNC( T32_INT1_IRQHandler,Default_Handler)
WEAK_ALIAS_FUNC( T32_INT2_IRQHandler,Default_Handler)
WEAK_ALIAS_FUNC( T32_INTC_IRQHandler,Default_Handler)
WEAK_ALIAS_FUNC( AES256_IRQHandler,  Default_Handler)
WEAK_ALIAS_FUNC( RTC_C_IRQHandler,   Default_Handler)
WEAK_ALIAS_FUNC( DMA_ERR_IRQHandler, Default_Handler)
WEAK_ALIAS_FUNC( DMA_INT3_IRQHandler,Default_Handler)
WEAK_ALIAS_FUNC( DMA_INT2_IRQHandler,Default_Handler)
WEAK_ALIAS_FUNC( DMA_INT1_IRQHandler,Default_Handler)
WEAK_ALIAS_FUNC( DMA_INT0_IRQHandler,Default_Handler)
WEAK_ALIAS_FUNC( PORT1_IRQHandler,   Default_Handler)
WEAK_ALIAS_FUNC( PORT2_IRQHandler,   Default_Handler)
WEAK_ALIAS_FUNC( PORT3_IRQHandler,   Default_Handler)
WEAK_ALIAS_FUNC( PORT4_IRQHandler,   Default_Handler)
WEAK_ALIAS_FUNC( PORT5_IRQHandler,   Default_Handler)
WEAK_ALIAS_FUNC( PORT6_IRQHandler,   Default_Handler)

/* Interrupt vector table.  Note that the proper constructs must be placed on this to */
/* ensure that it ends up at physical address 0x0000.0000 or at the start of          */
/* the program if located at a start address other than 0.                            */
void (*const isr_vector[])(void) __attribute__ ((section (".intvecs"), used)) = {
    (pFunc)&__StackTop,
    /* The initial stack pointer */
    Reset_Handler,          /* The reset handler         */
    NMI_Handler,            /* The NMI handler           */
    HardFault_Handler,      /* The hard fault handler    */
    MemManage_Handler,      /* The MPU fault handler     */
    BusFault_Handler,       /* The bus fault handler     */
    UsageFault_Handler,     /* The usage fault handler   */
    0,                      /* Reserved                  */
    0,                      /* Reserved                  */
    0,                      /* Reserved                  */
    0,                      /* Reserved                  */
    SVC_Handler,            /* SVCall handler            */
    DebugMon_Handler,       /* Debug monitor handler     */
    0,                      /* Reserved                  */
    PendSV_Handler,         /* The PendSV handler        */
    SysTick_Handler,        /* The SysTick handler       */
    PSS_IRQHandler,         /* PSS Interrupt             */
    CS_IRQHandler,          /* CS Interrupt              */
    PCM_IRQHandler,         /* PCM Interrupt             */
    WDT_A_IRQHandler,       /* WDT_A Interrupt           */
    FPU_IRQHandler,         /* FPU Interrupt             */
    FLCTL_IRQHandler,       /* Flash Controller Interrupt*/
    COMP_E0_IRQHandler,     /* COMP_E0 Interrupt         */
    COMP_E1_IRQHandler,     /* COMP_E1 Interrupt         */
    TA0_0_IRQHandler,       /* TA0_0 Interrupt           */
    TA0_N_IRQHandler,       /* TA0_N Interrupt           */
    TA1_0_IRQHandler,       /* TA1_0 Interrupt           */
    TA1_N_IRQHandler,       /* TA1_N Interrupt           */
    TA2_0_IRQHandler,       /* TA2_0 Interrupt           */
    TA2_N_IRQHandler,       /* TA2_N Interrupt           */
    TA3_0_IRQHandler,       /* TA3_0 Interrupt           */
    TA3_N_IRQHandler,       /* TA3_N Interrupt           */
    EUSCIA0_IRQHandler,     /* EUSCIA0 Interrupt         */
    EUSCIA1_IRQHandler,     /* EUSCIA1 Interrupt         */
    EUSCIA2_IRQHandler,     /* EUSCIA2 Interrupt         */
    EUSCIA3_IRQHandler,     /* EUSCIA3 Interrupt         */
    EUSCIB0_IRQHandler,     /* EUSCIB0 Interrupt         */
    EUSCIB1_IRQHandler,     /* EUSCIB1 Interrupt         */
    EUSCIB2_IRQHandler,     /* EUSCIB2 Interrupt         */
    EUSCIB3_IRQHandler,     /* EUSCIB3 Interrupt         */
    ADC14_IRQHandler,       /* ADC14 Interrupt           */
    T32_INT1_IRQHandler,    /* T32_INT1 Interrupt        */
    T32_INT2_IRQHandler,    /* T32_INT2 Interrupt        */
    T32_INTC_IRQHandler,    /* T32_INTC Interrupt        */
    AES256_IRQHandler,      /* AES256 Interrupt          */
    RTC_C_IRQHandler,       /* RTC_C Interrupt           */
    DMA_ERR_IRQHandler,     /* DMA_ERR Interrupt         */
    DMA_INT3_IRQHandler,    /* DMA_INT3 Interrupt        */
    DMA_INT2_IRQHandler,    /* DMA_INT2 Interrupt        */
    DMA_INT1_IRQHandler,    /* DMA_INT1 Interrupt        */
    DMA_INT0_IRQHandler,    /* DMA_INT0 Interrupt        */
    PORT1_IRQHandler,       /* Port1 Interrupt           */
    PORT2_IRQHandler,       /* Port2 Interrupt           */
    PORT3_IRQHandler,       /* Port3 Interrupt           */
    PORT4_IRQHandler,       /* Port4 Interrupt           */
    PORT5_IRQHandler,       /* Port5 Interrupt           */
    PORT6_IRQHandler        /* Port6 Interrupt           */
};

/* Forward declaration of the default fault handlers. */
/* This is the code that gets called when the processor first starts execution */
/* following a reset event.  Only the absolutely necessary set is performed,   */
/* after which the application supplied entry() routine is called.  Any fancy  */
/* actions (such as making decisions based on the reset cause register, and    */
/* resetting the bits in that register) are left solely in the hands of the    */
/* application.                                                                */
void Reset_Handler(void) {
    // Call system initialization routine. Remember that
    // data and bss sections are NOT yet initialized, but
    // copied AFTER this call!
    SystemInit();

    // Let cmsis code do the initialization of the C++
    // runtime and jump to main
    __cmsis_start();
}

/* This is the code that gets called when the processor receives an unexpected  */
/* interrupt.  This simply enters an infinite loop, preserving the system state */
/* for examination by a debugger.                                               */
void Default_Handler(void) {
    /* Enter an infinite loop. */
    while (1) {
    }
}

/* Dummy Posix File IO functions */
/* to suppress linker warnings   */
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
