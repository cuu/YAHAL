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
// the RP2040 lauchpad and the Edu MKII Boosterpack.
//

#ifndef _HW_H_
#define _HW_H_

#include "task.h"
#include "lock_base_rp2040.h"
#include "mutex.h"
#include "gpio_rp2040.h"
#include "adc_rp2040.h"
#include "spi_rp2040.h"
#include "st7735s_drv.h"
#include "i2c_rp2040.h"
#include "opt3001_drv.h"

class HW
{
private:
    HW()
    :
//      red        ( 13 ),
//      sw1        ( 16 ),
//      sw2        ( 17 ),
//      edu_red    ( 13 ),
//      edu_green  ( 10 ),
//      edu_blue   (  8 ),
//      edu_sw1    ( 16 ),
//      edu_sw2    ( 17 ),
      edu_joy_sw ( 19 ),
//      edu_speaker( 14 ),
//      servo      ( 12 ),
      lcd_cs     (  5 ),
      lcd_spi    (  0, 4, 7, 22, lcd_cs),
      lcd_rst    (  9 ),
      lcd_dc     (  2 ),
      lcd        ( lcd_spi, lcd_rst, lcd_dc, st7735s_drv::Crystalfontz_128x128, &lcd_mutex),
      sen_i2c    ( 0, 24, 25, 0 ),
      sen_light  ( sen_i2c, OPT3001::I2C_ADDR_GND),
      mic        (  6 ),
      joy_x      (  1 ),
      joy_y      (  3 ),
      accel_x    (  0 ),
      accel_y    (  2 ),
      accel_z    (  4 )
    {
//        red.        gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
//        rgb_red.    gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
//        rgb_green.  gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
//        rgb_blue.   gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
//        sw1.        gpioMode(GPIO::INPUT  | GPIO::PULLUP);
//        sw2.        gpioMode(GPIO::INPUT  | GPIO::PULLUP);
//        edu_red.    gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
//        edu_green.  gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
//        edu_blue.   gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
//        edu_sw1.    gpioMode(GPIO::INPUT);
//        edu_sw2.    gpioMode(GPIO::INPUT);
//        edu_joy_sw. gpioMode(GPIO::INPUT);
//        edu_speaker.gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
//        servo.      gpioMode(GPIO::OUTPUT);
////        servo.      setSEL(1);
//        // Set up SPI & I2C interface
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
        //adc_msp432::inst.adcSetupScan(ADC::ADC_12_BIT);
        //adc_msp432::inst.adcStartScan(9, 15);
    }

    static HW * _inst;

public:

    static HW * inst() {
        if (_inst == nullptr) {
            _inst = new HW();
        }
        return _inst;
    }

    // All HW on the rp2040 launchpad
//    gpio_rp2040_pin red;
//    gpio_rp2040_pin rgb_red;
//    gpio_rp2040_pin rgb_green;
//    gpio_rp2040_pin rgb_blue;
//    gpio_rp2040_pin sw1;
//    gpio_rp2040_pin sw2;
//
//    // All HW on the educational boosterpack MKII
//    gpio_rp2040_pin edu_red;
//    gpio_rp2040_pin edu_green;
//    gpio_rp2040_pin edu_blue;
//    gpio_rp2040_pin edu_sw1;
//    gpio_rp2040_pin edu_sw2;
    gpio_rp2040_pin edu_joy_sw;
//    gpio_rp2040_pin edu_speaker;
//
//    gpio_rp2040_pin servo;
//
    gpio_rp2040_pin lcd_cs;
    spi_rp2040      lcd_spi;
    gpio_rp2040_pin lcd_rst;
    gpio_rp2040_pin lcd_dc;
    mutex<lock_base_rp2040> lcd_mutex;
    st7735s_drv     lcd;
//
    i2c_rp2040      sen_i2c;
    opt3001_drv     sen_light;
//
    adc_rp2040_channel mic;
    adc_rp2040_channel joy_x;
    adc_rp2040_channel joy_y;
    adc_rp2040_channel accel_x;
    adc_rp2040_channel accel_y;
    adc_rp2040_channel accel_z;
};

#endif /* _HW_H_ */
