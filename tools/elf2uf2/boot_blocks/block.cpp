//
// Created by andreas on 05.03.25.
//

#include "block.h"
#include "item_image_def.h"
#include "item_version.h"
#include "item_load_map.h"

uint32_t * block::read (uint32_t* & ptr) {

    _start_pointer = ptr;

    if (*ptr != BLOCK_HEADER) {
        throw "Block does not begin with a correct header";
    }
    ptr++;

    bool more_items = true;
    uint16_t items_size = 0;
    item_image_def * image_def;
    item_version   * version;
    item_load_map  * load_map;
    int32_t link_offset = 0;

    do {
        switch (item_type_t(*ptr & 0xff)) {
            case item_type_t::IMAGE_DEF:
                image_def = new item_image_def;
                image_def->read(ptr);
                items_size += image_def->size32();
                _items.push_back(image_def);
                break;

            case item_type_t::VERSION: {
                version = new item_version;
                version->read(ptr);
                items_size += version->size32();
                _items.push_back(version);
                break;
            }

            case item_type_t::LOAD_MAP: {
                load_map = new item_load_map;
                load_map->read(ptr);
                items_size += load_map->size32();
                _items.push_back(load_map);
                break;
            }

            case item_type_t::LAST: {
                uint16_t sum_size = (*ptr++) >> 8;
                if (sum_size != items_size) {
                    std::cout << "Sum:" << sum_size << " items_size:" << items_size << std::endl;
                    throw "LAST item has wrong size";
                }
                link_offset = *ptr++;
                if (*ptr != BLOCK_FOOTER) {
                    throw "BLOCK has invalid footer";
                }
                more_items = false;
                break;
            }

            case item_type_t::VECTOR_TABLE:
            case item_type_t::ENTRY_POINT:
            case item_type_t::ROLLING_WINDOW_DELTA:
            case item_type_t::HASH_DEF:
            case item_type_t::SIGNATURE:
            case item_type_t::PARTITION_TABLE:
            case item_type_t::HASH_VALUE:

            case item_type_t::NEXT_BLOCK_OFFSET:
            case item_type_t::SALT:
            case item_type_t::IGNORED:
            default:
                throw ("Unsupported Item type");
        }
    } while(more_items);

    return (uint32_t *)((uint8_t *)_start_pointer + link_offset);
}