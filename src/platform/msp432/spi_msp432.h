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
// SPI driver for MSP432. It support master
// and client mode. Interrupts are supported
// for client mode (RX interrupts).
//

#ifndef _SPI_MSP432_H_
#define _SPI_MSP432_H_
#include "spi_interface.h"
#include "gpio_msp432.h"
#include "msp.h"

extern "C" {
void EUSCIA0_SPI_IRQHandler(void);
void EUSCIA1_SPI_IRQHandler(void);
void EUSCIA2_SPI_IRQHandler(void);
void EUSCIA3_SPI_IRQHandler(void);
void EUSCIB0_SPI_IRQHandler(void);
void EUSCIB1_SPI_IRQHandler(void);
void EUSCIB2_SPI_IRQHandler(void);
void EUSCIB3_SPI_IRQHandler(void);
}

namespace SPI {
const uint16_t CPHA_0      = 0x8000;
const uint16_t CPHA_1      = 0x0000;
const uint16_t CPOL_0      = 0x0000;
const uint16_t CPOL_1      = 0x4000;
const uint16_t LSB_FIRST   = 0x0000;
const uint16_t MSB_FIRST   = 0x2000;
const uint16_t _8_BIT      = 0x0000;
const uint16_t _7_BIT      = 0x1000;
const uint16_t CLK_ACLK    = 0x0040;
const uint16_t CLK_SMCLK   = 0x0080;

// Verbose constants for SPI role
const bool MASTER = true;
const bool CLIENT = false;
}

class spi_msp432 : public spi_interface {

public:

    spi_msp432(EUSCI_A_SPI_Type *spi_a, gpio_pin & cs_pin,
               const bool spi_master = SPI::MASTER,
               uint16_t mode = SPI::CPOL_0 | SPI::CPHA_0 | SPI::MSB_FIRST |
                               SPI::_8_BIT | SPI::CLK_SMCLK);

    spi_msp432(EUSCI_B_SPI_Type *spi_b, gpio_pin & cs_pin,
               const bool spi_master = SPI::MASTER,
               uint16_t mode = SPI::CPOL_0 | SPI::CPHA_0 | SPI::MSB_FIRST |
                               SPI::_8_BIT | SPI::CLK_SMCLK);

    ~spi_msp432();

    int16_t spiTxRx(const uint8_t *txbuf, uint8_t *rxbuf, uint16_t len) override;
    int16_t spiTx  (const uint8_t *txbuf, uint16_t len) override ;
    int16_t spiRx  (uint8_t txbyte, uint8_t *rxbuf, uint16_t len) override;

    void setSpeed(uint32_t) override;
    void generateCS(bool val) override;
    void setCS(bool val) override;

    void spiAttachRxIrq(void (*)(uint8_t data)) override;

    // IRQ handlers are our best friends
    ////////////////////////////////////
    friend void EUSCIA0_SPI_IRQHandler(void);
    friend void EUSCIA1_SPI_IRQHandler(void);
    friend void EUSCIA2_SPI_IRQHandler(void);
    friend void EUSCIA3_SPI_IRQHandler(void);
    friend void EUSCIB0_SPI_IRQHandler(void);
    friend void EUSCIB1_SPI_IRQHandler(void);
    friend void EUSCIB2_SPI_IRQHandler(void);
    friend void EUSCIB3_SPI_IRQHandler(void);

private:

    bool _initialized;
    void initialize();

    bool _master;
    bool _generate_CS;

    volatile uint16_t & _EUSCI_CTLW0;
    volatile uint16_t & _EUSCI_BRW;
    volatile uint16_t & _EUSCI_STATW;
    volatile uint16_t & _EUSCI_RXBUF;
    volatile uint16_t & _EUSCI_TXBUF;
    volatile uint16_t & _EUSCI_IE;
    volatile uint16_t & _EUSCI_IFG;
    volatile uint16_t & _EUSCI_IV;

    gpio_msp432_pin _clk;
    gpio_msp432_pin _miso;
    gpio_msp432_pin _mosi;

    uint16_t   _mode;
    gpio_pin & _cs; // pointer to currently selected CS pin
    IRQn_Type  _irq;

    static void (*_intHandler[8])(uint8_t);
};

#endif // _SPI_MSP432_H_
