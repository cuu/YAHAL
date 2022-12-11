cmake_minimum_required(VERSION 3.16)

project(uGUI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Ofast")

file(GLOB_RECURSE UGUI_FONTS fonts/*.cpp)

add_library(uGUI
    uGUI.cpp
    ${UGUI_FONTS}
)

target_include_directories(uGUI
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC fonts
    PUBLIC ${YAHAL_DIR}/include/interface
    PUBLIC ${YAHAL_DIR}/src/util
)
