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
// Definitions and templates for register
// bitmap handling (reading/writing of 
// specific bitfields within a register).
// Related C++ operators are provided.
//
#ifndef _BITFIELD_DEFS_H_
#define _BITFIELD_DEFS_H_

#include <stdint.h>

//////////////////////////////
// Helper templates and macros
//////////////////////////////
template <typename T, int Offset, int Bits>
struct add_bitfield_RO
{
  private:
    volatile T value;  // This is the value which is 'mirrored' by the union
    static const T maskl  = (T(1) << Bits) - T(1);

  public:
    inline operator T() const {
        return (value >> Offset) & maskl;
    }
};

template <typename T, int Offset, int Bits>
struct add_bitfield_WO
{
  private:
    volatile T value;  // This is the value which is 'mirrored' by the union
    static const T maskl = (T(1) << Bits) - T(1);
    static const T masks = maskl << Offset;

  public:
    // Assignment
    inline void operator = (T v) {
        value = (value & ~masks) | ((v & maskl) << Offset);
    }
    // Standard shortcut operators
    inline void operator |= (T v) {
        value |= ((v & maskl) << Offset);
    }
    inline void operator &= (T v) {
        value &= ~masks | ((v & maskl) << Offset);
    }
    // Optimized shortcut operator for
    // *.SET and *.CLR registers
    inline void operator <<= (T v) {
        value = v << Offset;
    }
};

template <typename T, int Offset, int Bits>
struct add_bitfield_RW
{
  private:
    volatile T value;  // This is the value which is 'mirrored' by the union
    static const T maskl = (T(1) << Bits) - T(1);
    static const T masks = maskl << Offset;

  public:
    inline operator T() const {
        return (value >> Offset) & maskl;
    }
    // Assignment
    inline void operator=(T v) {
        value = (value & ~masks) | ((v & maskl) << Offset);
    }
    // Standard shortcut operators
    inline void operator |= (T v) {
        value |= ((v & maskl) << Offset);
    }
    inline void operator &= (T v) {
        value &= ~masks | ((v & maskl) << Offset);
    }
    // Optimized shortcut operator for
    // *.SET and *.CLR registers
    inline void operator <<= (T v) {
        value = v << Offset;
    }
};

#define BEGIN_TYPE(typeName, T) \
    union typeName \
    { \
        volatile T value; \
        inline void operator = (T v)   { value = v;    } \
        inline operator volatile T& () { return value; } \
        inline operator T  () const    { return value; } \
        typedef T basicType;

#define ADD_BITFIELD_RO(memberName, offset, bits) \
        add_bitfield_RO<basicType,  offset, bits> memberName;

#define ADD_BITFIELD_WO(memberName, offset, bits) \
        add_bitfield_WO<basicType,  offset, bits> memberName;

#define ADD_BITFIELD_RW(memberName, offset, bits) \
        add_bitfield_RW<basicType,  offset, bits> memberName;

#define END_TYPE() \
    };

#endif // _BITFIELD_DEFS_H_
