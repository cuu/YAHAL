
target_sources(retro_PDP8_Focal PRIVATE
    retro_PDP8_Focal.cpp
    Memory.cpp
    Focal69.cpp
    CPU.cpp
    Devices.cpp
    Device_TTI.cpp
    Device_TTO.cpp
)

target_include_directories(retro_PDP8_Focal PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

