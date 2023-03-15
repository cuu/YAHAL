# Finds (or builds) the FILE2CPP executable
#
# This will define the following variables
#
#    FILE2CPP_FOUND
#
# and the following imported targets
#
#     FILE2CPP
#

if (NOT FILE2CPP_FOUND)
    include(ExternalProject)

    # Location of tool source code
    set(FILE2CPP_SOURCE_DIR ${YAHAL_DIR}/tools/file2cpp)

    # Location of tool binary
    set(FILE2CPP_BINARY_DIR ${CMAKE_BINARY_DIR}/file2cpp)

    # The tool binary
    set(FILE2CPP_EXECUTABLE ${FILE2CPP_BINARY_DIR}/file2cpp)

    # Target for ExternalProject
    set(FILE2CPP_BUILD_TARGET FILE2CPP_BUILD)
    # Target for executable
    set(FILE2CPP_TARGET       FILE2CPP)

    # Check if ExternalProject was already added
    if (NOT TARGET ${FILE2CPP_BUILD_TARGET})
        message("FILE2CPP will need to be built")

        ExternalProject_Add(${FILE2CPP_BUILD_TARGET}
            PREFIX          file2cpp
            SOURCE_DIR      ${FILE2CPP_SOURCE_DIR}
            BINARY_DIR      ${FILE2CPP_BINARY_DIR}
            BUILD_ALWAYS    1 # force dependency checking
            INSTALL_COMMAND ""
        )
    endif()

    if(NOT TARGET ${FILE2CPP_TARGET})
        add_executable(${FILE2CPP_TARGET} IMPORTED)
    endif()

    set_property(TARGET ${FILE2CPP_TARGET} PROPERTY IMPORTED_LOCATION
        ${FILE2CPP_EXECUTABLE})

    add_dependencies(${FILE2CPP_TARGET} ${FILE2CPP_BUILD_TARGET})

    set(FILE2CPP_FOUND 1)
endif()
