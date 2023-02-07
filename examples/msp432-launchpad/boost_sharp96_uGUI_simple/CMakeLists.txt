cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(boost_sharp96_uGUI_simple)

add_executable(boost_sharp96_uGUI_simple
    boost_sharp96_uGUI_simple.cpp
)

# Add YAHAL and uGUI
yahal_add_me(boost_sharp96_uGUI_simple)
yahal_add_library(boost_sharp96_uGUI_simple uGUI)

yahal_add_custom_targets(boost_sharp96_uGUI_simple)
yahal_add_extra_outputs(boost_sharp96_uGUI_simple)
