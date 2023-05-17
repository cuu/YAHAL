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
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

// Indent stuff
int currentIndent = 0;
inline void indentRight() { currentIndent += 4; }
inline void indentLeft()  { currentIndent -= 4; }

std::ostream& indent(std::ostream& os) {
    os << string(currentIndent, ' ');
    return os;
}

string pad_str(string val, int size) {
    string res = val;
    while (res.size() < size) res += ' ';
    return res;
}

string named_register(string val, string index) {
    string res = val;
    size_t pos = res.find("[%s]");
    if (pos != string::npos) {
        res.replace(pos, 4, index);
    }
    return res;
}


class svd2cpp {
public:
    // MCU name
    string MCU;

    // The output file
    ofstream _ofs;

    // Register being processed
    string currentRegister;

    // Current register size in bits. This
    // value can be set by a peripheral, but
    // overwritten by a specific register.
    int currentRegByteSize = 0;

    // List of registers for one peripheral
    struct register_info_t {
        string type;       // Type of register
        string name;       // Name of register
        int size;          // Size of register in bytes
        int dim;           // Dimension (array if > 1)
        int dimInc;        // Increment for dim elements in bytes
        bool userIndex;    // User-defined Index names
        vector<string> dimIndices; // Specific index names
        uint32_t offset;   // Offset from base address in bytes
    };

    class register_vector : public vector<register_info_t> {
      public:
        bool registers_left() {
            for (auto & e : *this) {
                if(e.dim > 0) return true;
            }
            return false;
        }

        register_info_t * next_register() {
            uint32_t min = 0xffffffff;
            register_info_t * res = nullptr;
            for (auto & e : *this) {
                if ((e.dim > 0) && (e.offset < min)) {
                    min = e.offset;
                    res = &e;
                }
            }
            return res;
        }
    };
    register_vector register_info;

    // List of enum value properties
    struct enum_info_t {
        const char *field;
        const char *desc;
        const char *name;
        const char *value;
    };
    vector<enum_info_t> enum_info;

    // List of interrupts
    struct irq_info_t {
        const char *name;
        int value;
    };
    vector<irq_info_t> irq_info;

    // Trim a string by deleting all tabs, spaces, newlines at
    // the beginning and at the end.
    string Trim(string str) {
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

    // Get the value of a child element with name 'name'.
    // Return nullptr if child is not exiting or there is no value
    const char* getChildElement(XMLElement *elem, const char *name) {
        XMLElement *child = elem->FirstChildElement(name);
        return child ? child->GetText() : nullptr;
    }

    // Check if a child node with name 'name' is existing
    bool childExists(XMLElement *elem, const char *name) {
        return elem->FirstChildElement(name) != nullptr;
    }

    // Parse a string with a numerical value to a uint32_t.
    // Automatically detect hex and decimal values. Octal
    // values are not supported right now.
    uint32_t parseNumber(const char *val) {
        if (val == nullptr) {
            cerr << "Can not parse nullptr. Exit" << endl;
            exit(1);
        }
        istringstream iss(val);
        uint32_t result;
        int len = strlen(val);
        if (len > 1 && val[0] == '0' && tolower(val[1]) == 'x') {
            iss >> hex >> result;
        } else {
            iss >> dec >> result;
        }
        return result;
    }

    // Output a single/multi-line text as a comment. This
    // is used e.g. for description values in the SVD file.
    void outputAsComment(const char *desc) {
        if (!desc)
            return;  // Silently return if we have a null-pointer
        string descStr = desc;
        size_t index = 0;
        while (true) {
            size_t newline = descStr.find("\\n", index);
            if (newline == string::npos) {
                _ofs << indent;
                _ofs << "// " << Trim(descStr.substr(index)) << endl;
                break;
            } else {
                _ofs << indent;
                _ofs << "// " << Trim(descStr.substr(index, newline - index))
                     << endl;
                index = newline + 2;
            }
        }
    }

    void ProcessComment(XMLElement *elem) {
        _ofs << "// " << indent << elem->Name();
        if (elem->GetText() != NULL) {
            _ofs << ": " << elem->GetText() << endl;
        } else
            _ofs << endl;

        // Check if we have some sub-elements
        if (!elem->NoChildren()) {
            currentIndent += 2;
            for (XMLElement *e = elem->FirstChildElement(); e;
                    e = e->NextSiblingElement()) {
                ProcessComment(e);
            }
            currentIndent -= 2;
        }
    }

    void ProcessBitRange(XMLElement *field, int &bitOffset, int &bitWidth) {
        // Try to find a bitRange Element
        const char *range = getChildElement(field, "bitRange");
        if (range != nullptr) {
            // Process bitRange
            string rangeStr = range;
            size_t colon = rangeStr.find(":");
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
            bitWidth = high - low + 1;
            return;
        }

        // Try to find bitOffset and bitWidth Elements
        const char *offset = getChildElement(field, "bitOffset");
        const char *width  = getChildElement(field, "bitWidth");
        if (offset != nullptr && width != nullptr) {
            // Process bitOffset and bitWidth
            bitOffset = parseNumber(offset);
            bitWidth = parseNumber(width);
            return;
        }

        // Try to find lsb and msb
        const char *lsb = getChildElement(field, "lsb");
        const char *msb = getChildElement(field, "msb");
        if (lsb != nullptr && msb != nullptr) {
            // Process lsb and msb
            int low   = parseNumber(lsb);
            int high  = parseNumber(msb);
            bitOffset = low;
            bitWidth  = high - low + 1;
            return;
        }
        cerr << "No valid bitrange found in field. Exit!" << endl;
        exit(1);
    }

    void ProcessField(XMLElement *field) {
        // Get all field parameters
        const char *name   = getChildElement(field, "name");
        const char *desc   = getChildElement(field, "description");
        const char *access = getChildElement(field, "access");

        if (name == nullptr) {
            cerr << "Can not find name for field. Exit." << endl;
            exit(1);
        }
        if (access == nullptr) {
            cerr << "Can not find access level for field. Exit." << endl;
            exit(1);
        }

        // Process the bit range
        int bitOffset, bitWidth;
        ProcessBitRange(field, bitOffset, bitWidth);

        // Process access mode
        string accessMode = "??";
        if (!strcmp(access, "read-write")) {
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
        _ofs << indent << dec << "ADD_BITFIELD_"
             << accessMode;
        _ofs << "(" << name << ", " << bitOffset << ", " << bitWidth << ")";
        _ofs << endl;

        // Check if we have some enum values
        if (childExists(field, "enumeratedValues")) {
            XMLElement *enums = field->FirstChildElement("enumeratedValues");
            for (XMLElement *enu  = enums->FirstChildElement("enumeratedValue");
                        enu; enu  = enu->NextSiblingElement()) {
                const char *ename = getChildElement(enu, "name");
                const char *value = getChildElement(enu, "value");
                const char *desc  = getChildElement(enu, "description");
                enum_info_t ei;
                ei.name  = ename;
                ei.value = value;
                ei.desc  = desc;
                ei.field = name;
                enum_info.push_back(ei);
            }
        }
    }

    void ProcessRegister(XMLElement *register_) {
        // Get register properties
        const char *r_name     = getChildElement(register_, "name");
        const char *size       = getChildElement(register_, "size");
        const char *addrOffset = getChildElement(register_, "addressOffset");
        const char *desc       = getChildElement(register_, "description");
        const char *resetVal   = getChildElement(register_, "resetValue");

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

        // Get the valid register size in bits
        int regByteSize = 0;
        if (size) {
            regByteSize = parseNumber(size) / 8;
        } else {
            regByteSize = currentRegByteSize;
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
            istringstream iss;
            string index;
            string indices;
            if (dimIndex) {
                ri.userIndex = 1;
                indices = dimIndex;
                // Replace all commas by blanks
                for (char & c : indices) if (c==',') c = ' ';
                iss.str(indices);
            }
            for(int i=0; i < ri.dim; ++i) {
                if (dimIndex) iss >> index;
                else index = to_string(i);
                ri.dimIndices.push_back(index);
            }
        } else {
            ri.dim = 1; // Default is one element
        }

        currentRegister = name;

        if (childExists(register_, "fields")) {
            _ofs << indent << "BEGIN_TYPE(" << named_register(name, "")
                 << "_t, uint" << dec << regByteSize*8 << "_t)" << endl;
            indentRight();
            XMLElement *fields = register_->FirstChildElement("fields");
            for (XMLElement *field = fields->FirstChildElement("field");
                      field; field = field->NextSiblingElement()) {
                ProcessField(field);
            }
            indentLeft();
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
        register_info.push_back(ri);

        // Handle enums for a register
        if (enum_info.size()) {
            for (auto &ei : enum_info) {
                outputAsComment(ei.desc);
                _ofs << indent << "static const uint32_t "
                     << named_register(currentRegister, "")
                     << "_" << ei.field << "__"  << ei.name
                     << " = " << ei.value << ";" << endl;
            }
            enum_info.clear();
            _ofs << endl;
        }
    }

    void ProcessPeripheral(XMLElement *peripheral) {
        const char *name     = getChildElement(peripheral, "name");
        const char *size     = getChildElement(peripheral, "size");
        const char *baseAddr = getChildElement(peripheral, "baseAddress");
        const char *desc     = getChildElement(peripheral, "description");

        if (name == nullptr) {
            cerr << "Can not find name for peripheral. Exit." << endl;
            exit(1);
        }
        if (baseAddr == nullptr) {
            cerr << "Can not find base address for peripheral. Exit." << endl;
            exit(1);
        }
        uint32_t baseAddr_int = parseNumber(baseAddr);
        if (size) {
            currentRegByteSize = parseNumber(size) / 8;
        }

        // Check if we are a derived peripheral
        string derivedFrom = "";
        const XMLAttribute *derived = peripheral->FindAttribute("derivedFrom");
        if (derived) {
            derivedFrom += derived->Value();
        }

        // Check if we have some interrupt definitons
        for (XMLElement *irq = peripheral->FirstChildElement("interrupt"); irq;
                         irq = irq->NextSiblingElement("interrupt")) {
            irq_info_t i;
            i.name  = getChildElement(irq, "name");
            i.value = parseNumber(getChildElement(irq, "value"));
            irq_info.push_back(i);
        }

        // Print out description if available
        outputAsComment(desc);

        _ofs << indent << "namespace _" << name << "_  {" << endl << endl;
        indentRight();

        XMLElement *registers = peripheral->FirstChildElement("registers");
        if (registers) {
            for (XMLElement *register_ = registers->FirstChildElement("register");
                  register_; register_ = register_->NextSiblingElement()) {
                ProcessRegister(register_);
            }
        }

        string periType;
        if (derivedFrom.size() == 0) {
            _ofs << indent << "struct " << name << "_t {" << endl;
            indentRight();
            uint32_t curr_off = 0;
            int res_index     = 0;
            string tmp;

            while(register_info.registers_left()) {
                // Get next register
                register_info_t * reg = register_info.next_register();
                // Check if we have to fill a gap with 'reserved'
                if (curr_off != reg->offset) {
                    int diff  = reg->offset - curr_off;
                    int typelen = 1;
                    // Try to use same int length as register
                    if ((diff % reg->size) == 0) {
                        diff   /= reg->size;
                        typelen = reg->size;
                    }
                    string type = "uint" + to_string(typelen * 8) + "_t";
                    tmp = pad_str(type, 30);
                    _ofs << indent << tmp << "reserved"
                         << to_string(res_index++);
                    if (diff > 1) {
                        _ofs << "[" << diff << "]";
                    }
                    _ofs << ";" << endl;
                    curr_off = reg->offset;
                }
                // Check if we have an array
                int dim_size = 0;
                do {
                    dim_size++;
                    curr_off += reg->size;
                    reg->dim--;
                    reg->offset += reg->dimInc;
                    if (reg->dim == 0) break;
                    if (reg->userIndex) break;
                } while(curr_off == reg->offset);
                // Output the register
                tmp = pad_str( named_register(reg->type, ""), 30);
                _ofs << indent << tmp;
                if (dim_size > 1) {
                    _ofs << named_register(reg->name, "");
                    _ofs << "[" << dim_size << "]";
                } else {
                    string index;
                    if (reg->dimIndices.size()) {
                        index = reg->dimIndices[0];
                        reg->dimIndices.erase(reg->dimIndices.begin());
                    }
                    _ofs << named_register(reg->name, index);
                }
                _ofs << ";" << endl;
            }

            register_info.clear();

            indentLeft();
            _ofs << indent << "};" << endl;
            _ofs << endl;
            periType = string(name) + "_t";
        } else {
            periType = "_" + derivedFrom + "_::" + derivedFrom + "_t";
        }

        _ofs << indent << "static "  << periType << " & "
             << name << "     = (*(" << periType << " *)0x" << hex
             << baseAddr_int << ");" << endl;
        if (MCU == "RP2040" && ((baseAddr_int >> 28) <= 5)) {
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
        _ofs << endl;

        indentLeft();
        _ofs << indent << "} // _" << name << "_" << endl;
        _ofs << endl;
    }

    void usage() {
        cout << "Usage: svd2cpp [-o outfile] <file>.svd"<< endl;
        cout << endl;
        cout << "-o outfile  : The output filename. Default is <file>.cpp" << endl;
        cout << "<file>.svd  : A valid SVD file" << endl;
        exit(1);
    }

    int main(int argc, char *argv[]) {
        string infile;
        string outfile;
        int opt;
        while ((opt = getopt(argc, argv, ":o:")) != -1) {
            switch (opt) {
                case 'o': {
                    outfile = optarg;
                    break;
                }
                case ':': {
                    cerr << "Option needs a value!" << endl;
                    usage();
                    break;
                }
                case '?': {
                    cerr << "Unknown option '" << (char)optopt << "'" << endl;
                    usage();
                    break;
                }
            }
        }

        if (optind == (argc-1)) {
            infile = argv[optind];
        } else {
            cerr << "No or too many filenames given!" << endl;
            usage();
        }

        // Process the file name
        size_t dot = infile.find_last_of('.');
        string name_we;
        if (dot != string::npos) {
            name_we = infile.substr(0, dot);
        } else {
            name_we = infile;
        }
        if(outfile.size() == 0) {
            outfile = name_we + ".h";
        }

        XMLDocument svd;
        cout << "Reading file " << infile << endl;
        XMLError ret = svd.LoadFile(infile.c_str());
        if (ret != XML_SUCCESS) {
            cerr << "Can not load file " << infile << ", Error code: " << ret
                 << endl;
            exit(1);
        }

        XMLElement *elem = svd.RootElement();
        if (elem == nullptr) {
            cerr << "Can not find root element in file " << infile
                 << endl;
            exit(1);
        }

        // Get the MCU name
        if (!childExists(elem, "name")) {
            cerr << "Can not find MCU name in file " << infile
                 << endl;
            exit(1);
        }
        MCU = getChildElement(elem, "name");

        // Open out file
        cout << "Writing file " << outfile << endl;
        _ofs.open(outfile.c_str(), ios::binary | ios::out);

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
            } else if (elemName == "licenseText") {
                outputAsComment(elem->GetText());
            } else {
                ProcessComment(elem);
            }
            elem = elem->NextSiblingElement();
        }

        // Sort the interrupts by number and print them
        std::sort(irq_info.begin(), irq_info.end(),
                [](irq_info_t &a, irq_info_t &b) {
                    return a.value < b.value;
        });
        _ofs << indent << "// Interrupt numbers" << endl;
        for (auto &elem : irq_info) {
            string tmp = "#define " + string(elem.name) + " ";
            while (tmp.size() < 30) tmp += ' ';
            _ofs << indent << tmp << dec << elem.value << endl;
        }
        return 0;
    }
};

int main(int argc, char *argv[]) {
    svd2cpp inst;
    inst.main(argc, argv);
}
