##############################
# Toolchain file for GCC ARM #
##############################

message("Using toolchain ARM GCC")

# Check if a specific toolchain should be used
if (DEFINED ENV{ARM_TOOLCHAIN_PATH} AND (NOT ARM_TOOLCHAIN_PATH))
    set(ARM_TOOLCHAIN_PATH $ENV{ARM_TOOLCHAIN_PATH}/)
    message("Using ARM_TOOLCHAIN_PATH from environment ('${ARM_TOOLCHAIN_PATH}'")
endif()

# Set cmake compiler tools
set(CMAKE_SYSTEM_NAME         Generic)
set(CMAKE_SYSTEM_PROCESSOR    arm)
set(TARGET_TRIPLET            arm-none-eabi-)

set(CMAKE_AR                  ${ARM_TOOLCHAIN_PATH}${TARGET_TRIPLET}ar${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_ASM_COMPILER        ${ARM_TOOLCHAIN_PATH}${TARGET_TRIPLET}gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_C_COMPILER          ${ARM_TOOLCHAIN_PATH}${TARGET_TRIPLET}gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_CXX_COMPILER        ${ARM_TOOLCHAIN_PATH}${TARGET_TRIPLET}g++${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_LINKER              ${ARM_TOOLCHAIN_PATH}${TARGET_TRIPLET}ld${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_OBJCOPY             ${ARM_TOOLCHAIN_PATH}${TARGET_TRIPLET}objcopy${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_RANLIB              ${ARM_TOOLCHAIN_PATH}${TARGET_TRIPLET}ranlib${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_SIZE                ${ARM_TOOLCHAIN_PATH}${TARGET_TRIPLET}size${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_STRIP               ${ARM_TOOLCHAIN_PATH}${TARGET_TRIPLET}strip${CMAKE_EXECUTABLE_SUFFIX})

# Without that flag CMake is not able to pass test compilation check
set(CMAKE_TRY_COMPILE_TARGET_TYPE  STATIC_LIBRARY)

# Set generic compiler options
set(ARM_GCC_COMMON_FLAGS  "-ffunction-sections -fdata-sections \
                           -fno-unwind-tables  -fno-asynchronous-unwind-tables \
                           -fno-strict-aliasing -Wall -Wextra")
set(ARM_GCC_DEBUG_FLAGS   "-O0 -DDEBUG -g -gdwarf-3 -gstrict-dwarf")
set(ARM_GCC_RELEASE_FLAGS "-O3 -DNDEBUG")
set(ARM_GCC_LINK_FLAGS    "-Wl,--no-warn-rwx-segment -Wl,--gc-sections,-Map,mapfile,-print-memory-usage --specs=nosys.specs")

# Copy the flags to the relevant cmake variables for all languages
foreach(LANG IN ITEMS C CXX ASM)
    set(CMAKE_${LANG}_FLAGS_INIT         "${ARM_GCC_COMMON_FLAGS}")
    set(CMAKE_${LANG}_FLAGS_DEBUG_INIT   "${ARM_GCC_DEBUG_FLAGS}")
    set(CMAKE_${LANG}_FLAGS_RELEASE_INIT "${ARM_GCC_RELEASE_FLAGS}")
    set(CMAKE_${LANG}_LINK_FLAGS         "${ARM_GCC_LINK_FLAGS}")
endforeach()

# Add specific C++ flags
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT} -fno-exceptions -fno-rtti")

# Set language standards
set(CMAKE_C_STANDARD   11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

