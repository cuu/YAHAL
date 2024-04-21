#include "WifiTick.h"
#include "task.h"

WifiTick::WifiTick()
: _gpio0  (PORT_PIN( 7, 4)),
  _gpio2  (PORT_PIN( 7, 5)),
  _gpio15 (PORT_PIN(10, 0)),
  _reset  (PORT_PIN(10, 5)),
  _powerUp(PORT_PIN( 9, 5)),
  _led    (PORT_PIN( 8, 0))
{
    // We only set the modes for the GPIOs which we control.
    // gpio0/2/15 might be used for other purposes, so we
    // don't touch their modes.
    _reset.gpioMode  (GPIO::OUTPUT | GPIO::INIT_HIGH);
    _powerUp.gpioMode(GPIO::OUTPUT_OPEN_DRAIN | GPIO::INIT_HIGH);
    _led.gpioMode    (GPIO::OUTPUT | GPIO::INIT_LOW);
}

void WifiTick::reset(bool boot_from_uart)
{
    // Perform reset
    _reset.gpioWrite(LOW);
    // Read current state of GPIOs
    bool gpio0  = _gpio0. gpioRead();
    bool gpio2  = _gpio2. gpioRead();
    bool gpio15 = _gpio15.gpioRead();
    // Make sure GPIOs have the correct
    // setting for the required boot mode
    _gpio0. gpioWrite(!boot_from_uart);
    _gpio2. gpioWrite(HIGH);
    _gpio15.gpioWrite(LOW);
    task::sleep_ms(100);
    _reset.gpioWrite(HIGH);
    task::sleep_ms(100);
    // Restore the GPIOs to their original state,
    // if they have been used as OUTPUT
    if (gpio0 == boot_from_uart) {
        _gpio0. gpioWrite(boot_from_uart);
    }
    if (!gpio2) _gpio2. gpioWrite(LOW);
    if (gpio15) _gpio15.gpioWrite(HIGH);
}
