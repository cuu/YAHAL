cmake_minimum_required(VERSION 3.16)

if (NOT TARGET yahal_list_guard)
add_library(yahal_list_guard INTERFACE)

include(cmake/YAHAL_init.cmake)

project(YAHAL C CXX ASM)

#if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
#    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
#endif()

#set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

# Initialize the SDK

YAHAL_init()

#include(example_auto_set_url.cmake)

file(GLOB         DRIVER_SRC   src/driver/*.cpp)
file(GLOB         PLATFORM_SRC src/platform/msp432/*.cpp)
file(GLOB_RECURSE DSP_SRC      src/platform/msp432/DSP/*.c)
file(GLOB         FATFS_SRC    src/FatFs/*.cpp)
file(GLOB         TASK_SRC     src/task/*.cpp)


add_library(YAHAL
    ${DRIVER_SRC}
    ${PLATFORM_SRC}
    ${DSP_SRC}
    ${FATFS_SRC}
    ${TASK_SRC}
)

target_include_directories(YAHAL PUBLIC
    src/platform/msp432
    src/platform/msp432/DSP/Include
    include/interface
    include/platform/msp432
    include/platform/msp432/CMSIS
    src/driver
    src/util
    src/task
)

# pull in common dependencies
#target_link_libraries(blink pico_stdlib)

# create map/bin/hex file etc.
#pico_add_extra_outputs(blink)

# add url via pico_set_program_url
#example_auto_set_url(blink)

#add_compile_options(-Wall
#        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
#        -Wno-unused-function # we have some for the docs that aren't called
#        -Wno-maybe-uninitialized
#        )

endif()
