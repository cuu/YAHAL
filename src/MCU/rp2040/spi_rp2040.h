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
// SPI driver for RP2040. It support master
// and client mode. Interrupts are supported
// for client mode (RX interrupts).
//
#ifndef _SPI_RP2040_H_
#define _SPI_RP2040_H_

#include "spi_interface.h"
#include "gpio_rp2040.h"
#include "RP2040.h"

using namespace _SPI0_;
using namespace _SPI1_;

extern "C" {
void SPI0_IRQ_Handler(void);
void SPI1_IRQ_Handler(void);
}

namespace SPI {
const uint16_t CPHA_0      = 0x0000;
const uint16_t CPHA_1      = 0x0080;
const uint16_t CPOL_0      = 0x0000;
const uint16_t CPOL_1      = 0x0040;
const uint16_t _4_BIT      = 0x0003;
const uint16_t _5_BIT      = 0x0004;
const uint16_t _6_BIT      = 0x0005;
const uint16_t _7_BIT      = 0x0006;
const uint16_t _8_BIT      = 0x0007;
const uint16_t _9_BIT      = 0x0008;
const uint16_t _10_BIT     = 0x0009;
const uint16_t _11_BIT     = 0x000a;
const uint16_t _12_BIT     = 0x000b;
const uint16_t _13_BIT     = 0x000c;
const uint16_t _14_BIT     = 0x000d;
const uint16_t _15_BIT     = 0x000e;
const uint16_t _16_BIT     = 0x000f;

// Verbose constants for SPI role
const bool MASTER = true;
const bool CLIENT = false;
}

class spi_rp2040 : public spi_interface {

public:

    spi_rp2040(uint8_t     index,
               gpio_pin_t  miso_pin,
               gpio_pin_t  mosi_pin,
               gpio_pin_t  sclk_pin,
               gpio_pin &  cs_pin,
               const bool  spi_master = SPI::MASTER,
               uint16_t    mode = SPI::CPOL_0 | SPI::CPHA_0 | SPI::_8_BIT);

    ~spi_rp2040();

    int16_t spiTxRx(const uint8_t *txbuf, uint8_t *rxbuf, uint16_t len) override;
    int16_t spiTx  (const uint8_t *txbuf, uint16_t len) override ;
    int16_t spiRx  (uint8_t txbyte, uint8_t *rxbuf, uint16_t len) override;

    void setSpeed(uint32_t) override;
    void generateCS(bool val) override;
    void setCS(bool val) override;

    void spiAttachRxIrq(function<void(uint8_t data)> f) override;

    // IRQ handlers are our best friends
    ////////////////////////////////////
    friend void SPI0_IRQ_Handler(void);
    friend void SPI1_IRQ_Handler(void);

private:
    int         _index;
    gpio_rp2040_pin  _miso;
    gpio_rp2040_pin  _mosi;
    gpio_rp2040_pin  _sclk;
    gpio_pin &  _cs;
    bool        _master;
    uint16_t    _mode;

    bool        _init;
    bool        _generate_CS;
    uint32_t    _baud;

    SPI0_t *    _spi;
    SPI0_t *    _spi_set;
    SPI0_t *    _spi_clr;

    void    init();

    static int8_t _spi_miso_pins[2][5];

    static function<void(uint8_t)> _intHandler[2];
};

#endif // _SPI_RP2040_H_
