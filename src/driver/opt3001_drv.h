/*
 * opt3001_drv.h
 *
 *  Created on: Mar 12, 2017
 *      Author: Dennis Hoffmann
 */

#ifndef SRC_DRIVER_OPT3001_DRV_H_
#define SRC_DRIVER_OPT3001_DRV_H_

#include "i2c_interface.h"

namespace OPT3001 {

	static const uint8_t ADDRESS = 0x44;
	static const uint8_t REG_RESULT = 0x00;
	static const uint8_t REG_CONF = 0x01;
	static const uint8_t REG_LIMIT_LOW = 0x02;
	static const uint8_t REG_LIMIT_HIGH = 0x03;
	static const uint8_t REG_MAN_ID = 0x7E;
	static const uint8_t REG_DEV_ID = 0x7F;

	static const uint16_t CONF_800MS_CONT = 0b1100110000010000;
	static const uint16_t CONF_100MS_CONT = 0b1100010000010000;
	static const uint16_t CONF_800MS_SINGLE = 0b1100101000010000;
	static const uint16_t CONF_100MS_SINGLE = 0b1100001000010000;

	static const uint16_t MASK_RESULT_EXP = 0xF000;
	static const uint16_t MAST_RESULT_MAT = 0x0FFF;
}

class opt3001_drv{
public:
	opt3001_drv(i2c_interface & i2c, uint8_t _i2c_addr);
	void set_conf(uint16_t CONF);
	float get_light();
	inline uint16_t get_raw() { return _raw; }

private:
	float _light;
	i2c_interface & _i2c;
	uint16_t _raw;
	uint8_t _i2c_addr;
	void calc_lux();
	void read_measure();
	uint16_t readRegister(uint8_t reg);
	void writeRegister(uint8_t reg, uint16_t value);

};



#endif /* SRC_DRIVER_OPT3001_DRV_H_ */
