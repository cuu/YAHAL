# Finds (or builds) the PNG2CPP executable
#
# This will define the following variables
#
#    PNG2CPP_FOUND
#
# and the following imported targets
#
#     PNG2CPP
#

if (NOT PNG2CPP_FOUND)
    include(ExternalProject)

    # Location of tool source code
    set(PNG2CPP_SOURCE_DIR ${YAHAL_DIR}/tools/png2cpp)

    # Location of tool binay
    set(PNG2CPP_BINARY_DIR ${CMAKE_BINARY_DIR}/png2cpp)

    # The tool binary
    set(PNG2CPP_EXECUTABLE ${PNG2CPP_BINARY_DIR}/png2cpp)

    # Target for ExternalProject
    set(PNG2CPP_BUILD_TARGET PNG2CPP_BUILD)
    # Target for executable
    set(PNG2CPP_TARGET       PNG2CPP)

    # Check if ExternalProject was already added
    if (NOT TARGET ${PNG2CPP_BUILD_TARGET})
        message("PNG2CPP will need to be built")

        ExternalProject_Add(${PNG2CPP_BUILD_TARGET}
            PREFIX          png2cpp
            SOURCE_DIR      ${PNG2CPP_SOURCE_DIR}
            BINARY_DIR      ${PNG2CPP_BINARY_DIR}
            BUILD_ALWAYS    1 # force dependency checking
            INSTALL_COMMAND ""
        )
    endif()

    if(NOT TARGET ${PNG2CPP_TARGET})
        add_executable(${PNG2CPP_TARGET} IMPORTED)
    endif()

    set_property(TARGET ${PNG2CPP_TARGET} PROPERTY IMPORTED_LOCATION
        ${PNG2CPP_EXECUTABLE})

    add_dependencies(${PNG2CPP_TARGET} ${PNG2CPP_BUILD_TARGET})

    set(PNG2CPP_FOUND 1)
endif()
