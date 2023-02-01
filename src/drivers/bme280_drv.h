/*
 * bme280_drv.h
 *
 *  Created on: Mar 15, 2017
 *      Author: Dennis Hoffmann
 */

#ifndef SRC_DRIVER_BME280_DRV_H_
#define SRC_DRIVER_BME280_DRV_H_

#include "i2c_interface.h"

namespace BME280 {
	// SDO connected to GND
	static const uint8_t ADDRESS 		= 0x76;

	// value softreset
	static const uint8_t RESET			= 0xB6;

	// V_DDIO connected to GND
	//static const uint8_t ADDRESS = 0x77;
	static const uint8_t REG_HUM_LSB 	= 0xFE;
	static const uint8_t REG_HUM_MSB 	= 0xFD;
	static const uint8_t REG_TEMP_XLSB 	= 0xFC;
	static const uint8_t REG_TEMP_LSB 	= 0xFB;
	static const uint8_t REG_TEMP_MSB 	= 0xFA;
	static const uint8_t REG_PRESS_XLSB = 0xF9;
	static const uint8_t REG_PRESS_LSB 	= 0xF8;
	static const uint8_t REG_PRESS_MSB 	= 0xF7;
	static const uint8_t REG_CONFIG 	= 0xF5;
	static const uint8_t REG_CTRL_MEAS 	= 0xF4;
	static const uint8_t REG_STATUS 	= 0xF3;
	static const uint8_t REG_CTRL_HUM 	= 0xF2;
	static const uint8_t REG_RESET 		= 0xE0;
	static const uint8_t REG_ID 		= 0xD0;// ID = 0x60

	//Calibration Data Register
	//temperature
	static const uint8_t REG_DIG_T1		= 0x88;
	static const uint8_t REG_DIG_T2		= 0x8A;
	static const uint8_t REG_DIG_T3		= 0x8C;

	//pressure
	static const uint8_t REG_DIG_P1		= 0x8E;
	static const uint8_t REG_DIG_P2		= 0x90;
	static const uint8_t REG_DIG_P3		= 0x92;
	static const uint8_t REG_DIG_P4		= 0x94;
	static const uint8_t REG_DIG_P5		= 0x96;
	static const uint8_t REG_DIG_P6		= 0x98;
	static const uint8_t REG_DIG_P7		= 0x9A;
	static const uint8_t REG_DIG_P8		= 0x9C;
	static const uint8_t REG_DIG_P9		= 0x9E;

	//humidity
	static const uint8_t REG_DIG_H1		= 0xA1;
	static const uint8_t REG_DIG_H2		= 0xE1;
	static const uint8_t REG_DIG_H3		= 0xE3;
	static const uint8_t REG_DIG_H4		= 0xE4;
	static const uint8_t REG_DIG_H5		= 0xE5;
	static const uint8_t REG_DIG_H6		= 0xE7;

	enum class SAMPLING : uint8_t {
		OFF	    = 0b000,
		X1		= 0b001,
		X2		= 0b010,
		X4		= 0b011,
		X8		= 0b100,
		X16		= 0b101
	};

	enum class MODE : uint8_t {
		SLEEP 	= 0b000,
		FORCED	= 0b001,
		NORMAL	= 0b011
	};

	enum class FILTER : uint8_t {
		OFF		= 0b000,
		X2		= 0b001,
		X4		= 0b010,
		X8		= 0b011,
		X16	= 0b100
	};

	enum class STANDBY_TIME : uint8_t {
		MS_0	= 0b000, //  0,5ms
		MS_62	= 0b001, // 62,5ms
		MS_125	= 0b010,
		MS_250	= 0b011,
		MS_500	= 0b100,
		MS_1000	= 0b101,
		MS_10	= 0b110,
		MS_20	= 0b111
	};

	struct CALIBRATION_DATA {
		//temperature
		uint16_t	dig_T1;
		int16_t		dig_T2;
		int16_t		dig_T3;

		//pressure
		uint16_t	dig_P1;
		int16_t		dig_P2;
		int16_t		dig_P3;
		int16_t		dig_P4;
		int16_t		dig_P5;
		int16_t		dig_P6;
		int16_t		dig_P7;
		int16_t		dig_P8;
		int16_t		dig_P9;

		//humidity
		uint8_t		dig_H1;
		int16_t		dig_H2;
		uint8_t		dig_H3;
		int16_t		dig_H4;
		int16_t		dig_H5;
		int8_t		dig_H6;
	};

}

class bme280_drv {

public:
	bme280_drv(i2c_interface & i2c, uint8_t _i2c_addr);
	float get_temperature();
	float get_pressure();
	float get_humidity();
	void set_sampling(BME280::MODE m,
					  BME280::FILTER f,
					  BME280::STANDBY_TIME t,
					  BME280::SAMPLING s_temp,
					  BME280::SAMPLING s_press,
					  BME280::SAMPLING s_hum);

	void get_calibration_data();
	bool detect_sensor();

private:
	i2c_interface & _i2c;
	uint8_t _i2c_addr;
	int32_t t_fine;
	BME280::CALIBRATION_DATA _calibration_data;
	void soft_reset();

	void writeRegister(uint8_t reg, uint8_t val);
	uint8_t readRegister(uint8_t reg);
	uint32_t read_u24(uint8_t reg);
	uint16_t read_u16(uint8_t reg);
	uint16_t read_u16_le(uint8_t reg);
	uint16_t read_s16_le(uint8_t reg);
};

#endif /* SRC_DRIVER_BME280_DRV_H_ */
