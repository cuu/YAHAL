
target_sources(boostxl_edumkII_mp3_bird_sound PRIVATE
    boostxl_edumkII_mp3_bird_sound.cpp
    audio_output.cpp
    decoder_task.cpp
)

target_include_directories(boostxl_edumkII_mp3_bird_sound PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)
