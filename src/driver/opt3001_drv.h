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
// Driver for OPT3001 light sensor made by TI.
// This sensor is accessed by a I2C interface.

#ifndef SRC_DRIVER_OPT3001_DRV_H_
#define SRC_DRIVER_OPT3001_DRV_H_

#include "i2c_interface.h"

namespace OPT3001 {
static const uint8_t I2C_ADDR_GND = 0x44;
static const uint8_t I2C_ADDR_VDD = 0x45;
static const uint8_t I2C_ADDR_SDA = 0x46;
static const uint8_t I2C_ADDR_SCL = 0x47;

static const uint16_t CONF_800MS_CONT   = 0b1100110000010000;
static const uint16_t CONF_100MS_CONT   = 0b1100010000010000;
static const uint16_t CONF_800MS_SINGLE = 0b1100101000010000;
static const uint16_t CONF_100MS_SINGLE = 0b1100001000010000;
}

class opt3001_drv {
public:
	opt3001_drv(i2c_interface & i2c, uint8_t i2c_addr);
	void  start_measure(uint16_t conf);
	bool  measure_ready();
	float get_light();
	bool  detect_sensor();

private:
	i2c_interface & _i2c;
	uint8_t         _i2c_addr;

	uint16_t readRegister(uint8_t reg);
	void     writeRegister(uint8_t reg, uint16_t value);
};

#endif /* SRC_DRIVER_OPT3001_DRV_H_ */
