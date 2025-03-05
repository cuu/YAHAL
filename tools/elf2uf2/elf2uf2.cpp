// ---------------------------------------------
//           This file is part of
//      _  _   __    _   _    __    __
//     ( \/ ) /__\  ( )_( )  /__\  (  )
//      \  / /(__)\  ) _ (  /(__)\  )(__
//      (__)(__)(__)(_) (_)(__)(__)(____)
//
//     Yet Another HW Abstraction Library
//      Copyright (C) Andreas Terstegge
//      BSD Licensed (see file LICENSE)
//
// ---------------------------------------------
//
#include <iostream>
#include <cstring>
#include <vector>

#include "block.h"
#include "crc32.h"
#include "elfio/elfio_dump.hpp"
#include "item_image_def.h"
#include "uf2_ofstream.h"

using namespace ELFIO;
using namespace std;

#define BOOT2_SIZE 256

void usage(const char * bin) {
    cout << "Usage: " << bin << " [-v] <INPUT> [OUTPUT]" << endl;
    cout << endl;
    cout << "-v     : Verbose output"               << endl;
    cout << "INPUT  : A valid ARM elf file"         << endl;
    cout << "OUTPUT : An optional UF2 output file." << endl;
    cout << "         Default is <INPUT_NAME>.uf2"  << endl;
    exit(1);
}

int main(int argc, char *argv[]) {
    bool verbose = false;
    string elf_filename;
    string uf2_filename;

    // Check number of command line args
    if (argc < 2 || argc > 4 ) {
        usage(argv[0]);
    }

    if (strcmp(argv[1], "-v")) {
        elf_filename = argv[1];
        if (argc == 3) {
            uf2_filename = argv[2];
        }
    } else {
        verbose = true;
        if (argc == 2) {
            usage(argv[0]);
        } else if (argc == 3) {
            elf_filename = argv[2];
        } else if (argc == 4) {
            elf_filename = argv[2];
            uf2_filename = argv[3];
        }
    }

    // Set filenames
    if (uf2_filename.empty()) {
        size_t dot = elf_filename.find_last_of('.');
        string name_we;
        if (dot != string::npos) {
            name_we = elf_filename.substr(0, dot);
        } else {
            name_we = elf_filename;
        }
        uf2_filename = name_we + ".uf2";
    }

    // Read the ELF file
    if (verbose) cout << "Reading " << elf_filename << endl;
    elfio elf;
    if ( !elf.load( elf_filename ) ) {
        cerr << "File " << elf_filename << " is not found or is not an ELF file.\n" << endl;
        exit(1);
    }

    // Check ELF file format
    if (elf.get_elf_version() != EV_CURRENT ||
        elf.get_version()     != EV_CURRENT ||
        elf.get_class()       != ELFCLASS32 ||
        elf.get_machine()     != EM_ARM ||
        elf.get_encoding()    != ELFDATA2LSB ||
        elf.get_os_abi()      != ELFOSABI_NONE ||
        elf.get_abi_version() != 0) {
        cerr << "File " << elf_filename << " is not a 32bit ARM little endian ELF file." << endl;
        exit(1);
    }

    // Open the UF2 file for writing
    uf2_ofstream uf2(uf2_filename);
    if (!uf2.good()) {
        cerr << "Output file " << uf2_filename << "Could not be opened." << endl;
        uf2.close();
        exit(1);
    }

    if (verbose) cout << "Found the following loadable ELF segments:" << endl;
    if (verbose) cout << "[  Nr ] Type           VirtAddr   PhysAddr   FileSize   "
                         "Mem.Size   Flags    Align" << endl;
    int seg_no = 1;

    // Iterate over all ELF segments.
    // Find the lowest and highest physical address
    uint64_t low_addr  = UINT32_MAX;
    uint64_t high_addr = 0;
    for (auto & seg : elf.segments) {
        // Only check loadable segments
        if (seg->get_type() == PT_LOAD) {
            if (verbose) dump::segment_header(cout, seg_no++, seg.get(), elf.get_class());
            uint32_t phy_addr  = seg->get_physical_address();
            uint32_t file_size = seg->get_file_size();
            // Check minimum
            if (phy_addr < low_addr) low_addr = phy_addr;
            // Check maximum
            if ((phy_addr + file_size) > high_addr) {
                high_addr = phy_addr + file_size - 1;
            }
        }
    }
    // Calculate loadable size
    uint32_t bin_size  = high_addr - low_addr + 1;

    if (bin_size > 16*1024*1024) {
        cerr << "Loadable size exceeds 16MiB." << endl;
        exit(1);
    }

    if (verbose) {
        if (low_addr == 0x10000000) {
            cout << "Using FLASH ";
        } else if (low_addr == 0x20000000) {
            cout << "Using RAM ";
        }
        cout << "from 0x" << DUMP_HEX_FORMAT(8) << low_addr << " - 0x" << high_addr << endl;
    }
    // Create array to hold all loadable code/data.
    // Make sure the bin_array is n * PAGE_SIZE;
    while (bin_size & (PAGE_SIZE-1)) bin_size++;
    auto * bin_array = new uint8_t [bin_size];

    // Load all segments
    if (verbose) cout << "Loading segments ..." << endl;
    for (auto & seg : elf.segments) {
        // Only loadable segments
        if (seg->get_type() == PT_LOAD) {
            uint8_t * bin_addr =
                bin_array + (seg->get_physical_address() - low_addr);
            memcpy(bin_addr, seg->get_data(), seg->get_file_size());
        }
    }

    // Check for stage 2 bootloader in first page
    bool found_boot2 = false;
    if (bin_size >= BOOT2_SIZE) {
        uint32_t crc = crc32::calculate(bin_array, 252);
        if (((uint32_t *)bin_array)[63] == crc) {
            found_boot2 = true;
            if (verbose) cout << "Found stage 2 bootloader in first page." << endl;
        }
    }


    std::vector<block *> blocks;
    try {
        // Check for boot blocks in for 4096 bytes of the image
        uint32_t *bin_array_32 = (uint32_t *) bin_array;
        uint32_t bin_size_32 = bin_size >= 4096 ? 1024 : bin_size / 4;
        for (int i = 0; i < bin_size_32; ++i) {
            if (bin_array_32[i] == BLOCK_HEADER) {
                if (verbose) cout << "Found BOOT BLOCK at physical address 0x"
                                  << DUMP_HEX_FORMAT(8) << (low_addr + i*4) << endl;
                uint32_t *first_block_addr = bin_array_32 + i;
                uint32_t *block_addr = first_block_addr;
                do {
                    block *b = new block;
                    block_addr = b->read(block_addr);
                    blocks.push_back(b);
                } while (block_addr != first_block_addr);
            }
        }
    } catch(const char * msg) {
        cerr << "Error: " << msg << endl;
        cerr << "Exiting." << endl;
        exit(1);
    }

    bool found_image_def = false;
    item_image_def * image_def;
    // Find an image in the blocks
    for (auto b : blocks) {
        for (auto i : b->_items) {
            if (i->get_type() == item_type_t::IMAGE_DEF) {
                image_def = dynamic_cast<item_image_def *>(i);
                found_image_def = true;
            }
        }
    }

    // Derive family type
    family_id_t family = family_id_t::RP2040; // default
    if (!found_boot2 && !found_image_def) {
        cerr << "Could not find a stage 2 bootloader or boot blocks." << endl;
        cerr << "Exiting." << endl;
        exit(1);
    } else if (found_boot2 && !found_image_def) {
        // default is okay
    } else if (found_image_def) {
        switch (image_def->header.chip) {
            case chip_t::RP2040:
                // Default is okay
                break;
            case chip_t::RP2350:
                if (image_def->header.cpu == cpu_t::RISCV) {
                    family = family_id_t::RP2350_RISCV;
                    break;
                }
                if (image_def->header.cpu == cpu_t::ARM) {
                    if (image_def->header.security == security_t::S) {
                        family = family_id_t::RP2350_ARM_S;
                        break;
                    } else if (image_def->header.security == security_t::NS) {
                        family = family_id_t::RP2350_ARM_NS;
                        break;
                    } else {
                        cerr << "No security spec. Defaulting to S." << endl;
                        family = family_id_t::RP2350_ARM_S;
                        break;
                    }
                }
                cerr << "Wrong cpu specification. Defaulting to RP2040" << endl;
                break;
            default: {
                cerr << "Wrong chip specification. Defaulting to RP2040" << endl;
                break;
            }
        }
    }

    if (verbose) {
        cout << "Using UF2 family ID ";
        switch (family) {
            case family_id_t::RP2040:
                cout << "RP2040";
                break;
            case family_id_t::RP2XXX_ABSOLUTE:
                cout << "RP2xxx_ABSOLUTE";
                break;
            case family_id_t::RP2350_ARM_S:
                cout << "RP2350_ARM_S";
                break;
            case family_id_t::RP2350_RISCV:
                cout << "RP2350_RISCV";
            case family_id_t::RP2350_ARM_NS:
                cout << "RP2350_NS";
                break;
            default:
                cout << "?";
                break;
        }
        cout << endl;
    }

    // Add a dummy block due to errata E10
    if (family == family_id_t::RP2350_ARM_S  ||
        family == family_id_t::RP2350_ARM_NS ||
        family == family_id_t::RP2350_RISCV) {
        uf2.set_block_no(0);
        uf2.set_num_blocks(2);
        uf2.set_target_addr(0x10ffff00);
        uf2.set_family_id(family_id_t::RP2XXX_ABSOLUTE);
        uf2.add_extension_flag(UF2_EXTENSION_RP2_IGNORE_BLOCK.data(),
                               UF2_EXTENSION_RP2_IGNORE_BLOCK.size());
        array<uint8_t, PAGE_SIZE> dummy_data{0};
        for (auto &c: dummy_data) c = 0xef;
        uf2.write_block(dummy_data.data());
        uf2.clear_extension_flags();
    }
    // Write data from bin_array
    if (verbose) cout << "Writing UF2 file " << uf2_filename << endl;
    uint32_t num_blocks = bin_size / PAGE_SIZE;
    uint32_t block      = 0;
    uint32_t phy_addr   = low_addr;
    uint8_t * bin_ptr   = bin_array;
    uf2.set_num_blocks(num_blocks);
    uf2.set_family_id(family);
    for (uint32_t i = 0; i < num_blocks; ++i) {
        uf2.set_target_addr(phy_addr);
        uf2.set_block_no(block);
        uf2.write_block(bin_ptr);
        block++;
        phy_addr += PAGE_SIZE;
        bin_ptr  += PAGE_SIZE;
    }
    uf2.close();
    return 0;
}
