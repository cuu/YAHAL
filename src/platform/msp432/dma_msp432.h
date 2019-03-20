#ifndef _DMA_MSP432_H_
#define _DMA_MSP432_H_

#include <stdint.h>

#define __RO    const volatile
#define __WO    volatile
#define __RW    volatile

//////////////////////////////
// Helper templates and macros
//////////////////////////////
template<typename T, int Offset, int Bits>
struct BitFieldMember_RO
{
private:
    T value;  // This is the value which is 'mirrored' by the union
    static const T max = (T(1) << Bits) - T(1);

public:
    inline operator T() const
    {
        return (value >> Offset) & max;
    }
};

template<typename T, int Offset, int Bits>
struct BitFieldMember_WO
{
private:
    T value;  // This is the value which is 'mirrored' by the union
    static const T max = (T(1) << Bits) - T(1);
    static const T mask = max << Offset;

public:
    inline BitFieldMember_WO & operator=(T v)
    {
        value = (value & ~mask) | ((v & max) << Offset);
        return *this;
    }
};

template<typename T, int Offset, int Bits>
struct BitFieldMember_RW
{
private:
    T value;  // This is the value which is 'mirrored' by the union
    static const T max = (T(1) << Bits) - T(1);
    static const T mask = max << Offset;

public:
    inline operator T() const
    {
        return (value >> Offset) & max;
    }
    inline BitFieldMember_RW & operator=(T v)
    {
        value = (value & ~mask) | ((v & max) << Offset);
        return *this;
    }
};

#define BEGIN_BITFIELD_TYPE(typeName, T) \
        union typeName \
        { \
    T value{0}; \
    typeName& operator=(T v) {  value = v; return *this; } \
    operator T&()      { return value; } \
    operator T() const { return value; } \
    typedef  T StorageType;

#define ADD_BITFIELD_MEMBER_RO(memberName, offset, bits) \
        BitFieldMember_RO<StorageType, offset, bits> memberName;

#define ADD_BITFIELD_MEMBER_WO(memberName, offset, bits) \
        BitFieldMember_WO<StorageType, offset, bits> memberName;

#define ADD_BITFIELD_MEMBER_RW(memberName, offset, bits) \
        BitFieldMember_RW<StorageType, offset, bits> memberName;

#define END_BITFIELD_TYPE() \
        };

////////////////////////////////
// Control Data Configuration //
////////////////////////////////

namespace DMA
{
    BEGIN_BITFIELD_TYPE(ctrl_data_conf_t, uint32_t)
        ADD_BITFIELD_MEMBER_RW(CYCLE_CTRL,     0,  3)
        ADD_BITFIELD_MEMBER_RW(NEXT_USEBURST,  3,  1)
        ADD_BITFIELD_MEMBER_RW(N_MINUS_1,      4, 10)
        ADD_BITFIELD_MEMBER_RW(R_POWER,       14,  4)
        ADD_BITFIELD_MEMBER_RW(SRC_PROT_CTRL, 18,  3)
        ADD_BITFIELD_MEMBER_RW(DST_PROT_CTRL, 21,  3)
        ADD_BITFIELD_MEMBER_RW(SRC_SIZE,      24,  2)
        ADD_BITFIELD_MEMBER_RW(SRC_INC,       26,  2)
        ADD_BITFIELD_MEMBER_RW(DST_SIZE,      28,  2)
        ADD_BITFIELD_MEMBER_RW(DST_INC,       30,  2)
    END_BITFIELD_TYPE()

    // values for CYCLE_CTRL bitfield
    const uint8_t CYCLE_STOP         = 0;
    const uint8_t CYCLE_BASIC        = 1;
    const uint8_t CYCLE_AUTO_REQUEST = 2;
    const uint8_t CYCLE_PING_PONG    = 3;
    const uint8_t CYCLE_MEM_SCATTER_GATHER_PRI  = 4;
    const uint8_t CYCLE_MEM_SCATTER_GATHER_ALT  = 5;
    const uint8_t CYCLE_PERI_SCATTER_GATHER_PRI = 6;
    const uint8_t CYCLE_PERI_SCATTER_GATHER_ALT = 7;

    // values for R_POWER bitfield
    const uint8_t ARB_AFTER_1    = 0;
    const uint8_t ARB_AFTER_2    = 1;
    const uint8_t ARB_AFTER_4    = 2;
    const uint8_t ARB_AFTER_8    = 3;
    const uint8_t ARB_AFTER_16   = 4;
    const uint8_t ARB_AFTER_32   = 5;
    const uint8_t ARB_AFTER_64   = 6;
    const uint8_t ARB_AFTER_128  = 7;
    const uint8_t ARB_AFTER_256  = 8;
    const uint8_t ARB_AFTER_512  = 9;
    const uint8_t ARB_AFTER_1024 = 10;

    // values for SIZE and INC bitfields
    const uint8_t BYTE         = 0;
    const uint8_t HALFWORD     = 1;
    const uint8_t WORD         = 2;
    const uint8_t NO_INCREMENT = 3;

    struct CH_CTRL_DATA
    {
        __RW void * SRC_DATA_END_PTR;
        __RW void * DST_DATA_END_PTR;
        ctrl_data_conf_t CTRL;
        __RW uint32_t unused = 0;
    };
}

class dma_msp432 {
public:
    // DMA is a singleton...
    static dma_msp432 & inst();

    // public structure for 8 primary
    // and 8 alternate channels
    __attribute__ ((aligned (256)))
    DMA::CH_CTRL_DATA ctrl_data[16];

private:
    static dma_msp432 _inst;
    dma_msp432();
};

#endif // _DMA_MSP432_H_
