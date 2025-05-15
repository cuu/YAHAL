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
// structure. Not all features of SVD are (yet) supported!
//
#include "svd2cpp.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <regex>
#include <cassert>

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
    // get some basic device properties
    _device_name        = getChildElement(elem, "name");

    // get default values for registerPropertiesGroup
    _device_size        = getChildElement(elem, "size");
    _device_access      = getChildElement(elem, "access");
    _device_protection  = getChildElement(elem, "protection");
    _device_resetValue  = getChildElement(elem, "resetValue");
    _device_resetMask   = getChildElement(elem, "resetMask");

    // Check MCU name
    if (_device_name.empty()) {
        cerr << "Can not find device name (MCU) in file " << infile
             << endl;
        exit(1);
    }

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
            ProcessAsComment(elem);
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
            _ofs << indent << "#define " + irq.name
                 << string(25-irq.name.size(),' ') << dec << irq.value << endl;
        }
    }
}

void svd2cpp::ProcessPeripheral(XMLElement *peripheral) {
    // get some basic device properties
    _peri_name          = getChildElement(peripheral, "name");
    _peri_baseAddress   = getChildElement(peripheral, "baseAddress");
    _peri_description   = getChildElement(peripheral, "description");

    // get default values for registerPropertiesGroup
    _peri_size          = getChildElement(peripheral, "size");
    _peri_access        = getChildElement(peripheral, "access");
    _peri_protection    = getChildElement(peripheral, "protection");
    _peri_resetValue    = getChildElement(peripheral, "resetValue");
    _peri_resetMask     = getChildElement(peripheral, "resetMask");

    // Some sanity checks
    if (_peri_name.empty()) {
        cerr << "Can not find name for peripheral. Exit." << endl;
        exit(1);
    }
    if (_peri_baseAddress.empty()) {
        cerr << "Can not find base address for peripheral. Exit." << endl;
        exit(1);
    }

    // Get base address and default register size in bytes
    uint32_t baseAddr_int = parseNumber(_peri_baseAddress);

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
    outputAsComment(_peri_description);

    // Start a new namespace for every peripheral
    _ofs << indent << "namespace _" << _peri_name << "_ {" << endl << endl;
    incIndent();

    // Loop over all registers. This will output all register
    // field definitions and optionally related enum-values.
    XMLElement *registers = peripheral->FirstChildElement("registers");
    if (registers) {
        XMLElement *cluster = registers->FirstChildElement("cluster");
        if (cluster) {
            cerr << "Clusters are not supported. Exit." << endl;
            exit(1);
        }
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
        periType = named_register(_peri_name,"") + "_t";

        // Start the register struct
        _ofs << indent << "struct " << periType << " {" << endl;
        incIndent();

        // Loop over all registers
        uint32_t curr_off = 0;
        int res_index     = 0;
        while(_registerInfo.registers_left()) {
            // Get next register with the smallest offset
            register_info_t * reg = _registerInfo.next_register();

            // Check if we have to fill a gap with 'reserved'
            if (curr_off != reg->offset) {
                uint32_t diff  = reg->offset - curr_off;
                uint32_t type_size = 1;
                // Try to use same int length as register
                if ((diff % reg->size) == 0) {
                    diff   /= reg->size;
                    type_size = reg->size;
                }
                string type = "uint" + to_string(type_size * 8) + "_t";
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
         << _peri_name << " = (*(" << periType << " *)0x" << hex
         << baseAddr_int << ");" << endl;

    // Generate additional register struct instances,
    // depending on the MCU type
    bool is_rpi_mcu = (_device_name == "RP2040" || _device_name == "RP2350");
    if (is_rpi_mcu && ((baseAddr_int >> 28) <= 5)) {
        _ofs << indent << "static " << periType << " & "
             << _peri_name << "_XOR = (*(" << periType << " *)0x" << hex
             << baseAddr_int + 0x1000 << ");" << endl;
        _ofs << indent << "static " << periType << " & "
             << _peri_name << "_SET = (*(" << periType << " *)0x" << hex
             << baseAddr_int + 0x2000 << ");" << endl;
        _ofs << indent << "static " << periType << " & "
             << _peri_name << "_CLR = (*(" << periType << " *)0x" << hex
             << baseAddr_int + 0x3000 << ");" << endl;
    }

    // Finalize the peripheral namespace
    _ofs << endl;
    decIndent();
    _ofs << indent << "} // _" << _peri_name << "_" << endl;
    _ofs << endl;
}


void svd2cpp::ProcessRegister(XMLElement *register_) {
    // get some register properties
    _reg_name        = getChildElement(register_, "name");
    _reg_addrOffset  = getChildElement(register_, "addressOffset");
    _reg_description = getChildElement(register_, "description");

    // get values for registerPropertiesGroup
    _reg_size        = getChildElement(register_, "size");
    _reg_access      = getChildElement(register_, "access");
    _reg_protection  = getChildElement(register_, "protection");
    _reg_resetValue  = getChildElement(register_, "resetValue");
    _reg_resetMask   = getChildElement(register_, "resetMask");

    if (_reg_name.empty()) {
        cerr << "Can not find name for register. Exit." << endl;
        exit(1);
    }

    if (_reg_addrOffset.empty()) {
        cerr << "Can not find address Offset for register " << _reg_name
             << ". Exit." << endl;
        exit(1);
    }
    uint32_t addrOff = parseNumber(_reg_addrOffset);

    // Print out description if available
    outputAsComment(_reg_description);
    if (!_reg_resetValue.empty()) {
        outputAsComment("Reset value: " + _reg_resetValue);
    }

    // Get the valid register size in bytes
    uint32_t regByteSize = 0;
    if (!_reg_size.empty()) {
        regByteSize = parseNumber(_reg_size) / 8;
    } else if (!_peri_size.empty()) {
        regByteSize = parseNumber(_peri_size) / 8;
    } else if (!_device_size.empty()) {
        regByteSize = parseNumber(_device_size) / 8;
    } else {
        cerr << "Can not determine register size for " << _reg_name << ". Exit" << endl;
        exit(1);
    }

    register_info_t ri;
    ri.userIndex = false;

    // Handle dimensions
    string dim          = getChildElement(register_, "dim");
    string dimIncrement = getChildElement(register_, "dimIncrement");
    if (!dim.empty()) {
        if (dimIncrement.empty()) {
            cerr << "dim given without dimIncrement for register " << _reg_name
                 << ". Exit." << endl;
            exit(1);
        }
        ri.dim    = parseNumber(dim);
        ri.dimInc = parseNumber(dimIncrement);
        // Check if we have a specific register naming
        string dimIndex = getChildElement(register_, "dimIndex");
        string index;
        if (!dimIndex.empty()) {
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

//    _curReg = name;

    if (childExists(register_, "fields")) {
        _ofs << indent << "BEGIN_TYPE(" << named_register(_reg_name, "")
             << "_t, uint" << dec << regByteSize*8 << "_t)" << endl;
        incIndent();
        XMLElement *fields = register_->FirstChildElement("fields");
        for (XMLElement *field = fields->FirstChildElement("field");
             field; field = field->NextSiblingElement()) {
            ProcessField(field);
        }
        decIndent();
        _ofs << indent << "END_TYPE()" << endl << endl;
        ri.type = _reg_name + "_t";
    } else {
        ri.type = _reg_name + "_t";
        _ofs << indent;
        _ofs << "typedef " << "uint" << dec << regByteSize*8 << "_t "
             << named_register(_reg_name, "") << "_t" << ";" << endl << endl;
    }

    ri.name   = _reg_name;
    ri.offset = addrOff;
    ri.size   = regByteSize;
    _registerInfo.push_back(ri);

    // Handle enums for a register
    if (!enum_info.empty()) {
        for (auto &ei : enum_info) {
            outputAsComment(ei.desc);
            _ofs << indent << "static const uint32_t "
                 << named_register(_reg_name, "")
                 << "_" << ei.field << "__"  << ei.name
                 << " = " << parseNumber(ei.value) << ";" << endl;
        }
        enum_info.clear();
        _ofs << endl;
    }
}

void svd2cpp::ProcessField(XMLElement *field) {
    // Get all field parameters
    _field_name         = getChildElement(field, "name");
    _field_description  = getChildElement(field, "description");
    _field_access       = getChildElement(field, "access");
    _field_modWrVal     = getChildElement(field, "modifiedWriteValues");
    _field_wrConst      = getChildElement(field, "writeConstraint");
    _field_read_action  = getChildElement(field, "readAction");

    if (_field_name.empty()) {
        cerr << "Can not find name for field. Exit." << endl;
        exit(1);
    }
    if (_field_access.empty()) {
        if (!_reg_access.empty()) {
            _field_access = _reg_access;
        } else if (!_peri_access.empty()) {
            _field_access = _peri_access;
        } else if (!_device_access.empty()) {
            _field_access = _device_access;
        } else {
            cerr << "Can not find access level for field. Exit." << endl;
            exit(1);
        }
    }

    // Process the bit range
    uint32_t bitOffset, bitWidth;
    ProcessBitRange(field, bitOffset, bitWidth);

    // Process access mode
    string accessMode = "??";
    if (_field_access == "read-write" ||
        _field_access == "read-writeonce") {
        accessMode = "RW";
    } else if (_field_access == "read-only") {
        accessMode = "RO";
    } else if (_field_access == "write-only") {
        accessMode = "WO";
    } else {
        cerr << "Unknown mode " << _field_access << endl;
        exit(1);
    }

    // Print out description if available
    outputAsComment(_field_description);
    if (!_field_modWrVal.empty()) {
        outputAsComment("modifiedWriteValues: " + _field_modWrVal);
    }
    if (!_field_wrConst.empty()) {
        outputAsComment("writeConstraint: " + _field_wrConst);
    }
    if (!_field_read_action.empty()) {
        outputAsComment("readAction: " + _field_read_action);
    }

    // Output the field
    _ofs << indent << dec << "ADD_BITFIELD_"
         << accessMode;
    _ofs << "(" << _field_name << ", " << bitOffset << ", " << bitWidth << ")";
    _ofs << endl;

    // Add enum values if available
    if (childExists(field, "enumeratedValues")) {
        XMLElement *enums = field->FirstChildElement("enumeratedValues");
        for (XMLElement *enu  = enums->FirstChildElement("enumeratedValue");
             enu; enu  = enu->NextSiblingElement()) {
            enum_info_t ei;
            ei.field = _field_name;
            ei.name  = getChildElement(enu, "name");
            ei.value = getChildElement(enu, "value");
            ei.desc  = getChildElement(enu, "description");
            enum_info.push_back(ei);
        }
    }
}

void svd2cpp::ProcessBitRange(XMLElement *field, uint32_t &bitOffset, uint32_t &bitWidth) {
    // Try to find a bitRange Element
    string range = getChildElement(field, "bitRange");
    if (!range.empty()) {
        // Process bitRange
        size_t colon = range.find(':');
        if (colon == string::npos) {
            cerr << "Can not find colon in bitRange. Exit!" << endl;
            exit(1);
        }
        range[0] = ' ';
        range[colon] = ' ';
        range[range.length() - 1] = ' ';
        istringstream iss(range);
        int high, low;
        iss >> high >> low;
        if (low > high)
            swap(high, low);
        bitOffset = low;
        bitWidth  = high - low + 1;
        return;
    }

    // Try to find bitOffset and bitWidth Elements
    string offset = getChildElement(field, "bitOffset");
    string width  = getChildElement(field, "bitWidth");
    if (!offset.empty() && !width.empty()) {
        // Process bitOffset and bitWidth
        bitOffset = parseNumber(offset);
        bitWidth  = parseNumber(width);
        return;
    }

    // Try to find lsb and msb
    string lsb = getChildElement(field, "lsb");
    string msb = getChildElement(field, "msb");
    if (!lsb.empty() && !msb.empty()) {
        // Process lsb and msb
        uint32_t low  = parseNumber(lsb);
        uint32_t high = parseNumber(msb);
        bitOffset = low;
        bitWidth  = high - low + 1;
        return;
    }
    cerr << "No valid bitrange: " << range << endl;
    exit(1);
}

void svd2cpp::ProcessAsComment(XMLElement *elem) {
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
            ProcessAsComment(e);
        }
        decIndent();
    }
}

// Output a single/multi-line text as a comment. This
// is used e.g. for description values in the SVD file.
void svd2cpp::outputAsComment(string desc, bool continueLine) {
    if (desc.empty()) {
        // Silently return if we have a null-pointer
        return;
    }
    desc = regex_replace(desc, regex("[' ']{2,}"), " ");

    size_t index = 0;
    bool firstLine = true;

    while (true) {
        // Start with C++ comment if not continuing a line
        if (!continueLine || !firstLine) {
            _ofs << indent << "// ";
        }
        // Find a newline in text
        size_t newline = desc.find("\\n", index);
        if (newline == string::npos) {
            if ((desc.size() - index) < 70) {
                // We (finally) have a short line ->
                // output it and exit.
                _ofs << Trim(desc.substr(index)) << endl;
                break;
            } else {
                // Line too long. Find last blank in line.
                size_t blank = desc.rfind(' ', index+70);
                if ((blank != string::npos) && (blank >= index)) {
                    _ofs << Trim(desc.substr(index, blank-index)) << endl;
                    index = blank+1;
                } else {
                    // Strange: very long line without any blank ...
                    _ofs << Trim(desc.substr(index)) << endl;
                    break;
                }
            }
        } else {
            // We found a newline. Also check for long string
            if ((newline - index) < 70) {
                _ofs << Trim(desc.substr(index, newline - index)) << endl;
                index = newline + 2;
            } else {
                // Line too long. Find last blank in line
                size_t blank = desc.rfind(' ', index+70);
                if ((blank != string::npos) && (blank >= index)) {
                    _ofs << Trim(desc.substr(index, blank - index)) << endl;
                    index = blank+1;
                } else {
                    // Strange:: very long line without blank...
                    _ofs << Trim(desc.substr(index, newline - index)) << endl;
                    index = newline + 2;
                }
            }
        }
        firstLine = false;
    }
}


enum output_state {
    TRIM_START,
    FIND_LINE_END
};

void svd2cpp::outputAsComment2(const char *desc, bool continueLine) {
    if (!desc) {
        // Silently return if we have a null-pointer
        return;
    }

    const char *typeOfWhitespaces = " \t\n";
    string descStr = desc;
    // Convert all literal newlines to real newlines
    descStr = regex_replace(descStr, regex("[\"\\n\"]{2,}"), "\n");


    bool running = true;
    string str = desc;
    output_state state = TRIM_START;
    size_t line_start = 0;

    while(running) {
        switch(state) {
            case TRIM_START: {
                line_start= str.find_first_not_of(typeOfWhitespaces);
                assert(line_start != string::npos);
                state = FIND_LINE_END;
                break;
            }
            case FIND_LINE_END: {
//                if ()
            }
        }
    }
}


uint32_t svd2cpp::parseNumber(const string & s) {
    if (s.empty()) {
        cerr << "Can not parse empty string as number. Exit" << endl;
        exit(1);
    }
    uint32_t result;
    if (s.size() > 1 && s[0] == '0' && tolower(s[1]) == 'x') {
        result = strtol(s.c_str()+2, nullptr, 16);
    } else if (s.size() > 1 && s[0] == '#') {
        result = strtol(s.c_str()+1, nullptr, 2);
    } else {
        result = strtol(s.c_str(), nullptr, 10);
    }
    return result;
}

string svd2cpp::getChildElement(XMLElement *elem, const char *name) {
    XMLElement *child = elem->FirstChildElement(name);
    return child ? child->GetText() : "";
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
    if (val.size() >= size) {
        val += ' ';
    } else {
        while (val.size() < size) val += ' ';
    }
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
