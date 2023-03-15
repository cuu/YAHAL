# Finds (or builds) the elf2uf2 executable
#
# This will define the following variables
#
#    ELF2UF2_FOUND
#
# and the following imported targets
#
#     ELF2UF2
#

if (NOT ELF2UF2_FOUND)
    include(ExternalProject)

    # Location of tool source code
    set(ELF2UF2_SOURCE_DIR ${YAHAL_DIR}/tools/elf2uf2)

    # Location of tool binary
    set(ELF2UF2_BINARY_DIR ${CMAKE_BINARY_DIR}/elf2uf2)

    # The tool binary
    set(ELF2UF2_EXECUTABLE ${ELF2UF2_BINARY_DIR}/elf2uf2)

    # Target for ExternalProject
    set(ELF2UF2_BUILD_TARGET ELF2UF2_BUILD)
    # Target for executable
    set(ELF2UF2_TARGET       ELF2UF2)

    # Check if ExternalProject was already added
    if (NOT TARGET ${ELF2UF2_BUILD_TARGET})
        message("ELF2UF2 will need to be built")

        ExternalProject_Add(${ELF2UF2_BUILD_TARGET}
            PREFIX          elf2uf2
            SOURCE_DIR      ${ELF2UF2_SOURCE_DIR}
            BINARY_DIR      ${ELF2UF2_BINARY_DIR}
            BUILD_ALWAYS    1 # force dependency checking
            INSTALL_COMMAND ""
        )
    endif()

    if(NOT TARGET ${ELF2UF2_TARGET})
        add_executable(${ELF2UF2_TARGET} IMPORTED)
    endif()

    set_property(TARGET ${ELF2UF2_TARGET} PROPERTY IMPORTED_LOCATION
        ${ELF2UF2_EXECUTABLE})

    add_dependencies(${ELF2UF2_TARGET} ${ELF2UF2_BUILD_TARGET})

    set(ELF2UF2_FOUND 1)
endif()
