#ifndef _GPIO_BBB_IF_H_
#define _GPIO_BBB_IF_H_

#include <linux/ioctl.h>

/* 
 * The name of the device file 
 */
#define GPIO_DEV_NAME "gpio_bbb"

/* 
 * Number of available GPIOs
*/
#define GPIO_COUNT 128

/*
 * Definition of GPIO mode flags.
 * Should be compatible with gpio_interface.h
 */
#define GPIO_INPUT              0x0001
#define GPIO_OUTPUT             0x0002
#define GPIO_OUTPUT_OPEN_DRAIN  0x0004
#define GPIO_OUTPUT_OPEN_SOURCE 0x0008
#define GPIO_PULLUP             0x0010
#define GPIO_PULLDOWN           0x0020
#define GPIO_SLOW               0x0040
#define GPIO_FAST               0x0080
#define GPIO_INIT_HIGH          0x0100
#define GPIO_INIT_LOW           0x0200
#define GPIO_REQUESTED          0x8000

/*
 * Definition of IRQ trigger flags.
 * Should be compatible with gpio_interface.h
 */
#define GPIO_RISING      0x0001
#define GPIO_FALLING     0x0002
#define GPIO_LEVEL_HIGH  0x0004
#define GPIO_LEVEL_LOW   0x0008

/*
 * Macro to support coding of data into the
 * IOCTL parameter: Lower 8 bits are GPIO
 * number (0...127), higher bits are data.
 */
#define GPIO_DATA(gpio, data) (((data) << 8) | (gpio))

/* 
 * The major IOCTL 'magic' number.
 */
#define MAJOR_NUM 100

#define IOCTL_GPIO_MODE         _IOW(MAJOR_NUM,  0, unsigned long)
#define IOCTL_GPIO_READ         _IOW(MAJOR_NUM,  1, unsigned long)
#define IOCTL_GPIO_WRITE        _IOW(MAJOR_NUM,  2, unsigned long)
#define IOCTL_GPIO_TOGGLE       _IOW(MAJOR_NUM,  3, unsigned long)
#define IOCTL_GPIO_ATTACH_IRQ   _IOW(MAJOR_NUM,  4, unsigned long)
#define IOCTL_GPIO_DETACH_IRQ   _IOW(MAJOR_NUM,  5, unsigned long)
#define IOCTL_GPIO_ENABLE_IRQ   _IOW(MAJOR_NUM,  6, unsigned long)
#define IOCTL_GPIO_DISABLE_IRQ  _IOW(MAJOR_NUM,  7, unsigned long)
#define IOCTL_SET_DEBOUNCE      _IOW(MAJOR_NUM,  8, unsigned long)

#endif
