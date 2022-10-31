/*
 * gpio_rp2040.cpp
 *
 *  Created on: 17.10.2022
 *      Author: Andreas Terstegge
 */

#include "gpio_rp2040.h"

#include "RP2040.h"
#include "yahal_assert.h"

using namespace _SIO_;
using namespace _IO_BANK0_;
using namespace _PADS_BANK0_;

gpio_rp2040 gpio_rp2040::inst;

void
gpio_rp2040::gpioMode (uint16_t gpio, uint16_t mode) {
    yahal_assert(gpio < 30);
    setSEL  (gpio, GPIO0_CTRL_FUNCSEL__sio_0);
    setMode (gpio, mode);
}

bool
gpio_rp2040::gpioRead (uint16_t gpio) {
    yahal_assert(gpio < 30);
    return SIO.GPIO_IN & (1 << gpio);
}

void
gpio_rp2040::gpioWrite (uint16_t gpio, bool value) {
    yahal_assert(gpio < 30);
    uint32_t mask = 1 << gpio;
    if (_open_drain & mask) {
        if (value) SIO.GPIO_OE_CLR = mask;
        else       SIO.GPIO_OE_SET = mask;
    }
    else if (_open_source & mask) {
        if (value) SIO.GPIO_OE_SET = mask;
        else       SIO.GPIO_OE_CLR = mask;
    }
    else {
        // No open drain/source
        if (value) SIO.GPIO_OUT_SET = mask;
        else       SIO.GPIO_OUT_CLR = mask;
    }
}

void
gpio_rp2040::gpioToggle (uint16_t gpio) {
    yahal_assert(gpio < 30);
    uint32_t mask = 1 << gpio;
    if ((_open_drain & mask) || (_open_source & mask))
          SIO.GPIO_OE_XOR  = mask;
    else  SIO.GPIO_OUT_XOR = mask;
}

void
gpio_rp2040::gpioAttachIrq (gpio_pin_t gpio, gpio_mode_t mode,
                            function<void()> handler) {
    yahal_assert(gpio < 30);
    _irqConfig[gpio] = 0;
    // configure irqs according to mode
    if (mode & GPIO::LEVEL_LOW) {
        _irqConfig[gpio] |= 0x1;
    }
    if (mode & GPIO::LEVEL_HIGH) {
        _irqConfig[gpio] |= 0x2;
    }
    if (mode & GPIO::FALLING) {
        _irqConfig[gpio] |= 0x4;
    }
    if (mode & GPIO::RISING) {
        _irqConfig[gpio] |= 0x8;
    }
    // store handler addr
    _intHandler[gpio] = handler;
    // Finally enable irqs
    gpioEnableIrq(gpio);
}

void
gpio_rp2040::gpioDetachIrq (uint16_t gpio) {
    yahal_assert(gpio < 30);
    // Disable irqs
    gpioDisableIrq(gpio);
    // unregister handler
    _intHandler[gpio] = 0;
}

void
gpio_rp2040::gpioEnableIrq (uint16_t gpio) {
    yahal_assert(gpio < 30);
    PROC0_INTE0_t *INTE_SET = &IO_BANK0_SET.PROC0_INTE0 + (gpio >> 3);
    INTR0_t       *INTR     = &IO_BANK0.INTR0           + (gpio >> 3);
    int mask_shift = (gpio & 0x7) * 4;
    // Switch off NVIC irq so we get no
    // handler calls during configuration
    NVIC_DisableIRQ(IO_IRQ_BANK0_IRQn);
    // Enable irqs
    *INTE_SET = _irqConfig[gpio] << mask_shift;
    // Clear pending interrupts
    *INTR = (0xf << mask_shift);
    // Enable NVIC irq
    NVIC_ClearPendingIRQ(IO_IRQ_BANK0_IRQn);
    NVIC_EnableIRQ      (IO_IRQ_BANK0_IRQn);
}

void
gpio_rp2040::gpioDisableIrq (uint16_t gpio) {
    yahal_assert(gpio < 30);
    PROC0_INTE0_t *INTE_CLR = &IO_BANK0_CLR.PROC0_INTE0 + (gpio >> 3);
    INTR0_t       *INTR     = &IO_BANK0.INTR0           + (gpio >> 3);
    int mask_shift = (gpio & 0x7) * 4;
    // Clear pending interrupts
    *INTR = (0xf << mask_shift);
    // Disable irqs
    *INTE_CLR = (0xf << mask_shift);
}

void gpio_rp2040::setSEL (uint16_t gpio, uint8_t sel) {
    yahal_assert(gpio < 30);
    GPIO0_CTRL_t *io_ctrl = &IO_BANK0.GPIO0_CTRL + (gpio << 1);
    // Set the pad function and reset all other bits
    io_ctrl->FUNCSEL = sel;
    io_ctrl->OUTOVER = 0;
    io_ctrl->OEOVER  = 0;
    io_ctrl->INOVER  = 0;
    io_ctrl->IRQOVER = 0;
}

void gpio_rp2040::setMode (uint16_t gpio, uint16_t mode) {
    yahal_assert(gpio < 30);
    uint32_t mask = 1 << gpio;
    GPIO0_t *pad_ctrl = &PADS_BANK0.GPIO0 + gpio;

    // Reset open drain/source
    _open_drain  &= ~(1 << gpio);
    _open_source &= ~(1 << gpio);
    // Reset SIO configuration
    SIO.GPIO_OUT_CLR = mask;
    SIO.GPIO_OE_CLR  = mask;
    // Reset pad configuration
    pad_ctrl->OD       = 0;
    pad_ctrl->IE       = 1;
    pad_ctrl->DRIVE    = GPIO0_DRIVE__2mA;
    pad_ctrl->PUE      = 0;
    pad_ctrl->PDE      = 0;
    pad_ctrl->SCHMITT  = 1;
    pad_ctrl->SLEWFAST = 0;

    if (mode & GPIO::INPUT) {
        // Default is okay
    }
    if (mode & GPIO::OUTPUT) {
        SIO.GPIO_OE_SET = mask;
    }
    if (mode & GPIO::OUTPUT_OPEN_DRAIN) {
        _open_drain |= mask;
        SIO.GPIO_OE_SET = mask;
    }
    if (mode & GPIO::OUTPUT_OPEN_SOURCE) {
        _open_source |= mask;
        SIO.GPIO_OUT_SET = mask;
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
        pad_ctrl->DRIVE = (mode >> 10);
    }
    if (mode & GPIO::INIT_HIGH) {
        gpioWrite (gpio, HIGH);
    }
    if (mode & GPIO::INIT_LOW) {
        gpioWrite (gpio, LOW);
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
            gpio_rp2040::inst._intHandler[gpio]();
        }
    }
}

} // extern "C"
