// This file defines a gemeric interface to
// the functionality of a BOOSTXL-EDU MKII board.

#ifndef _BOOSTXL_EDUMKII_BASE_H_
#define _BOOSTXL_EDUMKII_BASE_H_

#include "gpio_interface.h"
#include "spi_interface.h"
#include "i2c_interface.h"
#include "adc_interface.h"

class boostxl_eduMKII_base {
public:
    boostxl_eduMKII_base(
            gpio_pin &      _button1,
            gpio_pin &      _button2,
            gpio_pin &      _led_red,
            gpio_pin &      _led_green,
            gpio_pin &      _led_blue,
            gpio_pin &      _buzzer,
            gpio_pin &      _gator,
            gpio_pin &      _servo,
            spi_interface & _lcd_spi,
            gpio_pin &      _lcd_cs,
            gpio_pin &      _lcd_rst,
            gpio_pin &      _lcd_dc,
            gpio_pin &      _lcd_bl,
//            i2c_interface & _sensor_i2c,
            gpio_pin &      _opt3001_int,
            gpio_pin &      _tmp006_int,
//            adc_channel &   _joy_x,
//            adc_channel &   _joy_y,
            gpio_pin &      _joy_button
//            adc_channel &   _mic,
//            adc_channel &   _acc_x,
//            adc_channel &   _acc_y,
//            adc_channel &   _acc_z
    )
        :   button1     (_button1    ),
            button2     (_button2    ),
            led_red     (_led_red    ),
            led_green   (_led_green  ),
            led_blue    (_led_blue   ),
            buzzer      (_buzzer     ),
            gator       (_gator      ),
            servo       (_servo      ),
            lcd_spi     (_lcd_spi    ),
            lcd_cs      (_lcd_cs     ),
            lcd_rst     (_lcd_rst    ),
            lcd_dc      (_lcd_dc     ),
            lcd_bl      (_lcd_bl     ),
//            sensor_i2c  (_sensor_i2c ),
            opt3001_int (_opt3001_int),
            tmp006_int  (_tmp006_int ),
//            joy_x       (_joy_x      ),
//            joy_y       (_joy_y      ),
            joy_button  (_joy_button )
//            mic         (_mic        ),
//            acc_x       (_acc_x      ),
//            acc_y       (_acc_y      ),
//            acc_z       (_acc_z      )
    {
    }

public:
    gpio_pin &      button1;
    gpio_pin &      button2;
    gpio_pin &      led_red;
    gpio_pin &      led_green;
    gpio_pin &      led_blue;
    gpio_pin &      buzzer;
    gpio_pin &      gator;
    gpio_pin &      servo;
    spi_interface & lcd_spi;
    gpio_pin &      lcd_cs;
    gpio_pin &      lcd_rst;
    gpio_pin &      lcd_dc;
    gpio_pin &      lcd_bl;
//    i2c_interface & sensor_i2c;
    gpio_pin &      opt3001_int;
    gpio_pin &      tmp006_int;
//    adc_channel &   joy_x;
//    adc_channel &   joy_y;
    gpio_pin &      joy_button;
//    adc_channel &   mic;
//    adc_channel &   acc_x;
//    adc_channel &   acc_y;
//    adc_channel &   acc_z;
};

#endif // _BOOSTXL_EDUMKII_BASE_H_
