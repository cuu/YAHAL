#include <fcntl.h>	// O_RDWR
#include <unistd.h>	// close
#include <sys/ioctl.h>	// ioctl
#include <linux/spi/spidev.h>  // SPI_IOC_MESSAGE
#include <memory.h>	// memset
#include "spi_BBB.h"
#include "yahal_assert.h"

spi_BBB::spi_BBB(const char * dev) : _device(dev) { 
  _fd = open(_device, O_RDWR);
  yahal_assert(_fd != -1);
}

spi_BBB::~spi_BBB() {
  int ret = close( _fd );
  yahal_assert(ret != -1);
}


int16_t spi_BBB::spiTxRx(const uint8_t *txbuf, uint8_t *rxbuf, uint16_t len) {
  spi_ioc_transfer tr;
  memset(&tr, 0, sizeof(tr));
  
  tr.tx_buf = (unsigned long)txbuf;
  tr.rx_buf = (unsigned long)rxbuf;
  tr.len    = len;

  int ret = ioctl(_fd, SPI_IOC_MESSAGE(1), &tr);
  yahal_assert(ret != -1);
  return ret;
}

int16_t spi_BBB::spiTx(const uint8_t *txbuf, uint16_t len) {
  spi_ioc_transfer tr;
  memset(&tr, 0, sizeof(tr));
  
  tr.tx_buf = (unsigned long)txbuf;
  tr.rx_buf = (unsigned long)NULL;
  tr.len    = len;

  int ret = ioctl(_fd, SPI_IOC_MESSAGE(1), &tr);
  yahal_assert(ret != -1);
  return ret;
}

int16_t spi_BBB::spiRx(uint8_t txbyte, uint8_t *rxbuf, uint16_t len) {
  spi_ioc_transfer tr;
  memset(&tr, 0, sizeof(tr));
  
  tr.tx_buf = (unsigned long)NULL;
  tr.rx_buf = (unsigned long)rxbuf;
  tr.len    = len;

  int ret = ioctl(_fd, SPI_IOC_MESSAGE(1), &tr);
  yahal_assert(ret != -1);
  return ret;
}

void spi_BBB::setSpeed(uint32_t Hz) {
}

void spi_BBB::generateCS(bool val) {
}

void spi_BBB::setCS(bool val) {
}

void spi_BBB::spiAttachRxIrq(void (*)(uint8_t data)) {
}

