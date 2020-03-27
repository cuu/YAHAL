/************************************************
  G P I O _ B B B

  A performant GPIO library for the BeagleBone 

  (c) 2015-2019  A. Terstegge 
           <Andreas.Terstegge@googlemail.com>

************************************************/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>

#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <linux/pinctrl/consumer.h>

#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/cdev.h>

#include "gpio_bbb.h"

MODULE_LICENSE    ("GPL");
MODULE_AUTHOR     ("Andreas Terstegge");
MODULE_DESCRIPTION("A fast IOCTL-based GPIO driver for the BBB");

#define MOD_STR    "gpio_bbb: "

static int open_count = 0;

static dev_t         devnum; // Global var for the device number
static struct class *cl;     // Global var for the device class
static struct cdev   c_dev;  // Global var for the character device structure

static wait_queue_head_t queue;
static int gpio_irq;

static int irq_enabled[GPIO_COUNT];
static u16   gpio_mode[GPIO_COUNT];

/**************************/
/* global memory adresses */
/**************************/
#define CTRL_MODULE_ADDR 0x44e10000
#define CTRL_MODULE_LEN  0xa00
void __iomem *ctrl_module_base;

unsigned int GPIO_BANK_ADDR[4] = {
  0x44e07000,  // GPIO0  
  0x4804c000,  // GPIO1
  0x481ac000,  // GPIO2
  0x481ae000   // GPIO3
};
#define GPIO_BANK_LEN 0x200
void __iomem *gpio_base[4];

/******************************/
/* GPIO bank register offsets */
/******************************/
#define GPIO_IRQSTATUS_RAW_0	0x024
#define GPIO_IRQSTATUS_0	0x02c
#define GPIO_IRQSTATUS_SET_0	0x034
#define GPIO_IRQSTATUS_CLR_0	0x03c
#define GPIO_OE           	0x134
#define GPIO_DATAIN       	0x138
#define GPIO_DATAOUT            0x13c
#define GPIO_LEVELDETECT0	0x140
#define GPIO_LEVELDETECT1	0x144
#define GPIO_RISINGDETECT	0x148
#define GPIO_FALLINGDETECT	0x14c
#define GPIO_SETDATAOUT   	0x194
#define GPIO_CLEARDATAOUT 	0x190

/*************/
/* GPIO data */
/*************/
#define ENABLE  0x80
#define DISABLE 0x00
#define GPIO0 (00 << 5)
#define GPIO1 (01 << 5)
#define GPIO2 (02 << 5)
#define GPIO3 (03 << 5)
u8 gpio_data[GPIO_COUNT] = {
// ========+=========+=======+======+=========+=======+=========
//  Offset | Status  | Bank  | Pin  | GPIO-No |Header |Usage
// ========+=========+=======+======+=========+=======+=========
  /*0x800*/  ENABLE  | GPIO1 |  0, // GPIO-32   P8-25  MMC1 DAT0
  /*0x804*/  ENABLE  | GPIO1 |  1, // GPIO-33   P8-24  MMC1 DAT1
  /*0x808*/  ENABLE  | GPIO1 |  2, // GPIO-34   P8-05  MMC1 DAT2
  /*0x80c*/  ENABLE  | GPIO1 |  3, // GPIO-35   P8-06  MMC1 DAT3
  /*0x810*/  ENABLE  | GPIO1 |  4, // GPIO-36   P8-23  MMC1 DAT4
  /*0x814*/  ENABLE  | GPIO1 |  5, // GPIO-37   P8-22  MMC1 DAT5
  /*0x818*/  ENABLE  | GPIO1 |  6, // GPIO-38   P8-03  MMC1 DAT6   
  /*0x81c*/  ENABLE  | GPIO1 |  7, // GPIO-39   P8-04  MMC1 DAT7
  /*0x820*/  ENABLE  | GPIO0 | 22, // GPIO-22   P8-19  (EHRPWM2A)
  /*0x824*/  ENABLE  | GPIO0 | 23, // GPIO-23   P8-13  (EHRPWM2B)
  /*0x828*/  ENABLE  | GPIO0 | 26, // GPIO-26   P8-14
  /*0x82c*/  ENABLE  | GPIO0 | 27, // GPIO-27   P8-17
  /*0x830*/  ENABLE  | GPIO1 | 12, // GPIO-44   P8-12
  /*0x834*/  ENABLE  | GPIO1 | 13, // GPIO-45   P8-11
  /*0x838*/  ENABLE  | GPIO1 | 14, // GPIO-46   P8-16
  /*0x83c*/  ENABLE  | GPIO1 | 15, // GPIO-47   P8-15

  /*0x840*/  ENABLE  | GPIO1 | 16, // GPIO-48   P9-15  connected to GPIO-64
  /*0x844*/  ENABLE  | GPIO1 | 17, // GPIO-49   P9-23
  /*0x848*/  ENABLE  | GPIO1 | 18, // GPIO-50   P9-14  (EHRPWM1A)
  /*0x84c*/  ENABLE  | GPIO1 | 19, // GPIO-51   P9-16  (EHRPWM1B)
  /*0x850*/  ENABLE  | GPIO1 | 20, // GPIO-52   -----  EMMC_RSTN (MMC1)
  /*0x854*/  ENABLE  | GPIO1 | 21, // GPIO-53   -----  LED USR0
  /*0x858*/  ENABLE  | GPIO1 | 22, // GPIO-54   -----  LED USR1
  /*0x85c*/  ENABLE  | GPIO1 | 23, // GPIO-55   -----  LED USR2
  /*0x860*/  ENABLE  | GPIO1 | 24, // GPIO-56   -----  LED USR3
  /*0x864*/  ENABLE  | GPIO1 | 25, // GPIO-57   -----  LCD INT
  /*0x868*/  ENABLE  | GPIO1 | 26, // GPIO-58   -----  USB1 OCN
  /*0x86c*/  ENABLE  | GPIO1 | 27, // GPIO-59   -----  HDMICLK DISN
  /*0x870*/  ENABLE  | GPIO0 | 30, // GPIO-30   P9-11  (UART4RXD)
  /*0x874*/  ENABLE  | GPIO0 | 31, // GPIO-31   P9-13  (UART4TXD)
  /*0x878*/  ENABLE  | GPIO1 | 28, // GPIO-60   P9-12
  /*0x87c*/  ENABLE  | GPIO1 | 29, // GPIO-61   P8-26

  /*0x880*/  ENABLE  | GPIO1 | 30, // GPIO-62   P8-21  MMC1 CLK
  /*0x884*/  ENABLE  | GPIO1 | 31, // GPIO-63   P8-20  MMC1 CMD
  /*0x888*/  ENABLE  | GPIO2 |  0, // GPIO-64   -----  connected to GPIO-48
  /*0x88c*/  ENABLE  | GPIO2 |  1, // GPIO-65   P8-18
  /*0x890*/  ENABLE  | GPIO2 |  2, // GPIO-66   P8-07  (TIMER4)
  /*0x894*/  ENABLE  | GPIO2 |  3, // GPIO-67   P8-08  (TIMER7)
  /*0x898*/  ENABLE  | GPIO2 |  4, // GPIO-68   P8-10  (TIMER6)
  /*0x89c*/  ENABLE  | GPIO2 |  5, // GPIO-69   P8-09  (TIMER5)
  /*0x8a0*/  ENABLE  | GPIO2 |  6, // GPIO-70   P8-45  LCD DATA 0
  /*0x8a4*/  ENABLE  | GPIO2 |  7, // GPIO-71   P8-46  LCD DATA 1
  /*0x8a8*/  ENABLE  | GPIO2 |  8, // GPIO-72   P8-43  LCD DATA 2
  /*0x8ac*/  ENABLE  | GPIO2 |  9, // GPIO-73   P8-44  LCD DATA 3
  /*0x8b0*/  ENABLE  | GPIO2 | 10, // GPIO-74   P8-41  LCD DATA 4
  /*0x8b4*/  ENABLE  | GPIO2 | 11, // GPIO-75   P8-42  LCD DATA 5
  /*0x8b8*/  ENABLE  | GPIO2 | 12, // GPIO-76   P8-39  LCD DATA 6
  /*0x8bc*/  ENABLE  | GPIO2 | 13, // GPIO-77   P8-40  LCD DATA 7

  /*0x8c0*/  ENABLE  | GPIO2 | 14, // GPIO-78   P8-37  LCD DATA 8
  /*0x8c4*/  ENABLE  | GPIO2 | 15, // GPIO-79   P8-38  LCD DATA 9
  /*0x8c8*/  ENABLE  | GPIO2 | 16, // GPIO-80   P8-36  LCD DATA 10
  /*0x8cc*/  ENABLE  | GPIO2 | 17, // GPIO-81   P8-34  LCD DATA 11
  /*0x8d0*/  ENABLE  | GPIO0 |  8, // GPIO-8    P8-35  LCD DATA 12
  /*0x8d4*/  ENABLE  | GPIO0 |  9, // GPIO-9    P8-33  LCD DATA 13
  /*0x8d8*/  ENABLE  | GPIO0 | 10, // GPIO-10   P8-31  LCD DATA 14
  /*0x8dc*/  ENABLE  | GPIO0 | 11, // GPIO-11   P8-32  LCD DATA 15
  /*0x8e0*/  ENABLE  | GPIO2 | 22, // GPIO-86   P8-27  LCD VSYNC
  /*0x8e4*/  ENABLE  | GPIO2 | 23, // GPIO-87   P8-29  LCD HSYNC
  /*0x8e8*/  ENABLE  | GPIO2 | 24, // GPIO-88   P8-28  LCD PCLK
  /*0x8ec*/  ENABLE  | GPIO2 | 25, // GPIO-89   P8-30  LCD DE     
  /*0x8f0*/  ENABLE  | GPIO2 | 26, // GPIO-90   -----  MMC0 DAT3
  /*0x8f4*/  ENABLE  | GPIO2 | 27, // GPIO-91   -----  MMC0 DAT2
  /*0x8f8*/  ENABLE  | GPIO2 | 28, // GPIO-92   -----  MMC0 DAT1
  /*0x8fc*/  ENABLE  | GPIO2 | 29, // GPIO-93   -----  MMC0 DAT0

  /*0x900*/  ENABLE  | GPIO2 | 30, // GPIO-94   -----  MMC0 CLKO
  /*0x904*/  ENABLE  | GPIO2 | 31, // GPIO-95   -----  MMC0 CMD
  /*0x908*/  DISABLE | GPIO3 |  0, // GPIO-96   -----  MII1_COL  
  /*0x90c*/  DISABLE | GPIO3 |  1, // GPIO-97   -----  MII1_CRS_DV
  /*0x910*/  DISABLE | GPIO3 |  2, // GPIO-98   -----  MII1_RXERR
  /*0x914*/  DISABLE | GPIO3 |  3, // GPIO-99   -----  MII1_TXEN
  /*0x918*/  DISABLE | GPIO3 |  4, // GPIO-100  -----  MII1_RXDV
  /*0x91c*/  DISABLE | GPIO0 | 16, // GPIO-16   -----  MII1_TXD3
  /*0x920*/  DISABLE | GPIO0 | 17, // GPIO-17   -----  MII1_TXD2
  /*0x924*/  DISABLE | GPIO0 | 21, // GPIO-21   -----  MII1_TXD1
  /*0x928*/  DISABLE | GPIO0 | 28, // GPIO-28   -----  MII1_TXD0
  /*0x92c*/  DISABLE | GPIO3 |  9, // GPIO-105  -----  MII1_TXCLK
  /*0x930*/  DISABLE | GPIO3 | 10, // GPIO-106  -----  MII1_RXCLK
  /*0x934*/  DISABLE | GPIO2 | 18, // GPIO-82   -----  MII1_RXD3
  /*0x938*/  DISABLE | GPIO2 | 19, // GPIO-83   -----  MII1_RXD2
  /*0x93c*/  DISABLE | GPIO2 | 20, // GPIO-84   -----  MII1_RXD1

  /*0x940*/  DISABLE | GPIO2 | 21, // GPIO-85   -----  MII1_RXD0
  /*0x944*/  DISABLE | GPIO0 | 29, // GPIO-29   -----  MII1_REFCLK
  /*0x948*/  DISABLE | GPIO0 |  0, // GPIO-0    -----  MDIO_DATA
  /*0x94c*/  DISABLE | GPIO0 |  1, // GPIO-1    -----  MDIO_CLK
  /*0x950*/  ENABLE  | GPIO0 |  2, // GPIO-2    P9-22  (UART2_RXD)
  /*0x954*/  ENABLE  | GPIO0 |  3, // GPIO-3    P9-21  (UART2_TXD)
  /*0x958*/  ENABLE  | GPIO0 |  4, // GPIO-4    P9-17  (I2C1 SDA)
  /*0x95c*/  ENABLE  | GPIO0 |  5, // GPIO-5    P9-18  (I2C1 SCL)
  /*0x960*/  ENABLE  | GPIO0 |  6, // GPIO-6    -----  MMC0_CD
  /*0x964*/  ENABLE  | GPIO0 |  7, // GPIO-7    P9-42A connected to GPIO-114
  /*0x968*/  ENABLE  | GPIO1 |  8, // GPIO-40   -----  n.c.
  /*0x96c*/  ENABLE  | GPIO1 |  9, // GPIO-41   -----  (TESTPT1)
  /*0x970*/  ENABLE  | GPIO1 | 10, // GPIO-42   -----  UART0_RXD
  /*0x974*/  ENABLE  | GPIO1 | 11, // GPIO-43   -----  UART0_TXD
  /*0x978*/  ENABLE  | GPIO0 | 12, // GPIO-12   P9-20  I2C2_SDA (CAPE)
  /*0x97c*/  ENABLE  | GPIO0 | 13, // GPIO-13   P9-19  I2C2_SCL (CAPE)

  /*0x980*/  ENABLE  | GPIO0 | 14, // GPIO-14   P9-26  (UART1_RXD)
  /*0x984*/  ENABLE  | GPIO0 | 15, // GPIO-15   P9-24  (UART1_TXD)
  /*0x988*/  ENABLE  | GPIO3 |  5, // GPIO-101  -----  I2C0_SDA      
  /*0x98c*/  ENABLE  | GPIO3 |  6, // GPIO-102  -----  I2C0_SCL
  /*0x990*/  ENABLE  | GPIO3 | 14, // GPIO-110  P9-31  (SPI1_SCLK)
  /*0x994*/  ENABLE  | GPIO3 | 15, // GPIO-111  P9-29  (SPI1_D0)
  /*0x998*/  ENABLE  | GPIO3 | 16, // GPIO-112  P9-30  (SPI1_D1)
  /*0x99c*/  ENABLE  | GPIO3 | 17, // GPIO-113  P9-28  (SPI1_CS0)
  /*0x9a0*/  ENABLE  | GPIO3 | 18, // GPIO-114  P9-42B connected to GPIO-7
  /*0x9a4*/  ENABLE  | GPIO3 | 19, // GPIO-115  P9-27  
  /*0x9a8*/  ENABLE  | GPIO3 | 20, // GPIO-116  P9-41B connected TO GPIO-20 
  /*0x9ac*/  ENABLE  | GPIO3 | 21, // GPIO-117  P9-25
  /*0x9b0*/  ENABLE  | GPIO0 | 19, // GPIO-19   CLKOUT HDMI
  /*0x9b4*/  ENABLE  | GPIO0 | 20, // GPIO-20   P9-41A CLKOUT
  /*0x9b8*/  DISABLE,              // WARMRSTN 
  /*0x9bc*/  DISABLE,              // UNUSED   

  /*0x9c0*/  DISABLE,		   // nNMI      -----
  /*0x9c4*/  DISABLE,              // UNUSED   
  /*0x9c8*/  DISABLE, 		   // UNUSED   
  /*0x9cc*/  DISABLE,		   // UNUSED   
  /*0x9d0*/  DISABLE,		   // TMS       -----  JTAG
  /*0x9d4*/  DISABLE,		   // TDI       -----  JTAG
  /*0x9d8*/  DISABLE,		   // TDO       -----  JTAG
  /*0x9dc*/  DISABLE,		   // TCK       -----  JTAG
  /*0x9e0*/  DISABLE,		   // TRSTN     -----  JTAG
  /*0x9e4*/  ENABLE | GPIO3 | 7,   // GPIO-103  -----  JTAG 
  /*0x9e8*/  ENABLE | GPIO3 | 8,   // GPIO-104  -----  JTAG 
  /*0x9ec*/  DISABLE,		   // UNUSED   
  /*0x9f0*/  DISABLE,		   // UNUSED   
  /*0x9f4*/  DISABLE,		   // UNUSED   
  /*0x9f8*/  DISABLE,              // PWRONRSTN
  /*0x9fc*/  DISABLE               // PMIC_POWER_EN
};


struct file_operations Fops = {
  .open           = device_open,	/* open  */
  .release        = device_release,	/* close */
  .read           = device_read,	/* read  */
  .write          = device_write,	/* write */
  .unlocked_ioctl = device_ioctl,	/* ioctl */
};

module_init (gpio_bbb_start);
module_exit (gpio_bbb_end);


/****************************************/
/******* Module Lifecycle methods *******/
/****************************************/
static int __init gpio_bbb_start (void) {
  struct device * dev;
  int ret;

  /* map memory areas */
  ret = _map_memory();
  if (ret < 0) return ret;
  /* create device class */
  cl = class_create( THIS_MODULE, "chardev" );
  if (cl == NULL ) {
    printk (KERN_ALERT MOD_STR"Class creation failed\n" );
    return -EPERM;
  }
  /* set the file mode of /dev/gpio_bbb */
  cl->dev_uevent = my_dev_uevent;

  /* create device */
  devnum = MKDEV(MAJOR_NUM, 0);
  dev = device_create( cl, NULL, devnum, NULL, GPIO_DEV_NAME );
  if (dev == NULL) {
    printk(KERN_ALERT MOD_STR"Device creation failed\n" );
    class_destroy(cl);
    return -EPERM;
  }
  /* initialize and add device */
  cdev_init( &c_dev, &Fops );
  ret = cdev_add( &c_dev, devnum, 1 );
  if(ret < 0) {
    printk (KERN_ALERT MOD_STR"Device addition failed\n" );
    device_destroy(cl, devnum);
    class_destroy (cl);
    return ret;
  }
  /* clear variables */
  memset(&irq_enabled, 0, GPIO_COUNT);
  /* initialize the wait queue */
  init_waitqueue_head(&queue);
  printk(KERN_INFO MOD_STR"Device %s registered\n", "/dev/"GPIO_DEV_NAME);
  return 0;
}

static int my_dev_uevent(struct device *dev, struct kobj_uevent_env *env)
{
  add_uevent_var(env, "DEVMODE=%#o", 0666);
  return 0;
}

static void __exit gpio_bbb_end(void) {
  /* unmap memory */
  _unmap_memory();
  /* release irqs and gpios */
  _release_all_irqs();
  /* unregister the device */
  cdev_del ( &c_dev );
  device_destroy (cl, devnum);
  class_destroy  (cl);
  printk(KERN_INFO MOD_STR"Device %s unregistered\n", "/dev/"GPIO_DEV_NAME);
}


/****************************/
/* Character device methods */
/****************************/
static int device_open (struct inode *inode, struct file *file) {
  open_count++;
  return 0;
}

static int device_release(struct inode *inode, struct file *file) {
  open_count--;
  if (open_count == 0) {
    _release_all_irqs();
  }
  return 0;
}

static ssize_t device_read(struct file *filp, char *buff,
                           size_t len, loff_t *off) {
  gpio_irq = -1;
  // wait for interrupt to occur
  wait_event_interruptible(queue, gpio_irq != -1);
  // do the processing in user space...
  return gpio_irq;
}

static ssize_t device_write(struct file *filp, const char *buff,
                            size_t len, loff_t *off) {
  /* Generate a dummy interrupt. This
   * can be used to e.g. terminate the
   * irq handler in user space w/o
   * using a signal... */ 
  gpio_irq = -2;
  wake_up_interruptible(&queue);
  return 0;
}
                  
long device_ioctl(struct        file *file,
                  unsigned int  ioctl_num,   /* number and param for ioctl */
                  unsigned long ioctl_param) {

  u8 gpio_num = ioctl_param & 0x7f;

  switch(ioctl_num) {
    case IOCTL_GPIO_MODE:
      return _gpioMode(gpio_num, ioctl_param >> 8);
    case IOCTL_GPIO_READ:
      return _gpioRead(gpio_num);
    case IOCTL_GPIO_WRITE:
      return _gpioWrite(gpio_num, ioctl_param >> 8);
    case IOCTL_GPIO_TOGGLE:
      return _gpioToggle(gpio_num);
    case IOCTL_GPIO_ATTACH_IRQ:
      return _gpioAttachIrq(gpio_num, ioctl_param >> 8);
    case IOCTL_GPIO_DETACH_IRQ:
      return _gpioDetachIrq(gpio_num);
    case IOCTL_GPIO_ENABLE_IRQ:
      return _gpioEnableIrq(gpio_num);
    case IOCTL_GPIO_DISABLE_IRQ:
      return _gpioDisableIrq(gpio_num);
    case IOCTL_SET_DEBOUNCE:
      if (!(gpio_mode[gpio_num] & GPIO_REQUESTED)) return -EINVAL;
      return gpio_set_debounce(gpio_num, ioctl_param >> 8);
  }
  return 0;
}


/****************/
/* GPIO methods */
/****************/
static int _gpioMode(u8 gpio_num, u16 flags) {
  u8  gpio_bank = gpio_num >> 5;
  u32 gpio_mask = 1 << (gpio_num & 0x1f);

  int ret;
  u16 val;
  /* calculate the offset */
  u16 offset = _gpio_to_offset (gpio_num);
  if (!(gpio_mode[gpio_num] & GPIO_REQUESTED)) {
    if (offset < 0) return offset;
    /* Try to request the gpio ... */
    printk(KERN_INFO MOD_STR "Requesting GPIO #%i\n", gpio_num);
    ret = gpio_request(gpio_num, GPIO_DEV_NAME);
    if (ret < 0) {
      /* okay, gpio is in use :( ... We might only switch */
      /* on the receiver, if not already enabled          */
      if (flags == GPIO_INPUT) {
        /* is the receiver already switched on ? */
        ret = ioread32(ctrl_module_base + offset);
        if (!(ret & 0x20)) {
          printk(KERN_WARNING 
            MOD_STR "Enabling receiver on already used GPIO #%i\n", gpio_num);
          _ioset32 (0x20, ctrl_module_base + offset);
          gpio_mode[gpio_num] = flags;
          return 0;
        }
      } else {
        return ret;
      }
    }
    /* store mode for later usage */
    gpio_mode[gpio_num] = flags | GPIO_REQUESTED;
  }
   /* set modes in control module */
  val = 0xf; // Mode 7 -> GPIO OUTPUT, no pullup/down, fast 
  if (flags & GPIO_INPUT)    val |=  0x20;
  if (flags & GPIO_PULLDOWN) val ^=  0x08; // toggle
  if (flags & GPIO_PULLUP)   val ^=  0x18;
  if (flags & GPIO_SLOW)     val |=  0x40;
  if (flags & GPIO_FAST)     val &= ~0x40;
  iowrite32(val, ctrl_module_base + offset);
  printk(KERN_INFO MOD_STR "GPIO #%i set to mode 0x%02X\n", gpio_num, val);
  
  /* set IO mode in gpio bank */
  if (flags & GPIO_INPUT) {
    _ioset32  (gpio_mask, gpio_base[gpio_bank] + GPIO_OE);
  }
  if (flags & GPIO_OUTPUT) {
    _ioclear32(gpio_mask, gpio_base[gpio_bank] + GPIO_OE);
  }
  if (flags & GPIO_OUTPUT_OPEN_SOURCE) {
    iowrite32(gpio_mask, gpio_base[gpio_bank] + GPIO_SETDATAOUT);
  }
  if (flags & GPIO_OUTPUT_OPEN_DRAIN) {
    iowrite32(gpio_mask, gpio_base[gpio_bank] + GPIO_CLEARDATAOUT);
  }
  if (flags & GPIO_INIT_HIGH) {
    _gpioWrite(gpio_num, 1);
  }
  if (flags & GPIO_INIT_LOW) {
    _gpioWrite(gpio_num, 0);
  }
  return 0;
}

static int _gpioRead(u8 gpio_num) {
  u8  gpio_bank = gpio_num >> 5;
  u32 gpio_mask = 1 << (gpio_num & 0x1f);
  u32 val;

  if (gpio_mode[gpio_num] & GPIO_INPUT) {
    val = ioread32(gpio_base[gpio_bank] + GPIO_DATAIN) & gpio_mask;
  } else {
    val = ioread32(gpio_base[gpio_bank] + GPIO_DATAOUT) & gpio_mask;
  }
  return (val) ? 1 : 0;
}

static int _gpioWrite (u8 gpio_num, int value) {
  u8  gpio_bank = gpio_num >> 5;
  u32 gpio_mask = 1 << (gpio_num & 0x1f);
  u16 flags;

  if (!(gpio_mode[gpio_num] & GPIO_REQUESTED)) return -EPERM;
  flags = gpio_mode[gpio_num];
   if (value) {
     if (flags & GPIO_OUTPUT_OPEN_DRAIN) {
      _ioset32(gpio_mask, gpio_base[gpio_bank] + GPIO_OE); // Input
      return 0;
    } 
    if (flags & GPIO_OUTPUT_OPEN_SOURCE) {
      _ioclear32(gpio_mask, gpio_base[gpio_bank] + GPIO_OE); // Output
      return 0;
    } 
    iowrite32(gpio_mask, gpio_base[gpio_bank] + GPIO_SETDATAOUT);
  }
  else {
    if (flags & GPIO_OUTPUT_OPEN_DRAIN) {
      _ioclear32(gpio_mask, gpio_base[gpio_bank] + GPIO_OE); // Output
      return 0;
    } 
    if (flags & GPIO_OUTPUT_OPEN_SOURCE) {
      _ioset32(gpio_mask, gpio_base[gpio_bank] + GPIO_OE); // Input
      return 0;
    } 
    iowrite32(gpio_mask, gpio_base[gpio_bank] + GPIO_CLEARDATAOUT);
  }
  return 0;
}

static int _gpioToggle (u8 gpio_num) {
  u8  gpio_bank = gpio_num >> 5;
  u32 gpio_mask = 1 << (gpio_num & 0x1f);

  u32 val = ioread32(gpio_base[gpio_bank] + GPIO_DATAOUT) & gpio_mask;
  return _gpioWrite(gpio_num, !val);  
}

static int _gpioAttachIrq(u8 gpio_num, u16 flags) {
  u8  gpio_bank = gpio_num >> 5;
  u32 gpio_mask = 1 << (gpio_num & 0x1f);
  int irq, ret;

  /* request the irq and install handler */
  if (!irq_enabled[gpio_num]) {
    irq = gpio_to_irq(gpio_num);
    /* request irq and install handler */
    ret = request_any_context_irq (irq, _gpio_irq_handler, IRQF_SHARED, "gpio_bbb", &gpio_data);
    if (ret < 0) {
      printk(KERN_ERR MOD_STR"Failed to request IRQ %i (error %i)\n", irq, ret);
      return ret;
    }
    // Set IRQ type
    irq_set_irq_type(irq, IRQ_TYPE_NONE);
    irq_enabled[gpio_num] = irq;
    printk(KERN_INFO MOD_STR"Using IRQ #%i for GPIO #%i\n", irq, gpio_num);
  }
  /* configure the gpio irq triggers */
  _ioclear32(gpio_mask, gpio_base[gpio_bank] + GPIO_RISINGDETECT);
  _ioclear32(gpio_mask, gpio_base[gpio_bank] + GPIO_FALLINGDETECT);
  _ioclear32(gpio_mask, gpio_base[gpio_bank] + GPIO_LEVELDETECT1);
  _ioclear32(gpio_mask, gpio_base[gpio_bank] + GPIO_LEVELDETECT0);
  if (flags & GPIO_RISING)
    _ioset32 (gpio_mask, gpio_base[gpio_bank] + GPIO_RISINGDETECT);
  if (flags & GPIO_FALLING)
    _ioset32 (gpio_mask, gpio_base[gpio_bank] + GPIO_FALLINGDETECT);
  if (flags & GPIO_LEVEL_HIGH)
    _ioset32 (gpio_mask, gpio_base[gpio_bank] + GPIO_LEVELDETECT1);
  if (flags & GPIO_LEVEL_LOW)
    _ioset32 (gpio_mask, gpio_base[gpio_bank] + GPIO_LEVELDETECT0);
  return 0;
}

static int _gpioDetachIrq(u8 gpio_num) {
  u8  gpio_bank = gpio_num >> 5;
  u32 gpio_mask = 1 << (gpio_num & 0x1f);

  if (!irq_enabled[gpio_num]) return -EINVAL;
  /* diable and clear the gpio irq */
  iowrite32(gpio_mask, gpio_base[gpio_bank] + GPIO_IRQSTATUS_CLR_0);
  iowrite32(gpio_mask, gpio_base[gpio_bank] + GPIO_IRQSTATUS_0);
  /* release the irq */
  _release_irq (gpio_num);
  return 0;
}

static int _gpioEnableIrq(u8 gpio_num) {
  u8  gpio_bank = gpio_num >> 5;
  u32 gpio_mask = 1 << (gpio_num & 0x1f);

  if (!irq_enabled[gpio_num]) return -EINVAL;
  /* clear and re-enable irqs */
  iowrite32(gpio_mask, gpio_base[gpio_bank] + GPIO_IRQSTATUS_0);
  iowrite32(gpio_mask, gpio_base[gpio_bank] + GPIO_IRQSTATUS_SET_0);
  return 0;
}

static int _gpioDisableIrq(u8 gpio_num) {
  u8  gpio_bank = gpio_num >> 5;
  u32 gpio_mask = 1 << (gpio_num & 0x1f);

  if (!irq_enabled[gpio_num]) return -EINVAL;
  iowrite32(gpio_mask, gpio_base[gpio_bank] + GPIO_IRQSTATUS_CLR_0);
  iowrite32(gpio_mask, gpio_base[gpio_bank] + GPIO_IRQSTATUS_0);
  return 0;
}


/*******************/
/* Utility methods */
/*******************/
static void _ioset32(u32 v, void __iomem *addr) {
  u32 tmp;
  tmp = ioread32(addr);
  tmp |= v;
  iowrite32(tmp, addr);
}

static void _ioclear32(u32 v, void __iomem *addr) {
  u32 tmp;
  tmp = ioread32(addr);
  tmp &= ~v;
  iowrite32(tmp, addr);
}

static int _map_memory(void) {
  int i;
  ctrl_module_base = ioremap(CTRL_MODULE_ADDR, CTRL_MODULE_LEN);
  if(!ctrl_module_base) {
    printk (KERN_ALERT MOD_STR"Failed to map memory for CTRL_MODULE.%c\n", 0x20);
    return -EPERM;
  }
  for (i=0; i < 4; ++i) {
    gpio_base[i] = ioremap(GPIO_BANK_ADDR[i], GPIO_BANK_LEN);
    if (!gpio_base[i]) {
      printk (KERN_ALERT MOD_STR"Failed to map memory for GPIO bank %d.\n", i);
      iounmap(ctrl_module_base);
      for (--i; i >= 0; --i) iounmap(gpio_base[i]);
      return -EPERM;
    }
  }
  return 0;
}

static void _unmap_memory(void) {
  int i;
  iounmap (ctrl_module_base);
  for(i=0; i < 4; ++i) iounmap (gpio_base[i]);
}

static u16 _gpio_to_offset(u8 gpio_num) {
  u16 offset;
  u8  entry = gpio_num | ENABLE;
  for (offset = 0; offset < GPIO_COUNT; ++offset) {
    if (gpio_data[offset] == entry)
      break;
  }
  if (offset == GPIO_COUNT) return -EINVAL;
  offset *= 4;
  offset += 0x800;
  return offset;
}

static u8 _irq_to_gpio(int irq) {
  u8 i;
  for (i=0; i < GPIO_COUNT; ++i) {
    if (irq_enabled[i] == irq) break;
  }
  return (i==GPIO_COUNT) ? -1 : i;
}

static void _release_irq(u8 gpio_num) {
  u8  gpio_bank = gpio_num >> 5;
  u32 gpio_mask = 1 << (gpio_num & 0x1f);
  u32 offset;
  if (irq_enabled[gpio_num]) {
    printk (KERN_INFO MOD_STR "Releasing IRQ #%i\n", irq_enabled[gpio_num]);
    free_irq (irq_enabled[gpio_num], &gpio_data);
    irq_enabled[gpio_num] = 0;
    if (!(gpio_mode[gpio_num] & GPIO_REQUESTED)) {
      /* the gpio was not requested, and the receiver     */
      /* was not enabled, when getting the irq. Since     */
      /* free_irq is enabling the receiver automatically, */
      /* switch it off again...                           */
      offset = _gpio_to_offset(gpio_num);
      if (offset >= 0) {
        /* disable receiver */
        _ioclear32(0x20, ctrl_module_base + offset);
        /* re-enable output */
        _ioclear32(gpio_mask, gpio_base[gpio_bank] + GPIO_OE);
      }
    }
  }
}

static void _release_all_irqs(void) {
  int i;
  for (i=0; i < GPIO_COUNT; ++i) {
    _release_irq (i);
    if (gpio_mode[i] & GPIO_REQUESTED) {
      printk(KERN_INFO MOD_STR "Freeing GPIO #%i\n", i);
      gpio_free(i);
      pinctrl_free_gpio(i);
    }
    gpio_mode[i] = 0;
  }
}

/*********************/
/* interrupt handler */
/*********************/
irqreturn_t _gpio_irq_handler(int irq, void *dev_id) {
  int gpio_num;
  // Check dev_id
  if (dev_id != (void *)&gpio_data) {
    return IRQ_NONE;
  }
  // Get gpio number from irq
  gpio_num = _irq_to_gpio(irq);
  if (gpio_num >= 0) {
    gpio_irq = gpio_num;
    wake_up_interruptible(&queue);
  }
  return IRQ_HANDLED;
}

