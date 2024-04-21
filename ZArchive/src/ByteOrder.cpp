#include "ByteOrder.h"

#define TEMP_SWAP(a,b,tmp) tmp = a; a = b; b = tmp

namespace ZArchive {



        ByteOrder::ByteOrderJudge ByteOrder::IsLittleEndian;


        UInt16 ByteOrder::SwapUInt16(UInt16 x)
        {
            UInt8 b0 = static_cast<UInt8>(x & 0xFF);
            UInt8 b1 = static_cast<UInt8>((x >> 8) & 0xFF);
            return static_cast<UInt16>((b0 << 8) | b1);
        }




        UInt32 ByteOrder::SwapUInt32(UInt32 x)
        {
            UInt8 b0 = static_cast<UInt8>(x & 0xFF);
            UInt8 b1 = static_cast<UInt8>((x >> 8) & 0xFF);
            UInt8 b2 = static_cast<UInt8>((x >> 16) & 0xFF);
            UInt8 b3 = static_cast<UInt8>((x >> 24) & 0xFF);
            return (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
        }



        UInt64 ByteOrder::SwapUInt64(UInt64 x)
        {
            union
            {
                UInt64 val;
                UInt8 bytes[8];
            } u;
            u.val = x;

            // 0 1 2 3 4 5 6 7 -> 7 6 5 4 3 2 1 0
            UInt8 tmp;
            TEMP_SWAP(u.bytes[0], u.bytes[7], tmp);
            TEMP_SWAP(u.bytes[1], u.bytes[6], tmp);
            TEMP_SWAP(u.bytes[2], u.bytes[5], tmp);
            TEMP_SWAP(u.bytes[3], u.bytes[4], tmp);
            return u.val;
        }

        Float32 ByteOrder::SwapFloat32(Float32 x)
        {
            union
            {
                Float32 val;
                UInt8 bytes[4];
            } u;
            u.val = x;
            // 0 1 2 3 -> 3 2 1 0
            UInt8 tmp;
            TEMP_SWAP(u.bytes[0], u.bytes[3], tmp);
            TEMP_SWAP(u.bytes[1], u.bytes[2], tmp);
            return u.val;
        }

        Float64 ByteOrder::SwapFloat64(Float64 x)
        {
            union
            {
                Float64 val;
                UInt8 bytes[8];
            } u;
            u.val = x;
            // 0 1 2 3 4 5 6 7 -> 7 6 5 4 3 2 1 0
            UInt8 tmp;
            TEMP_SWAP(u.bytes[0], u.bytes[7], tmp);
            TEMP_SWAP(u.bytes[1], u.bytes[6], tmp);
            TEMP_SWAP(u.bytes[2], u.bytes[5], tmp);
            TEMP_SWAP(u.bytes[3], u.bytes[4], tmp);
            return u.val;
        }

}

#undef TEMP_SWAP