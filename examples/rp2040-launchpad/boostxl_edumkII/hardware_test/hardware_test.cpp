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
// This program contains a full HW test for
// the Educational Boosterpack MK II. It is
// also a larger programming example how
// interrupt handlers and the multitasking
// kernel can be combined.
//

#include "HW.h"

// YAHAL includes
#include "uart_rp2040.h"
#include "posix_io.h"
#include "yahal_String.h"

#include "uGUI.h"
#include "uGUI_colors.h"
#include "font_6x10.h"
#include "task.h"
#include "task_monitor.h"

///////////////////////////////////////
// A Task to draw the microphone signal
///////////////////////////////////////
class task_mic : public task {
public:

    task_mic(uGUI & gui) : task("MIC task"), _gui(gui) {
        _x = 0;
        for (int i=0; i < 64; ++i) _y[i] = 32;
    }

    void run() override {
        while(true) {
            sleep_ms(1);
            uint16_t val = HW::inst()->mic.adcReadRaw();
            val >>= 6;
            _gui.DrawPixel(_x, _y[_x], C_BLACK);
            _gui.DrawPixel(_x, val,    mic_color);
            _y[_x] = val;
            _x++;
            _x %= 64;
        }
    }

    static UG_COLOR mic_color;

private:
    uint16_t    _x;
    uint16_t    _y[64];
    uGUI &      _gui;
};

UG_COLOR task_mic::mic_color = C_CYAN;

///////////////////////////////////////
// A Task to draw the Joystick position
///////////////////////////////////////
class task_joy : public task {
public:

    task_joy(uGUI & gui) : task("JOY task"), _gui(gui) {
        _x = 32;
        _y = 32;
    }

    void run() override {
        while(true) {
            uint16_t x = HW::inst()->joy_x.adcReadRaw();
            uint16_t y = HW::inst()->joy_y.adcReadRaw();
            // Set servo position
//            TA0CCR2  = 6550 - x;
            // Scale to 0..64 (from 12 to 6 bits) and limit
            x >>= 6;
            y >>= 6; y = 63 - y;
            if (x < 3)  x = 3;
            if (x > 60) x = 60;
            if (y < 3)  y = 3;
            if (y > 60) y = 60;
            // Erase old circle and draw new one
            if ((x == _x) && (y == _y)) {
                sleep_ms(10);
                continue;
            } else {
                _gui.PutString(71, 1, "Joystick", false);
                _gui.FillCircle(_x+64, _y, 2, C_BLACK);
                _gui.FillCircle( x+64,  y, 2, C_RED);
                _x = x;
                _y = y;
            }
        }
    }

private:
    uint16_t    _x;
    uint16_t    _y;
    uGUI &      _gui;
};

/////////////////////////////////////
// A Task to print some sensor values
/////////////////////////////////////
class task_sensor : public task {
public:

    task_sensor(uGUI & gui) : task("SENSOR task"), _gui(gui),
      _accel_x(0),_accel_y(0), _accel_z(0), _light(0), _temp(0) {
    }

    void run() override {
        uint16_t tmp = 0;
        String s;
        s.reserve(10);
        while(true) {
            // Show some measurements
            tmp = HW::inst()->accel_x.adcReadRaw();
            if (tmp != _accel_x) {
                _accel_x = tmp;
                s  = to_String(tmp-2048) + "  ";
                _gui.PutString(70, 70, s.c_str());
                sleep_ms(20);
            }
            tmp = HW::inst()->accel_y.adcReadRaw();
            if (tmp != _accel_y) {
                _accel_y = tmp;
                s  = to_String(tmp-2048) + "  ";
                _gui.PutString(70, 80, s.c_str());
                sleep_ms(20);
            }
            tmp = HW::inst()->accel_z.adcReadRaw();
            if (tmp != _accel_z) {
                _accel_z = tmp;
                s  = to_String(tmp-2048) + "  ";
                _gui.PutString(70, 90, s.c_str());
                sleep_ms(20);
            }
            tmp = HW::inst()->sen_light.get_light();
            if (tmp != _light) {
                _light = tmp;
                s  = to_String(tmp) + " lux  ";
                _gui.PutString(55, 105, s.c_str());
                sleep_ms(20);
            }

            uint8_t buf2[3];
            buf2[0] = 0x01; // Temp register
            HW::inst()->sen_i2c.i2cWrite(0x40,  buf2,   1); //, false);
            HW::inst()->sen_i2c.i2cRead (0x40,  buf2+1, 2);
            int16_t temp = (buf2[1] << 8) + buf2[2];
            temp /= 4;
            if (temp != _temp) {
                _temp = temp;
                s = to_String(temp/32) + "." + to_String(temp%32*3) + " °C";
                _gui.PutString(55,115, s.c_str());
                sleep_ms(20);
            }
            sleep_ms(100);
        }
    }

private:
    uGUI &      _gui;
    uint16_t    _accel_x;
    uint16_t    _accel_y;
    uint16_t    _accel_z;
    uint16_t    _light;
    int16_t     _temp;
};


int main(void)
{
    // Setup backchannel UART
    uart_rp2040 uart;
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    // Setup uGUI
    uGUI gui(HW::inst()->lcd);
    gui.FillScreen(C_BLACK);
    gui.FontSelect(&FONT_6X10);
    gui.FontSetHSpace(0);
    gui.SetForecolor(C_YELLOW);
    gui.SetBackcolor(C_BLACK);

    // Setup TA0.4 for speaker sound
    // and TA0.2 for servo output
//    TIMER_A0->EX0     = TAIDEX__2; // Divide by 2
//    TIMER_A0->CCR[0]  = 60000;
//    TIMER_A0->CCR[2]  = 4500;
//    TIMER_A0->CCTL[2] = 0xe0;
//    TIMER_A0->CCR[4]  = 30000;
//    TIMER_A0->CCTL[4] = 0xe0;
//    TIMER_A0->CTL     = 0x2d0;  // up-mode, divide by 8

    // Button S1 toggles the left LED on the Launchpad
    //////////////////////////////////////////////////
//    HW::inst()->sw1.gpioAttachIrq(GPIO::FALLING, []() {
//        HW::inst()->red.gpioToggle();
//    });

    // Button S2 toggles the RGB LED on the Launchpad
    /////////////////////////////////////////////////
//    HW::inst()->sw2.gpioAttachIrq(GPIO::FALLING, []() {
//        static int i = 0;
//        HW::inst()->rgb_red.gpioWrite(LOW);
//        HW::inst()->rgb_green.gpioWrite(LOW);
//        HW::inst()->rgb_blue.gpioWrite(LOW);
//        switch(i) {
//            case 0: { HW::inst()->rgb_red.gpioWrite(HIGH);   break; }
//            case 1: { HW::inst()->rgb_green.gpioWrite(HIGH); break; }
//            case 2: { HW::inst()->rgb_blue.gpioWrite(HIGH);  break; }
//            case 3: break;
//        }
//        i++;
//        i %= 4;
//    });

    // Button S1 on EDU MKII toggles the EDU RGB LED
    ////////////////////////////////////////////////
//    HW::inst()->edu_sw1.gpioAttachIrq(GPIO::FALLING, []() {
//        static int i = 0;
//        HW::inst()->edu_red.gpioWrite(LOW);
//        HW::inst()->edu_green.gpioWrite(LOW);
//        HW::inst()->edu_blue.gpioWrite(LOW);
//        switch(i) {
//            case 0: { HW::inst()->edu_red.gpioWrite(HIGH);   break; }
//            case 1: { HW::inst()->edu_green.gpioWrite(HIGH); break; }
//            case 2: { HW::inst()->edu_blue.gpioWrite(HIGH);  break; }
//        case 3: break;
//        }
//        i++;
//        i %= 4;
//    });

    // Button S2 on EDU MKII toggles speaker on/off
    ///////////////////////////////////////////////
//    HW::inst()->edu_sw2.gpioAttachIrq(GPIO::FALLING, []() {
//        static bool b = false;
//        b = !b;
//        HW::inst()->edu_speaker.setSEL(b);
//    });

    // Joystick button changes the color of the
    // microphone signal
    ///////////////////////////////////////////
    HW::inst()->edu_joy_sw.gpioAttachIrq(GPIO::FALLING, []() {
        static int i = 0;
        i++;
        i %= 3;
        switch(i) {
            case 0: { task_mic::mic_color = C_RED;    break; }
            case 1: { task_mic::mic_color = C_YELLOW; break; }
            case 2: { task_mic::mic_color = C_CYAN;   break; }
        }
    });

    // Draw static elements on the display
    gui.DrawLine( 0, 64, 127, 64, C_GREEN);
    gui.DrawLine(64,  0,  64, 64, C_GREEN);
    gui.PutString(5,    1, "Mic",      false);
    gui.PutString(71,   1, "Joystick", false);
    gui.PutString(12,  70, "Accel X:", false);
    gui.PutString(12,  80, "Accel Y:", false);
    gui.PutString(12,  90, "Accel Z:", false);
    gui.PutString(12, 105, "Light:",   false);
    gui.PutString(12, 115, "Temp :",   false);

    task_monitor monitor;
    monitor.start();

    task_mic mic_task(gui);
    mic_task.start();

    task_joy joy_task(gui);
    joy_task.start();

    task_sensor sensor_task(gui);
    sensor_task.start();

    printf("Hallo!\n");

    // Start the multitasking kernel.
    task::start_scheduler();
}
