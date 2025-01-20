cmake_minimum_required(VERSION 3.16)

set(uGUI_TARGET uGUI_${PROJECT_NAME})
file(GLOB_RECURSE UGUI_FONTS fonts/*.cpp)

add_library(${uGUI_TARGET}
        uGUI.cpp
        ${UGUI_FONTS}
)

target_compile_options(${uGUI_TARGET} PRIVATE -Ofast)

target_include_directories(${uGUI_TARGET}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC fonts
        PRIVATE ${YAHAL_DIR}/include/interface
        PRIVATE ${YAHAL_DIR}/src/util
)
