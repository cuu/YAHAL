####################################
# Configuration for ARM Cortex M4F #
####################################
# Set CPU name
set(YAHAL_CPU "cortex-m4f")

# Architecture flags
set(CORTEX_FLAGS "-mcpu=cortex-m4 -march=armv7e-m -mthumb")

# FPU flags
set(CORTEX_FLAGS "${CORTEX_FLAGS} -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mabi=aapcs")
add_compile_definitions(ARM_MATH_CM4 __FPU_PRESENT)

# Add flags
foreach(LANG IN ITEMS C CXX ASM)
    set(CMAKE_${LANG}_FLAGS "${CMAKE_${LANG}_FLAGS} ${CORTEX_FLAGS}")
endforeach()

