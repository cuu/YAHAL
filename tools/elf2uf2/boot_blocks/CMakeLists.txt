target_sources(elf2uf2 PRIVATE
        block.cpp
        item_base.cpp
        item_image_def.cpp
        item_load_map.cpp
        item_version.cpp
)

target_include_directories(elf2uf2 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

