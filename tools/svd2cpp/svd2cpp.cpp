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
// Small program to convert a SVD file into a C++
// structure. Not all features of SVD are supported!
//
#include "svd2cpp.h"
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;
using namespace tinyxml2;

svd2cpp svd2cpp::inst;

// Stream output manipulator for indentation
std::ostream& indent(std::ostream& os) {
    os << string(svd2cpp::inst._currentIndent, ' ');
    return os;
}

void svd2cpp::processSvdFile(const string & infile,
                             const string & outfile,
                             XMLElement *elem,
                             bool generateIrqNumbers) {
    // Get the MCU name
    if (!childExists(elem, "name")) {
        cerr << "Can not find MCU name in file " << infile
             << endl;
        exit(1);
    }
    _mcu = getChildElement(elem, "name");

    // Open out file
    cout << "Writing file " << outfile << endl;
    _ofs.open(outfile.c_str(), ios::out);

    _ofs << string(75, '/') << endl;
    _ofs << "// This file was generated with svd2cpp, source file was "
         << infile << endl;
    _ofs << "// DO NOT EDIT - CHANGES MIGHT BE OVERWRITTEN !!" << endl;
    _ofs << string(75, '/') << endl;
    _ofs << "//" << endl;
    _ofs << "#include \"bitfield_defs.h\"" << endl;
    _ofs << endl;

    // Loop over all first-level elements
    elem = elem->FirstChildElement();
    while (elem != nullptr) {
        // Get the name of the current element
        string elemName = elem->Name();
        cout << "Processing " << elemName << endl;
        if (elemName == "peripherals") {
            _ofs << endl;
            // Loop over all peripherals
            for (XMLElement *peripheral = elem->FirstChildElement();
                 peripheral; peripheral = peripheral->NextSiblingElement()) {
                ProcessPeripheral(peripheral);
            }
        }
        else {
            // All other first-level items are written as a comment
            ProcessComment(elem);
        }
        elem = elem->NextSiblingElement();
    }

    // Generate IRQ numbers if required
    if(generateIrqNumbers) {
        // Sort the interrupts by number and print them
        std::sort(irq_info.begin(), irq_info.end(),
                  [](irq_info_t &a, irq_info_t &b) {
                      return a.value < b.value;
                  });
        _ofs << indent << "// Interrupt numbers" << endl;
        for (auto & irq : irq_info) {
            string tmp = "#define " + string(irq.name) + " ";
            while (tmp.size() < 30) tmp += ' ';
            _ofs << indent << tmp << dec << irq.value << endl;
        }
    }
}

void svd2cpp::ProcessPeripheral(XMLElement *peripheral) {
    const char *name     = getChildElement(peripheral, "name");
    const char *size     = getChildElement(peripheral, "size");
    const char *baseAddr = getChildElement(peripheral, "baseAddress");
    const char *desc     = getChildElement(peripheral, "description");

    // Some sanity checks
    if (name == nullptr) {
        cerr << "Can not find name for peripheral. Exit." << endl;
        exit(1);
    }
    if (baseAddr == nullptr) {
        cerr << "Can not find base address for peripheral. Exit." << endl;
        exit(1);
    }

    // Get base address and default register size in bytes
    uint32_t baseAddr_int = parseNumber(baseAddr);
    if (size) {
        _curRegSizeBytes = parseNumber(size) / 8;
    }

    // Check if we are a derived peripheral
    string derivedFrom;
    const XMLAttribute *derived = peripheral->FindAttribute("derivedFrom");
    if (derived) {
        derivedFrom += derived->Value();
    }

    // Check if we have some interrupt information
    for (XMLElement *irq = peripheral->FirstChildElement("interrupt"); irq;
         irq = irq->NextSiblingElement("interrupt")) {
        irq_info_t i;
        i.name  = getChildElement(irq, "name");
        i.value = parseNumber(getChildElement(irq, "value"));
        irq_info.push_back(i);
    }

    // Print out description if available
    outputAsComment(desc);

    // Start a new namespace for every peripheral
    _ofs << indent << "namespace _" << name << "_  {" << endl << endl;
    incIndent();

    // Loop over all registers. This will output all register
    // field definitions and optionally related enum-values.
    XMLElement *registers = peripheral->FirstChildElement("registers");
    if (registers) {
        for (XMLElement *reg = registers->FirstChildElement("register");
             reg; reg = reg->NextSiblingElement()) {
            ProcessRegister(reg);
        }
    }

    // Generate and output the peripheral struct
    string periType;
    if (!derivedFrom.empty()) {
        // Set the derived peripheral type
        periType = "_" + derivedFrom + "_::" + derivedFrom + "_t";
    } else {
        // Set the standard peripheral type
        periType = named_register(name,"") + "_t";

        // Start the register struct
        _ofs << indent << "struct " << periType << " {" << endl;
        incIndent();

        // Loop over all registers
        uint32_t curr_off = 0;
        int res_index     = 0;
        //string tmp;
        while(_registerInfo.registers_left()) {
            // Get next register with the smallest offset
            register_info_t * reg = _registerInfo.next_register();

            // Check if we have to fill a gap with 'reserved'
            if (curr_off != reg->offset) {
                uint32_t diff  = reg->offset - curr_off;
                uint32_t typelen = 1;
                // Try to use same int length as register
                if ((diff % reg->size) == 0) {
                    diff   /= reg->size;
                    typelen = reg->size;
                }
                string type = "uint" + to_string(typelen * 8) + "_t";
                pad_str(type, 30);
                _ofs << indent << type << "reserved"
                     << to_string(res_index++);
                if (diff > 1) {
                    _ofs << "[" << diff << "]";
                }
                _ofs << ";" << endl;
                curr_off = reg->offset;
            }

            // Output the register type
            string reg_type = named_register(reg->type, "");
            pad_str(reg_type , 30);
            _ofs << indent << reg_type;

            // Output the register name
            if (reg->name.find("[%s]") != string::npos) {
                // The register is an array in the SVD file
                if (reg->userIndex) {
                    cerr << "Warning: dimIndex given for register array " << reg->name << endl;
                }
                _ofs << named_register(reg->name, to_string(reg->dim));
                // Mark register as processed
                curr_off += reg->size * reg->dim;
                reg->dim = 0;
            } else {
                // The register is no array. Try to sum up as many
                // as possible consecutive array elements
                int dim_size = 0;
                do {
                    dim_size++;
                    curr_off += reg->size;
                    reg->dim--;
                    reg->offset += reg->dimInc;
                    if (reg->dim == 0) break;
                    if (reg->userIndex) break;
                } while(curr_off == reg->offset);

                // Check if we found an array
                if (dim_size > 1) {
                    // We did find an array!
                    _ofs << named_register(reg->name, "");
                    _ofs << "[" << dim_size << "]";
                } else {
                    string index;
                    if (!reg->dimIndices.empty()) {
                        index = reg->dimIndices[0];
                        reg->dimIndices.erase(reg->dimIndices.begin());
                    }
                    _ofs << named_register(reg->name, index);
                }
            }
            _ofs << ";" << endl;
        }
        // Clear the registerInfo for the next peripheral
        _registerInfo.clear();

        // Finalize the peripheral struct
        decIndent();
        _ofs << indent << "};" << endl;
        _ofs << endl;
    }

    // Generate the final register struct instance
    _ofs << indent << "static "  << periType << " & "
         << name << " = (*(" << periType << " *)0x" << hex
         << baseAddr_int << ");" << endl;

    // Generate additional register struct instances,
    // depending on the MCU type
    if (_mcu == "RP2040" && ((baseAddr_int >> 28) <= 5)) {
        _ofs << indent << "static " << periType << " & "
             << name << "_XOR = (*(" << periType << " *)0x" << hex
             << baseAddr_int + 0x1000 << ");" << endl;
        _ofs << indent << "static " << periType << " & "
             << name << "_SET = (*(" << periType << " *)0x" << hex
             << baseAddr_int + 0x2000 << ");" << endl;
        _ofs << indent << "static " << periType << " & "
             << name << "_CLR = (*(" << periType << " *)0x" << hex
             << baseAddr_int + 0x3000 << ");" << endl;
    }

    // Finalize the peripheral namespace
    _ofs << endl;
    decIndent();
    _ofs << indent << "} // _" << name << "_" << endl;
    _ofs << endl;
}


void svd2cpp::ProcessRegister(XMLElement *register_) {
    // Get register properties
    const char *r_name     = getChildElement(register_, "name");
    const char *size       = getChildElement(register_, "size");
    const char *addrOffset = getChildElement(register_, "addressOffset");
    const char *desc       = getChildElement(register_, "description");
    const char *resetVal   = getChildElement(register_, "resetValue");
    const char *access     = getChildElement(register_, "access");

    if (r_name == nullptr) {
        cerr << "Can not find name for register. Exit." << endl;
        exit(1);
    }
    string name = r_name;
    if (addrOffset == nullptr) {
        cerr << "Can not find address Offset for register " << name
             << ". Exit." << endl;
        exit(1);
    }
    uint32_t addrOff = parseNumber(addrOffset);

    // Print out description if available
    outputAsComment(desc);
    if (resetVal) {
        string tmp = "Reset value: " + string(resetVal);
        outputAsComment(tmp.c_str());
    }

    // Get the valid register size in bytes
    uint32_t regByteSize = 0;
    if (size) {
        regByteSize = parseNumber(size) / 8;
    } else {
        regByteSize = _curRegSizeBytes;
    }

    register_info_t ri;
    ri.userIndex = false;

    // Handle dimensions
    const char *dim          = getChildElement(register_, "dim");
    const char *dimIncrement = getChildElement(register_, "dimIncrement");
    if (dim) {
        if (!dimIncrement) {
            cerr << "dim given without dimIncrement for register " << name
                 << ". Exit." << endl;
            exit(1);
        }
        ri.dim    = parseNumber(dim);
        ri.dimInc = parseNumber(dimIncrement);
        // Check if we have a specific register naming
        const char *dimIndex = getChildElement(register_, "dimIndex");
        string index;
        if (dimIndex) {
            string indices = dimIndex;
            ri.userIndex = true;
            // Check for range
            size_t dash = indices.find('-');
            if (dash != string::npos) {
                // Range specification
                indices[dash] = ' ';
                if (dash > 0 && indices[dash-1] >= 'A' && indices[dash-1] <= 'Z') {
                    // Letter range
                    string from, to;
                    istringstream iss(indices);
                    iss >> from >> to;
                    if (from.size() != 1 || to.size() != 1) {
                        cerr << "Wrong dimIndex range: " << dimIndex << endl;
                        exit(1);
                    }
                    for(char c=from[0]; c <= to[0]; ++c) {
                        index = c;
                        ri.dimIndices.push_back(index);
                    }
                    if (ri.dimIndices.size() != ri.dim) {
                        cerr << "dim and dimIndex do not match in size: "
                             << ri.dim << " and " << dimIndex << endl;
                        exit(1);
                    }
                } else {
                    // Numeric range
                    int from, to;
                    istringstream iss(indices);
                    iss >> from >> to;
                    if (from > to) {
                        cerr << "Wrong dimIndex range: " << dimIndex << endl;
                        exit(1);
                    }
                    for(int i=from; i <= to; ++i) {
                        index = to_string(i);
                        ri.dimIndices.push_back(index);
                    }
                    if (ri.dimIndices.size() != ri.dim) {
                        cerr << "dim and dimIndex do not match in size: "
                             << ri.dim << " and " << dimIndex << endl;
                        exit(1);
                    }
                }
            } else {
                // Comma-separated values:
                // Replace all commas by blanks
                for (char & c : indices) if (c==',') c = ' ';
                istringstream iss(indices);
                for(int i=0; i < ri.dim; ++i) {
                    iss >> index;
                    if (index.empty()) {
                        cerr << "dimIndex List too short: " << dimIndex << endl;
                        exit(1);
                    }
                    ri.dimIndices.push_back(index);
                }
            }
        } else {
            // No dimIndex given -> fill dimIndices with sequential numbers from 0
            for(int i=0; i < ri.dim; ++i) {
                index = to_string(i);
                ri.dimIndices.push_back(index);
            }
        }
    } else {
        ri.dim = 1; // Default is one element
    }

    _curReg = name;

    if (childExists(register_, "fields")) {
        _ofs << indent << "BEGIN_TYPE(" << named_register(name, "")
             << "_t, uint" << dec << regByteSize*8 << "_t)" << endl;
        incIndent();
        XMLElement *fields = register_->FirstChildElement("fields");
        for (XMLElement *field = fields->FirstChildElement("field");
             field; field = field->NextSiblingElement()) {
            ProcessField(field, access);
        }
        decIndent();
        _ofs << indent << "END_TYPE()" << endl << endl;
        ri.type = name + "_t";
    } else {
        //        ri.type = "uint" + to_string(regBitSize) + "_t";
        ri.type = name + "_t";
        _ofs << indent;
        _ofs << "typedef " << "uint" << dec << regByteSize*8 << "_t "
             << named_register(name, "") << "_t" << ";" << endl << endl;
        //        _ofs << "// Register: " << ri.type << " " << name;
        //        _ofs << endl << endl;
    }

    ri.name   = name;
    ri.offset = addrOff;
    ri.size   = regByteSize;
    _registerInfo.push_back(ri);

    // Handle enums for a register
    if (!enum_info.empty()) {
        for (auto &ei : enum_info) {
            outputAsComment(ei.desc);
            _ofs << indent << "static const uint32_t "
                 << named_register(_curReg, "")
                 << "_" << ei.field << "__"  << ei.name
                 << " = " << parseNumber(ei.value) << ";" << endl;
        }
        enum_info.clear();
        _ofs << endl;
    }
}

void svd2cpp::ProcessField(XMLElement *field, const char * reg_access) {
    // Get all field parameters
    const char *name   = getChildElement(field, "name");
    const char *desc   = getChildElement(field, "description");
    const char *access = getChildElement(field, "access");

    if (name == nullptr) {
        cerr << "Can not find name for field. Exit." << endl;
        exit(1);
    }
    if (access == nullptr) {
        if (reg_access == nullptr) {
            cerr << "Can not find access level for field. Exit." << endl;
            exit(1);
        } else access = reg_access;
    }

    // Process the bit range
    uint32_t bitOffset, bitWidth;
    ProcessBitRange(field, bitOffset, bitWidth);

    // Process access mode
    string accessMode = "??";
    if (!strcmp(access, "read-write") || !strcmp(access, "read-writeonce")) {
        accessMode = "RW";
    } else if (!strcmp(access, "read-only")) {
        accessMode = "RO";
    } else if (!strcmp(access, "write-only")) {
        accessMode = "WO";
    } else {
        cerr << "Unknown mode " << access << endl;
        exit(1);
    }

    // Print out description if available
    outputAsComment(desc);

    // Output the field
    _ofs << indent << dec << "ADD_BITFIELD_"
         << accessMode;
    _ofs << "(" << name << ", " << bitOffset << ", " << bitWidth << ")";
    _ofs << endl;

    // Add enum values if available
    if (childExists(field, "enumeratedValues")) {
        XMLElement *enums = field->FirstChildElement("enumeratedValues");
        for (XMLElement *enu  = enums->FirstChildElement("enumeratedValue");
             enu; enu  = enu->NextSiblingElement()) {
            const char *ename = getChildElement(enu, "name");
            const char *eval  = getChildElement(enu, "value");
            const char *edesc = getChildElement(enu, "description");
            enum_info_t ei;
            ei.name  = ename;
            ei.value = eval;
            ei.desc  = edesc;
            ei.field = name;
            enum_info.push_back(ei);
        }
    }
}

void svd2cpp::ProcessBitRange(XMLElement *field, uint32_t &bitOffset, uint32_t &bitWidth) {
    // Try to find a bitRange Element
    const char *range = getChildElement(field, "bitRange");
    if (range != nullptr) {
        // Process bitRange
        string rangeStr = range;
        size_t colon = rangeStr.find(':');
        if (colon == string::npos) {
            cerr << "Can not find colon in bitRange. Exit!" << endl;
            exit(1);
        }
        rangeStr[0] = ' ';
        rangeStr[colon] = ' ';
        rangeStr[rangeStr.length() - 1] = ' ';
        istringstream iss(rangeStr);
        int high, low;
        iss >> high >> low;
        if (low > high)
            swap(high, low);
        bitOffset = low;
        bitWidth  = high - low + 1;
        return;
    }

    // Try to find bitOffset and bitWidth Elements
    const char *offset = getChildElement(field, "bitOffset");
    const char *width  = getChildElement(field, "bitWidth");
    if (offset != nullptr && width != nullptr) {
        // Process bitOffset and bitWidth
        bitOffset = parseNumber(offset);
        bitWidth  = parseNumber(width);
        return;
    }

    // Try to find lsb and msb
    const char *lsb = getChildElement(field, "lsb");
    const char *msb = getChildElement(field, "msb");
    if (lsb != nullptr && msb != nullptr) {
        // Process lsb and msb
        uint32_t low  = parseNumber(lsb);
        uint32_t high = parseNumber(msb);
        bitOffset = low;
        bitWidth  = high - low + 1;
        return;
    }
    cerr << "No valid bitrange: " << range  << endl;
    exit(1);
}

void svd2cpp::ProcessComment(XMLElement *elem) {
    _ofs << "// " << indent << elem->Name();
    const char * text = elem->GetText();
    if (text != nullptr) {
        _ofs << ": ";
        if (text[0] == '\n') {
            _ofs << endl << "// ";
        }
        outputAsComment(text, true);
    } else {
        _ofs << endl;
    }
    // Check if we have some sub-elements
    if (!elem->NoChildren()) {
        incIndent();
        for (XMLElement *e = elem->FirstChildElement(); e;
             e = e->NextSiblingElement()) {
            ProcessComment(e);
        }
        decIndent();
    }
}

// Output a single/multi-line text as a comment. This
// is used e.g. for description values in the SVD file.
void svd2cpp::outputAsComment(const char *desc, bool continueLine) {
    if (!desc)
        return;  // Silently return if we have a null-pointer
    string descStr = desc;
    size_t index = 0;
    bool firstLine = true;
    while (true) {
        size_t newline = descStr.find("\\n", index);
        if (!continueLine || !firstLine) {
            _ofs << indent << "// ";
        }
        if (newline == string::npos) {
            _ofs << Trim(descStr.substr(index)) << endl;
            break;
        } else {
            _ofs << Trim(descStr.substr(index, newline - index)) << endl;
            index = newline + 2;
        }
        firstLine = false;
    }
}

uint32_t svd2cpp::parseNumber(const char *val) {
    if (val == nullptr) {
        cerr << "Can not parse nullptr. Exit" << endl;
        exit(1);
    }
    uint32_t result;
    size_t len = strlen(val);
    if (len > 1 && val[0] == '0' && tolower(val[1]) == 'x') {
        result = strtol(val, nullptr, 16);
    } else if (len > 1 && val[0] == '#') {
        result = strtol(val+1, nullptr, 2);
    } else {
        result = strtol(val, nullptr, 10);
    }
    return result;
}

const char* svd2cpp::getChildElement(XMLElement *elem, const char *name) {
    XMLElement *child = elem->FirstChildElement(name);
    return child ? child->GetText() : nullptr;
}

bool svd2cpp::childExists(XMLElement *elem, const char *name) {
    return elem->FirstChildElement(name) != nullptr;
}

// Trim a string by deleting all tabs, spaces, newlines at
// the beginning and at the end.
string svd2cpp::Trim(string str) {
    const char *typeOfWhitespaces = " \t\n";
    // Erase trailing whitespaces
    str.erase(str.find_last_not_of(typeOfWhitespaces) + 1);
    // Erase leading whitespaces
    str.erase(0, str.find_first_not_of(typeOfWhitespaces));
    // Erase \n within the string
    size_t pos=0;
    while((pos=str.find('\n')) != string::npos) {
        size_t pos2 = str.find_first_not_of(typeOfWhitespaces, pos);
        str.erase(pos, pos2-pos);
        str.insert(pos, " ");
    }
    return str;
}

void svd2cpp::pad_str(string & val, int size) {
    while (val.size() < size) val += ' ';
}

string svd2cpp::named_register(string val, const string & index) {
    size_t pos = val.find("%s");
    if (pos != string::npos) {
        val.replace(pos, 2, index);
    }
    // Did we end up with empty index brackets?
    // -> remove them!
    pos = val.find("[]");
    if (pos != string::npos) {
        val.replace(pos, 2, "");
    }
    return val;
}
