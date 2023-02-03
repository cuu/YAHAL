
target_sources(boostxl_audio_mp3_player PRIVATE
    boostxl_audio_mp3_player.cpp
    audio_output.cpp
    mp3_decoder_task.cpp
    sd_reader_task.cpp
)

target_include_directories(boostxl_audio_mp3_player PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

