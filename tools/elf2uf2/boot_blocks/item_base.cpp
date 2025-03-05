//
// Created by andreas on 05.03.25.
//

#include "item_base.h"

std::ostream & operator << (std::ostream & os, const item_type_t & it) {
    switch (it) {
        case item_type_t::NEXT_BLOCK_OFFSET:
            os << "NEXT_BLOCK_OFFSET"; break;
        case item_type_t::IMAGE_DEF:
            os << "IMAGE_DEF   "; break;
        case item_type_t::VECTOR_TABLE:
            os << "VECTOR_TABLE"; break;
        case item_type_t::ENTRY_POINT:
            os << "ENTRY_POINT "; break;
        case item_type_t::ROLLING_WINDOW_DELTA:
            os << "ROLLING_WINDOW_DELTA"; break;
        case item_type_t::LOAD_MAP:
            os << "LOAD_MAP    "; break;
        case item_type_t::HASH_DEF:
            os << "HASH_DEF    "; break;
        case item_type_t::VERSION:
            os << "VERSION     "; break;
        case item_type_t::SIGNATURE:
            os << "SIGNATURE   "; break;
        case item_type_t::PARTITION_TABLE:
            os << "PARTITION_TABLE"; break;
        case item_type_t::HASH_VALUE:
            os << "HASH_VALUE"; break;
        case item_type_t::SALT:
            os << "SALT"; break;
        case item_type_t::IGNORED:
            os << "IGNORED"; break;
        case item_type_t::LAST:
            os << "LAST"; break;
    }
    return os;
}

