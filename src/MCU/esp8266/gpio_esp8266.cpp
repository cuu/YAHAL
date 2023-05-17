#include "gpio_esp8266.h"
#include "ESP8266.h"
#include <cassert>

extern "C"
{
#include "ets_sys.h"
}

const uint8_t gpio_esp8266::GPIO_TO_IOMUX[] = { 12,5,13,4,14,15,6,7,8,9,10,11,0,1,2,3 };

gpio_esp8266 gpio_esp8266::inst;

gpio_esp8266::gpio_esp8266()
{
    for (int i = 0; i < 16; ++i) {
        intHandler[i] = 0;
        intMode[i]    = _GPIO_::PIN_INT_TYPE__DISABLE;
    }
    ETS_GPIO_INTR_ATTACH(gpio_irq_handler, this);
    ETS_GPIO_INTR_ENABLE();
}


gpio_esp8266::~gpio_esp8266()
{
    ETS_GPIO_INTR_DISABLE();
}


void gpio_esp8266::gpioMode(uint16_t gpio, uint16_t mode)
{
    assert(gpio < 16);

    // Select GPIO as pin function
    uint8_t mux_idx = GPIO_TO_IOMUX[gpio];
    _IO_MUX_::IO_MUX.ENTRY[mux_idx].FUNC = (mux_idx > 11) ? 1 : 4;

    // Configure basic GPIO modes
    if (mode & GPIO::INPUT) {
        _IO_MUX_::IO_MUX.ENTRY[mux_idx].OE = 0;
        _GPIO_::GPIO.ENABLE_W1TC = 1 << gpio;
    }
    else if (mode & GPIO::OUTPUT) {
        _IO_MUX_::IO_MUX.ENTRY[mux_idx].OE = 1;
        _GPIO_::GPIO.ENABLE_W1TS = 1 << gpio;
        _GPIO_::GPIO.PIN[gpio].DRIVER = _GPIO_::PIN_DRIVER__PUSH_PULL;
    }
    else if (mode & GPIO::OUTPUT_OPEN_DRAIN) {
        _IO_MUX_::IO_MUX.ENTRY[mux_idx].OE = 1;
        _GPIO_::GPIO.ENABLE_W1TS = 1 << gpio;
        _GPIO_::GPIO.PIN[gpio].DRIVER = _GPIO_::PIN_DRIVER__OPEN_DRAIN;
    }
    else assert(false);

    _IO_MUX_::IO_MUX.ENTRY[mux_idx].PULLUP   = (mode & GPIO::PULLUP) ?   1 : 0;
    _IO_MUX_::IO_MUX.ENTRY[mux_idx].PULLDOWN = (mode & GPIO::PULLDOWN) ? 1 : 0;
    if (mode & GPIO::INIT_HIGH) {
        _GPIO_::GPIO.OUT_W1TS = (1 << gpio);
    }
    if (mode & GPIO::INIT_LOW) {
        _GPIO_::GPIO.OUT_W1TC = (1 << gpio);
    }
}


bool gpio_esp8266::gpioRead(uint16_t gpio)
{
    assert(gpio < 16);
    return (_GPIO_::GPIO.IN.DATA & (1 << gpio));
}


void gpio_esp8266::gpioWrite(uint16_t gpio, bool value)
{
    assert(gpio < 16);
    if (value) {
        _GPIO_::GPIO.OUT_W1TS = (1 << gpio);
    } else {
        _GPIO_::GPIO.OUT_W1TC = (1 << gpio);
    }
}


void gpio_esp8266::gpioToggle(uint16_t gpio)
{
    assert(gpio < 16);
    _GPIO_::GPIO.OUT ^= (1 << gpio);
}


void gpio_esp8266::gpioAttachIrq(uint16_t gpio, uint16_t irq_mode,
                                 function<void()> handler)
{
    assert(gpio < 16);
    intHandler[gpio] = handler;
    int esp_mode = _GPIO_::PIN_INT_TYPE__DISABLE;
    switch (irq_mode)
    {
        case GPIO::RISING:
            esp_mode = _GPIO_::PIN_INT_TYPE__RAISING_EDGE;
            break;
        case GPIO::FALLING:
            esp_mode = _GPIO_::PIN_INT_TYPE__FALLING_EDGE;
            break;
        case GPIO::RISING | GPIO::FALLING:
            esp_mode = _GPIO_::PIN_INT_TYPE__BOTH_EDGES;
            break;
        case GPIO::LEVEL_HIGH:
            esp_mode = _GPIO_::PIN_INT_TYPE__LEVEL_HIGH;
            break;
        case GPIO::LEVEL_LOW:
            esp_mode = _GPIO_::PIN_INT_TYPE__LEVEL_LOW;
            break;
        default:
            assert(false);
    }
    intMode[gpio]                   = esp_mode;
    _GPIO_::GPIO.PIN[gpio].INT_TYPE = esp_mode;
}


void gpio_esp8266::gpioDetachIrq(uint16_t gpio)
{
    assert(gpio < 16);
    gpioDisableIrq(gpio);
    intMode[gpio] = _GPIO_::PIN_INT_TYPE__DISABLE;
    intHandler[gpio] = 0;
}


void gpio_esp8266::gpioEnableIrq(uint16_t gpio)
{
    assert(gpio < 16);
    // Clear pending interrupts
    _GPIO_::GPIO.STATUS_W1TC = (1 << gpio);
    _GPIO_::GPIO.PIN[gpio].INT_TYPE = intMode[gpio];
}


void gpio_esp8266::gpioDisableIrq(uint16_t gpio)
{
    assert(gpio < 16);
    _GPIO_::GPIO.PIN[gpio].INT_TYPE = _GPIO_::PIN_INT_TYPE__DISABLE;
}


void gpio_esp8266::handleInterrupt()
{
    // Acknowledge all pending IRQs
    uint16_t status = _GPIO_::GPIO.STATUS;
    _GPIO_::GPIO.STATUS_W1TC = status;

    // Serve all pending IRQs
    while (uint8_t gpio = __builtin_ffs(status)) {
        --gpio;
        status &= ~(1 << gpio);
        if (intHandler[gpio])
            intHandler[gpio]();
    }
}


void gpio_irq_handler(gpio_esp8266 * gpio)
{
    gpio->handleInterrupt();
}


void gpio_esp8266::brightnessControl(uint16_t gpio, bool on)
{
    assert(gpio < 16);
    if (on) {
        _GPIO_::GPIO.PIN[gpio].SOURCE = _GPIO_::PIN_SOURCE__SIGMA_DELTA;
    } else {
        _GPIO_::GPIO.PIN[gpio].SOURCE = _GPIO_::PIN_SOURCE__GPIO;
    }
}


void gpio_esp8266::setBrightness(uint8_t value)
{
    _GPIO_::GPIO.SIGMA_DELTA.ENABLE = 1;
    _GPIO_::GPIO.SIGMA_DELTA.PRESCALE = 0x80;
    _GPIO_::GPIO.SIGMA_DELTA.TARGET = value;
}

