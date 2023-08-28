cmake_minimum_required(VERSION 3.16)

project(tinyUSB++_${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Ofast)

add_library(${PROJECT_NAME})

add_subdirectory(class)
add_subdirectory(drivers)
add_subdirectory(src)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${YAHAL_DIR}/include/MCU/rp2040
    PUBLIC ${YAHAL_DIR}/include/CPU/CMSIS
)
