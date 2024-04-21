#pragma once

#include "Stream.h"

//#include <vector>

namespace ZArchive {

    class BufferStream : public Stream
    {
    public:
        BufferStream(UInt32 initSize = 1024);
        ~BufferStream();

        virtual bool WriteBytes(const void* buffer, UInt32 size) override;
        virtual bool ReadBytes(void* buffer, UInt32 size) override;
        virtual bool Seek(UInt32 pos) override {
            m_cursor = pos;
            return true;
        }
        virtual UInt32 GetSize() const override {
            return m_size;
        }
    private:
        bool resize(UInt32 dstSize);

        UInt32              m_cursor = 0;
        UInt32              m_size = 0;
        void*               m_data = nullptr;
    };


}