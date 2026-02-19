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
// GPIO driver for RP2350. Supports open-source and
// open-drain modes as well as interrupts.
//
#include "gpio_rp2350.h"
#include "RP2350.h"
#include <cassert>

// Macro to increment the address of a register if the
// GPIO number is larger than 31. The register for the
// 'higher' GPIOs (32 to 47) is usually at the following
// address location.
#define OFF32(x) (*(&x + _high_gpio))

using namespace _SIO_;
using namespace _IO_BANK0_;
using namespace _PADS_BANK0_;

function<void()> gpio_rp2350::_intHandler[48] {nullptr};
uint8_t          gpio_rp2350::_irqConfig [48] {0};

gpio_rp2350::gpio_rp2350(gpio_pin_t gpio) : _gpio(gpio) {
    // Set GPIO mask and 'high' boolean
    // The value gpio is not checked, because
    // it might be 'not connected' (0xffff)
    _mask = 1 << (gpio % 32);
    _high_gpio = (gpio > 31);
}

void gpio_rp2350::setGpio(gpio_pin_t gpio) {
    assert(gpio < 48);
    _gpio = gpio;
    _mask = 1 << (gpio % 32);
    _high_gpio = (gpio > 31);
}

gpio_pin_t gpio_rp2350::getGpio() const {
    return _gpio;
}

void gpio_rp2350::gpioMode (uint16_t mode) {
    assert(_gpio < 48);
    setSEL (GPIO_CTRL_FUNCSEL__sio);
    setMode(mode);
}

bool gpio_rp2350::gpioRead () const {
    assert(_gpio < 48);
//    GPIO_t *pad_ctrl = &PADS_BANK0.GPIO[_gpio]; // Bug E9
//    pad_ctrl->IE = 1; //1; Bug E9
    bool res = OFF32( SIO.GPIO_IN ) & _mask;
//    pad_ctrl->IE = 0; //1; Bug E9
    return res;
}

void gpio_rp2350::gpioWrite (bool value) {
    assert(_gpio < 48);
    if (_open_drain) {
        if (value) {
            OFF32( SIO.GPIO_OE_CLR ) = _mask;
        } else {
            OFF32( SIO.GPIO_OE_SET ) = _mask;
        }
    }
    else if (_open_source) {
        if (value) {
            OFF32( SIO.GPIO_OE_SET ) = _mask;
        } else {
            OFF32( SIO.GPIO_OE_CLR ) = _mask;
        }
    }
    else {
        // No open drain/source
        if (value) {
            OFF32( SIO.GPIO_OUT_SET ) = _mask;
        } else {
            OFF32( SIO.GPIO_OUT_CLR ) = _mask;
        }
    }
}

void gpio_rp2350::gpioToggle() {
    assert(_gpio < 48);
    if (_open_drain || _open_source) {
        OFF32( SIO.GPIO_OE_XOR ) = _mask;
    } else {
        OFF32( SIO.GPIO_OUT_XOR ) = _mask;
    }
}

void gpio_rp2350::gpioAttachIrq (gpio_mode_t mode,
                                 function<void()> handler) {
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
    // Finally enable interrupts
    gpioEnableIrq();
}

void gpio_rp2350::gpioDetachIrq () {
    // Disable irqs
    gpioDisableIrq();
    // unregister handler
    _intHandler[_gpio] = nullptr;
}

void gpio_rp2350::gpioEnableIrq() {
    PROC0_INTE0_t *INTE_SET = &IO_BANK0_SET.PROC0_INTE0 + (_gpio >> 3) + (SIO.CPUID*18);
    PROC0_INTE0_t *INTE_CLR = &IO_BANK0_CLR.PROC0_INTE0 + (_gpio >> 3) + (SIO.CPUID*18);
    INTR0_t       *INTR     = &IO_BANK0.INTR0           + (_gpio >> 3);
    int mask_shift = (_gpio & 0x7) * 4;
    // Switch off NVIC irq, so we get no
    // handler calls during configuration
    NVIC_DisableIRQ(IO_IRQ_BANK0_IRQn);
    // Enable irqs (reset values and set related bits)
    *INTE_CLR = (0xf << mask_shift);
    *INTE_SET = _irqConfig[_gpio] << mask_shift;
    // Clear pending interrupts
    *INTR = (0xf << mask_shift);
    // Enable NVIC irq
    NVIC_ClearPendingIRQ(IO_IRQ_BANK0_IRQn);
    NVIC_EnableIRQ      (IO_IRQ_BANK0_IRQn);
}

void gpio_rp2350::gpioDisableIrq() {
    PROC0_INTE0_t *INTE_CLR = &IO_BANK0_CLR.PROC0_INTE0 + (_gpio >> 3) + (SIO.CPUID*18);
    INTR0_t       *INTR     = &IO_BANK0.INTR0           + (_gpio >> 3);
    int mask_shift = (_gpio & 0x7) * 4;
    // Clear pending interrupts
    *INTR = (0xf << mask_shift);
    // Disable irqs
    *INTE_CLR = (0xf << mask_shift);
}

void gpio_rp2350::setSEL (uint8_t sel) const {
    assert(_gpio < 48);
    GPIO_CTRL_t *IO_CTRL = &IO_BANK0.GPIO0_CTRL + (_gpio << 1);
    // Set the pad function and reset all other bits
    IO_CTRL->FUNCSEL = sel;
    IO_CTRL->OUTOVER = 0;
    IO_CTRL->OEOVER  = 0;
    IO_CTRL->INOVER  = 0;
    IO_CTRL->IRQOVER = 0;
    // Obviously we want to use this pin.
    // So deactivate the PAD isolation and
    // enable gpio input
    GPIO_t *PAD_CTRL = &PADS_BANK0.GPIO[_gpio];
    PAD_CTRL->ISO    = 0;
    PAD_CTRL->IE     = 1;
}

void gpio_rp2350::setMode (uint16_t mode) {
    // Reset open drain/source
    _open_drain  = false;
    _open_source = false;
    // Reset SIO configuration
    OFF32( SIO.GPIO_OUT_CLR ) = _mask;
    OFF32( SIO.GPIO_OE_CLR ) = _mask;
    // Reset pad configuration
    GPIO_t *PAD_CTRL = &PADS_BANK0.GPIO[_gpio];
    PAD_CTRL->ISO      = 0;
    PAD_CTRL->OD       = 0;
    PAD_CTRL->IE       = 0;
    PAD_CTRL->DRIVE    = GPIO_DRIVE__2mA;
    PAD_CTRL->PUE      = 0;
    PAD_CTRL->PDE      = 0;
    PAD_CTRL->SCHMITT  = 1;
    PAD_CTRL->SLEWFAST = 0;

    if (mode & GPIO::INPUT) {
        // Enable input
        PAD_CTRL->IE = 1;
    }
    if (mode & GPIO::INPUT_INVERT) {
        // Enable input
        PAD_CTRL->IE = 1;
        GPIO_CTRL_t *io_ctrl = &IO_BANK0.GPIO0_CTRL + (_gpio << 1);
        io_ctrl->INOVER = GPIO_CTRL_INOVER__INVERT;
    }
    if (mode & GPIO::OUTPUT) {
        OFF32( SIO.GPIO_OE_SET ) = _mask;
    }
    if (mode & GPIO::OUTPUT_OPEN_DRAIN) {
        _open_drain |= _mask;
        OFF32( SIO.GPIO_OE_SET ) = _mask;
    }
    if (mode & GPIO::OUTPUT_OPEN_SOURCE) {
        _open_source |= _mask;
        OFF32( SIO.GPIO_OUT_SET ) = _mask;
    }
    if (mode & GPIO::PULLUP) {
        PAD_CTRL->PUE = 1;
    }
    if (mode & GPIO::PULLDOWN) {
        PAD_CTRL->PDE = 1;
    }
    if (mode & GPIO::FAST) {
        PAD_CTRL->SLEWFAST = 1;
    }
    if ((mode & GPIO::DRIVE_4mA) || (mode & GPIO::DRIVE_8mA)) {
        PAD_CTRL->DRIVE = (mode >> 10) & 0x3;
    }
    if (mode & GPIO::INIT_HIGH) {
        gpioWrite(HIGH);
    }
    if (mode & GPIO::INIT_LOW) {
        gpioWrite(LOW);
    }
}

// Interrupt handler
////////////////////
extern "C" {

void IO_IRQ_BANK0_Handler(void) {
    PROC0_INTS0_t *INTS = &IO_BANK0.PROC0_INTS0 + (SIO.CPUID*18);
    INTR0_t       *INTR = &IO_BANK0.INTR0;
    for (int i = 0; i < 6; ++i, INTS++, INTR++) {
        while (uint8_t pos = __builtin_ffs(*INTS)) {
            // Clear irq
            *INTR = (1 << --pos);
            // Call irq handler
            uint16_t gpio = (pos >> 2) + (i << 3);
            if (gpio_rp2350::_intHandler[gpio]) {
                gpio_rp2350::_intHandler[gpio]();
            }
        }
    }
}

} // extern "C"
