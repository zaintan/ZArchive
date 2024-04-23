#include "BufferStream.h"
#include "Macro.h"

namespace ZArchive {

    BufferStream::BufferStream(UInt32 initCapacity/* = 1024*/)
        : m_Capacity(initCapacity)
    {
        if (m_Capacity > 0) {
            m_data = ZA_MALLOC(m_Capacity);
        }
    }

    BufferStream::~BufferStream()
    {
        clear();
    }

    bool BufferStream::WriteBytes(const void* buffer, UInt32 size)
    {
        if (m_cursor + size > m_Capacity) {
            bool ret = reCapacity(m_Capacity == 0 ? 1024 :(UInt32)(m_Capacity * 1.5f) );
            if (!ret) return false;
        }

        memcpy((void*)((UInt8*)m_data + m_cursor), buffer, size);
        m_cursor += size;
        m_size = m_cursor;
        return true;
    }

    bool BufferStream::ReadBytes(void* buffer, UInt32 size)
    {
        if (m_cursor + size > m_size)
            return false;

        memcpy(buffer, (void*)((UInt8*)m_data + m_cursor), size);
        m_cursor += size;
        return true;
    }

  

    bool BufferStream::reCapacity(UInt32 dstCapacity)
    {
        if (dstCapacity == 0) {//do nothing
            return false;
        }
        void* data = ZA_REALLOC(m_data, dstCapacity);
        if (!data)
            return false;
        m_data = data;
        m_Capacity = dstCapacity;
        return true;
    }

    void BufferStream::clear()
    {
        ZA_FREE(m_data);
        m_data = nullptr;
        m_Capacity = 0;
    }
}
