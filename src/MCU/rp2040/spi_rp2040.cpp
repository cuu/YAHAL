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
// The STE line is never used in HW mode, because
// STE is deactivated after every byte, which is
// not appropriate for most applications. We always
// pass in a CS gpio pin, which might be used by
// higher layers or automatically in this driver.

#include "yahal_assert.h"
#include "spi_rp2040.h"

using namespace _IO_BANK0_;
using namespace _RESETS_;

function<void(uint8_t)> spi_rp2040::_intHandler[2];

int8_t spi_rp2040::_spi_miso_pins[2][4] =
    { { 0,  4, 16, 20 }, { 8, 12, 24, 28 } };

spi_rp2040::spi_rp2040( uint8_t     index ,
                        gpio_pin_t  miso_pin,
                        gpio_pin_t  mosi_pin,
                        gpio_pin_t  sclk_pin,
                        gpio_pin &  cs_pin,
                        const bool  spi_master,
                        uint16_t    mode)
    : _index(index),  _miso(miso_pin),   _mosi(mosi_pin), _sclk(sclk_pin),
      _cs(cs_pin),  _master(spi_master), _mode(mode),     _init(false),
      _generate_CS(true), _baud(0)  {

    yahal_assert(index < 2);
    _spi     = (index==0) ? &SPI0     : &SPI1;
    _spi_set = (index==0) ? &SPI0_SET : &SPI1_SET;
    _spi_clr = (index==0) ? &SPI0_CLR : &SPI1_CLR;
    bool miso_found = false;
    bool mosi_found = false;
    bool sclk_found = false;
    for (int i = 0; i < 4; ++i) {
        if (miso_pin ==  _spi_miso_pins[index][i])   miso_found = true;
        if (mosi_pin ==  _spi_miso_pins[index][i]+3) mosi_found = true;
        if (sclk_pin ==  _spi_miso_pins[index][i]+2) sclk_found = true;
    }
    (void)miso_found;  // suppress warnings
    (void)mosi_found;
    (void)sclk_found;
    yahal_assert(miso_found && mosi_found && sclk_found);
}

spi_rp2040::~spi_rp2040() {
    // Wait for pending operations
//    while (_EUSCI_STATW & EUSCI_A_STATW_BUSY);

    // Reset CTLW0 register to default values
    // (EUSCI_A is in reset state)
//    _EUSCI_CTLW0 = EUSCI_A_CTLW0_SWRST;
}

void spi_rp2040::init() {
    // Take SPI out of reset state
    if (_index)  RESETS_CLR.RESET.spi1 = 1;
    else         RESETS_CLR.RESET.spi0 = 1;
    // Configure GPIO pins MISO, MOSI & SCLK
    _miso.setSEL(GPIO_CTRL_FUNCSEL__spi);
    _mosi.setSEL(GPIO_CTRL_FUNCSEL__spi);
    _sclk.setSEL(GPIO_CTRL_FUNCSEL__spi);
    // Configure CS pin
    _cs.gpioMode(_master ? GPIO::OUTPUT | GPIO::INIT_HIGH : GPIO::INPUT);
    // Configure SPI port
    _spi_set->SSPCR0 = _mode;
    if (!_master) {
        _spi_set->SSPCR1.MS = 1;
    }
    // Finally enable EUSCI module
    _spi_set->SSPCR1.SSE = 1;
    _init = true;
}

int16_t spi_rp2040::spiTxRx(const uint8_t *txbuf, uint8_t *rxbuf, uint16_t len)
{
    if (!_init) init();
    if (_master) {
        // Activate CS line
        if (_generate_CS) _cs.gpioWrite(LOW);
    } else {
        // Wait for CS to be LOW
        while(_cs.gpioRead()) ;
    }

    for (int i = 0; i < len; ++i)
    {
        // Wait until next byte can be written
        while(_spi->SSPSR.TNF == 0) ;
        // Transfer single char to TX buffer
        _spi->SSPDR = (uint16_t) (txbuf[i]);
        // Wait for next received byte
        while(_spi->SSPSR.RNE == 0) ;
        rxbuf[i] = (uint8_t)(_spi->SSPDR);
    }

    if (_master) {
        // De-activate CS line
        if (_generate_CS) _cs.gpioWrite(HIGH);
    } else {
        // Wait for CS to be HIGH
        while(!_cs.gpioRead()) ;
    }
    return len;
}

int16_t spi_rp2040::spiTx(const uint8_t *txbuf, uint16_t len) {
    if (!_init) init();
    if (_master) {
        // Activate CS line
        if (_generate_CS) _cs.gpioWrite(LOW);
    } else {
        // Wait for CS to be LOW
        while(_cs.gpioRead()) ;
    }

    for (int i = 0; i < len; ++i) {
        //uint8_t dummy;
        // Wait until last data was sent
        while( (_spi->SSPSR.TNF) == 0) ;
        // Transfer single char to TX buffer
        _spi->SSPDR = (uint16_t) (txbuf[i]);
        // Wait for next received byte
        while(_spi->SSPSR.RNE == 0) ;
        (void)(uint8_t)(_spi->SSPDR);


//        while(_spi->SSPSR.RNE) (void)_spi->SSPDR;
//        while(_spi->SSPSR.BSY) ;
//        // Wait for next received byte
//        while(_spi->SSPSR.RNE) (void)_spi->SSPDR;
//        _spi->SSPICR.RORIC = 1;
    }

    if (_master) {
        // De-activate CS line
        if (_generate_CS) _cs.gpioWrite(HIGH);
    } else {
        // Wait for CS to be HIGH
        while(!_cs.gpioRead()) ;
    }
    return len;
}

int16_t spi_rp2040::spiRx(uint8_t tx_byte, uint8_t *rxbuf, uint16_t len) {
    if (!_init) init();
    if (_master) {
        // Activate CS line
        if (_generate_CS) _cs.gpioWrite(LOW);
    } else {
        // Wait for CS to be LOW
        while(_cs.gpioRead()) ;
    }

    for (int i = 0; i < len; ++i)
    {
        // Wait until next byte can be written
        while(_spi->SSPSR.TNF == 0) ;
        // Transfer single char to TX buffer
        _spi->SSPDR = tx_byte;
        // Wait for next received byte
        while(_spi->SSPSR.RNE == 0) ;
        rxbuf[i] = (uint8_t)(_spi->SSPDR);
    }

    if (_master) {
        // De-activate CS line
        if (_generate_CS) _cs.gpioWrite(HIGH);
    } else {
        // Wait for CS to be HIGH
        while(!_cs.gpioRead()) ;
    }
    return len;
}


void spi_rp2040::setSpeed(uint32_t baud)
{
    if (!_init) init();

    uint32_t freq_in = 125000000;
    uint32_t prescale, postdiv;

    // Find smallest prescale value which puts output frequency in range of
    // post-divide. Prescale is an even number from 2 to 254 inclusive.
    for (prescale = 2; prescale <= 254; prescale += 2) {
        if (freq_in < (prescale + 2) * 256 * (uint64_t) baud)
            break;
    }
    yahal_assert(prescale <= 254); // Frequency too low

    // Find largest post-divide which makes output <= baudrate. Post-divide is
    // an integer in the range 1 to 256 inclusive.
    for (postdiv = 256; postdiv > 1; --postdiv) {
        if (freq_in / (prescale * (postdiv - 1)) > baud)
            break;
    }
    _spi->SSPCPSR    = prescale;
    _spi->SSPCR0.SCR = postdiv - 1;
    _baud            = freq_in / (prescale * postdiv);

//    _spi_set->SSPCR1.SSE = 1;
}

void spi_rp2040::generateCS(bool val)
{
    if (!_init) init();
    _generate_CS = val;
}

void spi_rp2040::setCS(bool val) {
    if (!_init) init();
    _cs.gpioWrite(val);
}

void spi_rp2040::spiAttachRxIrq(function<void(uint8_t data)> f) {
    // Register handler
    _intHandler[_index] = f;
    // Enable receive IRQ
    //_spi->   _EUSCI_IE = EUSCI_A_IE_RXIE;
    // Enable IRQ in NVIC
    NVIC_EnableIRQ((IRQn_Type)(SPI0_IRQ_IRQn + _index));
}


extern "C"
{

void SPI0_IRQ_Handler(void) {
    spi_rp2040::_intHandler[0]( SPI0.SSPDR );
}

void SPI1_IRQ_Handler(void) {
    spi_rp2040::_intHandler[1]( SPI1.SSPDR );
}

} // extern "C"
