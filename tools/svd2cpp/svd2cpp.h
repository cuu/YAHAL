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
// structure. Not all (but many) features of the
// SVD specification are supported!
//
#include "tinyxml2.h"
#include "registerInfo.h"
#include <fstream>

using namespace std;
using namespace tinyxml2;

class svd2cpp {
    friend std::ostream& indent(std::ostream& os);

public:
    // This class is a singleton
    static svd2cpp inst;

    // Convert the SVD-infile to a C++ structure
    // and write it to outfile. The root element
    // of the XML DOM is the third parameter.
    void processSvdFile(const string & infile,
                        const string & outfile,
                        XMLElement *root,
                        bool generateIrqNumbers);
 private:
    // Singleton, so no public CTOR
    svd2cpp() = default;

    // Process a peripheral with all its registers and enums
    void ProcessPeripheral(XMLElement *peripheral);

    void ProcessRegister(XMLElement *register_);

    void ProcessField(XMLElement *field, const char * access);

    static void ProcessBitRange(XMLElement *field, uint32_t &bitOffset, uint32_t &bitWidth);

    void ProcessComment(XMLElement *elem);

    // Utility methods

    // Output a single/multi-line text as a comment. This
    // is used e.g. for description values in the SVD file.
    void outputAsComment(const char *desc, bool continueLine = false);


    // Parse a string with a numerical value to an uint32_t.
    // Automatically detect binary, decimal and hex values.
    static uint32_t parseNumber(const char *val);

    // Get the value of a child element with name 'name'.
    // Return nullptr if child is not existing or there is no value
    static const char* getChildElement(XMLElement *elem, const char *name);

    // Check if a child node with name 'name' is existing
    static bool childExists(XMLElement *elem, const char *name);


    // Trim a string by deleting all tabs, spaces, newlines at
    // the beginning and at the end.
    static string Trim(string str);

    static void pad_str(string & val, int size);

    static string named_register(string val, const string & index);

    /////////////
    // Attributes
    /////////////
    string      _mcu;               // MCU name
    ofstream    _ofs;               // The output file
    string      _curReg;            // Current Register being processed
    uint32_t    _curRegSizeBytes{}; // Size in bytes of current register
    uint32_t    _globalSize{};      // Size in top-level tags. Inherited by peripherals

    // List of register information
    registerInfo _registerInfo;

    // List of enum value properties
    struct enum_info_t {
        const char *field {nullptr};
        const char *desc  {nullptr};
        const char *name  {nullptr};
        const char *value {nullptr};
    };
    vector<enum_info_t> enum_info;

    // List of interrupts
    struct irq_info_t {
        const char *name  {nullptr};
        uint32_t    value {0};
    };
    vector<irq_info_t> irq_info;

    // Indent stuff
    int _currentIndent = 0;
    inline void incIndent() { _currentIndent += 4; }
    inline void decIndent() { _currentIndent -= 4; }
};
