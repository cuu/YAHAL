cmake_minimum_required(VERSION 3.16)

# Set the target board and locate YAHAL
set(YAHAL_BOARD "rp2350-launchpad")
include(YAHAL_import.cmake)

project(floppy_adapter CXX ASM)

add_executable(floppy_adapter
    floppy_adapter.cpp
    MFM_reader.cpp
    MFM_reader_states.cpp
)

target_compile_options(floppy_adapter
    PRIVATE -Ofast
)

# Add YAHAL to target
yahal_add_me(floppy_adapter)
yahal_add_library(floppy_adapter tinyUSB++)

yahal_add_custom_targets(floppy_adapter)
yahal_add_extra_outputs(floppy_adapter)

# generate PIO header files
generate_pio_header(
        floppy_adapter
        ${CMAKE_CURRENT_LIST_DIR}/pio/mfm.pio
        OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/pio)

target_compile_options(YAHAL_floppy_adapter
        PRIVATE -Ofast
)
