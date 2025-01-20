cmake_minimum_required(VERSION 3.16)

set(FatFs_TARGET FatFs_${PROJECT_NAME})

add_library(${FatFs_TARGET}
        ff.cpp
        ffsystem.cpp
        ffunicode.cpp
)

target_compile_options(${FatFs_TARGET}
        PRIVATE -Ofast)

target_include_directories(${FatFs_TARGET}
        PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE ${YAHAL_DIR}/include/interface
)
