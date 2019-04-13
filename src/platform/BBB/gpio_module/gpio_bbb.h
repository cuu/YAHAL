#ifndef _GPIO_BBB_MOD_H_
#define _GPIO_BBB_MOD_H_

#include "gpio_bbb_if.h"

/****************************/
/* module lifecycle methods */
/****************************/                  
static int  __init gpio_bbb_start (void);
static int  my_dev_uevent(struct device *dev, struct kobj_uevent_env *env);
static void __exit gpio_bbb_end(void);

/****************************/
/* character device methods */
/****************************/
static int device_open     (struct inode *inode, struct file *file);
static int device_release  (struct inode *inode, struct file *file);
static ssize_t device_read (struct file *filp, char *buff, 
                            size_t len, loff_t *off);
static ssize_t device_write(struct file *filp, const char *buff,
                            size_t len, loff_t *off);
long device_ioctl(struct        file *file,
                  unsigned int  ioctl_num,
                  unsigned long ioctl_param);

/****************/
/* GPIO methods */
/****************/
static int _gpioMode(u8 gpio_num, u16 flags);
static int _gpioRead(u8 gpio_num);
static int _gpioWrite (u8 gpio_num, int value);
static int _gpioToggle (u8 gpio_num);
static int _gpioAttachIrq(u8 gpio_num, u16 flags);
static int _gpioDetachIrq(u8 gpio_num);
static int _gpioEnableIrq(u8 gpio_num);
static int _gpioDisableIrq(u8 gpio_num);

/*******************/
/* Utility methods */
/*******************/
static void _ioset32  (u32 v, void __iomem *addr);
static void _ioclear32(u32 v, void __iomem *addr);

static int  _map_memory(void);
static void _unmap_memory(void);

static u16 _gpio_to_offset(u8 gpio_num);
static u8  _irq_to_gpio(int irq);

static void _release_irq(u8 gpio_num);
static void _release_all_irqs(void);
irqreturn_t _gpio_irq_handler(int irq, void *dev_id);

#endif
