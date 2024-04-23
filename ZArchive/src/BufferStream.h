#pragma once

#include "Stream.h"
#include <algorithm>

#define STREAM_MIN_BUFFER_SIZE 512

namespace ZArchive {

    class BufferStream : public Stream
    {
    public:
        BufferStream(UInt32 initCapacity = STREAM_MIN_BUFFER_SIZE );
        ~BufferStream();

        virtual bool WriteBytes(const void* buffer, UInt32 capacity) override;
        virtual bool ReadBytes(void* buffer, UInt32 capacity) override;
        virtual bool ReCapacity(UInt32 dstCapacity) override;
        bool operator==(const BufferStream& other);
    protected:
        void clear();
    };


}