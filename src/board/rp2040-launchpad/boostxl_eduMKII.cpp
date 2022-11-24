/*
 * boostxleduMKII.cpp
 *
 *  Created on: 23.11.2022
 *      Author: andreas
 */

#include "boostxl_eduMKII.h"

boostxl_eduMKII * boostxl_eduMKII::_inst = nullptr;

boostxl_eduMKII & boostxl_eduMKII::inst() {
    if (!_inst) {
        _inst = new boostxl_eduMKII();
    }
    return *_inst;
}

boostxl_eduMKII::boostxl_eduMKII()
    : boostxl_eduMKII_base(
        _button1,
        _button2,
        _led_red,
        _led_green,
        _led_blue,
        _buzzer,
        _gator,
        _servo,
        _lcd_spi,
        _lcd_cs,
        _lcd_rst,
        _lcd_dc,
        _lcd_bl,
//        _sensor_i2c,
        _opt3001_int,
        _tmp006_int,
//        _joy_x,
//        _joy_y,
        _joy_button
//        _mic,
//        _acc_x,
//        _acc_y,
//        _acc_z
      ),
        _button1        (BUTTON1),
        _button2        (BUTTON2),
        _led_red        (RGB_LED_RED),
        _led_green      (RGB_LED_GREEN),
        _led_blue       (RGB_LED_BLUE),
        _buzzer         (BUZZER),
        _gator          (GATOR),
        _servo          (SERVO),
        _lcd_spi        (0, LCD_MISO, LCD_MOSI, LCD_SCLK, lcd_cs),
        _lcd_cs         (LCD_CS),
        _lcd_rst        (LCD_RST),
        _lcd_dc         (LCD_DC),
        _lcd_bl         (LCD_BL),
//        _sensor_i2c     (SENSOR_SDA, SENSOR_SCL),
        _opt3001_int    (OPT3001_INT),
        _tmp006_int     (TMP006_INT),
//        _joy_x          (JOY_X),
//        _joy_y          (JOY_Y),
        _joy_button     (JOY_BUTTON)
//        _mic            (MIC),
//        _acc_x          (ACC_X),
//        _acc_y          (ACC_Y),
//        _acc_z          (ACC_Z)
{
}

