
#ifndef _MSP432_LAUNCHPAD_BOOSTXL_EDUMKII_H_
#define _MSP432_LAUNCHPAD_BOOSTXL_EDUMKII_H_

// Big Buttons
#define BUTTON1         PORT_PIN(5,1)
#define BUTTON2         PORT_PIN(3,5)
// 3 color LED
#define RGB_LED_RED     PORT_PIN(2,6)
#define RGB_LED_GREEN   PORT_PIN(2,4)
#define RGB_LED_BLUE    PORT_PIN(5,6)
// Buzzer
#define BUZZER          PORT_PIN(2,7)
// Gator holes
#define GATOR           PORT_PIN(2,3)
// Servo PWM signal
#define SERVO           PORT_PIN(2,5)
// LCD
#define LCD_MISO
#define LCD_MOSI
#define LCD_SCLK
#define LCD_CS          PORT_PIN(5,0)
#define LCD_RST         PORT_PIN(5,7)
#define LCD_DC          PORT_PIN(3,7)
// I2C sensors
#define SENSOR_SDA
#define SENSOR_SCL
#define OPT3001_INT     PORT_PIN(4,6)
#define TMP006_INT      PORT_PIN(3,6)
// Joystick
#define JOY_X           15
#define JOY_Y            9
#define JOY_BUTTON      PORT_PIN(4,1)
// Microphone
#define MIC             10
// Accelerometer
#define ACC_X           14
#define ACC_Y           13
#define ACC_Z           11

#include "boostxl_eduMKII_base.h"

struct boostxl_eduMKII : public boostxl_eduMKII_base {
    boostxl_eduMKII();
    void inject();
};

#endif // _MSP432_LAUNCHPAD_BOOSTXL_EDUMKII_H_
