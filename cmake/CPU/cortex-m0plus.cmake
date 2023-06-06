####################################
# Configuration for ARM Cortex M0+ #
####################################
# Set CPU name
set(YAHAL_CPU "cortex-m0plus")

# Architecture flags
add_compile_options(-mcpu=cortex-m0plus -march=armv6s-m -mthumb)

# Math flags 
add_compile_definitions(ARM_MATH_CM0PLUS)
