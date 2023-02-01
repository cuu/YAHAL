#include "boostxl_eduMKII_base.h"
#include <cassert>

gpio_pin & boostxl_eduMKII_base::button1() {
    assert(_button1);
    return *_button1;
}

gpio_pin & boostxl_eduMKII_base::button2(){
    assert(_button2);
    return *_button2;
}

gpio_pin & boostxl_eduMKII_base::led_red(){
    assert(_led_red);
    return *_led_red;
}

gpio_pin & boostxl_eduMKII_base::led_green(){
    assert(_led_green);
    return *_led_green;
}

gpio_pin & boostxl_eduMKII_base::led_blue(){
    assert(_led_blue);
    return *_led_blue;
}

gpio_pin & boostxl_eduMKII_base::buzzer(){
    assert(_buzzer);
    return *_buzzer;
}

gpio_pin & boostxl_eduMKII_base::gator(){
    assert(_gator);
    return *_gator;
}

gpio_pin & boostxl_eduMKII_base::servo(){
    assert(_servo);
    return *_servo;
}

spi_interface & boostxl_eduMKII_base::lcd_spi(){
    assert(_lcd_spi);
    return *_lcd_spi;
}

gpio_pin & boostxl_eduMKII_base::lcd_cs(){
    assert(_lcd_cs);
    return *_lcd_cs;
}

gpio_pin & boostxl_eduMKII_base::lcd_rst(){
    assert(_lcd_rst);
    return *_lcd_rst;
}

gpio_pin & boostxl_eduMKII_base::lcd_dc(){
    assert(_lcd_dc);
    return *_lcd_dc;
}

i2c_interface & boostxl_eduMKII_base::sensor_i2c(){
    assert(_sensor_i2c);
    return *_sensor_i2c;
}

gpio_pin & boostxl_eduMKII_base::opt3001_int(){
    assert(_opt3001_int);
    return *_opt3001_int;
}

gpio_pin & boostxl_eduMKII_base::tmp006_int(){
    assert(_tmp006_int);
    return *_tmp006_int;
}

adc_channel & boostxl_eduMKII_base::joy_x(){
    assert(_joy_x);
    return *_joy_x;
}

adc_channel & boostxl_eduMKII_base::joy_y(){
    assert(_joy_y);
    return *_joy_y;
}

gpio_pin & boostxl_eduMKII_base::joy_button(){
    assert(_joy_button);
    return *_joy_button;
}

adc_channel & boostxl_eduMKII_base::mic(){
    assert(_mic);
    return *_mic;
}

adc_channel & boostxl_eduMKII_base::acc_x(){
    assert(_acc_x);
    return *_acc_x;
}

adc_channel & boostxl_eduMKII_base::acc_y(){
    assert(_acc_y);
    return *_acc_y;
}

adc_channel & boostxl_eduMKII_base::acc_z(){
    assert(_acc_z);
    return *_acc_z;
}
