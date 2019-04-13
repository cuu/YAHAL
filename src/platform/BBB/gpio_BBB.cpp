#include "gpio_BBB.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <string>
#include <iostream>
using namespace std;

gpio_BBB gpio_BBB::inst;

bool running;

// Simple exception class for error handling
class gpio_exception : public std::exception {
  public:
    gpio_exception (std::string msg, int err) {
      _msg = msg + strerror(abs(err));
    }
    ~gpio_exception () throw() { }
    const char* what() const throw() {
      return _msg.c_str();
    }
  private:
    std::string _msg;
};

// The user-space irq-handler thread. It blocks on a
// read on the gpio_bbb character device. When the
// read succeeds an irq has occured, and the gpio
// producing the irq is returned. After that the
// related user irq handler is called.

void gpio_BBB::irq_handler() {
  while (running) {
    int gpio = read(_fd_gpio, NULL, 0);
    // Exit thread if we get a wrong gpio number
    if (gpio < 0 || gpio >= GPIO_COUNT) break;
    // Call user handler
    if (usrHandler[gpio]) usrHandler[gpio](gpio, NULL);
  }
}

gpio_BBB::gpio_BBB() {
  // Clear the irq handlers
  for (int i=0; i < GPIO_COUNT; ++i)
    usrHandler[i] = 0;
  // open the GPIO device
  _fd_gpio = open("/dev/" GPIO_DEV_NAME, O_RDWR );
  if( _fd_gpio < 0 ) {
    throw gpio_exception("Cannot open /dev/" GPIO_DEV_NAME ", ", errno);
  }
  // start the irq thread
  running=true;
  irq_thread = std::thread([&](){ irq_handler();} );
}

gpio_BBB::~gpio_BBB() {
  // Stop the irq thread
  running=false;
  write(_fd_gpio, NULL, 0);
  irq_thread.join();
  close(_fd_gpio);
}

//////////////////
// GPIO methods //
//////////////////
void gpio_BBB::gpioMode (gpio_pin_t gpio, gpio_mode_t mode) {
  if (gpio >= GPIO_COUNT) {
    throw gpio_exception("GPIO out of range, ", EINVAL);
  }
  int ret = ioctl(_fd_gpio, IOCTL_GPIO_MODE, GPIO_DATA(gpio, mode));
  if (ret < 0) {
    throw gpio_exception("gpioMode: ", ret);
  }
}

bool gpio_BBB::gpioRead (gpio_pin_t gpio) {
  return ioctl(_fd_gpio, IOCTL_GPIO_READ, gpio);
}

void gpio_BBB::gpioWrite (gpio_pin_t gpio, bool value) {
  int ret = ioctl(_fd_gpio, IOCTL_GPIO_WRITE, GPIO_DATA(gpio, value));
  if (ret < 0) {
    throw gpio_exception("gpioWrite: ", ret);
  }
}

void gpio_BBB::gpioToggle (gpio_pin_t gpio) {
  int ret = ioctl(_fd_gpio, IOCTL_GPIO_TOGGLE, gpio);
  if (ret < 0) {
    throw gpio_exception("gpioToggle: ", ret);
  }
}

///////////////////////
// Interrupt methods //
///////////////////////
void gpio_BBB::gpioAttachIrq (gpio_pin_t gpio, gpio_irq_t mode,
                    void (*handler)(gpio_pin_t, void *), void * arg) {
  if (gpio >= GPIO_COUNT) {
    throw gpio_exception("GPIO number out of range, ", EINVAL);
  }
  usrHandler[gpio] = handler;
  int ret = ioctl(_fd_gpio, IOCTL_GPIO_ATTACH_IRQ, GPIO_DATA(gpio, mode));
  if (ret < 0) {
    throw gpio_exception("gpioAttachIrq: ", ret);
  }
  gpioEnableIrq(gpio);
}

void gpio_BBB::gpioDetachIrq (gpio_pin_t gpio) {
  gpioDisableIrq(gpio);
  usrHandler[gpio] = 0;
  int ret = ioctl(_fd_gpio, IOCTL_GPIO_DETACH_IRQ, gpio);
  if (ret < 0) {
    throw gpio_exception("gpioDetachIrq: ", ret);
  }
}

void gpio_BBB::gpioEnableIrq (gpio_pin_t gpio) {
  int ret = ioctl(_fd_gpio, IOCTL_GPIO_ENABLE_IRQ, gpio);
  if (ret < 0) {
    throw gpio_exception("gpioEnableIrq: ", ret);
  }
}

void gpio_BBB::gpioDisableIrq(gpio_pin_t gpio) {
  int ret = ioctl(_fd_gpio, IOCTL_GPIO_DISABLE_IRQ, gpio);
  if (ret < 0) {
    throw gpio_exception("gpioDisableIrq: ", ret);
  }
}

void gpio_BBB::setDebounce (uint8_t gpio, uint16_t msdelay) {
  int ret = ioctl(_fd_gpio, IOCTL_SET_DEBOUNCE, GPIO_DATA(gpio, msdelay));
  if (ret < 0) {
    throw gpio_exception("setDebounce: ", ret);
  }
}

