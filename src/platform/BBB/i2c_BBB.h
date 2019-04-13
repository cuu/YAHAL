#ifndef _I2C_BBB_H_
#define _I2C_BBB_H_

#include "i2c_interface.h"

class i2c_BBB : public i2c_interface {
  public:

    i2c_BBB(const char * dev);
   ~i2c_BBB();
 
    int16_t i2cRead (uint16_t addr,
                     uint8_t *rxbuf, uint16_t len,
                     bool sendStop = true);

    int16_t i2cWrite(uint16_t addr,
                     uint8_t *txbuf, uint16_t len,
                     bool sendStop = true);

    void setSpeed(uint32_t Hz);

  private:
    int           _fd;
};

#endif
