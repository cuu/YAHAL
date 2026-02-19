target_sources(retro_PDP8_Focal PRIVATE
    main.cpp
    CPU.cpp
    Devices.cpp
    Device_TTI.cpp
    Device_TTO.cpp
    Memory.cpp
    Focal69.cpp
)

target_include_directories(retro_PDP8_Focal PRIVATE
    .
)

