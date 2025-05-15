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

    void ProcessField(XMLElement *field);

    static void ProcessBitRange(XMLElement *field, uint32_t &bitOffset, uint32_t &bitWidth);

    void ProcessAsComment(XMLElement *elem);

    // Utility methods

    // Output a single/multi-line text as a comment. This
    // is used e.g. for description values in the SVD file.
    void outputAsComment(string s, bool continueLine = false);
    void outputAsComment2(const char *desc, bool continueLine = false);


    // Parse a string with a numerical value to an uint32_t.
    // Automatically detect binary, decimal and hex values.
    static uint32_t parseNumber(const string &s);

    // Get the value of a child element with name 'name'.
    // Return nullptr if child is not existing or there is no value
    static string getChildElement(XMLElement *elem, const char *name);

    // Check if a child node with name 'name' is existing
    static bool childExists(XMLElement *elem, const char *name);


    // Trim a string by deleting all tabs, spaces, newlines at
    // the beginning and at the end.
    static string Trim(string str);

    static void pad_str(string & val, int size);

    static string named_register(string val, const string & index);

    static inline std::string ValOrEmpty(const char * s) {
        return s == nullptr ? "" : s;
    }

    // Device attributes
    string _device_name;
    string _device_size;
    string _device_access;
    string _device_protection;
    string _device_resetValue;
    string _device_resetMask;

    // Peripheral attributes
    string _peri_name;
    string _peri_size;
    string _peri_access;
    string _peri_protection;
    string _peri_resetValue;
    string _peri_resetMask;
    string _peri_baseAddress;
    string _peri_description;

    // Register attributes
    string _reg_name;
    string _reg_size;
    string _reg_access;
    string _reg_protection;
    string _reg_resetValue;
    string _reg_resetMask;
    string _reg_addrOffset;
    string _reg_description;

    // Field attributes
    string _field_name ;
    string _field_description;
    string _field_access;
    string _field_modWrVal;
    string _field_wrConst;
    string _field_read_action;

    // The output file
    ofstream _ofs;

    // List of register information
    registerInfo _registerInfo;

    // List of enum value properties
    struct enum_info_t {
        string field;
        string desc;
        string name;
        string value;
    };
    vector<enum_info_t> enum_info;

    // List of interrupts
    struct irq_info_t {
        string      name;
        uint32_t    value;
    };
    vector<irq_info_t> irq_info;

    // Indent stuff
    int _currentIndent = 0;
    inline void incIndent() { _currentIndent += 4; }
    inline void decIndent() { _currentIndent -= 4; }
};
