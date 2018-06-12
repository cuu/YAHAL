/*
 * ina219_drv.cpp
 *
 *  Created on: Jun 8, 2018
 *      Author: Philipp Dressen
 */

#include "ina219_drv.h"

ina219_drv::ina219_drv(i2c_interface & i2c, uint8_t i2c_addr) : _i2c(i2c), _i2c_addr(i2c_addr){
}

/****************************************************************\
*  Sets INA219 config register & resets the chip if desired.
\****************************************************************/
void ina219_drv::setConfig(bool reset, INA219::BG busgain, INA219::PG powergain, INA219::ADC busadc, INA219::ADC shuntadc, INA219::MODE mode) {
    uint16_t conf = 0;
    conf |= reset << 15;
    conf |= busgain << 13;
    conf |= powergain << 11;
    conf |= busadc << 7;
    conf |= shuntadc << 3;
    conf |= mode;
    writeRegister(INA219::REG_CONF, conf);

    this->busgain = busgain;
    this->shuntgain = shuntgain;
    this->busadc = busadc;
    this->shuntadc = shuntadc;
    this->mode = mode;
}

/****************************************************************\
*  Sets INA219 calibration register based on the maximum expected
*  current in mA an the installed shunt resistor value in Ohm.
\****************************************************************/
void ina219_drv::setCalibration(uint16_t maxCurrent = 3200, float shuntR = 0.1) {
    currentLSB = maxCurrent / 32768000.;
    calibration = 0.04096 / (currentLSB * shuntR);  // see datasheet
    writeRegister(INA219::REG_CAL, calibration);
}

/****************************************************************\
*  Returns current shunt voltage in mV.
\****************************************************************/
float ina219_drv::getShuntVoltage(){
    int16_t raw = (int16_t)readRegister(INA219::REG_SHUNT_V);
    return (raw * 0.01);
}

/****************************************************************\
*  Returns current bus voltage in V or INA219::OVERFLOW
*  on math overflow.
\****************************************************************/
float ina219_drv::getBusVoltage(){
    uint16_t raw = readRegister(INA219::REG_BUS_V);
    bool ovf = raw & 0b1;       // overflow flag
    //bool cnvr = raw & 0b10;     // conversion ready flag

    if (ovf)
        return INA219::OVERFLOW;   // return magicnumber if overflow occured

    // eliminate flags
    float result = (int16_t)((raw >> 3) * 4);   // LSB = 4 mV
    result *= 0.001;                            // mV -> V
    return result;
}

/****************************************************************\
*  Returns current in mA.
*  Warning: setCalibration() has to be called first.
\****************************************************************/
float ina219_drv::getCurrent() {
    int16_t raw = (int16_t)readRegister(INA219::REG_CURRENT);
    return raw * currentLSB;
}

void ina219_drv::writeRegister(uint8_t reg, uint16_t value){
    uint8_t txbuf[3];
    txbuf[0] = reg;
    txbuf[1] = value >> 8;      // MSB
    txbuf[2] = value & 0xFF;    // LSB
    _i2c.i2cWrite(_i2c_addr, txbuf, 3);
}

uint16_t ina219_drv::readRegister(uint8_t reg){
	uint8_t txbuf[] = { reg };
	uint8_t rxbuf[2];
	_i2c.i2cWrite(_i2c_addr, txbuf, 1);
	_i2c.i2cRead (_i2c_addr, rxbuf, 2);
	return ((rxbuf[0] << 8) | rxbuf[1]);
}

