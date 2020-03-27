#include <fcntl.h>	// O_RDWR
#include <unistd.h>	// close
#include <sys/ioctl.h>	// ioctl
#include <linux/i2c-dev.h> 
#include <linux/i2c.h>

#include "i2c_BBB.h"
#include "yahal_assert.h"

namespace I2C {
enum i2c_mode { READ = 0x01, WRITE = 0x00 };
}

i2c_BBB::i2c_BBB(const char * dev) {
  int ret;
  _fd  = open (dev,  O_RDWR);
//  assert ((_fd  != -1), "I2C open failed");
  ret = ioctl (_fd, I2C_TIMEOUT, 300);  // in 10mS units ...
//  assert ((ret != -1), "I2C_TIMEOUT failed"); 
}

i2c_BBB::~i2c_BBB() {
  int ret = close( _fd );
  yahal_assert(ret != -1);
}
 

int16_t i2c_BBB::i2cRead (uint16_t addr, uint8_t *rxbuf, uint16_t len, bool sendStop) {
  yahal_assert(sendStop);
  yahal_assert(ioctl(_fd, I2C_SLAVE, addr) != -1);
  int n = ::read(_fd, rxbuf, len);
  yahal_assert(n == len);
  return n;
}


int16_t i2c_BBB::i2cWrite(uint16_t addr, uint8_t *txbuf, uint16_t len, bool sendStop) {
  yahal_assert(sendStop);

  i2c_rdwr_ioctl_data data;
  i2c_msg messages[1];

  data.msgs  = messages;
  data.nmsgs = 1;
    
  messages[0].addr  = addr;
  messages[0].flags = I2C::WRITE;
  messages[0].len   = len;
  messages[0].buf   = txbuf;
    
  int ret = ioctl(_fd, I2C_RDWR, &data);
  yahal_assert(ret != -1);
  return ret;


//  assert((ioctl(_fd, I2C_SLAVE, addr) != -1), "I2C_SLAVE failed");
//  int n = ::write(_fd, txbuf, len);
//  assert((n == len), "I2C write failed"); 
//  return n;
}

void i2c_BBB::setSpeed(uint32_t Hz) {
}


