/*
 * ina219_drv.cpp
 *
 *  Created on: Jun 8, 2018
 *      Author: Philipp Dressen
 */

#include "ina219_drv.h"

ina219_drv::ina219_drv(i2c_interface & i2c, uint8_t i2c_addr) : _i2c(i2c), _i2c_addr(i2c_addr){
}

float ina219_drv::get_shunt_voltage(){
    uint16_t raw = read_u16(INA219::REG_SHUNT_V);
    bool sign = raw >> 15;      // true = negative

    uint8_t shift = 1;
    switch (shuntgain) {
    case INA219::PG::X1:
        shift = 4;
        break;
    case INA219::PG::X2:
        shift = 3;
        break;
    case INA219::PG::X4:
        shift = 2;
        break;
    default:
        shift = 1;
        break;
    }

    // eliminate sign
    raw = raw << shift;
    raw = raw >> shift;

    float result = raw / 100.;
    if (sign)
        result *= -1;
    return result;
}

float ina219_drv::get_bus_voltage(){
    uint16_t raw = read_u16(INA219::REG_BUS_V);
    bool ovf = raw & 0b1;       // overflow flag
    //bool cnvr = raw & 0b10;     // conversion ready flag

    if (ovf)
        return 0;   // return 0 if overflow occured

    // eliminate flags
    float result = raw >> 3;
    result /= (1000. / 250);    // LSB = 4 mV
    return result;
}
void ina219_drv::writeRegister16(uint8_t reg, uint16_t value){
    uint8_t txbuf[3];
    txbuf[0] = reg;
    txbuf[1] = value >> 8;  // MSB
    txbuf[2] = value & 255; // LSB
    _i2c.i2cWrite(_i2c_addr, txbuf, 3);
}

void ina219_drv::writeRegister(uint8_t reg, uint8_t value){
	uint8_t txbuf[2];
	txbuf[0] = reg;
	txbuf[1] = value;
	_i2c.i2cWrite(_i2c_addr, txbuf, 2);
}

uint8_t ina219_drv::readRegister(uint8_t reg){
	uint8_t txbuf[1];
	uint8_t rxbuf[1];
	txbuf[0] = reg;
	_i2c.i2cWrite(_i2c_addr, txbuf, 1);
	_i2c.i2cRead (_i2c_addr, rxbuf, 1);
	return rxbuf[0];
}

uint16_t ina219_drv::read_u16_le(uint8_t reg){
	uint8_t txbuf[1];
	uint8_t rxbuf[2];
	txbuf[0] = reg;
	uint16_t val;
	_i2c.i2cWrite(_i2c_addr, txbuf, 1);
	_i2c.i2cRead (_i2c_addr, rxbuf, 2);
	val = (rxbuf[1] << 8) | rxbuf[0];
	return val;
}

uint16_t ina219_drv::read_u16(uint8_t reg){
	uint8_t txbuf[1];
	uint8_t rxbuf[2];
	txbuf[0] = reg;
	uint16_t val;
	_i2c.i2cWrite(_i2c_addr, txbuf, 1);
	_i2c.i2cRead (_i2c_addr, rxbuf, 2);
	val = (rxbuf[0] << 8) | rxbuf[1];
	return val;
}

uint16_t ina219_drv::read_s16_le(uint8_t reg){
	uint16_t val = read_u16_le(reg);
	return static_cast<int16_t>(val);
}

