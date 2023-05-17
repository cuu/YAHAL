# Initiaize YAHAL by setting the properties of
# the board, MCU, toolchain etc.
##############################################

if (NOT TARGET yahal_init_guard)
add_library(yahal_init_guard INTERFACE)

#
# Check if a target board has been set
#
if (DEFINED ENV{YAHAL_BOARD} AND (NOT YAHAL_BOARD))
    set(YAHAL_BOARD $ENV{YAHAL_BOARD})
    message("Using YAHAL_BOARD from environment ('${YAHAL_BOARD}')")
endif()
if (NOT YAHAL_BOARD)
    message(FATAL_ERROR "No target board was specified! (YAHAL_BOARD)")
endif()

#
# Add YAHAL's cmake folder to the known paths of cmake modules
#
list(APPEND CMAKE_MODULE_PATH ${YAHAL_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${YAHAL_DIR}/cmake/packages)

#
# Load board definition
#
include(boards/${YAHAL_BOARD})

#
# Macro to add YAHAL as a subdirectory to a project
#
function(yahal_add_me TARGET)
    if (NOT PROJECT_NAME)
        message(WARNING "yahal_add_me() should be called after the project is created (and languages added)")
    endif()
    add_subdirectory(${YAHAL_DIR}   YAHAL_${PROJECT_NAME})
    target_link_libraries(${TARGET} PRIVATE YAHAL_${PROJECT_NAME})

    # Add more libraries depending on MCU
    if (${YAHAL_MCU} STREQUAL "rp2040")
        if((YAHAL_WRAP_BITOPS EQUAL 1) OR (YAHAL_WRAP_DIVMUL EQUAL 1) OR (YAHAL_WRAP_FLOAT EQUAL 1) OR (YAHAL_WRAP_DOUBLE EQUAL 1))
            target_link_libraries(${TARGET} PRIVATE rp2040_wrapper)
        endif()
    endif()
endfunction()

function(yahal_add_library TARGET LIB)
    add_subdirectory(${YAHAL_DIR}/lib/${LIB} ${LIB}_${TARGET})
    target_link_libraries(${TARGET} PRIVATE ${LIB}_${TARGET})
endfunction()

function(yahal_add_custom_targets TARGET)
    # Add a upload target using openocd if configuration was given
    if (OPENOCD_CONFIG)
        set(TF $<TARGET_FILE:${TARGET}>)
        add_custom_target("upload_${TARGET}" 
            openocd ${OPENOCD_CONFIG} -c "program \"${TF}\" verify reset exit"
            DEPENDS ${TF}
            VERBATIM
        )
    endif()
endfunction()

function(yahal_add_hex_output TARGET)
    set(TF $<TARGET_FILE:${TARGET}>)
    set(TN $<TARGET_PROPERTY:${TARGET},NAME>)
    set(TO $<TARGET_PROPERTY:${TARGET},OUTPUT_NAME>)

    add_custom_command(TARGET ${TARGET} POST_BUILD 
        COMMAND ${CMAKE_OBJCOPY} -Oihex ${TF} ${TN}.hex
    )
endfunction()

function(yahal_add_bin_output TARGET)
    set(TF $<TARGET_FILE:${TARGET}>)
    set(TN $<TARGET_PROPERTY:${TARGET},NAME>)
    set(TO $<TARGET_PROPERTY:${TARGET},OUTPUT_NAME>)

    add_custom_command(TARGET ${TARGET} POST_BUILD 
        COMMAND ${CMAKE_OBJCOPY} -Obinary ${TF} ${TN}.bin
    )
endfunction()

function(yahal_add_dis_output TARGET)
    set(TF $<TARGET_FILE:${TARGET}>)
    set(TN $<TARGET_PROPERTY:${TARGET},NAME>)
    set(TO $<TARGET_PROPERTY:${TARGET},OUTPUT_NAME>)

    add_custom_command(TARGET ${TARGET} POST_BUILD 
        COMMAND ${CMAKE_OBJDUMP} ${TF} -h    > ${TN}.dis
        COMMAND ${CMAKE_OBJDUMP} ${TF} -d -C >>${TN}.dis
    )
endfunction()

function(yahal_rename_mapfile TARGET)
    set(TN $<TARGET_PROPERTY:${TARGET},NAME>)
    add_custom_command(TARGET ${TARGET} POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E rename mapfile ${TN}.map
    )
endfunction()

function(yahal_add_extra_outputs TARGET)
    set_property(TARGET ${TARGET} PROPERTY SUFFIX .elf)

    # Add hex, bin and disassembly outputs
    yahal_add_hex_output(${TARGET})
    yahal_add_bin_output(${TARGET})
    yahal_add_dis_output(${TARGET})

    # Add uf2 output for rp2040
    if (${YAHAL_MCU} STREQUAL rp2040)
        yahal_add_uf2_output(${TARGET})
    endif()

    yahal_rename_mapfile(${TARGET})
endfunction()

endif()

# Set the YAHAL target name depending on the fact
# if this file was included from another project,
# or if the YAHAL library is build standalone.
if (NOT PROJECT_NAME)
    set(YAHAL_TARGET "YAHAL")
else()
    set(YAHAL_TARGET "YAHAL_${PROJECT_NAME}")
endif()

#
# Set default values for YAHAL flags
#
if (NOT DEFINED YAHAL_DEBUG_FLAGS)
    set(YAHAL_DEBUG_FLAGS -g -gdwarf-3 -gstrict-dwarf)
endif()
if (NOT DEFINED YAHAL_OPT_FLAGS)
    set(YAHAL_OPT_FLAGS -Og)
endif()
if (NOT DEFINED YAHAL_USE_NANO_SPECS)
    set(YAHAL_USE_NANO_SPECS 1)
endif()
if (NOT DEFINED YAHAL_ENABLE_ASSERTS)
    set(YAHAL_ENABLE_ASSERTS 1)
endif()

#
# Evaluate YAHAL flags
#
if (YAHAL_USE_NANO_SPECS EQUAL 1)
    add_link_options("--specs=nano.specs")
endif()
if (YAHAL_ENABLE_ASSERTS EQUAL 1)
    add_compile_options(-DDEBUG)
else()
    add_compile_options(-DNDEBUG)
endif()

add_compile_options(${YAHAL_DEBUG_FLAGS} ${YAHAL_OPT_FLAGS})

if (YAHAL_WRAP_FLOAT EQUAL 1)
    set(CMAKE_EXE_LINKER_FLAGS 
    "${CMAKE_EXE_LINKER_FLAGS} -Wl,@\"${YAHAL_DIR}/cmake/toolchains/wrap_float\"")
#    add_link_options(-Wl,@${YAHAL_DIR}/cmake/toolchains/wrap_float)
endif()

if (YAHAL_WRAP_DOUBLE EQUAL 1)
    set(CMAKE_EXE_LINKER_FLAGS 
    "${CMAKE_EXE_LINKER_FLAGS} -Wl,@\"${YAHAL_DIR}/cmake/toolchains/wrap_double\"")
#    add_link_options(-Wl,@${YAHAL_DIR}/cmake/toolchains/wrap_double)
endif()

if (YAHAL_WRAP_BITOPS EQUAL 1)
    set(CMAKE_EXE_LINKER_FLAGS 
    "${CMAKE_EXE_LINKER_FLAGS} -Wl,@\"${YAHAL_DIR}/cmake/toolchains/wrap_bitops\"")
#    add_link_options(-Wl,@${YAHAL_DIR}/cmake/toolchains/wrap_bitops)
endif()

if (YAHAL_WRAP_DIVMUL EQUAL 1)
    set(CMAKE_EXE_LINKER_FLAGS 
    "${CMAKE_EXE_LINKER_FLAGS} -Wl,@\"${YAHAL_DIR}/cmake/toolchains/wrap_div_mul\"")
#    add_link_options(-Wl,@${YAHAL_DIR}/cmake/toolchains/wrap_div_mul)
endif()

