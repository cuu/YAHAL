/*
 * opt3001_drv.cpp
 *
 *  Created on: Mar 12, 2017
 *      Author: Dennis Hoffmann
 */

#include "opt3001_drv.h"

opt3001_drv::opt3001_drv(i2c_interface & i2c, uint8_t i2c_addr) : _i2c(i2c), _i2c_addr(i2c_addr){}

void opt3001_drv::set_conf(uint16_t CONF){
	writeRegister(OPT3001::REG_CONF, CONF);
}

float opt3001_drv::get_light(){
	read_measure();
	return _light;
}

void opt3001_drv::read_measure(){
	_raw = readRegister(OPT3001::REG_RESULT);
	calc_lux();
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

void opt3001_drv::calc_lux(){
	_light =  ((_raw & OPT3001::MAST_RESULT_MAT) << ((_raw & OPT3001::MASK_RESULT_EXP) >> 12)) * 0.01;
}

