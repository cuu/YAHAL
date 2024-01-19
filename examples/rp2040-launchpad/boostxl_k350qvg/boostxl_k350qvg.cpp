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
// A simple example for displaying text, lines and
// circles on the LCD using the uGUI library.
// See the doc folder in YAHAL/src/uGUI for more
// information on the uGUI API.

#include "gpio_rp2040.h"
#include "spi_rp2040.h"
#include "ssd2119_drv.h"
#include "uGUI.h"
#include "uGUI_colors.h"
#include "font_4x6.h"
#include "font_5x8.h"
#include "font_5x12.h"
#include "font_6x8.h"
#include "font_6x10.h"
#include "font_7x12.h"
#include "font_8x12.h"
#include "adc_rp2040.h"
#include "yahal_String.h"
#include "task.h"
#include <cstdlib>

#include <cstdio>
#include "uart_rp2040.h"
#include "posix_io.h"

//using namespace uGUI;

class Touch {
public:
    Touch(lcd_interface & lcd)
    : _lcd(lcd), _XN(2), _YN(3), _XP(27), _YP(26) {
    }

    bool pressed() {
        uint16_t x, y;
        this->getXY_raw(x,y);
        return x>400 && y>400;
    }

    void getXY_raw(uint16_t & x, uint16_t & y ) {
        _XN.gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
        _XP.gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);
        _YN.gpioMode(GPIO::INPUT);
        _YP.gpioMode(GPIO::INPUT | GPIO::PULLDOWN);
        task::sleep(10);
        x = adc_rp2040::inst.adcReadRaw(0);
        _YN.gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
        _YP.gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);
        _XN.gpioMode(GPIO::INPUT);
        _XP.gpioMode(GPIO::INPUT | GPIO::PULLDOWN);
        task::sleep(10);
        y = adc_rp2040::inst.adcReadRaw(2);
    }

    bool transform(uint16_t & x, uint16_t & y) {
        x = ((int)x - (int)_xs) * ((int)_lcd.getSizeX()-10) / ((int)_xe - (int)_xs) + 5;
        y = ((int)y - (int)_ys) * ((int)_lcd.getSizeY()-10) / ((int)_ye - (int)_ys) + 5;
        if (x > 319) return false;
        if (y > 239) return false;
        return true;
    }

    void calibrate() {
        uint16_t x,y;
        // Clear screen
        _lcd.fillArea(0, 0, _lcd.getSizeX()-1, _lcd.getSizeY()-1, C_BLACK);

        //
        _lcd.fillArea(0, 0, 19, 19, C_RED);
        while(!pressed()) ;
        task::sleep(10);
        getXY_raw(x, y);
        while(pressed());
        _xs = x;
        _ys = y;

        //
        _lcd.fillArea(_lcd.getSizeX()-20, 0,
                      _lcd.getSizeX()- 1, 19, C_RED);
        while(!pressed()) ;
        task::sleep(10);
        getXY_raw(x, y);
        while( pressed()) ;
        _xe = x;
        _ys = (_ys + y) / 2;

        //
        _lcd.fillArea( 0, _lcd.getSizeY()-20,
                      19, _lcd.getSizeY()- 1, C_RED);
        while(!pressed()) ;
        task::sleep(10);
        getXY_raw(x, y);
        while( pressed()) ;
        _xs = (_xs + x) / 2;
        _ye = y;

        //
        _lcd.fillArea(_lcd.getSizeX()-20, _lcd.getSizeY()-20,
                      _lcd.getSizeX()- 1, _lcd.getSizeY()- 1, C_RED);
        while(!pressed()) ;
        task::sleep(10);
        getXY_raw(x, y);
        while( pressed()) ;
        _xe = (_xe + x) / 2;
        _ye = (_ye + y) / 2;
    }

private:
    // The LCD we sit on
    lcd_interface   &   _lcd;
    // touch enable gpios
    gpio_rp2040_pin     _XN;
    gpio_rp2040_pin     _YN;
    gpio_rp2040_pin     _XP;
    gpio_rp2040_pin     _YP;

    uint16_t            _xs, _xe, _ys, _ye;
    bool _pressed;
};



int main(void)
{
    uart_rp2040 uart; // default is backchannel UART!

    posix_io::inst.register_stdin ( uart );
    posix_io::inst.register_stdout( uart );
    posix_io::inst.register_stderr( uart );

    // Switch on background LCD
    gpio_rp2040_pin lcd_led(14);
    lcd_led.gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);

    // Setup SPI interface in SPI mode 3.
    gpio_rp2040_pin lcd_cs (5);
    uint16_t spi_mode = SPI::CPOL_1 | SPI::CPHA_1 | SPI::_8_BIT;
    spi_rp2040  spi(0, 4, 7, 22, lcd_cs, SPI::MASTER, spi_mode );
    spi.setSpeed(24000000);

    // Setup LCD driver
    gpio_rp2040_pin lcd_rst(17);
    gpio_rp2040_pin lcd_dc (23);
    ssd2119_drv lcd(spi, lcd_rst, lcd_dc, ssd2119_drv::Kentec_K350QVG);

    // Clear screen
    lcd.clearScreen(C_BLACK);

    // Setup uGUI
    uGUI gui(lcd);

    gui.SetForecolor(C_YELLOW);
    gui.FontSelect(&FONT_4X6);
    gui.PutString(4, 3, "Hallo MATSE", false);

    gui.SetForecolor(C_GREEN);
    gui.FontSelect(&FONT_5X8);
    gui.PutString(4, 9, "Hallo MATSE", false);

    gui.SetForecolor(C_CYAN);
    gui.FontSelect(&FONT_5X12);
    gui.PutString(4, 18, "Hallo MATSE", false);

    gui.SetForecolor(C_RED);
    gui.FontSelect(&FONT_6X8);
    gui.PutString(4, 31, "Hallo MATSE");

    gui.SetForecolor(C_WHITE);
    gui.FontSelect(&FONT_6X10);
    gui.PutString(4, 40, "Hallo MATSE");

    gui.SetForecolor(C_MAGENTA);
    gui.FontSelect(&FONT_7X12);
    gui.PutString(4, 51, "Hallo MATSE");

    gui.SetForecolor(C_ORANGE);
    gui.FontSelect(&FONT_8X12);
    gui.PutString(4, 64, "Hallo MATSE");

    // Draw some lines and circles
    gui.DrawCircle(30, 96, 15, C_YELLOW);
    gui.FillCircle(30, 96, 13, C_RED);

    gui.DrawLine(0,     0, 127,   0, C_YELLOW);
    gui.DrawLine(127,   0, 127, 127, C_YELLOW);
    gui.DrawLine(127, 127,   0, 127, C_YELLOW);
    gui.DrawLine(0,   127,   0,   0, C_YELLOW);

    // Draw some random-colored pixels
    for (uint16_t x=128; x < 319; x++) {
        for (uint16_t y=0; y < 239; y++) {
            gui.DrawPixel(x, y, rand() % 0x1000000);
        }
    }

    // Touch interface
    Touch touch(lcd);
    gpio_rp2040::inst.gpioMode(18, GPIO::OUTPUT | GPIO::INIT_LOW);

    touch.calibrate();

//    uint16_t x, y;
//    while (1) {
//        touch.getXY_raw(x,y);
//        printf("%d %d %d\n", x, y, touch.pressed());
//        //task::sleep(100);
//    }

    gui.SetForecolor(C_GREEN);
    gui.FontSelect(&FONT_6X10);
    uint16_t x=0, y=0;
    while(1) {

        bool p = touch.pressed();
//        gui.FillCircle(160, 120, 10, p ? C_RED : C_GREEN);
        if (p) {
            touch.getXY_raw(x, y);
            if (touch.transform(x, y)) {
                if (x < 20 && y < 29) {
                    lcd.clearScreen(C_BLACK);
                } else {
                    gui.FillCircle(x, y, 2, C_RED);
                }
            }

//            gui.DrawLine(xl, 0,   xl, 239, C_BLACK);
//            gui.DrawLine(0,  yl, 319,  yl, C_BLACK);
//            xl = x;
//            yl = y;
//            gui.DrawLine(xl, 0,   xl, 239, C_WHITE);
//            gui.DrawLine(0,  yl, 319,  yl, C_WHITE);


//            for (int i=0; i < 100000; ++i) ;
        }

//        String xs = to_String(x) + "    ";
//        String ys = to_String(y) + "    ";
//        gui.PutString(200,  9, xs.c_str());
//        gui.PutString(200, 29, ys.c_str());
//
//        for (int i=0; i < 10000; ++i) ;
    }


//    for(int i=0; i < 100000; ++i) {
//        uint32_t c = rand() % 0x1000000;
//        uint16_t x1 = rand() % lcd.getSizeX();
//        uint16_t y1 = rand() % lcd.getSizeY();
//        uint16_t x2 = rand() % lcd.getSizeX();
//        uint16_t y2 = rand() % lcd.getSizeY();
//        gui.FillFrame(x1, y1, x2, y2, c);
//    }

}
