/*
 * softi2cmaster.h
 *
 *  Created on: 31.01.2017
 *      Author: aterstegge
 */

#ifndef _SOFT_I2C_MASTER_H_
#define _SOFT_I2C_MASTER_H_

#include <i2c_interface.h>
#include <gpio_interface.h>

class soft_i2c_master : public i2c_interface {
  public:

	soft_i2c_master(gpio_pin & sda, gpio_pin & scl, void (*delay)(), bool pullup = false);
	virtual ~soft_i2c_master();

    int16_t i2cRead (uint16_t addr, uint8_t *rxbuf, uint8_t len, bool sendStop=true) override;
	int16_t i2cWrite(uint16_t addr, uint8_t *txbuf, uint8_t len, bool sendStop=true) override;

  private:

    bool   i2c_start();
    bool   i2c_stop ();
    bool   i2c_write_bit(bool bit);
    bool   i2c_read_bit();
    bool   i2c_write_byte(uint8_t byte);
    int8_t i2c_read_byte(bool nack);


    bool _init;
    void init();

    gpio_pin & _sda;
    gpio_pin & _scl;
    void (*_delay)();
    bool _pullup;
};

#endif /* SRC_DRIVER_SOFT_I2C_MASTER_H_ */

