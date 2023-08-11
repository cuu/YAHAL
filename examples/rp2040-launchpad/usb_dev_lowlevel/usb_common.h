
#ifndef _USB_COMMON_H_
#define _USB_COMMON_H_

#include <stdint.h>

namespace USB {

    ///////////////
    // Setup packet
    ///////////////
    enum class bRequest_t : uint8_t  {
        REQ_GET_STATUS          = 0,
        REQ_CLEAR_FEATURE       = 1,
        REQ_SET_FEATURE         = 3,
        REQ_SET_ADDRESS         = 5,
        REQ_GET_DESCRIPTOR      = 6,
        REQ_SET_DESCRIPTOR      = 7,
        REQ_GET_CONFIGURATION   = 8,
        REQ_SET_CONFIGURATION   = 9,
        REQ_GET_INTERFACE       = 10,
        REQ_SET_INTERFACE       = 11,
        REQ_SYNCH_FRAME         = 12
    };

    enum class direction_t : uint8_t {
        DIR_OUT                 = 0,
        DIR_IN                  = 1
    };

    enum class type_t : uint8_t {
        TYPE_STANDARD           = 0,
        TYPE_CLASS              = 1,
        TYPE_VENDOR             = 2
    };

    enum class recipient_t : uint8_t {
        REC_DEVICE              = 0,
        REC_INTERFACE           = 1,
        REC_ENDPOINT            = 2
    };

    union bmRequestType_t {
        struct __attribute__((__packed__)) {
            recipient_t recipient : 5;
            type_t      type      : 2;
            direction_t direction : 1;
        };
        uint8_t val;
    };

    struct __attribute__((__packed__)) setup_packet_t {
        bmRequestType_t     bmRequestType;
        bRequest_t          bRequest;
        uint16_t            wValue;
        uint16_t            wIndex;
        uint16_t            wLength;
    };
    static_assert(sizeof(setup_packet_t) == 8);

    ////////////////////////
    // USB Device Descriptor
    ////////////////////////
    enum class bDescriptorType_t : uint8_t {
        DESC_DEVICE                = 1,
        DESC_CONFIGURATION         = 2,
        DESC_STRING                = 3,
        DESC_INTERFACE             = 4,
        DESC_ENDPOINT              = 5,
        DESC_DEVICE_QUALIFIER      = 6,
        DESC_OTHER_SPEED_CONFIG    = 7,
        DESC_INTERFACE_POWER       = 8,
        DESC_OTG                   = 9,
        DESC_DEBUG                 = 10,
        DESC_INTERFACE_ASSOCIATION = 11
    };

    enum class bDeviceClass_t : uint8_t {
        CLASS_UNSPECIFIED          = 0,
        CLASS_AUDIO                = 1,
        CLASS_CDC                  = 2,
        CLASS_HID                  = 3,
        CLASS_PHYSICAL             = 5,
        CLASS_IMAGE                = 6,
        CLASS_PRINTER              = 7,
        CLASS_MSC                  = 8,
        CLASS_HUB                  = 9,
        CLASS_CDC_DATA             = 10,
        CLASS_SMART_CARD           = 11,
        CLASS_CONTENT_SECURITY     = 13,
        CLASS_VIDEO                = 14,
        CLASS_PERSONAL_HEALTHCARE  = 15,
        CLASS_AUDIO_VIDEO          = 16,
        CLASS_APPLICATION_SPECIFIC = 0xFE,
        CLASS_VENDOR_SPECIFIC      = 0xFF
    };

    // USB Device Descriptor
    struct __attribute__((__packed__)) device_descriptor_t {
        uint8_t             bLength;            // Size of this descriptor in bytes.
        bDescriptorType_t   bDescriptorType;    // DEVICE Descriptor Type.
        uint16_t            bcdUSB;             // USB Specification Release Number in BCD (i.e., 2.10 is 210H)
        bDeviceClass_t      bDeviceClass;       // Class code (assigned by the USB-IF). \li If this field is reset to zero, each
        uint8_t             bDeviceSubClass;    // Subclass code (assigned by the USB-IF). These codes are qualified by the value
        uint8_t             bDeviceProtocol;    // Protocol code (assigned by the USB-IF). These codes are qualified by the value
        uint8_t             bMaxPacketSize0;    // Maximum packet size for endpoint zero (only 8, 16, 32, or 64 are valid). For H
        uint16_t            idVendor;           // Vendor ID (assigned by the USB-IF).
        uint16_t            idProduct;          // Product ID (assigned by the manufacturer).
        uint16_t            bcdDevice;          // Device release number in binary-coded decimal.
        uint8_t             iManufacturer;      // Index of string descriptor describing manufacturer.
        uint8_t             iProduct;           // Index of string descriptor describing product.
        uint8_t             iSerialNumber;      // Index of string descriptor describing the device's serial number.
        uint8_t             bNumConfigurations; // Number of possible configurations.
    };
    static_assert(sizeof(USB::device_descriptor_t) == 18);

    ///////////////////////////////
    // USB Configuration Descriptor
    ///////////////////////////////
    union conf_attr_t {
        struct __attribute__((__packed__)) {
            uint8_t     reserved        : 5;
            uint8_t     remote_wakeup   : 1;
            uint8_t     self_powered    : 1;
            uint8_t     bus_powered     : 1;
        };
        uint8_t val;
    };

    struct __attribute__((__packed__)) configuration_descriptor_t {
        uint8_t             bLength;
        bDescriptorType_t   bDescriptorType;
        uint16_t            wTotalLength;
        uint8_t             bNumInterfaces;
        uint8_t             bConfigurationValue;
        uint8_t             iConfiguration;
        conf_attr_t         bmAttributes;
        uint8_t             bMaxPower;
    };
    static_assert(sizeof(configuration_descriptor_t) == 9);

    ///////////////////////////////////////
    // USB Interface Association Descriptor
    ///////////////////////////////////////
    struct __attribute__((__packed__)) interface_association_descriptor_t {
        uint8_t             bLength;
        bDescriptorType_t   bDescriptorType;
        uint8_t             bFirstInterface;
        uint8_t             bInterfaceCount;
        bDeviceClass_t      bFunctionClass;
        uint8_t             bFunctionSubClass;
        uint8_t             bFunctionProtocol;
        uint8_t             iFunction;
    };
    static_assert(sizeof(interface_association_descriptor_t) == 8);

    ///////////////////////////
    // USB Interface Descriptor
    ///////////////////////////
    struct __attribute__((__packed__)) interface_descriptor_t {
        uint8_t             bLength;
        bDescriptorType_t   bDescriptorType;
        uint8_t             bInterfaceNumber;
        uint8_t             bAlternateSetting;
        uint8_t             bNumEndpoints;
        bDeviceClass_t      bInterfaceClass;
        uint8_t             bInterfaceSubClass;
        uint8_t             bInterfaceProtocol;
        uint8_t             iInterface;
    };
    static_assert(sizeof(interface_descriptor_t) == 9);

    //////////////////////////
    // USB Endpoint Descriptor
    //////////////////////////
    enum class ep_attributes_t : uint8_t {
        TRANS_CONTROL       = 0,
        TRANS_ISOCHRONOUS   = 1,
        TRANS_BULK          = 2,
        TRANS_INTERRUPT     = 3
    };

    struct __attribute__((__packed__)) endpoint_descriptor_t {
        uint8_t             bLength;
        bDescriptorType_t   bDescriptorType;
        uint8_t             bEndpointAddress;
        ep_attributes_t     bmAttributes;
        uint16_t            wMaxPacketSize;
        uint8_t             bInterval;
    };
    static_assert(sizeof(endpoint_descriptor_t) == 7);

};

#endif
