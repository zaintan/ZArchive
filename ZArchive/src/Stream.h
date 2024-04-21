#pragma once
#include "BaseType.h"

namespace ZArchive {

    class Stream
    {
    public:
        virtual bool WriteBytes(const void* buffer, UInt32 size) = 0;
        virtual bool ReadBytes(void* buffer, UInt32 size) = 0;

        virtual bool Seek(UInt32 pos) = 0;
        virtual UInt32 GetSize() const = 0;
    };
}