#include <msp.h>
#include "irq_dispatcher.h"

void irq_dispatcher::link_in() { }

extern "C" {

    void Default_EUSCI_Handler(void) {
        while(1) ;
    }

    void EUSCIA0_UART_IRQHandler(void) __attribute__((weak,alias("Default_EUSCI_Handler")));
    void EUSCIA1_UART_IRQHandler(void) __attribute__((weak,alias("Default_EUSCI_Handler")));
    void EUSCIA2_UART_IRQHandler(void) __attribute__((weak,alias("Default_EUSCI_Handler")));
    void EUSCIA3_UART_IRQHandler(void) __attribute__((weak,alias("Default_EUSCI_Handler")));
    void EUSCIB0_I2C_IRQHandler(void)  __attribute__((weak,alias("Default_EUSCI_Handler")));
    void EUSCIB1_I2C_IRQHandler(void)  __attribute__((weak,alias("Default_EUSCI_Handler")));
    void EUSCIB2_I2C_IRQHandler(void)  __attribute__((weak,alias("Default_EUSCI_Handler")));
    void EUSCIB3_I2C_IRQHandler(void)  __attribute__((weak,alias("Default_EUSCI_Handler")));
    void EUSCIA0_SPI_IRQHandler(void)  __attribute__((weak,alias("Default_EUSCI_Handler")));
    void EUSCIA1_SPI_IRQHandler(void)  __attribute__((weak,alias("Default_EUSCI_Handler")));
    void EUSCIA2_SPI_IRQHandler(void)  __attribute__((weak,alias("Default_EUSCI_Handler")));
    void EUSCIA3_SPI_IRQHandler(void)  __attribute__((weak,alias("Default_EUSCI_Handler")));
    void EUSCIB0_SPI_IRQHandler(void)  __attribute__((weak,alias("Default_EUSCI_Handler")));
    void EUSCIB1_SPI_IRQHandler(void)  __attribute__((weak,alias("Default_EUSCI_Handler")));
    void EUSCIB2_SPI_IRQHandler(void)  __attribute__((weak,alias("Default_EUSCI_Handler")));
    void EUSCIB3_SPI_IRQHandler(void)  __attribute__((weak,alias("Default_EUSCI_Handler")));

    void EUSCIA0_IRQHandler(void) {
        if (EUSCI_A0->CTLW0 & EUSCI_A_CTLW0_SYNC) {
            EUSCIA0_SPI_IRQHandler();
        } else {
            EUSCIA0_UART_IRQHandler();
        }
    }

    void EUSCIA1_IRQHandler(void) {
        if (EUSCI_A1->CTLW0 & EUSCI_A_CTLW0_SYNC) {
            EUSCIA1_SPI_IRQHandler();
        } else {
            EUSCIA1_UART_IRQHandler();
        }
    }

    void EUSCIA2_IRQHandler(void) {
        if (EUSCI_A2->CTLW0 & EUSCI_A_CTLW0_SYNC) {
            EUSCIA2_SPI_IRQHandler();
        } else {
            EUSCIA2_UART_IRQHandler();
        }
    }

    void EUSCIA3_IRQHandler(void){
        if (EUSCI_A3->CTLW0 & EUSCI_A_CTLW0_SYNC) {
            EUSCIA3_SPI_IRQHandler();
        } else {
            EUSCIA3_UART_IRQHandler();
        }
    }

    void EUSCIB0_IRQHandler(void) {
        if ((EUSCI_B0->CTLW0 & EUSCI_A_CTLW0_MODE_MASK) == EUSCI_A_CTLW0_MODE_3) {
            EUSCIB0_I2C_IRQHandler();
        } else {
            EUSCIB0_SPI_IRQHandler();
        }
    }

    void EUSCIB1_IRQHandler(void) {
        if ((EUSCI_B1->CTLW0 & EUSCI_A_CTLW0_MODE_MASK) == EUSCI_A_CTLW0_MODE_3) {
            EUSCIB1_I2C_IRQHandler();
        } else {
            EUSCIB1_SPI_IRQHandler();
        }
    }

    void EUSCIB2_IRQHandler(void) {
        if ((EUSCI_B2->CTLW0 & EUSCI_A_CTLW0_MODE_MASK) == EUSCI_A_CTLW0_MODE_3) {
            EUSCIB2_I2C_IRQHandler();
        } else {
            EUSCIB2_SPI_IRQHandler();
        }
    }

    void EUSCIB3_IRQHandler(void) {
        if ((EUSCI_B3->CTLW0 & EUSCI_A_CTLW0_MODE_MASK) == EUSCI_A_CTLW0_MODE_3) {
            EUSCIB3_I2C_IRQHandler();
        } else {
            EUSCIB3_SPI_IRQHandler();
        }
    }

}
