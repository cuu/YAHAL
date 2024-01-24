# Finds (or builds) the MP3PCM2CPP executable
#
# This will define the following variables
#
#    MP3PCM2CPP_FOUND
#
# and the following imported targets
#
#     MP3PCM2CPP
#

if (NOT MP3PCM2CPP_FOUND)
    include(ExternalProject)

    # Location of tool source code
    set(MP3PCM2CPP_SOURCE_DIR ${YAHAL_DIR}/tools/mp3pcm2cpp)

    # Location of tool binary
    set(MP3PCM2CPP_BINARY_DIR ${CMAKE_BINARY_DIR}/mp3pcm2cpp)

    # The tool binary
    set(MP3PCM2CPP_EXECUTABLE ${MP3PCM2CPP_BINARY_DIR}/mp3pcm2cpp)

    # Target for ExternalProject
    set(MP3PCM2CPP_BUILD_TARGET MP3PCM2CPP_BUILD)
    # Target for executable
    set(MP3PCM2CPP_TARGET       MP3PCM2CPP)

    # Check if ExternalProject was already added
    if (NOT TARGET ${MP3PCM2CPP_BUILD_TARGET})
        message("MP3PCM2CPP will need to be built")

        ExternalProject_Add(${MP3PCM2CPP_BUILD_TARGET}
            PREFIX          mp3pcm2cpp
            SOURCE_DIR      ${MP3PCM2CPP_SOURCE_DIR}
            BINARY_DIR      ${MP3PCM2CPP_BINARY_DIR}
            BUILD_ALWAYS    1 # force dependency checking
            INSTALL_COMMAND ""
        )
    endif()

    if(NOT TARGET ${MP3PCM2CPP_TARGET})
        add_executable(${MP3PCM2CPP_TARGET} IMPORTED)
    endif()

    set_property(TARGET ${MP3PCM2CPP_TARGET} PROPERTY IMPORTED_LOCATION
        ${MP3PCM2CPP_EXECUTABLE})

    add_dependencies(${MP3PCM2CPP_TARGET} ${MP3PCM2CPP_BUILD_TARGET})

    set(MP3PCM2CPP_FOUND 1)
endif()
