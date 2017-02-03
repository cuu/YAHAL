/*
 * gpio_msp432.cpp
 *
 *  Created on: 29.02.2016
 *      Author: Andreas Terstegge
 */

#include "msp.h"

#include "gpio_msp432.h"
#include "assert.h"

static const uint32_t IN_OFS   = 0x00;
static const uint32_t OUT_OFS  = 0x02;
static const uint32_t DIR_OFS  = 0x04;
static const uint32_t REN_OFS  = 0x06;
static const uint32_t SEL0_OFS = 0x0a;
static const uint32_t SEL1_OFS = 0x0c;
static const uint32_t IES_OFS  = 0x18;
static const uint32_t IE_OFS   = 0x1a;
static const uint32_t IFG_OFS  = 0x1c;

gpio_msp432 gpio_msp432::inst;

#define DIO_BIT(p, bit, off) (*((__IO uint8_t *) (_port_base[p-1] + (bit<<2) + (off<<5))))

gpio_msp432::gpio_msp432() {
	for (uint32_t i=0; i < 10; i++) {
		_port_base[i]  = (volatile int8_t *)((DIO_BASE-PERIPH_BASE) << 5);
		_port_base[i] += ((i>>1) * 0x20) << 5;
		_port_base[i] += ((i & 0x1))     << 5;
		_port_base[i] += BITBAND_PERI_BASE;
	}
}

void gpio_msp432::gpioMode (uint16_t gpio, uint16_t mode) {
	setSEL (gpio, 0);
	setMode(gpio, mode);
}

bool gpio_msp432::gpioRead (uint16_t gpio) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	assert((port > 0) && (port < 11) && (pin < 8));
	return DIO_BIT(port, pin, IN_OFS);
}

void gpio_msp432::gpioWrite(uint16_t gpio, bool value) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	assert((port > 0) && (port < 11) && (pin < 8));
	DIO_BIT(port, pin, OUT_OFS) = value;
}

void gpio_msp432::gpioAttachIrq (uint16_t gpio,
								 void (*handler)(uint16_t gpio),
 							     uint16_t mode) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	assert((port > 0) && (port < 7) && (pin < 8));
	switch(mode) {
	case GPIO::RISING: {
		DIO_BIT(port, pin, IES_OFS) = 0;
		break;
	}
	case GPIO::FALLING: {
		DIO_BIT(port, pin, IES_OFS) = 1;
		break;
	}
	default:
		assert(false);
	}
	// store handler addr
	_intHandler[port-1][pin] = handler;
	// Reset all pending IRQs
	for (uint32_t i=0; i < 8; ++i) {
		DIO_BIT(port, i, IFG_OFS) = 0;
	}
	gpioEnableIrq(gpio);
}

void gpio_msp432::gpioDetachIrq(uint16_t gpio) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	assert((port > 0) && (port < 7) && (pin < 8));
	gpioDisableIrq(gpio);
	_intHandler[port-1][pin] = 0;
}

void gpio_msp432::gpioEnableIrq(uint16_t gpio) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	assert((port > 0) && (port < 7) && (pin < 8));
	DIO_BIT(port, pin, IE_OFS) = HIGH;
	NVIC_EnableIRQ((IRQn_Type)(34 + port));
}

void gpio_msp432::gpioDisableIrq(uint16_t gpio) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	assert((port > 0) && (port < 7) && (pin < 8));
	DIO_BIT(port, pin, IE_OFS) = LOW;
}

void gpio_msp432::handleIrq(uint8_t port, uint8_t pin) {
	_intHandler[port-1][pin](PORT_PIN(port, pin));
}

void gpio_msp432::setSEL(uint16_t gpio, uint8_t mode) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	assert((port > 0) && (port < 11) && (pin < 8));
	DIO_BIT(port, pin, SEL0_OFS) =  mode       & 0x01;
	DIO_BIT(port, pin, SEL1_OFS) = (mode >> 1) & 0x01;
}

void gpio_msp432::setMode(uint16_t gpio, uint16_t mode) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	assert((port > 0) && (port < 11) && (pin < 8));
	switch (mode & ~GPIO::INIT_HIGH & ~GPIO::INIT_LOW) {
		case GPIO::INPUT: {
			DIO_BIT(port, pin, DIR_OFS) = LOW;
			DIO_BIT(port, pin, REN_OFS) = LOW;
			break;
		}
		case GPIO::INPUT | GPIO::PULLUP: {
			DIO_BIT(port, pin, DIR_OFS) = LOW;
			DIO_BIT(port, pin, REN_OFS) = HIGH;
			DIO_BIT(port, pin, OUT_OFS) = HIGH;
			break;
		}
		case GPIO::INPUT | GPIO::PULLDOWN: {
			DIO_BIT(port, pin, DIR_OFS) = LOW;
			DIO_BIT(port, pin, REN_OFS) = HIGH;
			DIO_BIT(port, pin, OUT_OFS) = LOW;
			break;
		}
		case GPIO::OUTPUT: {
			DIO_BIT(port, pin, DIR_OFS) = HIGH;
			break;
		}
		default: {
			assert(false);
		}
	}
	if (mode & GPIO::INIT_HIGH)
		DIO_BIT(port, pin, OUT_OFS) = HIGH;
	if (mode & GPIO::INIT_LOW)
		DIO_BIT(port, pin, OUT_OFS) = LOW;
}

// Interrupt handler for P1...P6
////////////////////////////////

extern "C" {
void PORT1_IRQHandler(void) {
	uint32_t pin = P1->IV >> 1;
	if (pin--) {
		gpio_msp432::inst.handleIrq(1,pin);
	}
}
void PORT2_IRQHandler(void) {
	uint32_t pin = P2->IV >> 1;
	if (pin--) {
		gpio_msp432::inst.handleIrq(2,pin);
	}
}
void PORT3_IRQHandler(void) {
	uint32_t pin = P3->IV >> 1;
	if (pin--) {
		gpio_msp432::inst.handleIrq(3,pin);
	}
}
void PORT4_IRQHandler(void) {
	uint32_t pin = P4->IV >> 1;
	if (pin--) {
		gpio_msp432::inst.handleIrq(4,pin);
	}
}
void PORT5_IRQHandler(void) {
	uint32_t pin = P5->IV >> 1;
	if (pin--) {
		gpio_msp432::inst.handleIrq(5,pin);
	}
}
void PORT6_IRQHandler(void) {
	uint32_t pin = P6->IV >> 1;
	if (pin--) {
		gpio_msp432::inst.handleIrq(6,pin);
	}
}
} // extern "C"

