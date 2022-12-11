cmake_minimum_required(VERSION 3.16)

if (NOT TARGET yahal_list_guard)
add_library(yahal_list_guard INTERFACE)

include(cmake/YAHAL_init.cmake)

project(YAHAL)

file(GLOB         BOARD_SRC    src/board/*.cpp src/board/${YAHAL_BOARD}/*.cpp)
file(GLOB         DRIVER_SRC   src/driver/*.cpp)
file(GLOB         MCU_SRC      src/MCU/${YAHAL_MCU}/*.cpp)
file(GLOB         TASK_SRC     src/task/*.cpp)
file(GLOB         UTIL_SRC     src/util/*.cpp)

add_library(YAHAL
    ${BOARD_SRC}
    ${DRIVER_SRC}
    ${MCU_SRC}
    ${TASK_SRC}
    ${UTIL_SRC}
)

target_include_directories(YAHAL PUBLIC
    include/interface
    src/board
    src/board/${YAHAL_BOARD}
    src/driver
    include/CPU/${YAHAL_CPU}
    src/MCU/${YAHAL_MCU}
    include/MCU/${YAHAL_MCU}
    src/task
    src/util
)

# Add various tools
add_subdirectory(tools)

endif()
