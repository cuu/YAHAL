#ifndef _SPI_BBB_H_
#define _SPI_BBB_H_

#include "spi_interface.h"

class spi_BBB : public spi_interface {

  public:
    spi_BBB(const char * dev);
   ~spi_BBB();

    int16_t spiTxRx(const uint8_t *txbuf, uint8_t *rxbuf, uint16_t len);

    int16_t spiTx(const uint8_t *txbuf, uint16_t len);

    int16_t spiRx(uint8_t txbyte, uint8_t *rxbuf, uint16_t len);

    void setSpeed(uint32_t Hz);

    void generateCS(bool val);

    void setCS(bool val);

    void spiAttachRxIrq(void (*)(uint8_t data));
    
  private:
    const char * _device;
    int          _fd;
};

#endif

