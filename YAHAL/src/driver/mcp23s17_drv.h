//
// mcp23s17_drv.h
//
//  Created on: 28.02.2016
//      Author: Andreas Terstegge
//


/*******************************************************
      MCP23S17 I/O Expander with Serial interface

 This is a driver for the MCP23S17 GPIO expander, which
 has 2 8-bit ports (A & B), and is accessed via the SPI
 interface.

 The two ports are accessed as one 16-bit port, using
 the following bit-numbering:

 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
 \_______GPIOB_________/ \_______GPIOA_________/
 MSB                 LSB MSB                 LSB

 29.01.2015  initial version

 (c) 2015 A. Terstegge

********************************************************/
#ifndef _MCP23S17_DRV_H_
#define _MCP23S17_DRV_H_

#include "gpio_interface.h"
#include "spi_interface.h"

class mcp23s17_drv : public gpio_interface {

  public:
    // User interface
    /////////////////
    // The 2. constructor parameter is the SPI hardware
    // address of the device (0...7);
    mcp23s17_drv(spi_interface & hw, uint8_t spi_addr);

    // Basic GPIO handling
    void gpioMode (uint8_t port, uint8_t pin, uint16_t mode);
    bool gpioRead (uint8_t port, uint8_t pin);
    void gpioWrite(uint8_t port, uint8_t pin, bool value);

    // Interrupt handling
    void attachInterrupt (uint8_t port, uint8_t pin,
    					  void (*)(uint8_t port, uint8_t pin), uint16_t mode);
    void detachInterrupt (uint8_t port, uint8_t pin);
    void enableInterrupt (uint8_t port, uint8_t pin);
    void disableInterrupt(uint8_t port, uint8_t pin);
    void handleInterrupt();

    // Methods to read/write the entire port
    // Only bits with '1' in the mask are processed
    uint16_t digitalReadPort (uint16_t mask = 0xffff);
    void     digitalWritePort(uint16_t value, uint16_t mask = 0xffff);

  private:

    // SPI data
    spi_interface & _spi;
    uint8_t         _spi_addr;  // 0...7

    // register values
    uint16_t _iodir;
    uint16_t _gppu;
    uint16_t _olat;
    uint16_t _gpinten;
    uint16_t _defval;
    uint16_t _intcon;

    // interrupt handler functions
    void   (*intHandler[2][8])(uint8_t port, uint8_t pin);
    uint16_t intMode[2][8];

    // Hardware interface
    /////////////////////
    uint16_t readRegister (uint8_t reg);
    void     writeRegister(uint8_t reg, uint16_t value);

};

#endif // _MCP23S17_DRV_H_
