# Finds (or builds) the pioasm executable
#
# This will define the following variables
#
#    PIOASM_FOUND
#
# and the following imported targets
#
#     PIOASM
#

if (NOT PIOASM_FOUND)
    include(ExternalProject)

    # Location of tool source code
    set(PIOASM_SOURCE_DIR ${YAHAL_DIR}/tools/pioasm)

    # Location of tool binary
    set(PIOASM_BINARY_DIR ${CMAKE_BINARY_DIR}/pioasm)

    # The tool binary
    set(PIOASM_EXECUTABLE ${PIOASM_BINARY_DIR}/pioasm)

    # Target for ExternalProject
    set(PIOASM_BUILD_TARGET PIOASM_BUILD)
    # Target for executable
    set(PIOASM_TARGET       PIOASM)

    # Check if ExternalProject was already added
    if (NOT TARGET ${PIOASM_BUILD_TARGET})
        message("PIOASM will need to be built")

        ExternalProject_Add(${PIOASM_BUILD_TARGET}
            PREFIX          pioasm 
            SOURCE_DIR      ${PIOASM_SOURCE_DIR}
            BINARY_DIR      ${PIOASM_BINARY_DIR}
            BUILD_ALWAYS    1 # force dependency checking
            INSTALL_COMMAND ""
        )
    endif()

    if(NOT TARGET ${PIOASM_TARGET})
        add_executable(${PIOASM_TARGET} IMPORTED)
    endif()

    set_property(TARGET ${PIOASM_TARGET} PROPERTY IMPORTED_LOCATION
        ${PIOASM_EXECUTABLE})

    add_dependencies(${PIOASM_TARGET} ${PIOASM_BUILD_TARGET})

    set(PIOASM_FOUND 1)
endif()
