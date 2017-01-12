/*
 * spi_msp432.h
 *
 *  Created on: 28.02.2016
 *      Author: Andreas Terstegge
 */

#ifndef _SPI_MSP432_H_
#define _SPI_MSP432_H_
#include "spi_interface.h"
#include "gpio_msp432.h"
#include "msp.h"

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
}

class spi_msp432 : public spi_interface {

  public:

    spi_msp432(EUSCI_A_SPI_Type *spi_a, gpio_pin & cs_pin,
    		   uint16_t mode = SPI::CPOL_0 | SPI::CPHA_0 | SPI::MSB_FIRST |
			                   SPI::_8_BIT | SPI::CLK_SMCLK);

    spi_msp432(EUSCI_B_SPI_Type *spi_b, gpio_pin & cs_pin,
    		   uint16_t mode = SPI::CPOL_0 | SPI::CPHA_0 | SPI::MSB_FIRST |
			   	   	   	       SPI::_8_BIT | SPI::CLK_SMCLK);

   ~spi_msp432();

    int16_t transfer(uint8_t *txbuf, uint8_t *rxbuf, uint16_t len);

  private:

    void spi_init();

    volatile uint16_t & _EUSCI_CTLW0;
    volatile uint16_t & _EUSCI_BRW;
    volatile uint16_t & _EUSCI_STATW;
    volatile uint16_t & _EUSCI_RXBUF;
    volatile uint16_t & _EUSCI_TXBUF;
    volatile uint16_t & _EUSCI_IE;
    volatile uint16_t & _EUSCI_IFG;
    volatile uint16_t & _EUSCI_IV;

    gpio_msp432_pin	_ste;
    gpio_msp432_pin	_clk;
	gpio_msp432_pin	_miso;
	gpio_msp432_pin	_mosi;

    uint16_t _mode;

    gpio_pin & _cs;
};

#endif // _SPI_MSP432_H_
