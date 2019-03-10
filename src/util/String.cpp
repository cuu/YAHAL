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

#include "yahal_assert.h"
#include "String.h"
#include <algorithm>
#include <cstring>

String::String(const char * ptr)
   : _len(strlen(ptr)), _cap(_len), _ptr(new char[_cap+1]) {
    strcpy(_ptr, ptr);
}

String::String(const String & s)
   : _len(s._len), _cap(_len), _ptr(new char[_cap+1]) {
   strcpy(_ptr, s._ptr);
}

String::String(char c, uint16_t n)
   : _len(n), _cap(n), _ptr(new char[n+1]) {
    uint16_t i=0;
    for (; i < n; ++i) _ptr[i] = c;
    _ptr[i] = 0;
}

String::~String()
{
    delete [] _ptr;
}

String & String::operator = (const char * ptr) {
    uint16_t temp = strlen(ptr);
    reserve_only(temp);
    strcpy(_ptr, ptr);
    _len = temp;
    return *this;
}

String & String::operator = (const String & s) {
    reserve_only(s._len);
    strcpy(_ptr, s._ptr);
    _len = s._len;
    return *this;
}

String & String::operator = (char c) {
    reserve_only(1);
    _ptr[0] = c;
    _ptr[1] = 0;
    _len = 1;
    return *this;
}

String::String(String && s) {
    _ptr = s._ptr;
    _len = s._len;
    _cap = s._cap;
    s._ptr = nullptr;
}

String & String::operator = (String && s) {
    std::swap(_ptr, s._ptr);
    _len = s._len;
    _cap = s._cap;
    return *this;
}

const char & String::operator [] (uint16_t pos) const {
    yahal_assert(pos < _len);
    return _ptr[pos];
}

char & String::operator [] (uint16_t pos) {
    yahal_assert(pos < _len);
    return _ptr[pos];
}

bool String::operator == (const String & r) const
{
    if (_len != r._len) return false;
    for (uint16_t pos = 0; pos < _len; ++pos) {
        if (_ptr[pos] != r._ptr[pos])
            return false;
    }
    return true;
}

bool String::operator != (const String & r) const
{
    return !((*this) == r);
}

void String::reserve(uint16_t size) {
    if(size > _cap) {
       char *temp = new char[size+1];
       strcpy(temp, _ptr);
       delete [] _ptr;
       _ptr = temp;
       _cap = size;
    }
}

void String::shrink_to_fit() {
    if(_cap > _len) {
       char * temp = new char[_len+1];
       strcpy(temp, _ptr);
       delete [] _ptr;
       _ptr = temp;
       _cap = _len;
    }
}

void String::clear() {
    _ptr[0] = 0;
    _len    = 0;
}

String & String::operator += (const String & s) {
    uint16_t temp = s._len;
    reserve(_len + temp);
    strcat(_ptr, s._ptr);
    _len += temp;
    return *this;
}

String String::substr(uint16_t pos, uint16_t n) const
{
    String s("");
    if (pos >= _len) return s;
    for (; pos < _len; ++pos) {
        if (!n) break; else --n;
        s += _ptr[pos];
    }
    return s;
}

uint16_t String::find (char c, uint16_t pos) const
{
    for (; pos < _len; ++pos) {
        if (c == _ptr[pos]) return pos;
    }
    return npos;
}

String String::fill_left (uint16_t width, const char c) {
    if (_len < width) {
        return String(c, width-_len) + *this;
    } else {
        return *this;
    }
}

String String::fill_right(uint16_t width, const char c) {
    if (_len < width) {
        return *this + String(c, width-_len);
    } else {
        return *this;
    }
}


// private methods
//////////////////

void String::reserve_only(uint16_t size) {
   if(size > _cap) {
      char * temp = new char[size+1];
      delete [] _ptr;
      _ptr = temp;
      _cap = size;
   }
}

String to_String(int num, int base) {
    char buf[20];
    int  i = sizeof(buf);
    bool isNegative = false;

    // Terminate with '\0'
    buf[--i] = '\0';

    // Check for 0
    if (num == 0)
    {
        buf[--i] = '0';
        return String(buf+i);
    }
    // Negative numbers are only handled with base 10
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
    // Process digits
    while (num != 0)
    {
        int rem = num % base;
        buf[--i] = (rem > 9) ? (rem-10) + 'a' : rem + '0';
        num = num / base;
    }
    // If number is negative, append '-'
    if (isNegative)
        buf[--i] = '-';

    return String(buf+i);
}

String operator + (const String & lhs, const String & rhs) {
    String res(lhs);
    return res += rhs;
}
