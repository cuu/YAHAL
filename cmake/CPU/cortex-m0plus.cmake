####################################
# Configuration for ARM Cortex M0+ #
####################################
# Set CPU name
set(YAHAL_CPU "cortex-m0plus")

# Architecture flags
set(CORTEX_FLAGS "-mcpu=cortex-m0plus -march=armv6s-m -mthumb")

# Math flags 
add_compile_definitions(ARM_MATH_CM0PLUS)

# Add flags
foreach(LANG IN ITEMS C CXX ASM)
    set(CMAKE_${LANG}_FLAGS_INIT "${CMAKE_${LANG}_FLAGS_INIT} ${CORTEX_FLAGS}")
endforeach()

