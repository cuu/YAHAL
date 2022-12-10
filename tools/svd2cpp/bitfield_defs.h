/*
 * bitfield_defs.h
 *
 *  Created on: 14.10.2022
 *      Author: andreas
 */

#ifndef SVD_DEFS_H_
#define SVD_DEFS_H_

#include <stdint.h>

//////////////////////////////
// Helper templates and macros
//////////////////////////////
template <typename T, int Offset, int Bits>
struct BitFieldMember_RO
{
  private:
    volatile T value;  // This is the value which is 'mirrored' by the union
    static const T max  = (T(1) << Bits) - T(1);

  public:
    inline operator T() const {
        return (value >> Offset) & max;
    }
};

template <typename T, int Offset, int Bits>
struct BitFieldMember_WO
{
  private:
    volatile T value;  // This is the value which is 'mirrored' by the union
    static const T max  = (T(1) << Bits) - T(1);
    static const T mask = max << Offset;

  public:
    inline void operator = (T v) {
        value = (value & ~mask) | ((v & max) << Offset);
    }
//    inline void operator |= (T v) {
//        value = (v & max) << Offset;
//    }
};

template <typename T, int Offset, int Bits>
struct BitFieldMember_RW
{
  private:
    volatile T value;  // This is the value which is 'mirrored' by the union
    static const T max  = (T(1) << Bits) - T(1);
    static const T mask = max << Offset;

  public:
    inline operator T() const {
        return (value >> Offset) & max;
    }
    inline void operator=(T v) {
        value = (value & ~mask) | ((v & max) << Offset);
    }
//    inline void operator |= (T v) {
//        value = (v & max) << Offset;
//    }
};

#define BEGIN_TYPE(typeName, T) \
    union typeName \
    { \
        volatile T value; \
        inline void operator = (volatile T v) { value = v;    } \
        inline operator volatile T&()         { return value; } \
        inline operator volatile T() const    { return value; } \
        typedef  volatile T StorageType;

#define ADD_BITFIELD_RO(memberName, offset, bits) \
        BitFieldMember_RO<StorageType, offset, bits> memberName;

#define ADD_BITFIELD_WO(memberName, offset, bits) \
        BitFieldMember_WO<StorageType, offset, bits> memberName;

#define ADD_BITFIELD_RW(memberName, offset, bits) \
        BitFieldMember_RW<StorageType, offset, bits> memberName;

#define END_TYPE() \
    };


#endif /* SVD_DEFS_H_ */
