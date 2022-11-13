cmake_minimum_required(VERSION 3.16)

if (NOT TARGET yahal_list_guard)
add_library(yahal_list_guard INTERFACE)

include(cmake/YAHAL_init.cmake)

project(YAHAL C CXX ASM)

file(GLOB         DRIVER_SRC   src/driver/*.cpp)
file(GLOB         PLATFORM_SRC src/platform/rp2040/*.cpp)
file(GLOB         FATFS_SRC    src/FatFs/*.cpp)
file(GLOB         TASK_SRC     src/task/*.cpp)
file(GLOB         UTIL_SRC     src/util/*.cpp)
file(GLOB_RECURSE UGUI_SRC     src/uGUI/*.cpp)

add_library(YAHAL
    ${DRIVER_SRC}
    ${PLATFORM_SRC}
    ${FATFS_SRC}
    ${TASK_SRC}
    ${UTIL_SRC}
    ${UGUI_SRC}
)

target_include_directories(YAHAL PUBLIC
    src/platform/rp2040
    include/interface
    include/platform/rp2040
    include/platform/rp2040/CMSIS
    src/driver
    src/FatFs
    src/util
    src/task
    src/uGUI
    src/uGUI/fonts
)

# Add ARM DSP as a separate library 
add_subdirectory(src/platform/msp432/DSP ARM_DSP)

# Add various tools
add_subdirectory(tools)

endif()

