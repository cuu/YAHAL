
#ifndef _RP2040_LAUNCHPAD_BOOSTXL_EDUMKII_H_
#define _RP2040_LAUNCHPAD_BOOSTXL_EDUMKII_H_

// Big Buttons
#define BUTTON1         16
#define BUTTON2         17
// 3 color LED
#define RGB_LED_RED     13
#define RGB_LED_GREEN   10
#define RGB_LED_BLUE     8
// Buzzer
#define BUZZER          14
// Gator holes
#define GATOR            6
// Servo PWM signal
#define SERVO           12
// LCD
#define LCD_MISO         4
#define LCD_MOSI         7
#define LCD_SCLK        22
#define LCD_CS           5
#define LCD_RST          9
#define LCD_DC           2
#define LCD_BL          13
// I2C sensors
#define SENSOR_SDA      24
#define SENSOR_SCL      26
#define OPT3001_INT     23
#define TMP006_INT       3
// Joystick
#define JOY_X           A1
#define JOY_Y           A3
#define JOY_BUTTON      19
// Microphone
#define MIC             A6
// Accelerometer
#define ACC_X           A0
#define ACC_Y           A2
#define ACC_Z           A4

#include "gpio_rp2040.h"
#include "spi_rp2040.h"
#include "boostxl_eduMKII_base.h"

class boostxl_eduMKII : public boostxl_eduMKII_base {
public:

    static boostxl_eduMKII & inst();

private:
    boostxl_eduMKII();
    static boostxl_eduMKII * _inst;

    gpio_rp2040_pin     _button1;
    gpio_rp2040_pin     _button2;
    gpio_rp2040_pin     _led_red;
    gpio_rp2040_pin     _led_green;
    gpio_rp2040_pin     _led_blue;
    gpio_rp2040_pin     _buzzer;
    gpio_rp2040_pin     _gator;
    gpio_rp2040_pin     _servo;
    spi_rp2040          _lcd_spi;
    gpio_rp2040_pin     _lcd_cs;
    gpio_rp2040_pin     _lcd_rst;
    gpio_rp2040_pin     _lcd_dc;
    gpio_rp2040_pin     _lcd_bl;
//    i2c_interface &     _sensor_i2c;
    gpio_rp2040_pin     _opt3001_int;
    gpio_rp2040_pin     _tmp006_int;
//    adc_channel &       _joy_x;
//    adc_channel &       _joy_y;
    gpio_rp2040_pin     _joy_button;
//    adc_channel &       _mic;
//    adc_channel &       _acc_x;
//    adc_channel &       _acc_y;
//    adc_channel &       _acc_z;
};

#endif // _RP2040_LAUNCHPAD_BOOSTXL_EDUMKII_H_
