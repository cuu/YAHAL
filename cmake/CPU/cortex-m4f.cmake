####################################
# Configuration for ARM Cortex M4F #
####################################
# Set CPU name
set(YAHAL_CPU "cortex-m4f")

# Architecture flags
add_compile_options(-mcpu=cortex-m4 -march=armv7e-m -mthumb)

# FPU flags
add_compile_definitions(ARM_MATH_CM4 __FPU_PRESENT)
add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16 -mabi=aapcs)

