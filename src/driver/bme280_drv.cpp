/*
 * bme280_drv.cpp
 *
 *  Created on: Mar 15, 2017
 *      Author: Dennis Hoffmann
 */

#include "bme280_drv.h"

bme280_drv::bme280_drv(i2c_interface & i2c, uint8_t i2c_addr) : _i2c(i2c), _i2c_addr(i2c_addr){
	get_calibration_data();
}

void bme280_drv::soft_reset(){
	writeRegister(BME280::REG_RESET, BME280::RESET);
}

float bme280_drv::get_temperature(){
    int32_t var1, var2;
    int32_t adc_T = static_cast<int32_t>(read_u24(BME280::REG_TEMP_MSB));

    if (adc_T == 0x800000){
    	return -273.15;
    }

    // expect 20bit value
    adc_T >>= 4;
    var1 = ((((adc_T>>3) - ((int32_t)_calibration_data.dig_T1 <<1))) * ((int32_t)_calibration_data.dig_T2)) >> 11;

    var2 = (((((adc_T>>4) - ((int32_t)_calibration_data.dig_T1)) *
              ((adc_T>>4) - ((int32_t)_calibration_data.dig_T1))) >> 12) *
            ((int32_t)_calibration_data.dig_T3)) >> 14;

    t_fine = var1 + var2;

    float T = (t_fine * 5 + 128) >> 8;
    return T/100;
}

/*
float bme280_drv::get_pressure(){
    int64_t var1, var2, p;

    int32_t adc_P = read_u24(BME280::REG_PRESS_MSB);
    if (adc_P == 0x800000){
    	return -1;
    }

    // expect 20bit value
    adc_P >>= 4;

    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)_calibration_data.dig_P6;
    var2 = var2 + ((var1*(int64_t)_calibration_data.dig_P5)<<17);
    var2 = var2 + (((int64_t)_calibration_data.dig_P4)<<35);
    var1 = ((var1 * var1 * (int64_t)_calibration_data.dig_P3)>>8) +
           ((var1 * (int64_t)_calibration_data.dig_P2)<<12);
    var1 = (((((int64_t)1)<<47)+var1))*((int64_t)_calibration_data.dig_P1)>>33;

    if (var1 == 0) {
        return 0; // avoid exception caused by division by zero
    }
    p = 1048576 - adc_P;
    p = (((p<<31) - var2)*3125) / var1;
    var1 = (((int64_t)_calibration_data.dig_P9) * (p>>13) * (p>>13)) >> 25;
    var2 = (((int64_t)_calibration_data.dig_P8) * p) >> 19;

    p = ((p + var1 + var2) >> 8) + (((int64_t)_calibration_data.dig_P7)<<4);
    return (float)p/256;
}
*/


float bme280_drv::get_pressure(){
	int32_t var1, var2;
	int32_t adc_P = read_u24(BME280::REG_PRESS_MSB);
	uint32_t p;

	// 20bit format
	adc_P >>= 4;

	var1 = (t_fine >> 1) - 64000;
	var2 = (((var1 >> 2) * (var1 >> 2)) >> 11) * static_cast<int32_t>(_calibration_data.dig_P6);
	var2 = var2 + ((var1 * static_cast<int32_t>(_calibration_data.dig_P5)) << 1);
	var2 = (var2 >> 2) + (static_cast<int32_t>(_calibration_data.dig_P4) << 16);
	var1 = (((_calibration_data.dig_P3 * (((var1 >> 2) * (var1 >> 2)) >> 13)) >> 3) + (((static_cast<int32_t>(_calibration_data.dig_P2)) * var1) >> 1)) >> 18;
	var1 = ((((32768 + var1)) * (static_cast<int32_t>(_calibration_data.dig_P1))) >> 15);
	if(var1 == 0){
		return 0;
	}
	p = ((static_cast<uint32_t>(((int32_t)1048576) - adc_P) - (var2 >> 12))) * 3125;
	if(p < 0x80000000){
		p = (p << 1) / static_cast<uint32_t>(var1);
	}else{
		p = (p / static_cast<uint32_t>(var1)) * 2;
	}

	var1 = (static_cast<int32_t>(_calibration_data.dig_P9) * static_cast<int32_t>(((p >> 3) * (p >> 3)) >> 13)) >> 12;
	var2 = (static_cast<int32_t>(p >> 2) * static_cast<int32_t>(_calibration_data.dig_P8)) >> 13;
	p = static_cast<uint32_t>(static_cast<int32_t>(p) + ((var1 + var2 + _calibration_data.dig_P7) >> 4));
	return p/100.0;
}


//from offical driver bme280.c
float bme280_drv::get_humidity(){
    int32_t adc_H = read_u16(BME280::REG_HUM_MSB);
    if (adc_H == 0x8000){
    	return -1;
    }

    int32_t v_x1_u32r;

    v_x1_u32r = (t_fine - ((int32_t)76800));

    v_x1_u32r = (((((adc_H << 14) - (((int32_t)_calibration_data.dig_H4) << 20) -
                    (((int32_t)_calibration_data.dig_H5) * v_x1_u32r)) + ((int32_t)16384)) >> 15) *
                 (((((((v_x1_u32r * ((int32_t)_calibration_data.dig_H6)) >> 10) *
                      (((v_x1_u32r * ((int32_t)_calibration_data.dig_H3)) >> 11) + ((int32_t)32768))) >> 10) +
                    ((int32_t)2097152)) * ((int32_t)_calibration_data.dig_H2) + 8192) >> 14));

    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) *
                               ((int32_t)_calibration_data.dig_H1)) >> 4));

    v_x1_u32r = (v_x1_u32r < 0) ? 0 : v_x1_u32r;
    v_x1_u32r = (v_x1_u32r > 419430400) ? 419430400 : v_x1_u32r;
    float h = (v_x1_u32r>>12);
    return h / 1024.0;
}


void bme280_drv::set_sampling(BME280::MODE m,
				  BME280::FILTER f,
				  BME280::STANDBY_TIME t,
				  BME280::SAMPLING s_temp,
				  BME280::SAMPLING s_press,
				  BME280::SAMPLING s_hum){
	uint8_t reg_conf =  static_cast<uint8_t>(t) << 5 | static_cast<uint8_t>(f) << 2;
	uint8_t reg_ctrl_meas = static_cast<uint8_t>(s_temp) << 5 | static_cast<uint8_t>(s_press) << 2 | static_cast<uint8_t>(m);
	uint8_t reg_ctrl_hum = static_cast<uint8_t>(s_hum);

	writeRegister(BME280::REG_CTRL_HUM, reg_ctrl_hum);
	writeRegister(BME280::REG_CTRL_MEAS, reg_ctrl_meas);
	writeRegister(BME280::REG_CONFIG, reg_conf);
}

void bme280_drv::get_calibration_data(){
	_calibration_data.dig_T1 = read_u16_le(BME280::REG_DIG_T1);
	_calibration_data.dig_T2 = read_s16_le(BME280::REG_DIG_T2);
	_calibration_data.dig_T3 = read_s16_le(BME280::REG_DIG_T3);

	_calibration_data.dig_P1 = read_u16_le(BME280::REG_DIG_P1);
	_calibration_data.dig_P2 = read_s16_le(BME280::REG_DIG_P2);
	_calibration_data.dig_P3 = read_s16_le(BME280::REG_DIG_P3);
	_calibration_data.dig_P4 = read_s16_le(BME280::REG_DIG_P4);
	_calibration_data.dig_P5 = read_s16_le(BME280::REG_DIG_P5);
	_calibration_data.dig_P6 = read_s16_le(BME280::REG_DIG_P6);
	_calibration_data.dig_P7 = read_s16_le(BME280::REG_DIG_P7);
	_calibration_data.dig_P8 = read_s16_le(BME280::REG_DIG_P8);
	_calibration_data.dig_P9 = read_s16_le(BME280::REG_DIG_P9);

	_calibration_data.dig_H1 = readRegister(BME280::REG_DIG_H1);
	_calibration_data.dig_H2 = read_s16_le(BME280::REG_DIG_H2);
	_calibration_data.dig_H3 = readRegister(BME280::REG_DIG_H3);
	_calibration_data.dig_H4 = readRegister(BME280::REG_DIG_H4) << 4 | (readRegister(BME280::REG_DIG_H4+1) & 0b00001111);
	_calibration_data.dig_H5 = readRegister(BME280::REG_DIG_H5+1) << 4 | readRegister(BME280::REG_DIG_H5) >> 4;
	_calibration_data.dig_H6 = static_cast<int8_t>(readRegister(BME280::REG_DIG_H6));
}

void bme280_drv::writeRegister(uint8_t reg, uint8_t value){
	uint8_t txbuf[2];
	txbuf[0] = reg;
	txbuf[1] = value;
	_i2c.write(_i2c_addr, txbuf, 2);
}

uint8_t bme280_drv::readRegister(uint8_t reg){
	uint8_t txbuf[1];
	uint8_t rxbuf[1];
	txbuf[0] = reg;
	_i2c.write(_i2c_addr, txbuf, 1);
	_i2c.read(_i2c_addr, rxbuf, 1);
	return rxbuf[0];
}

uint32_t bme280_drv::read_u24(uint8_t reg){
	uint8_t txbuf[1];
	uint8_t rxbuf[3];
	txbuf[0] = reg;
	uint32_t val = 0;
	_i2c.write(_i2c_addr, txbuf, 1);
	_i2c.read(_i2c_addr, rxbuf, 3);
	val = rxbuf[0] << 16 | rxbuf[1] << 8 | rxbuf[2];
	return val;
}

uint16_t bme280_drv::read_u16_le(uint8_t reg){
	uint8_t txbuf[1];
	uint8_t rxbuf[2];
	txbuf[0] = reg;
	uint16_t val;
	_i2c.write(_i2c_addr, txbuf, 1);
	_i2c.read(_i2c_addr, rxbuf, 2);
	val = (rxbuf[1] << 8) | rxbuf[0];
	return val;
}

uint16_t bme280_drv::read_u16(uint8_t reg){
	uint8_t txbuf[1];
	uint8_t rxbuf[2];
	txbuf[0] = reg;
	uint16_t val;
	_i2c.write(_i2c_addr, txbuf, 1);
	_i2c.read(_i2c_addr, rxbuf, 2);
	val = (rxbuf[0] << 8) | rxbuf[1];
	return val;
}

uint16_t bme280_drv::read_s16_le(uint8_t reg){
	uint16_t val = read_u16_le(reg);
	return static_cast<int16_t>(val);
}

