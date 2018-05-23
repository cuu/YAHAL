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

#include "spi_msp432.h"
#include "yahal_assert.h"
#include "irq_dispatcher.h"

//void cs_handler(uint16_t pin) {
//
//}

spi_msp432::spi_msp432(EUSCI_A_SPI_Type *mod, gpio_pin & cs,
                       const bool spi_master, uint16_t mode) :
        _master(spi_master), _use_CS(true),
        _EUSCI_CTLW0(mod->CTLW0), _EUSCI_BRW  (mod->BRW),
        _EUSCI_STATW(mod->STATW), _EUSCI_RXBUF(mod->RXBUF),
        _EUSCI_TXBUF(mod->TXBUF), _EUSCI_IE   (mod->IE),
        _EUSCI_IFG  (mod->IFG),  _EUSCI_IV    (mod->IV),
        _mode(mode), _cs(cs)
{
    // Link in IRQ handlers
    ///////////////////////
    irq_dispatcher::link_in();

    // Configure hardware characteristics of the 4 A-type modules
    /////////////////////////////////////////////////////////////
    if (mod == EUSCI_A0_SPI) {
        _ste.setGpio (PORT_PIN(1, 0));
        _clk.setGpio (PORT_PIN(1, 1));
        _miso.setGpio(PORT_PIN(1, 2));
        _mosi.setGpio(PORT_PIN(1, 3));
        _irq = EUSCIA0_IRQn;
    } else if (mod == EUSCI_A1_SPI) {
        _ste.setGpio (PORT_PIN(2, 0));
        _clk.setGpio (PORT_PIN(2, 1));
        _miso.setGpio(PORT_PIN(2, 2));
        _mosi.setGpio(PORT_PIN(2, 3));
        _irq = EUSCIA1_IRQn;
    } else if (mod == EUSCI_A2_SPI) {
        _ste.setGpio (PORT_PIN(3, 0));
        _clk.setGpio (PORT_PIN(3, 1));
        _miso.setGpio(PORT_PIN(3, 2));
        _mosi.setGpio(PORT_PIN(3, 3));
        _irq = EUSCIA2_IRQn;
    } else if (mod == EUSCI_A3_SPI) {
        _ste.setGpio (PORT_PIN(9, 4));
        _clk.setGpio (PORT_PIN(9, 5));
        _miso.setGpio(PORT_PIN(9, 6));
        _mosi.setGpio(PORT_PIN(9, 7));
        _irq = EUSCIA3_IRQn;
    }
    else yahal_assert(false);
    spi_init();
}

spi_msp432::spi_msp432(EUSCI_B_SPI_Type *mod, gpio_pin & cs,
                       const bool spi_master, uint16_t mode) :
        _master(spi_master), _use_CS(true),
        _EUSCI_CTLW0(mod->CTLW0), _EUSCI_BRW  (mod->BRW),
        _EUSCI_STATW(mod->STATW), _EUSCI_RXBUF(mod->RXBUF),
        _EUSCI_TXBUF(mod->TXBUF), _EUSCI_IE   (mod->IE),
        _EUSCI_IFG  (mod->IFG),   _EUSCI_IV   (mod->IV),
        _mode(mode), _cs(cs)
{
    // Configure hardware characteristics of the 4 B-type modules
    /////////////////////////////////////////////////////////////
    if (mod == EUSCI_B0_SPI) {
        _ste.setGpio (PORT_PIN(1, 4));
        _clk.setGpio (PORT_PIN(1, 5));
        _miso.setGpio(PORT_PIN(1, 7));
        _mosi.setGpio(PORT_PIN(1, 6));
        _irq = EUSCIB0_IRQn;
    } else if (mod == EUSCI_B1_SPI) {
        _ste.setGpio (PORT_PIN(6, 2));
        _clk.setGpio (PORT_PIN(6, 3));
        _miso.setGpio(PORT_PIN(6, 5));
        _mosi.setGpio(PORT_PIN(6, 4));
        _irq = EUSCIB1_IRQn;
    } else if (mod == EUSCI_B2_SPI) {
        _ste.setGpio(PORT_PIN (3, 4));
        _clk.setGpio(PORT_PIN (3, 5));
        _miso.setGpio(PORT_PIN(3, 7));
        _mosi.setGpio(PORT_PIN(3, 6));
        _irq = EUSCIB2_IRQn;
    } else if (mod == EUSCI_B3_SPI) {
        _ste.setGpio(PORT_PIN (10, 0));
        _clk.setGpio(PORT_PIN (10, 1));
        _miso.setGpio(PORT_PIN(10, 3));
        _mosi.setGpio(PORT_PIN(10, 2));
        _irq = EUSCIB3_IRQn;
    }
    else yahal_assert(false);
    spi_init();
}

spi_msp432::~spi_msp432() {
    // Wait for pending operations
    //////////////////////////////
    while (_EUSCI_STATW & EUSCI_A_STATW_BUSY);

    // Reset CTLW0 register to default values
    // (EUSCI_A is in reset state)
    /////////////////////////////////////////
    _EUSCI_CTLW0 = EUSCI_A_CTLW0_SWRST;

    // Unconfigure the digital lines
    ////////////////////////////////
    _ste.setSEL(0);  _ste.setMode(GPIO::INPUT);
    _clk.setSEL(0);  _clk.setMode(GPIO::INPUT);
    _miso.setSEL(0); _miso.setMode(GPIO::INPUT);
    _mosi.setSEL(0); _mosi.setMode(GPIO::INPUT);
    _cs.gpioMode(GPIO::INPUT);
}

void spi_msp432::spi_init() {

    // Reset CTLW0 register to default values
    // (EUSCI is in reset state)
    /////////////////////////////////////////
    _EUSCI_CTLW0 = EUSCI_A_CTLW0_SWRST;

    // Configure SPI port
    /////////////////////
    if (_master) {
        _mode |= EUSCI_A_CTLW0_MST;    // master mode
    }
    _mode |= EUSCI_A_CTLW0_SYNC |  // always synchronous mode
             EUSCI_A_CTLW0_STEM;   // always STE as CS-line
    // always 3 wire mode!
    _EUSCI_CTLW0 |= _mode;

    // Configure the digital RX/TX lines
    ////////////////////////////////////
    _clk.setSEL(1);  _clk.setMode (_master ? GPIO::OUTPUT : GPIO::INPUT);
    _miso.setSEL(1); _miso.setMode(_master ? GPIO::INPUT  : GPIO::OUTPUT);
    _mosi.setSEL(1); _mosi.setMode(_master ? GPIO::OUTPUT : GPIO::INPUT);

    // Configure CS line
    ////////////////////
    if (_master) {
        _cs.gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);
    } else {
        _cs.gpioMode(GPIO::INPUT);
        //	    _cs.gpioAttachIrq(cs_handler, GPIO::FALLING);
    }

    // Enable the EUSCI irq and NVIC irq,
    // we only need RX interrupt
    /////////////////////////////////////
    //_EUSCI_IE = EUSCI_A_IE_RXIE;
    _EUSCI_IE = 0;
    //NVIC_EnableIRQ(_irq);

    // Finally enable EUSCI module
    //////////////////////////////
    _EUSCI_CTLW0 &= ~EUSCI_A_CTLW0_SWRST;
}

int16_t spi_msp432::transfer(uint8_t *txbuf, uint8_t *rxbuf, uint16_t len)
{
    if (_use_CS) {
        if (_master) {
            // Activate CS line
            _cs.gpioWrite(LOW);
        } else {
            // Wait for CS to be LOW
            while(_cs.gpioRead()) ;
        }
    }

    _EUSCI_IFG = 0;
    _EUSCI_STATW = 0; // TODO: Works only in Reset mode ...
    rxbuf[0] = _EUSCI_RXBUF;

    for (int i = 0; i < len; ++i)
    {
        // Transfer single char to TX buffer
        _EUSCI_TXBUF = (uint16_t) (txbuf[i]);
        // Receive single char from RX buffer
        while( !(_EUSCI_IFG & EUSCI_A_IFG_RXIFG));
        rxbuf[i] = (uint8_t)(_EUSCI_RXBUF);
        // Wait until last data was sent
        while (!(_EUSCI_IFG & EUSCI_A_IFG_TXIFG));
    }

    if (_use_CS) {
        if (_master) {
            // De-activate CS line
            _cs.gpioWrite(HIGH);
        } else {
            // Wait for CS to be HIGH
            while(!_cs.gpioRead()) ;
        }
    }
    return len;
}

void spi_msp432::setSpeed(uint32_t baud)
{
    _EUSCI_BRW = SystemCoreClock / baud;
}

void spi_msp432::useCS(bool val)
{
    _use_CS = val;
    if (!val) {
        _cs.gpioWrite(LOW);
    }
}

extern "C"
{

void EUSCIA0_SPI_IRQHandler(void)
{
}

void EUSCIA1_SPI_IRQHandler(void)
{
}

void EUSCIA2_SPI_IRQHandler(void)
{
}

void EUSCIA3_SPI_IRQHandler(void)
{
}

void EUSCIB0_SPI_IRQHandler(void)
{
}

void EUSCIB1_SPI_IRQHandler(void)
{
}

void EUSCIB2_SPI_IRQHandler(void)
{
}

void EUSCIB3_SPI_IRQHandler(void)
{
}

} // extern "C"
