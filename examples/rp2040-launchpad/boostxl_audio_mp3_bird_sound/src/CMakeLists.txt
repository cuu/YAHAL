
target_sources(boostxl_audio_mp3_bird_sound PRIVATE
    boostxl_audio_mp3_bird_sound.cpp
    decoder_task.cpp
)

target_include_directories(boostxl_audio_mp3_bird_sound PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

