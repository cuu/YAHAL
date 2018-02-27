/*
 * spi_msp432.h
 *
 *  Created on: 14.06.2016
 *      Author: Andreas Terstegge
 */

#ifndef _I2C_MSP432_H_
#define _I2C_MSP432_H_

#include "msp.h"
#include "gpio_msp432.h"
#include "i2c_interface.h"

namespace I2C {
	const uint16_t OWN_7_BIT_ADDR    = 0x0000;
	const uint16_t OWN_10_BIT_ADDR   = EUSCI_B_CTLW0_A10;
	const uint16_t SLAVE_7_BIT_ADDR  = 0x0000;
	const uint16_t SLAVE_10_BIT_ADDR = EUSCI_B_CTLW0_SLA10;
	const uint16_t MASTER_MODE       = EUSCI_B_CTLW0_MST;
	const uint16_t SLAVE_MODE        = 0x0000;
	const uint16_t CLK_ACLK          = EUSCI_B_CTLW0_SSEL__ACLK;
	const uint16_t CLK_SMCLK         = EUSCI_B_CTLW0_SSEL__SMCLK;
}

class i2c_msp432 : public i2c_interface {

  public:

    i2c_msp432(EUSCI_B_Type *i2c,
              uint16_t mode = I2C::SLAVE_7_BIT_ADDR |
			                  I2C::MASTER_MODE |
							  I2C::CLK_SMCLK);

    virtual ~i2c_msp432();

    int16_t i2cRead (uint16_t addr, uint8_t *rxbuf,
                     uint8_t len, bool sendStop=true) override;
    int16_t i2cWrite(uint16_t addr, uint8_t *txbuf,
                     uint8_t len, bool sendStop=true) override;

    void setSpeed(uint32_t) override;

  private:

//    void send_ADR_ACK();
//    void send_ADR_NACK();
    void set_receiver();
    void set_transmitter();
//    void send_ACK();
//    void send_NACK();
    void send_START();
    void send_STOP();

	gpio_msp432_pin	_sda;
    gpio_msp432_pin	_scl;

	EUSCI_B_Type * _EUSCI;

};

#endif // _I2C_MSP432_H_
