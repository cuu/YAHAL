cmake_minimum_required(VERSION 3.16)

add_subdirectory(${YAHAL_BOARD})

target_sources(${YAHAL_TARGET} PRIVATE
    boostxl_eduMKII_base.cpp
)

target_include_directories(${YAHAL_TARGET} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

