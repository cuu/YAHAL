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
// This is a class for handling character strings.
// The class tries to implement most important
// functionality of the standard std::string class.
//

#ifndef STRING_H
#define STRING_H
#include <cstdint>

class String
{
public:
    // Constructors
    String(const char * ptr = "");
    String(const String &);
    String(char);

    // Destructor
    virtual ~String();

    // Assignment
    String & operator = (const char *);
    String & operator = (const String &);
    String & operator = (char);

    // Move support
    String(String &&);
    String & operator = (String &&);

    // Element access
    const char & operator [] (uint16_t) const;
    char &       operator [] (uint16_t);
    const char * c_str() { return _ptr; }

    // Capacity
    bool     empty() const { return _len == 0; }
    uint16_t size()  const { return _len; }
    void     reserve(uint16_t);
    uint16_t capacity() const { return _cap; }
    void     shrink_to_fit();

    // Operations
    void clear();
    String & operator += (const String &);

    // Conversions
    operator const char * () { return _ptr; }

protected:
    uint16_t _len;
    uint16_t _cap;
    char *   _ptr;

    void reserve_only(uint16_t bytes);
};

// Conversions
String to_String(int num, int base=10);

// Global operators
String operator + (const String & lhs, const String & rhs);

#endif /* _YAHAL_STRING_H_ */

