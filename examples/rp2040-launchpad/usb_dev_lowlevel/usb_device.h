#ifndef _USB_DEVICE_H_
#define _USB_DEVICE_H_

class usb_configuration;
#include "usb_common.h"
#include <array>

class usb_device {
public:
    usb_device();

    // Methods to modify the device descriptor
    inline void set_bcdUSB(uint16_t n) {
        descriptor.bcdUSB = n;
    }
    inline void set_bDeviceClass(USB::bDeviceClass_t n) {
        descriptor.bDeviceClass = n;
    }
    inline void set_bDeviceSubClass(uint8_t n) {
        descriptor.bDeviceSubClass = n;
    }
    inline void set_bDeviceProtocol(uint8_t n) {
        descriptor.bDeviceProtocol = n;
    }
    inline void set_bMaxPacketSize0(uint8_t n) {
        descriptor.bMaxPacketSize0 = n;
    }
    inline void set_idVendor(uint16_t n) {
        descriptor.idVendor = n;
    }
    inline void set_idProduct(uint16_t n) {
        descriptor.idProduct = n;
    }
    inline void set_bcdDevice(uint16_t n) {
        descriptor.bcdDevice = n;
    }
    void set_Manufacturer(const char *);
    void set_Product(const char *);
    void set_SerialNumber(const char *);

    // Add a new configuration to this device
    void add_configuration(usb_configuration & config);

    // Find a configuration based on its bConfigurationValue
    // Return nullptr if not found
    usb_configuration * find_configuration(uint8_t i);

    // The device descriptor
    USB::device_descriptor_t descriptor;

    // Configurations
    std::array<usb_configuration *, 5> configurations;
};

#endif // _USB_DEVICE_H_
