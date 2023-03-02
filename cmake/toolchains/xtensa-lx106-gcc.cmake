#######################################
# Toolchain file for xtensa LX106 GCC #
#######################################

message("Using toolchain XTENSA LX106 GCC")

# Check if a specific toolchain should be used
if (DEFINED ENV{XTENSA_TOOLCHAIN_PATH} AND (NOT XTENSA_TOOLCHAIN_PATH))
    set(XTENSA_TOOLCHAIN_PATH $ENV{XTENSA_TOOLCHAIN_PATH})
    message("Using XTENSA_TOOLCHAIN_PATH from environment ('${XTENSA_TOOLCHAIN_PATH}'")
endif()

# Set cmake compiler tools
set(CMAKE_SYSTEM_NAME         Generic)
set(CMAKE_SYSTEM_PROCESSOR    arm)
set(TARGET_TRIPLET            xtensa-lx106-elf-)

set(CMAKE_AR                  ${XTENSA_TOOLCHAIN_PATH}${TARGET_TRIPLET}ar${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_ASM_COMPILER        ${XTENSA_TOOLCHAIN_PATH}${TARGET_TRIPLET}gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_C_COMPILER          ${XTENSA_TOOLCHAIN_PATH}${TARGET_TRIPLET}gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_CXX_COMPILER        ${XTENSA_TOOLCHAIN_PATH}${TARGET_TRIPLET}g++${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_LINKER              ${XTENSA_TOOLCHAIN_PATH}${TARGET_TRIPLET}ld${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_OBJCOPY             ${XTENSA_TOOLCHAIN_PATH}${TARGET_TRIPLET}objcopy${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_RANLIB              ${XTENSA_TOOLCHAIN_PATH}${TARGET_TRIPLET}ranlib${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_SIZE                ${XTENSA_TOOLCHAIN_PATH}${TARGET_TRIPLET}size${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_STRIP               ${XTENSA_TOOLCHAIN_PATH}${TARGET_TRIPLET}strip${CMAKE_EXECUTABLE_SUFFIX})

# Without that flag CMake is not able to pass test compilation check
set(CMAKE_TRY_COMPILE_TARGET_TYPE  STATIC_LIBRARY)

# Set generic compiler options
set(XTENSA_GCC_COMMON_FLAGS  "-ffunction-sections -fdata-sections -fno-unwind-tables")
set(XTENSA_GCC_COMMON_FLAGS  "${XTENSA_GCC_COMMON_FLAGS} -fno-asynchronous-unwind-tables -fno-strict-aliasing")
set(XTENSA_GCC_COMMON_FLAGS  "${XTENSA_GCC_COMMON_FLAGS} -Wall -Wextra")

set(XTENSA_GCC_DEBUG_FLAGS   "-O0 -g -gdwarf-3 -gstrict-dwarf -DDEBUG")
set(XTENSA_GCC_RELEASE_FLAGS "-O3 -g -gdwarf-3 -gstrict-dwarf")
set(XTENSA_GCC_LINK_FLAGS    "-Wl,--gc-sections,-Map,mapfile,-print-memory-usage --specs=nosys.specs --specs=nano.specs")

if (DEFINED YAHAL_USE_NANO_SPECS)
    set(XTENSA_GCC_LINK_FLAGS    "${XTENSA_GCC_LINK_FLAGS} --specs=nano.specs")
endif()

foreach(LANG IN ITEMS C CXX ASM)
    set(CMAKE_${LANG}_FLAGS_INIT         "${XTENSA_GCC_COMMON_FLAGS}")
    set(CMAKE_${LANG}_FLAGS_DEBUG_INIT   "${XTENSA_GCC_DEBUG_FLAGS}")
    set(CMAKE_${LANG}_FLAGS_RELEASE_INIT "${XTENSA_GCC_RELEASE_FLAGS}")
    set(CMAKE_${LANG}_LINK_FLAGS         "${XTENSA_GCC_LINK_FLAGS}")
endforeach()

# Special C++ flags
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT} -fno-exceptions -fno-rtti")

# Set language standards
set(CMAKE_C_STANDARD   11)
set(CMAKE_CXX_STANDARD 17)

# Set executable suffix
set(CMAKE_EXECUTABLE_SUFFIX .elf)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

