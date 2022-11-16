cmake_minimum_required(VERSION 3.16)

if (NOT TARGET yahal_list_guard)
add_library(yahal_list_guard INTERFACE)

include(cmake/YAHAL_init.cmake)

project(YAHAL C CXX ASM)

file(GLOB         DRIVER_SRC   src/driver/*.cpp)
file(GLOB         MCU_SRC      src/MCU/${YAHAL_MCU}/*.cpp)
file(GLOB         FATFS_SRC    src/FatFs/*.cpp)
file(GLOB         TASK_SRC     src/task/*.cpp)
file(GLOB         UTIL_SRC     src/util/*.cpp)
file(GLOB_RECURSE UGUI_SRC     src/uGUI/*.cpp)

add_library(YAHAL
    ${DRIVER_SRC}
    ${MCU_SRC}
    ${FATFS_SRC}
    ${TASK_SRC}
    ${UTIL_SRC}
    ${UGUI_SRC}
)

target_include_directories(YAHAL PUBLIC
    include/board/${YAHAL_BOARD}
    include/MCU/${YAHAL_MCU}
    include/CPU/${YAHAL_CPU}
    src/MCU/${YAHAL_MCU}
    include/interface
    src/driver
    src/FatFs
    src/util
    src/task
    src/uGUI
    src/uGUI/fonts
)

# Add ARM DSP as a separate library 
# add_subdirectory(src/platform/msp432/DSP ARM_DSP)

# Add various tools
add_subdirectory(tools)

endif()

