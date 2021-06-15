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

#include "gpio_msp432.h"
#include "spi_msp432.h"
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
#include "adc14_msp432.h"
#include "yahal_String.h"

#include <cstdlib>

class Touch {
public:
    Touch(lcd_interface & lcd) : _lcd(lcd) {
        _XP.setGpio(PORT_PIN(4, 0));
        _YP.setGpio(PORT_PIN(6, 1));
        _XN.setGpio(PORT_PIN(3, 7));
        _YN.setGpio(PORT_PIN(3, 6));

        _touchX.setChannel(13);
        _touchX.adcMode(ADC::ADC_10_BIT);
        _touchY.setChannel(14);
        _touchY.adcMode(ADC::ADC_10_BIT);
    }

    bool pressed() {
        static bool last=false;

        _XN.gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
        _YN.gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);

        _XP.setSEL(0);
        _XP.gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);
        _YP.setSEL(3);
        int x = _touchY.adcReadRaw();

        _YP.setSEL(0);
        _YP.gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);
        _XP.setSEL(3);
        int y = _touchX.adcReadRaw();
        _pressed = (x > 10) || (y > 10);

        if (_pressed != last) {
            for (int i=0; i < 100000; ++i) ;
            last = _pressed;
        }
        return _pressed;
    }

    void getXY_raw(uint16_t & x, uint16_t & y ) {
        _XN.gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
        _XP.setSEL(0);
        _XP.gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);
        _YN.gpioMode(GPIO::INPUT);
        _YP.setSEL(3);
        x = _touchY.adcReadRaw();

        _YN.gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
        _YP.setSEL(0);
        _YP.gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);
        _XN.gpioMode(GPIO::INPUT);
        _XP.setSEL(3);
        y = _touchX.adcReadRaw();
    }

    void transform(uint16_t & x, uint16_t & y) {
        x = ((int)x - (int)_xs) * ((int)_lcd.getSizeX()-10) / ((int)_xe - (int)_xs) + 5;
        y = ((int)y - (int)_ys) * ((int)_lcd.getSizeY()-10) / ((int)_ye - (int)_ys) + 5;
        if (x > 319) x = 319;
        if (y > 239) y = 239;
    }

    void calibrate() {
        uint16_t x,y;
        // Clear screen
        _lcd.fillArea(0, 0, _lcd.getSizeX()-1, _lcd.getSizeY()-1, C_BLACK);

        //
        _lcd.fillArea(0, 0, 19, 19, C_RED);
        while(!pressed()) ;
        for (int i=0; i < 10000; ++i) ;
        getXY_raw(x, y);
        while(pressed()) ;
        _xs = x;
        _ys = y;

        //
        _lcd.fillArea(_lcd.getSizeX()-20, 0,
                      _lcd.getSizeX()- 1, 19, C_RED);
        while(!pressed()) ;
        for (int i=0; i < 10000; ++i) ;
        getXY_raw(x, y);
        while( pressed()) ;
        _xe = x;
        _ys = (_ys + y) / 2;

        //
        _lcd.fillArea( 0, _lcd.getSizeY()-20,
                      19, _lcd.getSizeY()- 1, C_RED);
        while(!pressed()) ;
        for (int i=0; i < 10000; ++i) ;
        getXY_raw(x, y);
        while( pressed()) ;
        _xs = (_xs + x) / 2;
        _ye = y;

        //
        _lcd.fillArea(_lcd.getSizeX()-20, _lcd.getSizeY()-20,
                      _lcd.getSizeX()- 1, _lcd.getSizeY()- 1, C_RED);
        while(!pressed()) ;
        for (int i=0; i < 10000; ++i) ;
        getXY_raw(x, y);
        while( pressed()) ;
        _xe = (_xe + x) / 2;
        _ye = (_ye + y) / 2;
    }

private:
    // The LCD we sit on
    lcd_interface   &       _lcd;
    // touch enable gpios
    gpio_msp432_pin         _XP, _XN;
    gpio_msp432_pin         _YP, _YN;
    // ADC channels
    adc14_msp432_channel    _touchX;
    adc14_msp432_channel    _touchY;

    uint16_t                _xs, _xe, _ys, _ye;
    bool _pressed;
};



int main(void)
{
    // Switch on background LCD
    gpio_msp432_pin lcd_led(PORT_PIN(2, 7));
    lcd_led.gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);

    // Setup SPI interface. Use EUSCI_B0 in SPI mode 3.
    gpio_msp432_pin lcd_cs (PORT_PIN(5, 0));
    uint16_t spi_mode = SPI::CPOL_1    | SPI::CPHA_1 |
                        SPI::MSB_FIRST | SPI::_8_BIT | SPI::CLK_SMCLK;
    spi_msp432  spi(EUSCI_B0_SPI, lcd_cs, SPI::MASTER, spi_mode );
    spi.setSpeed(24000000);

    // Setup LCD driver
    gpio_msp432_pin lcd_rst(PORT_PIN(3, 5));
    gpio_msp432_pin lcd_dc (PORT_PIN(4, 6));
    ssd2119_drv lcd(spi, lcd_rst, lcd_dc, ssd2119_drv::Kentec_K350QVG);

    // Touch interface
    Touch touch(lcd);

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
    for (uint16_t x=64; x < 120; x++) {
        for (uint16_t y=80; y < 120; y++) {
            gui.DrawPixel(x, y, rand() % 0x1000000);
        }
    }

    touch.calibrate();

    gui.SetForecolor(C_GREEN);
    gui.FontSelect(&FONT_6X10);
    uint16_t x=0, y=0;
    while(1) {

        bool p = touch.pressed();
//        gui.FillCircle(160, 120, 10, p ? C_RED : C_GREEN);
        if (p) {
            touch.getXY_raw(x, y);
            touch.transform(x, y);
            gui.FillCircle(x, y, 2, C_ORANGE);

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
