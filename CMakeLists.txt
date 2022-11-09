cmake_minimum_required(VERSION 3.16)

if (NOT TARGET yahal_list_guard)
add_library(yahal_list_guard INTERFACE)

include(cmake/YAHAL_init.cmake)

project(YAHAL C CXX ASM)

file(GLOB         DRIVER_SRC   src/driver/*.cpp)
file(GLOB         PLATFORM_SRC src/platform/msp432/*.cpp)
file(GLOB_RECURSE DSP_SRC      src/platform/msp432/DSP/*.c)
file(GLOB         FATFS_SRC    src/FatFs/*.cpp)
file(GLOB         TASK_SRC     src/task/*.cpp)
file(GLOB         UTIL_SRC     src/util/*.cpp)


add_library(YAHAL
    ${DRIVER_SRC}
    ${PLATFORM_SRC}
    ${DSP_SRC}
    ${FATFS_SRC}
    ${TASK_SRC}
    ${UTIL_SRC}
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

endif()

