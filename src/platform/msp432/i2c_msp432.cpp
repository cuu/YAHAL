/*
 * spi_msp432.cpp
 *
 *  Created on: 14.06.2016
 *      Author: Andreas Terstegge
 */

#include "i2c_msp432.h"
#include "yahal_assert.h"

i2c_msp432::i2c_msp432(EUSCI_B_Type *mod, uint16_t mode)
: _EUSCI(mod)
{
    // Configure hardware characteristics
    /////////////////////////////////////
    if (mod==EUSCI_B0) {
        _sda.setGpio (PORT_PIN(1, 6));
        _scl.setGpio (PORT_PIN(1, 7));
    } else if (mod==EUSCI_B1) {
        _sda.setGpio (PORT_PIN(6, 4));
        _scl.setGpio (PORT_PIN(6, 5));
    } else if (mod==EUSCI_B2) {
        _sda.setGpio (PORT_PIN(3, 6));
        _scl.setGpio (PORT_PIN(3, 7));
    } else if (mod==EUSCI_B3) {
        _sda.setGpio (PORT_PIN(10, 2));
        _scl.setGpio (PORT_PIN(10, 3));
    }
    else yahal_assert(false);

    // Reset CTLW0 register to default values
    // (EUSCI is in reset state)
    /////////////////////////////////////////
    _EUSCI->CTLW0 = EUSCI_B_CTLW0_SWRST;

    // Configure I2C port
    /////////////////////
    _EUSCI->CTLW0 |= (mode | EUSCI_B_CTLW0_MODE_3);
    _EUSCI->CTLW1  = 0;

    // Set i2c clock to default 100 kHz
    ///////////////////////////////////
    _EUSCI->BRW = SystemCoreClock / 100000;

    // Disable interrupts
    /////////////////////
    _EUSCI->IE = 0;

    // Configure the digital RX/TX lines
    ////////////////////////////////////
    _sda.setMode(GPIO::INPUT | GPIO::PULLUP); _sda.setSEL(1);
    _scl.setMode(GPIO::INPUT | GPIO::PULLUP); _scl.setSEL(1);

    // Finally enable EUSCI module
    //////////////////////////////
    _EUSCI->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;
}


i2c_msp432::~i2c_msp432() {
    // Wait for pending operations
    //////////////////////////////
    while (_EUSCI->STATW & EUSCI_B_STATW_BBUSY);

    // Reset CTLW0 register to default values
    // (EUSCI_B is in reset state)
    /////////////////////////////////////////
    _EUSCI->CTLW0 = EUSCI_B_CTLW0_SWRST;

    // De-configure the digital lines
    /////////////////////////////////
    _sda.setSEL(0); _sda.setMode(GPIO::INPUT);
    _scl.setSEL(0); _scl.setMode(GPIO::INPUT);
}

int16_t i2c_msp432::i2cRead (uint16_t addr, uint8_t *rxbuf, uint8_t len, bool sendStop) {
    // Check for len 0 because the sendStart/Stop
    // routines might hang in this case.
    if (!len) return 0;
    // clear interrupt status and set slave address
    int16_t i = _EUSCI->RXBUF;
    _EUSCI->IFG = 0;
    _EUSCI->I2CSA = addr;
    set_receiver();
    send_START();
    for (i=0; i < len; ++i) {
        // check for last byte to receive
        if ((i+1) == len) {
            if (sendStop) send_STOP();
            else _EUSCI->CTLW0 |= EUSCI_B_CTLW0_TXSTT;
        }
        // Wait until data available
        while(!(_EUSCI->IFG & (EUSCI_B_IFG_RXIFG0 | EUSCI_B_IFG_NACKIFG)));
        // Check NAK condition
        if (_EUSCI->IFG & EUSCI_B_IFG_NACKIFG) {
            if (sendStop) send_STOP();
            return i-1;
        }
        // read the data
        rxbuf[i] = _EUSCI->RXBUF;
    }
    return i;
}
int16_t i2c_msp432::i2cWrite(uint16_t addr, uint8_t *txbuf, uint8_t len, bool sendStop) {
    // Check for len 0 because the sendStart/Stop
    // routines might hang in this case.
    if (!len) return 0;
    // clear interrupt status and set slave address
    _EUSCI->IFG   = 0;
    _EUSCI->I2CSA = addr;
    set_transmitter();
    send_START();
    int16_t i = 0;
    for (i=0; i < len; ++i) {
        // Place character in buffer
        _EUSCI->TXBUF = txbuf[i];
        // Wait until byte has been sent or NACK
        while(!(_EUSCI->IFG & (EUSCI_B_IFG_TXIFG0 | EUSCI_B_IFG_NACKIFG)));
        // Check NAK condition (also if wrong address!)
        if (_EUSCI->IFG & EUSCI_B_IFG_NACKIFG) {
            if (sendStop) send_STOP();
            return i-1;
        }
    }
    // Wait until a NACK after the last byte can be
    // seen, and a send_STOP() is not discarded ...
    uint32_t delay = 0;
    while (!_scl.gpioRead()) delay++; // Wait until HIGH
    while ( _scl.gpioRead()) delay++; // Wait until LOW
    delay *= 128;
    while (delay) delay--;
    // Check NACK
    if (_EUSCI->IFG & EUSCI_B_IFG_NACKIFG) i--;
    if (sendStop) send_STOP();
    return i;
}

void i2c_msp432::setSpeed(uint32_t baud) {
    _EUSCI->BRW = SystemCoreClock / baud;
}

//void i2c_msp432::send_ADR_ACK() {
//	_EUSCI->CTLW0 |= EUSCI_B_CTLW0_TXACK;
//}
//
//void i2c_msp432::send_ADR_NACK() {
//	_EUSCI->CTLW0 &= ~EUSCI_B_CTLW0_TXACK;
//}

void i2c_msp432::set_receiver() {
    _EUSCI->CTLW0 &= ~EUSCI_B_CTLW0_TR;
}

void i2c_msp432::set_transmitter() {
    _EUSCI->CTLW0 |= EUSCI_B_CTLW0_TR;
}

//void i2c_msp432::send_ACK() {
//	_EUSCI->CTLW0 &= ~EUSCI_B_CTLW0_TXNACK;
//}
//
//void i2c_msp432::send_NACK() {
//	_EUSCI->CTLW0 |= EUSCI_B_CTLW0_TXNACK;
//}

void i2c_msp432::send_START() {
    _EUSCI->CTLW0 |= EUSCI_B_CTLW0_TXSTT;
    // Wait until the START condition has been sent
    while(_EUSCI->CTLW0 & EUSCI_B_CTLW0_TXSTT) ;
}

void i2c_msp432::send_STOP() {
    _EUSCI->CTLW0 |= EUSCI_B_CTLW0_TXSTP;
    // Wait until the STOP condition has been sent
    while (_EUSCI->CTLW0 & EUSCI_B_CTLW0_TXSTP);
}

