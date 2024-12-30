/*
 * gpio_msp432.cpp
 *
 *  Created on: 29.02.2016
 *      Author: Andreas Terstegge
 */

#include "msp.h"
#include "gpio_msp432.h"
#include <cassert>

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
volatile uint8_t *port_base[10] = {
        &BITBAND_PERI(P1->IN, 0),
        &BITBAND_PERI(P2->IN, 0),
        &BITBAND_PERI(P3->IN, 0),
        &BITBAND_PERI(P4->IN, 0),
        &BITBAND_PERI(P5->IN, 0),
        &BITBAND_PERI(P6->IN, 0),
        &BITBAND_PERI(P7->IN, 0),
        &BITBAND_PERI(P8->IN, 0),
        &BITBAND_PERI(P9->IN, 0),
        &BITBAND_PERI(P10->IN, 0)
};

#define DIO_BIT(p, bit, off) (*((__IO uint8_t *) (port_base[p-1] + (bit<<2) + (off<<5))))

function<void()> gpio_msp432::_intHandler[6][8];
bool             gpio_msp432::_both[6][8] = {0};

void gpio_msp432::gpioMode(uint16_t mode) {
    setSEL(0);
    setMode(mode);
}

bool gpio_msp432::gpioRead() const {
    assert((_port > 0) && (_port < 11) && (_pin < 8));
    return DIO_BIT(_port, _pin, PORT_IN_OFS);
}

void gpio_msp432::gpioWrite(bool value) {
    assert((_port > 0) && (_port < 11) && (_pin < 8));
    if (_open_drain) {
        if (_pull_up) {
            if (value) {
                DIO_BIT(_port, _pin, PORT_DIR_OFS) = LOW;
                DIO_BIT(_port, _pin, PORT_OUT_OFS) = HIGH;
            } else {
                DIO_BIT(_port, _pin, PORT_OUT_OFS) = LOW;
                DIO_BIT(_port, _pin, PORT_DIR_OFS) = HIGH;
            }
        } else {
            // Open drain without pullup
            DIO_BIT(_port, _pin, PORT_DIR_OFS) = !value;
        }
    } else if (_open_source) {
        if (_pull_down) {
            if (value) {
                DIO_BIT(_port, _pin, PORT_OUT_OFS) = HIGH;
                DIO_BIT(_port, _pin, PORT_DIR_OFS) = HIGH;
            } else {
                DIO_BIT(_port, _pin, PORT_DIR_OFS) = LOW;
                DIO_BIT(_port, _pin, PORT_OUT_OFS) = LOW;
            }
        } else {
            // Open source without pull down
            DIO_BIT(_port, _pin, PORT_DIR_OFS) = value;
        }
    } else {
        // No open drain/source
        DIO_BIT(_port, _pin, PORT_OUT_OFS) = value;
    }
}

void gpio_msp432::gpioToggle() {
    assert((_port > 0) && (_port < 11) && (_pin < 8));
    gpioWrite(!DIO_BIT(_port, _pin, PORT_IN_OFS));
}

void gpio_msp432::gpioAttachIrq(gpio_mode_t mode,
                                function<void()> handler) {
    assert((_port > 0) && (_port < 11) && (_pin < 8));
    switch (mode) {
        case GPIO::RISING: {
            DIO_BIT(_port, _pin, PORT_IES_OFS) = 0;
            _both[_port - 1][_pin] = false;
            break;
        }
        case GPIO::FALLING: {
            DIO_BIT(_port, _pin, PORT_IES_OFS) = 1;
            _both[_port - 1][_pin] = false;
            break;
        }
        case GPIO::FALLING | GPIO::RISING: {
            DIO_BIT(_port, _pin, PORT_IES_OFS) = DIO_BIT(_port, _pin, PORT_IN_OFS);
            _both[_port - 1][_pin] = true;
            break;
        }
        default:
            assert(false);
    }
    // store handler addr
    _intHandler[_port - 1][_pin] = handler;

    // Reset all pending IRQs
    for (uint32_t i = 0; i < 8; ++i) {
        DIO_BIT(_port, i, PORT_IFG_OFS) = 0;
    }
    gpioEnableIrq();
}

void gpio_msp432::gpioDetachIrq() {
    assert((_port > 0) && (_port < 11) && (_pin < 8));
    gpioDisableIrq();
    _intHandler[_port - 1][_pin] = 0;
}

void gpio_msp432::gpioEnableIrq() {
    assert((_port > 0) && (_port < 11) && (_pin < 8));
    // Clear pending interrupts
    DIO_BIT(_port, _pin, PORT_IFG_OFS) = LOW;
    DIO_BIT(_port, _pin, PORT_IE_OFS) = HIGH;
    NVIC_EnableIRQ((IRQn_Type) (34 + _port));
}

void gpio_msp432::gpioDisableIrq() {
    assert((_port > 0) && (_port < 11) && (_pin < 8));
    DIO_BIT(_port, _pin, PORT_IE_OFS) = LOW;
}

void gpio_msp432::handleIrq(uint8_t port, uint8_t pin) {
    _intHandler[port - 1][pin]();
    if (_both[port - 1][pin]) {
        DIO_BIT(port, pin, PORT_IES_OFS) = DIO_BIT(port, pin, PORT_IN_OFS);
        // Make sure we don't accidentally trigger a irq!
        DIO_BIT(port, pin, PORT_IFG_OFS) = 0;
    }
}

void gpio_msp432::setSEL(uint8_t mode) const {
    assert((_port > 0) && (_port < 11) && (_pin < 8));
    DIO_BIT(_port, _pin, PORT_SEL0_OFS) = mode & 0x01;
    DIO_BIT(_port, _pin, PORT_SEL1_OFS) = (mode >> 1) & 0x01;
}

void gpio_msp432::setMode(uint16_t mode) {
    assert((_port > 0) && (_port < 11) && (_pin < 8));
    // Set mode to default state
    _open_drain = false;
    _open_source= false;
    _pull_up    = false;
    _pull_down  = false;
    DIO_BIT(_port, _pin, PORT_DIR_OFS) = LOW;
    DIO_BIT(_port, _pin, PORT_REN_OFS) = LOW;
    DIO_BIT(_port, _pin, PORT_OUT_OFS) = LOW;

    if (mode & GPIO::INPUT) {
        // Default is okay
    }
    if (mode & GPIO::OUTPUT) {
        DIO_BIT(_port, _pin, PORT_DIR_OFS) = HIGH;
    }
    if (mode & GPIO::OUTPUT_OPEN_DRAIN) {
        _open_drain = true;
    }
    if (mode & GPIO::OUTPUT_OPEN_SOURCE) {
        _open_source = true;
        DIO_BIT(_port, _pin, PORT_OUT_OFS) = HIGH;
    }
    if (mode & GPIO::PULLUP) {
        _pull_up = true;
        DIO_BIT(_port, _pin, PORT_REN_OFS) = HIGH;
        DIO_BIT(_port, _pin, PORT_OUT_OFS) = HIGH;
    }
    if (mode & GPIO::PULLDOWN) {
        _pull_down = true;
        DIO_BIT(_port, _pin, PORT_REN_OFS) = HIGH;
    }
    if (mode & (GPIO::SLOW | GPIO::FAST)) {
        assert(false);
    }
    if (mode & GPIO::INIT_HIGH) {
        gpioWrite(HIGH);
    }
    if (mode & GPIO::INIT_LOW) {
        gpioWrite(LOW);
    }
}

// Interrupt handler for P1...P6
////////////////////////////////
extern "C" {
void PORT1_IRQHandler(void) {
    uint32_t pin = P1->IV >> 1;
    if (pin--) {
        gpio_msp432::handleIrq(1, pin);
    }
}
void PORT2_IRQHandler(void) {
    uint32_t pin = P2->IV >> 1;
    if (pin--) {
        gpio_msp432::handleIrq(2, pin);
    }
}
void PORT3_IRQHandler(void) {
    uint32_t pin = P3->IV >> 1;
    if (pin--) {
        gpio_msp432::handleIrq(3, pin);
    }
}
void PORT4_IRQHandler(void) {
    uint32_t pin = P4->IV >> 1;
    if (pin--) {
        gpio_msp432::handleIrq(4, pin);
    }
}
void PORT5_IRQHandler(void) {
    uint32_t pin = P5->IV >> 1;
    if (pin--) {
        gpio_msp432::handleIrq(5, pin);
    }
}
void PORT6_IRQHandler(void) {
    uint32_t pin = P6->IV >> 1;
    if (pin--) {
        gpio_msp432::handleIrq(6, pin);
    }
}
} // extern "C"

