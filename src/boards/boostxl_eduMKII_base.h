// This file defines a generic interface to
// the functionality of a BOOSTXL-EDU MKII board.

#ifndef _BOOSTXL_EDUMKII_BASE_H_
#define _BOOSTXL_EDUMKII_BASE_H_

#include "gpio_interface.h"
#include "spi_interface.h"
#include "i2c_interface.h"
#include "adc_interface.h"

struct boostxl_eduMKII_base {

    boostxl_eduMKII_base()
    :   need_buttons(false),
        need_led_rgb(false),
        need_buzzer(false),
        need_gator(false),
        need_servo(false),
        need_lcd(false),
        need_i2c(false),
        need_joystick(false),
        need_microphone(false),
        need_accelerometer(false),

        _button1(nullptr),
        _button2(nullptr),
        _led_red(nullptr),
        _led_green(nullptr),
        _led_blue(nullptr),
        _buzzer(nullptr),
        _gator(nullptr),
        _servo(nullptr),
        _lcd_spi(nullptr),
        _lcd_cs(nullptr),
        _lcd_rst(nullptr),
        _lcd_dc(nullptr),
        _sensor_i2c(nullptr),
        _opt3001_int(nullptr),
        _tmp006_int(nullptr),
        _joy_x(nullptr),
        _joy_y(nullptr),
        _joy_button(nullptr),
        _mic(nullptr),
        _acc_x(nullptr),
        _acc_y(nullptr),
        _acc_z(nullptr)
    {
    }

    bool    need_buttons;
    bool    need_led_rgb;
    bool    need_buzzer;
    bool    need_gator;
    bool    need_servo;
    bool    need_lcd;
    bool    need_i2c;
    bool    need_joystick;
    bool    need_microphone;
    bool    need_accelerometer;

    gpio_pin &      button1();
    gpio_pin &      button2();
    gpio_pin &      led_red();
    gpio_pin &      led_green();
    gpio_pin &      led_blue();
    gpio_pin &      buzzer();
    gpio_pin &      gator();
    gpio_pin &      servo();
    spi_interface & lcd_spi();
    gpio_pin &      lcd_cs();
    gpio_pin &      lcd_rst();
    gpio_pin &      lcd_dc();
    i2c_interface & sensor_i2c();
    gpio_pin &      opt3001_int();
    gpio_pin &      tmp006_int();
    adc_channel &   joy_x();
    adc_channel &   joy_y();
    gpio_pin &      joy_button();
    adc_channel &   mic();
    adc_channel &   acc_x();
    adc_channel &   acc_y();
    adc_channel &   acc_z();

protected:
    gpio_pin *      _button1;
    gpio_pin *      _button2;
    gpio_pin *      _led_red;
    gpio_pin *      _led_green;
    gpio_pin *      _led_blue;
    gpio_pin *      _buzzer;
    gpio_pin *      _gator;
    gpio_pin *      _servo;
    spi_interface * _lcd_spi;
    gpio_pin *      _lcd_cs;
    gpio_pin *      _lcd_rst;
    gpio_pin *      _lcd_dc;
    i2c_interface * _sensor_i2c;
    gpio_pin *      _opt3001_int;
    gpio_pin *      _tmp006_int;
    adc_channel *   _joy_x;
    adc_channel *   _joy_y;
    gpio_pin *      _joy_button;
    adc_channel *   _mic;
    adc_channel *   _acc_x;
    adc_channel *   _acc_y;
    adc_channel *   _acc_z;
};

#endif // _BOOSTXL_EDUMKII_BASE_H_
