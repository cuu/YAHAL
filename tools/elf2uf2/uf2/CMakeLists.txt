target_sources(elf2uf2 PRIVATE
        uf2_ofstream.cpp
)


target_include_directories(elf2uf2 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

