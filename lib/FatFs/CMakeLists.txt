cmake_minimum_required(VERSION 3.16)

project(FatFs_${PROJECT_NAME})

add_compile_options(-Ofast)

add_library(${PROJECT_NAME}
    ff.cpp
    ffsystem.cpp
    ffunicode.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${YAHAL_DIR}/include/interface
)

