cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2350-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(usb_msc_psram)

add_executable(usb_msc_psram
        usb_msc_psram.cpp
        gen/image.cpp
)

# Switch on compiler optimizations
target_compile_options(usb_msc_psram
        PRIVATE -Ofast
)

# Add YAHAL to target
yahal_add_me(usb_msc_psram)
yahal_add_library(usb_msc_psram tinyUSB++)
yahal_add_library(usb_msc_psram unzipLIB)

# Generate cpp-file from zipped disc image
file_to_cpp(usb_msc_psram
        image_zip/image.zip
        OUTPUT_DIR gen
)

yahal_add_custom_targets(usb_msc_psram)
yahal_add_extra_outputs(usb_msc_psram)

