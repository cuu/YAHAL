/*
 * opt3001_drv.cpp
 *
 *  Created on: Mar 12, 2017
 *      Author: Dennis Hoffmann
 */

#include "opt3001_drv.h"

namespace OPT3001 {

	// Register addresses
	static const uint8_t REG_RESULT     = 0x00;
	static const uint8_t REG_CONF       = 0x01;
	static const uint8_t REG_LIMIT_LOW  = 0x02;
	static const uint8_t REG_LIMIT_HIGH = 0x03;
	static const uint8_t REG_MAN_ID     = 0x7E;
	static const uint8_t REG_DEV_ID     = 0x7F;

	static const uint16_t MASK_RESULT_EXP = 0xF000;
	static const uint16_t MASK_RESULT_MAT = 0x0FFF;
}

opt3001_drv::opt3001_drv(i2c_interface & i2c, uint8_t i2c_addr)
: _i2c(i2c),  _i2c_addr(i2c_addr)  {} // _raw(0), light(0)

void opt3001_drv::start_measure(uint16_t CONF){
	writeRegister(OPT3001::REG_CONF, CONF);
}

bool opt3001_drv::measure_ready() {
	uint16_t val = readRegister(OPT3001::REG_CONF);
	return val & 0x0080;
}

float opt3001_drv::get_light(){
	uint16_t raw  = readRegister(OPT3001::REG_RESULT);
	uint16_t exp  = raw >> 12;
	uint16_t mant = raw & OPT3001::MASK_RESULT_MAT;
	return (float)(mant << exp) * 0.01;
}

bool opt3001_drv::detect_sensor() {
	uint16_t man = readRegister(OPT3001::REG_MAN_ID);
	uint16_t dev = readRegister(OPT3001::REG_DEV_ID);
	return (man == 0x5449 && dev == 0x3001);
}


void opt3001_drv::writeRegister(uint8_t reg, uint16_t value){
	uint8_t txbuf[3];
	txbuf[0] = reg;
	txbuf[1] = value >> 8;
	txbuf[2] = value & 0x00FF;
	_i2c.write(_i2c_addr, txbuf, 3);
}

uint16_t opt3001_drv::readRegister(uint8_t reg){
	uint8_t txbuf[1];
	uint8_t rxbuf[2];
	uint16_t val;
	txbuf[0] = reg;
	_i2c.write(_i2c_addr, txbuf, 1);
	_i2c.read(_i2c_addr, rxbuf, 2);
	val = (rxbuf[0] << 8) | rxbuf[1];
	return val;
}

