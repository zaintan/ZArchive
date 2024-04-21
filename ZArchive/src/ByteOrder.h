#pragma once
#include "BaseType.h"

namespace ZArchive {

    namespace ByteOrder {

        class ByteOrderJudge
        {
        public:
            ByteOrderJudge()
            {
                int number = 0x1;
                char* numPtr = (char*)(&number);
                m_bLittleEndian = (*numPtr == 1);
            }

            bool operator()() const {
                return m_bLittleEndian;
            }
        private:
            bool m_bLittleEndian;
        };
        extern ByteOrderJudge IsLittleEndian;

        UInt16 SwapUInt16(UInt16 target);
        UInt32 SwapUInt32(UInt32 target);
        UInt64 SwapUInt64(UInt64 target);
        Float32 SwapFloat32(Float32 target);
        Float64 SwapFloat64(Float64 target);
            
    }
}