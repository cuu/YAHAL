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

    static const uint16_t npos = -1;

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
	/* Returns the number of characters in the string,
	 * not including any null-terminaltion */
    uint16_t size()  const { return _len; }
    void     reserve(uint16_t);
    uint16_t capacity() const { return _cap; }
    void     shrink_to_fit();

    // Operations
    void clear();
    String & operator += (const String &);

    // Returns a newly constructed string object with
    // its value initialized to a copy of a substring
    // of this object. The substring is the portion of
    // the object that starts at character position pos
    // and spans len characters (or until the end of the
    // string, whichever comes first).
    String substr(uint16_t pos=0, uint16_t n=npos) const;

    // Searches the string for the first occurrence of
    // character c. When pos is specified, the search
    // only includes characters at or after position pos,
    // ignoring any possible occurrences that include
    // characters before pos.
    uint16_t find (char c, uint16_t pos=0) const;

    // Conversions
    operator const char * () { return _ptr; }

    // Comparison operators
    bool operator==(const String& r) const;
    bool operator!=(const String& r) const;

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

