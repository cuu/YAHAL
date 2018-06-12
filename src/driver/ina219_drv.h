/*
 * ina219_drv.h
 *
 *  Created on: Jun 8, 2018
 *      Author: Philipp Dressen
 *
 *  Based on: http://www.ti.com/lit/ds/symlink/ina219.pdf
 */

#ifndef SRC_DRIVER_INA219_DRV_H_
#define SRC_DRIVER_INA219_DRV_H_

#include "i2c_interface.h"

namespace INA219 {
	// adafruit: 0x40, 0x41, 0x44, 0x45
	static const uint8_t ADDRESS 		= 0x40;
	static const uint16_t OVERFLOW        = 0xFFFF;

	// 16-Bit registers, MSB-First
	static const uint8_t REG_CONF 	    = 0x00;
	static const uint8_t REG_SHUNT_V 	= 0x01;
	static const uint8_t REG_BUS_V 	    = 0x02;
	static const uint8_t REG_POWER 	    = 0x03;
	static const uint8_t REG_CURRENT 	= 0x04;
	static const uint8_t REG_CAL        = 0x05;

	// Reset (bit 15)
	// unused (bit 14)

	// Bus Voltage Range (bit 13)
	enum BG : uint8_t {
        FSR16V  = 0,
        FSR32V  = 1
    };

	// Shunt Voltage Range (bit 12-11)
	enum PG : uint8_t {
		X1		= 0b00,    // 40mV
		X2		= 0b01,    // 80mV
		X4		= 0b10,    // 160mV
		X8		= 0b11     // 320mV
	};

	// Bus Voltage ADC (bit 10-7)
	// Shunt Voltage ADC (bit 6-3)
	// Resolution/Samples
    enum ADC : uint8_t {
        ADC9        = 0b0000,
        ADC10       = 0b0001,
        ADC11       = 0b0010,
        ADC12       = 0b0011,
        SAMPLES2    = 0b1001,
        SAMPLES4    = 0b1010,
        SAMPLES8    = 0b1011,
        SAMPLES16   = 0b1100,
        SAMPLES32   = 0b1101,
        SAMPLES64   = 0b1110,
        SAMPLES128  = 0b1111
    };

	// Mode (bit 2-0)
	enum MODE : uint8_t {
		SLEEP 	    = 0b000,
		TRIG_SHUNT	= 0b001,
		TRIG_BUS    = 0b001,
		TRIG        = 0b011,
		ADC_OFF     = 0b100,
		CONT_SHUNT  = 0b101,
		CONT_BUS    = 0b110,
		CONT	    = 0b111
	};
}

class ina219_drv {

public:
	ina219_drv(i2c_interface & i2c, uint8_t _i2c_addr = INA219::ADDRESS);

	void setConfig(bool reset, INA219::BG busgain, INA219::PG powergain, INA219::ADC busadc, INA219::ADC shuntadc, INA219::MODE mode);
	void setCalibration(uint16_t maxCurrent, float shuntR);
	float getShuntVoltage();    // mV
	float getBusVoltage();      // V
	float getCurrent();         // ma

private:
	i2c_interface & _i2c;
	uint8_t _i2c_addr;

	INA219::BG busgain      = INA219::BG::FSR32V;
	INA219::PG shuntgain    = INA219::PG::X8;
	INA219::ADC busadc      = INA219::ADC::ADC12;
	INA219::ADC shuntadc    = INA219::ADC::ADC12;
	INA219::MODE mode       = INA219::MODE::CONT;

	uint16_t calibration    = 0;
	float currentLSB        = 0;

	void writeRegister(uint8_t reg, uint16_t val);
	uint16_t readRegister(uint8_t reg);
};

#endif
