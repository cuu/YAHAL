/*
 * gpio_rp2040.cpp
 *
 *  Created on: 17.10.2022
 *      Author: Andreas Terstegge
 */

#include "gpio_rp2040.h"

#include "RP2040.h"
#include <cassert>

using namespace _SIO_;
using namespace _IO_BANK0_;
using namespace _PADS_BANK0_;

function<void()> gpio_rp2040::_intHandler[30] {nullptr};
uint8_t          gpio_rp2040::_irqConfig [30] {0};

gpio_rp2040::gpio_rp2040(gpio_pin_t gpio)
    : _gpio(gpio) {
    _mask = 1 << gpio;
}

void gpio_rp2040::setGpio(gpio_pin_t gpio) {
    assert(gpio < 30);
    _gpio = gpio;
    _mask = 1 << (gpio % 32);
}

gpio_pin_t gpio_rp2040::getGpio() const {
    return _gpio;
}

void
gpio_rp2040::gpioMode (uint16_t mode) {
    assert(_gpio < 30);
    setSEL  (GPIO_CTRL_FUNCSEL__sio);
    setMode (mode);
}

bool
gpio_rp2040::gpioRead () const {
    assert(_gpio < 30);
    return SIO.GPIO_IN & _mask;
}

void
gpio_rp2040::gpioWrite (bool value) {
    assert(_gpio < 30);
    if (_open_drain) {
        if (value) SIO.GPIO_OE_CLR = _mask;
        else       SIO.GPIO_OE_SET = _mask;
    }
    else if (_open_source) {
        if (value) SIO.GPIO_OE_SET = _mask;
        else       SIO.GPIO_OE_CLR = _mask;
    }
    else {
        // No open drain/source
        if (value) SIO.GPIO_OUT_SET = _mask;
        else       SIO.GPIO_OUT_CLR = _mask;
    }
}

void
gpio_rp2040::gpioToggle () {
    assert(_gpio < 30);
    if (_open_drain || _open_source)
          SIO.GPIO_OE_XOR  = _mask;
    else  SIO.GPIO_OUT_XOR = _mask;
}

void
gpio_rp2040::gpioAttachIrq (gpio_mode_t mode,
                            function<void()> handler) {
    assert(_gpio < 30);
    _irqConfig[_gpio] = 0;
    // configure irqs according to mode
    if (mode & GPIO::LEVEL_LOW) {
        _irqConfig[_gpio] |= 0x1;
    }
    if (mode & GPIO::LEVEL_HIGH) {
        _irqConfig[_gpio] |= 0x2;
    }
    if (mode & GPIO::FALLING) {
        _irqConfig[_gpio] |= 0x4;
    }
    if (mode & GPIO::RISING) {
        _irqConfig[_gpio] |= 0x8;
    }
    // store handler addr
    _intHandler[_gpio] = handler;
    // Finally enable irqs
    gpioEnableIrq();
}

void
gpio_rp2040::gpioDetachIrq () {
    assert(_gpio < 30);
    // Disable irqs
    gpioDisableIrq();
    // unregister handler
    _intHandler[_gpio] = 0;
}

void
gpio_rp2040::gpioEnableIrq () {
    assert(_gpio < 30);
    PROC0_INTE0_t *INTE_SET = &IO_BANK0_SET.PROC0_INTE0 + (_gpio >> 3);
    INTR0_t       *INTR     = &IO_BANK0.INTR0           + (_gpio >> 3);
    int mask_shift = (_gpio & 0x7) * 4;
    // Switch off NVIC irq so we get no
    // handler calls during configuration
    NVIC_DisableIRQ(IO_IRQ_BANK0_IRQn);
    // Enable irqs
    *INTE_SET = _irqConfig[_gpio] << mask_shift;
    // Clear pending interrupts
    *INTR = (0xf << mask_shift);
    // Enable NVIC irq
    NVIC_ClearPendingIRQ(IO_IRQ_BANK0_IRQn);
    NVIC_EnableIRQ      (IO_IRQ_BANK0_IRQn);
}

void
gpio_rp2040::gpioDisableIrq () {
    assert(_gpio < 30);
    PROC0_INTE0_t *INTE_CLR = &IO_BANK0_CLR.PROC0_INTE0 + (_gpio >> 3);
    INTR0_t       *INTR     = &IO_BANK0.INTR0           + (_gpio >> 3);
    int mask_shift = (_gpio & 0x7) * 4;
    // Clear pending interrupts
    *INTR = (0xf << mask_shift);
    // Disable irqs
    *INTE_CLR = (0xf << mask_shift);
}

void gpio_rp2040::setSEL (uint8_t sel) {
    assert(_gpio < 30);
    GPIO_CTRL_t *io_ctrl = &IO_BANK0.GPIO0_CTRL + (_gpio << 1);
    // Set the pad function and reset all other bits
    io_ctrl->FUNCSEL = sel;
    io_ctrl->OUTOVER = 0;
    io_ctrl->OEOVER  = 0;
    io_ctrl->INOVER  = 0;
    io_ctrl->IRQOVER = 0;
}

void gpio_rp2040::setMode (uint16_t mode) {
    assert(_gpio < 30);
    GPIO_t *pad_ctrl = &PADS_BANK0.GPIO[_gpio];

    // Reset open drain/source
    _open_drain  = false;
    _open_source = false;
    // Reset SIO configuration
    SIO.GPIO_OUT_CLR    = _mask;
    SIO.GPIO_OE_CLR     = _mask;
    // Reset pad configuration
    pad_ctrl->OD        = 0;
    pad_ctrl->IE        = 1;
    pad_ctrl->DRIVE     = GPIO_DRIVE__2mA;
    pad_ctrl->PUE       = 0;
    pad_ctrl->PDE       = 0;
    pad_ctrl->SCHMITT   = 1;
    pad_ctrl->SLEWFAST  = 0;

    if (mode & GPIO::INPUT) {
        // Default is okay
    }
    if (mode & GPIO::INPUT_INVERT) {
        // Default is NEARLY okay :)
        GPIO_CTRL_t *io_ctrl = &IO_BANK0.GPIO0_CTRL + (_gpio << 1);
        io_ctrl->INOVER = GPIO_CTRL_INOVER__INVERT;
    }
    if (mode & GPIO::OUTPUT) {
        SIO.GPIO_OE_SET = _mask;
    }
    if (mode & GPIO::OUTPUT_OPEN_DRAIN) {
        _open_drain = true;
        SIO.GPIO_OE_SET = _mask;
    }
    if (mode & GPIO::OUTPUT_OPEN_SOURCE) {
        _open_source = true;
        SIO.GPIO_OUT_SET = _mask;
    }
    if (mode & GPIO::PULLUP) {
        pad_ctrl->PUE = 1;
    }
    if (mode & GPIO::PULLDOWN) {
        pad_ctrl->PDE = 1;
    }
    if (mode & GPIO::FAST) {
        pad_ctrl->SLEWFAST = 1;
    }
    if ((mode & GPIO::DRIVE_4mA) || (mode & GPIO::DRIVE_8mA)) {
        pad_ctrl->DRIVE = (mode >> 10) & 0x3;
    }
    if (mode & GPIO::INIT_HIGH) {
        gpioWrite (HIGH);
    }
    if (mode & GPIO::INIT_LOW) {
        gpioWrite (LOW);
    }
}

// Interrupt handler
////////////////////
extern "C" {

void IO_IRQ_BANK0_Handler(void) {
    PROC0_INTS0_t *INTS = &IO_BANK0.PROC0_INTS0;
    INTR0_t       *INTR = &IO_BANK0.INTR0;
    for (int i=0; i < 4; ++i, INTS++, INTR++) {
        while (uint8_t pos = __builtin_ffs(*INTS)) {
            // Clear irq
            *INTR = (1 << --pos);
            // Call irq handler
            uint16_t gpio = (pos >> 2) + (i << 3);
            gpio_rp2040::_intHandler[gpio]();
        }
    }
}

} // extern "C"
