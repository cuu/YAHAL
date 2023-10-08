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
#ifndef TUPP_SCSI_COMMON_H_
#define TUPP_SCSI_COMMON_H_

#include <cstdint>

namespace SCSI {

    ///////////////////////////
    // SCSI command op codes //
    ///////////////////////////
    enum class scsi_cmd_t : uint8_t  {
        TEST_UNIT_READY                 = 0x00,
        REQUEST_SENSE                   = 0x03,
        INQUIRY                         = 0x12,
        MODE_SELECT_6                   = 0x15,
        MODE_SENSE_6                    = 0x1A,
        START_STOP_UNIT                 = 0x1B,
        PREVENT_ALLOW_MEDIUM_REMOVAL    = 0x1E,
        READ_FORMAT_CAPACITIES          = 0x23,
        READ_CAPACITY_10                = 0x25,
        READ_10                         = 0x28,
        WRITE_10                        = 0x2A
    };

    // TEST UNIT READY
    //////////////////
    struct __attribute__((__packed__)) test_unit_ready_t {
        scsi_cmd_t  cmd;
        uint8_t     reserved[4];
        uint8_t     control;
    };
    static_assert(sizeof(test_unit_ready_t) == 6);

    // INQUIRY
    //////////
    struct __attribute__((__packed__)) inquiry_t {
        scsi_cmd_t  cmd;
        uint8_t     enable_vital_product_data   : 1;
        uint8_t     command_support_data        : 1;
        uint8_t                                 : 6;
        uint8_t     page_code;
        uint16_t    alloc_length;
        uint8_t     control;
    };
    static_assert(sizeof(inquiry_t) == 6);

    enum class peripheral_device_type_t : uint8_t  {
        SBC_4_DIRECT_ACCESS             = 0x00,
        SSC_3_SEQUENTIAL                = 0x01,
        SSC_PRINTER                     = 0x02,
        SPC_2_PROCESSOR                 = 0x03,
        SBC_WRITE_ONCE                  = 0x04,
        MMC_5_CD_DVD                    = 0x05,
        SBC_OPTICAL                     = 0x07,
        SMC_3_MEDIUM_CHANGE             = 0x08,
        SCC_2_STORAGE_ARRAY             = 0x0c,
        SES_ENCLOSURE_SERVICE           = 0x0d,
        RBC_DIRECT_ACCESS_SIMPLE        = 0x0e,
        OCRW_OPTICAL_CARD               = 0x0f,
        BCC_BRIDGE_CONTROLLER           = 0x10,
        OSD_OBJECT_STORE                = 0x11,
        ADC_2_AUTOMATION_DRIVE          = 0x12
    };

    enum class peripheral_qualifier_type_t : uint8_t  {
        DEVICE_CONNECTED_TO_LUN         = 0x00,
        DEVICE_NOT_CONNECTED_TO_LUN     = 0x01,
        DEVICE_NOT_SUPPORTED            = 0x03
    };

    enum class version_t : uint8_t  {
        NO_STANDARD                     = 0x00,
        STANDARD_SPC                    = 0x03,
        STANDARD_SPC_2                  = 0x04,
        STANDARD_SPC_3                  = 0x05,
        STANDARD_SPC_4                  = 0x06,
        STANDARD_SPC_5                  = 0x07
    };

    struct __attribute__((__packed__)) inquiry_response_t {
        peripheral_device_type_t    peripheral_device   : 5;
        peripheral_qualifier_type_t peripheral_qualifier: 3;

        uint8_t                             : 7;
        uint8_t removable_media             : 1;

        version_t version;

        uint8_t response_data_format        : 4;
        uint8_t hierarchical_support        : 1;
        uint8_t normal_aca_support          : 1;
        uint8_t                             : 2;

        uint8_t additional_length;

        uint8_t protect                     : 1;
        uint8_t                             : 2;
        uint8_t third_party_copy            : 1;
        uint8_t target_port_group_support   : 2;
        uint8_t access_controls_coordinator : 1;
        uint8_t scc_support                 : 1;

        uint8_t                             : 4;
        uint8_t multi_port                  : 1;
        uint8_t                             : 1;
        uint8_t enclosure_services          : 1;
        uint8_t                             : 1;

        uint8_t                            : 1;
        uint8_t command_queuing            : 1;
        uint8_t                            : 6;

        uint8_t vendor_id[8];
        uint8_t product_id[16];
        uint8_t product_rev[4];
    };

    // MODE SENSE 6
    ///////////////
    struct __attribute__((__packed__)) mode_sense_6_t {
        scsi_cmd_t  cmd;

        uint8_t                             : 3;
        uint8_t disable_block_descriptors   : 1;
        uint8_t                             : 4;

        uint8_t page_code                   : 6;
        uint8_t page_control                : 2;

        uint8_t subpage_code;
        uint8_t alloc_length;
        uint8_t control;
    };
    static_assert(sizeof(mode_sense_6_t) == 6);

    struct __attribute__((__packed__)) mode_sense_6_response_t {
        uint8_t mode_data_length;
        uint8_t medium_type;

        uint8_t                             : 4;
        uint8_t dpo_fua_support             : 1;
        uint8_t                             : 2;
        uint8_t write_protect               : 1;

        uint8_t block_descriptor_length;
    };
    static_assert(sizeof(mode_sense_6_response_t) == 4);


    // READ CAPACITY (10)
    /////////////////////
    struct __attribute__((__packed__)) read_capacity_10_t {
        scsi_cmd_t  cmd;
        uint8_t     reserved[8];
        uint8_t     control;
    };
    static_assert(sizeof(read_capacity_10_t) == 10);

    struct __attribute__((__packed__)) read_capacity_10_response_t {
        uint32_t    logical_block_address;
        uint32_t    block_length;
    };
    static_assert(sizeof(read_capacity_10_t) == 10);


    // READ FORMAT CAPACITY
    ///////////////////////
    struct __attribute__((__packed__)) read_format_capacity_10_t {
        scsi_cmd_t  cmd_code;
        uint8_t     reserved[6];
        uint16_t    alloc_length;
        uint8_t     control;
    };
    static_assert(sizeof(read_format_capacity_10_t) == 10);

    struct __attribute__((__packed__)) read_format_capacity_10_response_t {
        uint8_t     reserved[3];
        uint8_t     list_length; /// must be 8*n, length in bytes of formattable capacity descriptor followed it.

        uint32_t    block_num; /// Number of Logical Blocks
        uint8_t     descriptor_type; // 00: reserved, 01 unformatted media , 10 Formatted media, 11 No media present

        uint8_t     reserved2;
        uint16_t    block_size_u16;
    };
    static_assert(sizeof(read_format_capacity_10_t) == 10);

    // READ 10
    //////////
    struct __attribute__((__packed__)) read_10_t {
        scsi_cmd_t  cmd;
        uint8_t     reserved;
        uint32_t    logical_block_address;
        uint8_t     reserved2;
        uint16_t    transfer_length;
        uint8_t     control;
    };
    static_assert(sizeof(read_10_t) == 10);

    struct __attribute__((__packed__)) write_10_t {
        scsi_cmd_t  cmd;
        uint8_t     reserved;
        uint32_t    logical_block_address;
        uint8_t     reserved2;
        uint16_t    transfer_length;
        uint8_t     control;
    };
    static_assert(sizeof(write_10_t) == 10);

}   // namespace SCSI

#endif  // TUPP_SCSI_COMMON_H_
