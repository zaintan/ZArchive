#include "BufferStream.h"
#include "Macro.h"

namespace ZArchive {

    BufferStream::BufferStream(UInt32 initCapacity/* = 1024*/)
    {
        m_capacity = initCapacity;
        if (m_capacity > 0) {
            m_data = ZA_MALLOC(m_capacity);
        }
    }

    BufferStream::~BufferStream()
    {
        clear();
    }

    bool BufferStream::WriteBytes(const void* buffer, UInt32 size)
    {
        if (m_writePos + size > m_capacity) {
            bool ret = ReCapacity((UInt32)(m_capacity * 1.5f) );
            if (!ret) return false;
        }

        memcpy((void*)((UInt8*)m_data + m_writePos), buffer, size);
        m_writePos += size;
        m_len = m_writePos;
        return true;
    }

    bool BufferStream::ReadBytes(void* buffer, UInt32 size)
    {
        if (m_readPos + size > m_len)
            return false;

        memcpy(buffer, (void*)((UInt8*)m_data + m_readPos), size);
        m_readPos += size;
        return true;
    }

  

    bool BufferStream::ReCapacity(UInt32 dstCapacity)
    {
        dstCapacity = std::max(dstCapacity, (UInt32)STREAM_MIN_BUFFER_SIZE);
        void* data = ZA_REALLOC(m_data, dstCapacity);
        if (!data)
            return false;
        m_data = data;
        m_capacity = dstCapacity;
        return true;
    }

    void BufferStream::clear()
    {
        ZA_FREE(m_data);
        m_data = nullptr;
        m_capacity = 0;
    }

    bool BufferStream::operator==(const BufferStream& other)
    {
        if (m_len != other.m_len)
            return false;

        if (m_len == 0) return true;

        const UInt8* data1  = (const UInt8*) m_data;
        const UInt8* data2  = (const UInt8*)  other.m_data;
        for (UInt32 i = 0; i < m_len; i++)
            if (data1[i] != data2[i])
                return false;

        return true;
    }
}
