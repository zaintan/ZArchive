#pragma once
#include "BaseType.h"

namespace ZArchive {

    class Stream
    {
    public:
        virtual bool WriteBytes(const void* buffer, UInt32 capacity) = 0;
        virtual bool ReadBytes(void* buffer, UInt32 capacity) = 0;
        virtual UInt32 GetAvailableReadSize() const = 0;
        virtual void ResetRead() = 0;
        virtual void ResetWrite() = 0;
        virtual void* GetRawData() = 0;
    };
}