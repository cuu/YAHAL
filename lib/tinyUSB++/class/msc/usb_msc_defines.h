//    _   _             _    _  _____ ____
//   | | (_)           | |  | |/ ____|  _ \   _     _
//   | |_ _ _ __  _   _| |  | | (___ | |_) |_| |_ _| |_
//   | __| | '_ \| | | | |  | |\___ \|  _ < _   _|_   _|
//   | |_| | | | | |_| | |__| |____) | |_) | |_|   |_|
//    \__|_|_| |_|\__, |\____/|_____/|____/
//                __/ |
//               |___/
//
// This file is part of tinyUSB++, C++ based and easy to
// use library for USB host/device functionality.
// (c) 2023 A. Terstegge  (Andreas.Terstegge@gmail.com)
//
#ifndef TUPP_USB_CDC_DEFINES_H_
#define TUPP_USB_CDC_DEFINES_H_

//////////////////////////////
// CDC class specific requests
//////////////////////////////
#define CDC_CS_REQUESTS \
    CDC_REQ_SEND_ENCAPSULATED_COMMAND   = 0x00,    \
    CDC_REQ_GET_ENCAPSULATED_RESPONSE   = 0x01,    \
    CDC_REQ_SET_COMM_FEATURE            = 0x02,    \
    CDC_REQ_GET_COMM_FEATURE            = 0x03,    \
    CDC_REQ_CLEAR_COMM_FEATURE          = 0x04,    \
                                                   \
    CDC_REQ_SET_AUX_LINE_STATE          = 0x10,    \
    CDC_REQ_SET_HOOK_STATE              = 0x11,    \
    CDC_REQ_PULSE_SETUP                 = 0x12,    \
    CDC_REQ_SEND_PULSE                  = 0x13,    \
    CDC_REQ_SET_PULSE_TIME              = 0x14,    \
    CDC_REQ_RING_AUX_JACK               = 0x15,    \
                                                   \
    CDC_REQ_SET_LINE_CODING             = 0x20,    \
    CDC_REQ_GET_LINE_CODING             = 0x21,    \
    CDC_REQ_SET_CONTROL_LINE_STATE      = 0x22,    \
    CDC_REQ_SEND_BREAK                  = 0x23,    \
                                                   \
    CDC_REQ_SET_RINGER_PARMS            = 0x30,    \
    CDC_REQ_GET_RINGER_PARMS            = 0x31,    \
    CDC_REQ_SET_OPERATION_PARMS         = 0x32,    \
    CDC_REQ_GET_OPERATION_PARMS         = 0x33,    \
    CDC_REQ_SET_LINE_PARMS              = 0x34,    \
    CDC_REQ_GET_LINE_PARMS              = 0x35,    \
    CDC_REQ_DIAL_DIGITS                 = 0x36,    \
    CDC_REQ_SET_UNIT_PARAMETER          = 0x37,    \
    CDC_REQ_GET_UNIT_PARAMETER          = 0x38,    \
    CDC_REQ_CLEAR_UNIT_PARAMETER        = 0x39,    \
    CDC_REQ_GET_PROFILE                 = 0x3A,

////////////////////////////////////
// CDC class specific device classes
////////////////////////////////////
#define CDC_CS_DEVICE_CLASSES \
    CLASS_CDC       = 0x02,

///////////////////////////////////////
// CDC class specific interface classes
///////////////////////////////////////
#define CDC_CS_INTERFACE_CLASSES \
    CLASS_CDC       = 0x02,      \
    CLASS_CDC_DATA  = 0x0a,

//////////////////////////////////////////
// CDC class specific interface subclasses
//////////////////////////////////////////
#define CDC_CS_INTERFACE_SUBCLASSES \
    CLASS_DIRECT_LINE_CONTROL_MODEL         = 1,    \
    CLASS_ABSTRACT_CONTROL_MODEL            = 2,    \
    CLASS_TELEPHONE_CONTROL_MODEL           = 3,    \
    CLASS_MULTICHANNEL_CONTROL_MODEL        = 4,    \
    CLASS_CAPI_CONTROL_MODEL                = 5,    \
    CLASS_ETHERNET_CONTROL_MODEL            = 6,    \
    CLASS_ATM_NETWORKING_CONTROL_MODEL      = 7,    \
    CLASS_WIRELESS_HANDSET_CONTROL_MODEL    = 8,    \
    CLASS_DEVICE_MANAGEMENT                 = 9,    \
    CLASS_MOBILE_DIRECT_LINE_MODEL          = 10,   \
    CLASS_OBEX                              = 11,   \
    CLASS_ETHERNET_EMULATION_MODEL          = 12,   \
    CLASS_NETWORK_CONTROL_MODEL             = 13,

#define CDC_CS_PROTOCOLS \
    CDC_COMM_PROTOCOL_AT                        = 0x01, \
    CDC_COMM_PROTOCOL_AT_PCCA_101               = 0x02, \
    CDC_COMM_PROTOCOL_AT_PCCA_101_AND_ANNEXO    = 0x03, \
    CDC_COMM_PROTOCOL_AT_GSM_707                = 0x04, \
    CDC_COMM_PROTOCOL_AT_3GPP_27007             = 0x05, \
    CDC_COMM_PROTOCOL_AT_CDMA                   = 0x06, \
    CDC_COMM_PROTOCOL_ETHERNET_EMULATION_MODEL  = 0x07, \
                                                        \
    CDC_DATA_PROTOCOL_ISDN_BRI                  = 0x30, \
    CDC_DATA_PROTOCOL_HDLC                      = 0x31, \
    CDC_DATA_PROTOCOL_TRANSPARENT               = 0x32, \
    CDC_DATA_PROTOCOL_Q921_MANAGEMENT           = 0x50, \
    CDC_DATA_PROTOCOL_Q921_DATA_LINK            = 0x51, \
    CDC_DATA_PROTOCOL_Q921_TEI_MULTIPLEXOR      = 0x52, \
    CDC_DATA_PROTOCOL_V42BIS_DATA_COMPRESSION   = 0x90, \
    CDC_DATA_PROTOCOL_EURO_ISDN                 = 0x91, \
    CDC_DATA_PROTOCOL_V24_RATE_ADAPTION_TO_ISDN = 0x92, \
    CDC_DATA_PROTOCOL_CAPI_COMMAND              = 0x93, \
    CDC_DATA_PROTOCOL_HOST_BASED_DRIVER         = 0xFD,

#endif  // TUPP_USB_CDC_DEFINES_H_
