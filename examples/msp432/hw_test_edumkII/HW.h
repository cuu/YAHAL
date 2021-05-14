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
// This class contains all HW-dependencies for
// the MSP432 lauchpad and the Edu MKII Boosterpack.
//

#ifndef _HW_H_
#define _HW_H_

#include "task.h"
#include "lock_base_msp432.h"
#include "mutex.h"
#include "gpio_msp432.h"
#include "adc14_msp432.h"
#include "spi_msp432.h"
#include "st7735s_drv.h"
#include "i2c_msp432.h"
#include "opt3001_drv.h"

class HW
{
private:
    HW()
    : red        ( PORT_PIN(1,0) ),
      rgb_red    ( PORT_PIN(2,0) ),
      rgb_green  ( PORT_PIN(2,1) ),
      rgb_blue   ( PORT_PIN(2,2) ),
      sw1        ( PORT_PIN(1,1) ),
      sw2        ( PORT_PIN(1,4) ),
      edu_red    ( PORT_PIN(2,6) ),
      edu_green  ( PORT_PIN(2,4) ),
      edu_blue   ( PORT_PIN(5,6) ),
      edu_sw1    ( PORT_PIN(5,1) ),
      edu_sw2    ( PORT_PIN(3,5) ),
      edu_joy_sw ( PORT_PIN(4,1) ),
      edu_speaker( PORT_PIN(2,7) ),
      servo      ( PORT_PIN(2,5) ),
      lcd_cs     ( PORT_PIN(5, 0)),
      lcd_spi    ( EUSCI_B0_SPI, lcd_cs),
      lcd_rst    ( PORT_PIN(5, 7)),
      lcd_dc     ( PORT_PIN(3, 7)),
      lcd        ( lcd_spi, lcd_rst, lcd_dc, st7735s_drv::Crystalfontz_128x128, &lcd_mutex),
      sen_i2c    ( EUSCI_B1 ),
      sen_light  ( sen_i2c, OPT3001::I2C_ADDR_GND),
      mic        ( 10 ),
      joy_x      ( 15 ),
      joy_y      (  9 ),
      accel_x    ( 14 ),
      accel_y    ( 13 ),
      accel_z    ( 11 )
    {
        red.        gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
        rgb_red.    gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
        rgb_green.  gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
        rgb_blue.   gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
        sw1.        gpioMode(GPIO::INPUT  | GPIO::PULLUP);
        sw2.        gpioMode(GPIO::INPUT  | GPIO::PULLUP);
        edu_red.    gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
        edu_green.  gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
        edu_blue.   gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
        edu_sw1.    gpioMode(GPIO::INPUT);
        edu_sw2.    gpioMode(GPIO::INPUT);
        edu_joy_sw. gpioMode(GPIO::INPUT);
        edu_speaker.gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
        servo.      gpioMode(GPIO::OUTPUT);
        servo.      setSEL(1);
        // Set up SPI & I2C interface
        lcd_spi.setSpeed(12000000);
        sen_i2c.setSpeed(100000);
        // Set up sensors
        sen_light.start_measure(OPT3001::CONF_100MS_CONT);
        // Set up temp sensor
        uint8_t buf[3];
        buf[0] = 0x02; // Config register
        buf[1] = 0x74;
        buf[2] = 0x00;
        sen_i2c.i2cWrite(0x40, buf, 3);
        // Set up ADC conversion (scan mode)
        adc14_msp432::inst.adcSetupScan(ADC::ADC_12_BIT);
        adc14_msp432::inst.adcStartScan(9, 15);
    }

    static HW * _inst;

public:

    static HW * inst() {
        if (_inst == nullptr) {
            _inst = new HW();
        }
        return _inst;
    }

    // All HW on the msp432 launchpad
    gpio_msp432_pin red;
    gpio_msp432_pin rgb_red;
    gpio_msp432_pin rgb_green;
    gpio_msp432_pin rgb_blue;
    gpio_msp432_pin sw1;
    gpio_msp432_pin sw2;

    // All HW on the educational boosterpack MKII
    gpio_msp432_pin edu_red;
    gpio_msp432_pin edu_green;
    gpio_msp432_pin edu_blue;
    gpio_msp432_pin edu_sw1;
    gpio_msp432_pin edu_sw2;
    gpio_msp432_pin edu_joy_sw;
    gpio_msp432_pin edu_speaker;

    gpio_msp432_pin servo;

    gpio_msp432_pin lcd_cs;
    spi_msp432      lcd_spi;
    gpio_msp432_pin lcd_rst;
    gpio_msp432_pin lcd_dc;
    mutex<lock_base_msp432> lcd_mutex;
    st7735s_drv     lcd;

    i2c_msp432      sen_i2c;
    opt3001_drv     sen_light;

    adc14_msp432_channel mic;
    adc14_msp432_channel joy_x;
    adc14_msp432_channel joy_y;
    adc14_msp432_channel accel_x;
    adc14_msp432_channel accel_y;
    adc14_msp432_channel accel_z;
};

#endif /* _HW_H_ */
