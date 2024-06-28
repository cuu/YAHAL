/* Name: mpu6050_low.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include <cmath>
#include <cstdlib>
#include <cassert>
#include "mpu6050.h"

/**
 * Move pointer to register
 * @param reg register address [hex]
 */
void _MPU6050_moveToReg(i2c_interface & i2c, uint8_t reg) {
    uint8_t buf[1];
    buf[0] = reg;
    i2c.i2cWrite(MPU6050_I2C_ADDR, buf, 1);
}

/**
 * Getting the value from a register
 * @param  reg register address [hex]
 * @param  len number of bytes of the register
 * @return     register value
 */
int32_t _MPU6050_getRegValue(i2c_interface & i2c, uint8_t reg, uint8_t len) {
    _MPU6050_moveToReg(i2c, reg);
    uint8_t buf[20];

    int16_t l = i2c.i2cRead(MPU6050_I2C_ADDR, buf, len);
    int32_t value = 0;
    assert(l==len);
    for (uint8_t i = 0; i < l; i++) {
        value <<= 8;
        value += buf[i];
    }
    return value;
}

/**
 * Writing value to the register
 * @param reg   register address [hex]
 * @param value value to write
 */
void _MPU6050_writeToReg(i2c_interface & i2c, uint8_t reg, uint8_t value) {
    uint8_t buf[2];
    buf[0] = reg;
    buf[1] = value;
    i2c.i2cWrite(0x68, buf, 2);
}

/**
 * Getting an array of registers values
 * @param  reg - register address [hex]
 * @param  len - number of bytes of the register
 * @return     the array of values
 */
int32_t* _MPU6050_getArrValues(i2c_interface & i2c, uint8_t reg, uint8_t len) {
    // Create array
    int32_t *arr = (int32_t *)malloc(len * sizeof(int32_t));

    // Getting values of registers
    for (uint8_t i = 0; i < len; i++) {
        arr[i] = (int16_t)_MPU6050_getRegValue(i2c, reg + i * 2, 2);
    }
    return arr;
}

/**
 * Initialize and set the settings MPU6050
 */
void MPU6050_Init(i2c_interface & i2c) {
    // I2C Initialize
//    I2C_init();

    //Sets sample rate to 8000/1+7 = 1000Hz
    _MPU6050_writeToReg(i2c, SMPLRT_DIV, 0x07);

    //Disable FSync, 256Hz DLPF
    _MPU6050_writeToReg(i2c, CONFIG, 0x00);

    //Disable gyro self tests, scale of 2000 degrees/s
    _MPU6050_writeToReg(i2c, GYRO_CONFIG, 0b00011000);

    //Disable accel self tests, scale of +-2g, no DHPF
    _MPU6050_writeToReg(i2c, ACCEL_CONFIG, 0x00);

    //Freefall threshold of |0mg|
    _MPU6050_writeToReg(i2c, FF_THR, 0x00);

    //Freefall duration limit of 0
    _MPU6050_writeToReg(i2c, FF_DUR, 0x00);

    //Motion threshold of 0mg
    _MPU6050_writeToReg(i2c, MOT_THR, 0x00);

    //Motion duration of 0s
    _MPU6050_writeToReg(i2c, MOT_DUR, 0x00);

    //Zero motion threshold
    _MPU6050_writeToReg(i2c, ZRMOT_THR, 0x00);

    //Zero motion duration threshold
    _MPU6050_writeToReg(i2c, ZRMOT_DUR, 0x00);

    //Disable sensor output to FIFO buffer
    _MPU6050_writeToReg(i2c, FIFO_EN, 0x00);

    //AUX I2C setup
    //Sets AUX I2C to single master control, plus other config
    _MPU6050_writeToReg(i2c, I2C_MST_CTRL, 0x00);
    //Setup AUX I2C slaves
    _MPU6050_writeToReg(i2c, I2C_SLV0_ADDR, 0x00);
    _MPU6050_writeToReg(i2c, I2C_SLV0_REG, 0x00);
    _MPU6050_writeToReg(i2c, I2C_SLV0_CTRL, 0x00);
    _MPU6050_writeToReg(i2c, I2C_SLV1_ADDR, 0x00);
    _MPU6050_writeToReg(i2c, I2C_SLV1_REG, 0x00);
    _MPU6050_writeToReg(i2c, I2C_SLV1_CTRL, 0x00);
    _MPU6050_writeToReg(i2c, I2C_SLV2_ADDR, 0x00);
    _MPU6050_writeToReg(i2c, I2C_SLV2_REG, 0x00);
    _MPU6050_writeToReg(i2c, I2C_SLV2_CTRL, 0x00);
    _MPU6050_writeToReg(i2c, I2C_SLV3_ADDR, 0x00);
    _MPU6050_writeToReg(i2c, I2C_SLV3_REG, 0x00);
    _MPU6050_writeToReg(i2c, I2C_SLV3_CTRL, 0x00);
    _MPU6050_writeToReg(i2c, I2C_SLV4_ADDR, 0x00);
    _MPU6050_writeToReg(i2c, I2C_SLV4_REG, 0x00);
    _MPU6050_writeToReg(i2c, I2C_SLV4_DO, 0x00);
    _MPU6050_writeToReg(i2c, I2C_SLV4_CTRL, 0x00);
    _MPU6050_writeToReg(i2c, I2C_SLV4_DI, 0x00);
    //I2C_MST_STATUS //Read-only
    //Setup INT pin and AUX I2C pass through
    _MPU6050_writeToReg(i2c, INT_PIN_CFG, 0x00);
    //Enable data ready interrupt
    _MPU6050_writeToReg(i2c, INT_ENABLE, 0x00);

    //Slave out, dont care
    _MPU6050_writeToReg(i2c, I2C_SLV0_DO, 0x00);
    _MPU6050_writeToReg(i2c, I2C_SLV1_DO, 0x00);
    _MPU6050_writeToReg(i2c, I2C_SLV2_DO, 0x00);
    _MPU6050_writeToReg(i2c, I2C_SLV3_DO, 0x00);
    //More slave config
    _MPU6050_writeToReg(i2c, I2C_MST_DELAY_CTRL, 0x00);
    //Reset sensor signal paths
    _MPU6050_writeToReg(i2c, SIGNAL_PATH_RESET, 0x00);
    //Motion detection control
    _MPU6050_writeToReg(i2c, MOT_DETECT_CTRL, 0x00);
    //Disables FIFO, AUX I2C, FIFO and I2C reset bits to 0
    _MPU6050_writeToReg(i2c, USER_CTRL, 0x00);
    //Sets clock source to gyro reference w/ PLL
    _MPU6050_writeToReg(i2c, PWR_MGMT_1, 0b00000010);
    //Controls frequency of wakeups in accel low power mode plus the sensor standby modes
    _MPU6050_writeToReg(i2c, PWR_MGMT_2, 0x00);
}

/**
 * Returning a value of "whoAmI" register MPU6050
 * @return  "whoAmI" register value
 */
uint8_t MPU6050_whoAmI(i2c_interface & i2c) {
    // Getting value of "whoAmI" register
    return _MPU6050_getRegValue(i2c, WHO_AM_I, 1);
}

/**
 * Getting a value of temperature registers MPU6050
 * @return  temperature register value
 */
int16_t MPU6050_getTemp(i2c_interface & i2c) {
    // Getting value of temperature register
    return _MPU6050_getRegValue(i2c, TEMP_OUT_H, 2);
}

/**
 * Getting a value of accelerometer registers MPU6050
 * @return  the array of accelerometer registers values
 */
int32_t* MPU6050_getAccel(i2c_interface & i2c) {
    // Getting value of accelerometer registers for X, Y and Z axises
    return _MPU6050_getArrValues(i2c, ACCEL_XOUT_H, 3);
}

/**
 * Getting a value of gyroscope registers MPU6050
 * @return  the array of gyroscope registers values
 */
int32_t* MPU6050_getGyro(i2c_interface & i2c) {
    // Getting value of gyroscope registers for X, Y and Z axises
    return _MPU6050_getArrValues(i2c, GYRO_XOUT_H, 3);
}

/**
 * Computing the temperature in degrees Celsius
 * @return      temperature in degrees Celsius
 */
float MPU6050_countTemp(i2c_interface & i2c) {
    // Getting the values of temp_high and temp_l registers
    int16_t temp_reg = MPU6050_getTemp(i2c);

    // Computing the temperature in degrees Celsius
    return temp_reg / 340 + 36.53;
}

/**
 * Counts the deviation angle of the MPU6050 module from the accelerometer data
 * @param  a - accelerometer data on the axes x, y, z
 * @param  b - accelerometer data on the axes x, y, z
 * @param  c - accelerometer data on the axes x, y, z
 * @return   calculated angle
 */
float _MPU6050_countAccelAngle(float a, float b, float c) {
    return 57.295 * atan(a / sqrt(pow(b, 2) + pow(c,2)));
}

/**
 * [_MPU6050_countGyroAngle description]
 * @param  previous_data - angles that has benn counted on previous iteration
 * @param  data          - gyroscope data
 * @param  delta         - the time that passed between the measurements
 * @return               calculated angle
 */
float _MPU6050_countGyroAngle(float previous_data, int32_t data, int32_t delta) {
    return previous_data + data * delta * 0.001;
}

/**
 * Counts the deviation angles of the MPU6050 module from the accelerometer data on the axes x, y, z
 * @return an array of the calculated angles
 */
float* MPU6050_getAccelAngles(i2c_interface & i2c) {
    int32_t* accel = MPU6050_getAccel(i2c);
    float *accel_angle = (float *)malloc(sizeof(float) * 3);
    accel_angle[0] = _MPU6050_countAccelAngle(accel[0], accel[1], accel[2]);
    accel_angle[1] = _MPU6050_countAccelAngle(accel[1], accel[0], accel[2]);
    accel_angle[2] = _MPU6050_countAccelAngle(accel[2], accel[0], accel[1]);

    return accel_angle;
}

/**
 * Counts the deviation angles of the MPU6050 module from the accelerometer data on the axes x, y, z
 * @param  previous_data - angles that has benn counted on previous iteration
 * @param  delta         - the time that passed between the measurements
 * @return               an array of the calculated angles
 */
float* MPU6050_getGyroAngles(i2c_interface & i2c, float* previous_data, int32_t delta) {
    int32_t* gyro = MPU6050_getGyro(i2c);
    float *gyro_angle = (float *)malloc(sizeof(float) * 3);
    for (uint8_t i = 0; i < 3; i++) {
        gyro_angle[i] = _MPU6050_countGyroAngle(previous_data[i], gyro[i], delta);
    }
    return gyro_angle;
}

/**
 * Carries out the filtration of calculated angles
 * @param  previous_data - a previous values array of data
 * @param  filter_func   - a function that filters a data
 * @return               an array of filtered data
 */
float* MPU6050_getFilteredAngles(i2c_interface & i2c,
    float *previous_data,
    float* (* filter_func)(float* accel, float* gyro, float* previous_data, uint8_t len)
) {
    // Obtain the angles calculated from the accelerometer data
    float* accel = MPU6050_getAccelAngles();

    // Obtain the angles calculated from the gyroscope data
    float* gyro = MPU6050_getGyroAngles(i2c, previous_data, 200);

    // Use callback function and return an array of filtered data
    return filter_func(accel, gyro, previous_data, 3);
}
