cmake_minimum_required(VERSION 3.16)

project(uGUI_${PROJECT_NAME})

add_compile_options(-Ofast)

file(GLOB_RECURSE UGUI_FONTS fonts/*.cpp)

add_library(${PROJECT_NAME}
    uGUI.cpp
    ${UGUI_FONTS}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC fonts
    PUBLIC ${YAHAL_DIR}/include/interface
    PUBLIC ${YAHAL_DIR}/src/util
)
