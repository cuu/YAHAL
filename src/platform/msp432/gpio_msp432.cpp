/*
 * gpio_msp432.cpp
 *
 *  Created on: 29.02.2016
 *      Author: Andreas Terstegge
 */

#include "msp.h"

#include "gpio_msp432.h"
#include "yahal_assert.h"

// GPIO register offsets
#define PORT_IN_OFS   0x00
#define PORT_OUT_OFS  0x02
#define PORT_DIR_OFS  0x04
#define PORT_REN_OFS  0x06
#define PORT_SEL0_OFS 0x0a
#define PORT_SEL1_OFS 0x0c
#define PORT_IES_OFS  0x18
#define PORT_IE_OFS   0x1a
#define PORT_IFG_OFS  0x1c

// Bit-Band base addresses of the 10 GPIO ports
volatile uint8_t * port_base[10] = {
    &BITBAND_PERI( P1->IN, 0),
    &BITBAND_PERI( P2->IN, 0),
    &BITBAND_PERI( P3->IN, 0),
    &BITBAND_PERI( P4->IN, 0),
    &BITBAND_PERI( P5->IN, 0),
    &BITBAND_PERI( P6->IN, 0),
    &BITBAND_PERI( P7->IN, 0),
    &BITBAND_PERI( P8->IN, 0),
    &BITBAND_PERI( P9->IN, 0),
    &BITBAND_PERI(P10->IN, 0)
};

#define DIO_BIT(p, bit, off) (*((__IO uint8_t *) (port_base[p-1] + (bit<<2) + (off<<5))))


gpio_msp432 gpio_msp432::inst;

void gpio_msp432::gpioMode (uint16_t gpio, uint16_t mode) {
	setSEL (gpio, 0);
	setMode(gpio, mode);
}

bool gpio_msp432::gpioRead (uint16_t gpio) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	yahal_assert((port > 0) && (port < 11) && (pin < 8));
	return DIO_BIT(port, pin, PORT_IN_OFS);
}

void gpio_msp432::gpioWrite(uint16_t gpio, bool value) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	yahal_assert((port > 0) && (port < 11) && (pin < 8));
	if (_open_drain[port-1] & (1 << gpio)) {
	    if (_pull_up[port-1] & (1<< gpio)) {
	        if (value) {
	            DIO_BIT(port, pin, PORT_DIR_OFS) = LOW;
                DIO_BIT(port, pin, PORT_OUT_OFS) = HIGH;
	        } else {
                DIO_BIT(port, pin, PORT_OUT_OFS) = LOW;
                DIO_BIT(port, pin, PORT_DIR_OFS) = HIGH;
	        }
	    } else {
	        // Open drain without pullup
	        DIO_BIT(port, pin, PORT_DIR_OFS) = !value;
	    }
	} else if (_open_source[port-1] & (1 << gpio)) {
        if (_pull_down[port-1] & (1<< gpio)) {
            if (value) {
                DIO_BIT(port, pin, PORT_OUT_OFS) = HIGH;
                DIO_BIT(port, pin, PORT_DIR_OFS) = HIGH;
            } else {
                DIO_BIT(port, pin, PORT_DIR_OFS) = LOW;
                DIO_BIT(port, pin, PORT_OUT_OFS) = LOW;
            }
        } else {
            // Open source without pull down
            DIO_BIT(port, pin, PORT_DIR_OFS) = value;
        }
    } else {
        // No open drain/source
        DIO_BIT(port, pin, PORT_OUT_OFS) = value;
    }
}

void gpio_msp432::gpioToggle(uint16_t gpio) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
    yahal_assert((port > 0) && (port < 11) && (pin < 8));
    gpioWrite(gpio, !DIO_BIT(port, pin, PORT_IN_OFS));
}

void gpio_msp432::gpioAttachIrq (gpio_pin_t  gpio,
                                 gpio_mode_t mode,
                                 void (*handler)(uint16_t, void *),
 							     void * arg) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	yahal_assert((port > 0) && (port < 7) && (pin < 8));
	switch(mode) {
	case GPIO::RISING: {
		DIO_BIT(port, pin, PORT_IES_OFS) = 0;
		_both[port-1][pin] = false;
		break;
	}
	case GPIO::FALLING: {
		DIO_BIT(port, pin, PORT_IES_OFS) = 1;
        _both[port-1][pin] = false;
		break;
	}
	case GPIO::FALLING | GPIO::RISING: {
	    DIO_BIT(port, pin, PORT_IES_OFS) = DIO_BIT(port, pin, PORT_IN_OFS);
        _both[port-1][pin] = true;
	    break;
	}
	default:
		yahal_assert(false);
	}
	// store handler addr
	_intHandler[port-1][pin] = handler;
	_arg[port-1][pin] = arg;

	// Reset all pending IRQs
	for (uint32_t i=0; i < 8; ++i) {
		DIO_BIT(port, i, PORT_IFG_OFS) = 0;
	}
	gpioEnableIrq(gpio);
}

void gpio_msp432::gpioDetachIrq(uint16_t gpio) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	yahal_assert((port > 0) && (port < 7) && (pin < 8));
	gpioDisableIrq(gpio);
	_intHandler[port-1][pin] = 0;
}

void gpio_msp432::gpioEnableIrq(uint16_t gpio) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	yahal_assert((port > 0) && (port < 7) && (pin < 8));
	DIO_BIT(port, pin, PORT_IE_OFS) = HIGH;
	NVIC_EnableIRQ((IRQn_Type)(34 + port));
}

void gpio_msp432::gpioDisableIrq(uint16_t gpio) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	yahal_assert((port > 0) && (port < 7) && (pin < 8));
	DIO_BIT(port, pin, PORT_IE_OFS) = LOW;
}

void gpio_msp432::handleIrq(uint8_t port, uint8_t pin) {
	_intHandler[port-1][pin](PORT_PIN(port, pin), _arg[port-1][pin]);
    if (_both[port-1][pin]) {
        DIO_BIT(port, pin, PORT_IES_OFS) = DIO_BIT(port, pin, PORT_IN_OFS);
        // Make sure we don't accidently trigger a irq!
        DIO_BIT(port, pin, PORT_IFG_OFS) = 0;
    }
}

void gpio_msp432::setSEL(uint16_t gpio, uint8_t mode) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
    yahal_assert((port > 0) && (port < 11) && (pin < 8));
    DIO_BIT(port, pin, PORT_SEL0_OFS) =  mode       & 0x01;
    DIO_BIT(port, pin, PORT_SEL1_OFS) = (mode >> 1) & 0x01;
}

void gpio_msp432::setMode(uint16_t gpio, uint16_t mode) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	yahal_assert((port > 0) && (port < 11) && (pin < 8));

	// Set mode to default state
	_open_drain [port-1] &= ~(1 << gpio);
    _open_source[port-1] &= ~(1 << gpio);
    _pull_up    [port-1] &= ~(1 << gpio);
    _pull_down  [port-1] &= ~(1 << gpio);
    DIO_BIT(port, pin, PORT_DIR_OFS) = LOW;
    DIO_BIT(port, pin, PORT_REN_OFS) = LOW;
    DIO_BIT(port, pin, PORT_OUT_OFS) = LOW;

	if (mode & GPIO::INPUT) {
	    // Default is okay
	}
    if (mode & GPIO::OUTPUT) {
        DIO_BIT(port, pin, PORT_DIR_OFS) = HIGH;
    }
    if (mode & GPIO::OUTPUT_OPEN_DRAIN) {
        _open_drain[port-1] |= (1 << gpio);
    }
    if (mode & GPIO::OUTPUT_OPEN_SOURCE) {
        _open_source[port-1] |= (1 << gpio);
        DIO_BIT(port, pin, PORT_OUT_OFS) = HIGH;
    }
    if (mode & GPIO::PULLUP) {
        _pull_up[port-1] |= (1 << gpio);
        DIO_BIT(port, pin, PORT_REN_OFS) = HIGH;
        DIO_BIT(port, pin, PORT_OUT_OFS) = HIGH;
    }
    if (mode & GPIO::PULLDOWN) {
        _pull_down[port-1] |= (1 << gpio);
        DIO_BIT(port, pin, PORT_REN_OFS) = HIGH;
    }
    if (mode & (GPIO::SLOW | GPIO::FAST)) {
        yahal_assert(false);
    }
    if (mode & GPIO::INIT_HIGH) {
        gpioWrite(gpio, HIGH);
    }
    if (mode & GPIO::INIT_LOW) {
        gpioWrite(gpio, LOW);
    }
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

