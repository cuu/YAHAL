/*
 * cy8c95xxa_drv.h
 *
 *  Created on: 28.02.2016
 *      Author: Andreas Terstegge
 */

/*******************************************************
      CY8C9520A / CY8C9540A / CY8C9560A
      20-, 40- 60-Bit I/O Expander with EEPROM

 This is a driver for the CY8C95xxA GPIO expander, which
 has 3 to 8 8-bit ports (0...7), and is accessed via the I2C
 interface.

 Pin numbers are calculated with:
           pin =   pin_in_port(0...7) + port(0...7) * 8

 Note that not all pins on Port 1 and 2 are available
 (depens on the chip addressing)!

 02.05.2015  initial version

 (c) 2015 A. Terstegge

 ********************************************************/

#ifndef _CY8C95XXA_DRV_H_
#define _CY8C95XXA_DRV_H_

#include "gpio_interface.h"
#include "i2c_interface.h"

namespace CY8C95XXA {

enum pwm_clk  {
    CLK_32KHZ        = 0x00, CLK_24MHZ    = 0x01,
    CLK_1_5MHZ       = 0x02, CLK_93_75KHZ = 0x03,
    CLK_93_75KHZ_DIV = 0x04, CLK_PRE_PWM  = 0x05 };

enum gpio_cmd {
    CMD_STORE_CONFIG = 0x01,
    CMD_RESTORE_FD   = 0x02,
    CMD_RESET        = 0x07 };

enum gpio_en  {
    ENABLE_RO        = 0x04,
    ENABLE_EEPROM    = 0x02,
    ENABLE_WD_PIN    = 0x01 };

}

class cy8c95xxa_drv : public gpio_interface {

public:
    // User interface
    /////////////////
    cy8c95xxa_drv(i2c_interface & hw, uint8_t addr);

    /* Basic GPIO handling */
    void gpioMode  (uint16_t gpio, uint16_t mode) override;
    bool gpioRead  (uint16_t gpio) override;
    void gpioWrite (uint16_t gpio, bool value) override;
    void gpioToggle(uint16_t gpio) override;

    /* Interrupt handling */
    void gpioAttachIrq (uint16_t gpio,
                        uint16_t mode,
                        void (*)(gpio_pin_t, void *),
                        void * arg = nullptr) override;
    void gpioDetachIrq (uint16_t gpio) override;
    void gpioEnableIrq (uint16_t gpio) override;
    void gpioDisableIrq(uint16_t gpio) override;
    void handleInterrupt();

    // PWM stuff
    bool configPWM (uint8_t port,  uint8_t pin, CY8C95XXA::pwm_clk clk,
                    uint8_t period,uint8_t width);
    void setDivider(uint8_t div);
    void enablePWM (uint16_t gpio);
    void disablePWM(uint16_t gpio);

    // Config
    void sendCommand (CY8C95XXA::gpio_cmd cmd);
    void setEnableReg(CY8C95XXA::gpio_en  en);

    virtual ~cy8c95xxa_drv() { }

private:
    // Reference to HW interface
    i2c_interface & _i2c;
    // Storage for current output state
    uint8_t _output[8];
    // I2C addr
    uint8_t _i2c_addr;
    // mask for pwm channels
    uint8_t _pwm_mask;

    // interrupt handler functions
    void   (*intHandler[8][8])(gpio_pin_t, void *);
    uint16_t intMode[8][8];
    void *   intArg[8][8];

    // Register access
    //////////////////
    uint8_t readRegister (uint8_t reg);
    bool    writeRegister(uint8_t reg, uint8_t value,
                          uint8_t mask = 0xff);

};

#endif // _CY8C95XXA_DRV_H_

