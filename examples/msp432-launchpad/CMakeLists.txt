cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(examples-msp432)

#
# Various blinky examples
#
add_subdirectory(blink_asm)
add_subdirectory(blink_register)
add_subdirectory(blink_simple)
add_subdirectory(blink_task_sleep)
add_subdirectory(blink_timer)
add_subdirectory(blink_timerA)

#
# Examples for BOOSTXL-AUDIO module
#
add_subdirectory(boostxl_audio_mp3_bird_sound)
add_subdirectory(boostxl_audio_mp3_player)
add_subdirectory(boostxl_audio_sin_wave)

#
# Examples for BOOSTXL-EDUMKII module
#
add_subdirectory(boostxl_edumkII_adc_interrupt)
add_subdirectory(boostxl_edumkII_adc_scan)
add_subdirectory(boostxl_edumkII_adc_simple)
add_subdirectory(boostxl_edumkII_i2c_simple)
add_subdirectory(boostxl_edumkII_mic_fft)
add_subdirectory(boostxl_edumkII_mp3_bird_sound)
add_subdirectory(boostxl_edumkII_opt3001_irq)
add_subdirectory(boostxl_edumkII_opt3001_simple)
add_subdirectory(boostxl_edumkII_timer_A_LEDs)
add_subdirectory(boostxl_edumkII_uGUI_bitmap)
add_subdirectory(boostxl_edumkII_uGUI_simple)

#
# Examples for BOOSTXL-K350QVG module
#
add_subdirectory(boostxl_k350qvg)

#
# Examples for 430BOOST-SHARP96 module
#
add_subdirectory(boost_sharp96_uGUI_simple)

#
# Other examples 
#
add_subdirectory(config_clock_system)
add_subdirectory(gpio_interrupt)
add_subdirectory(gpio_simple)
add_subdirectory(mixed_c_asm)
add_subdirectory(multitasking_simple)
add_subdirectory(retro_PDP8_Focal)
add_subdirectory(sd_card_spi)
add_subdirectory(soft_i2c_master_slave)
add_subdirectory(stepper_motor)
add_subdirectory(uart_simple)
add_subdirectory(ws2812_leds)

#
# HW testing programs
#
add_subdirectory(boostxl_edumkII_hw_test)
add_subdirectory(boostxl_lp_tester)
