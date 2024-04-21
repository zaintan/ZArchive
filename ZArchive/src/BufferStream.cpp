#include "BufferStream.h"
#include <memory>

namespace ZArchive {

    BufferStream::BufferStream(UInt32 initSize/* = 1024*/)
        : m_size (initSize)
    {
        if (m_size > 0) {
            m_data = malloc(m_size);
        }
    }

    BufferStream::~BufferStream()
    {
        resize(0);
    }

    bool BufferStream::WriteBytes(const void* buffer, UInt32 size)
    {
        if (m_cursor + size > m_size) {
            bool ret = resize( m_size == 0 ? 1024 :(UInt32)(m_size * 1.5f) );
            if (!ret) return false;
        }

        memcpy((void*)((UInt8*)m_data + m_cursor), buffer, size);
        m_cursor += size;
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

    //bool BufferStream::Seek(UInt32 pos)
    //{

    //}

    bool BufferStream::resize(UInt32 dstSize)
    {
        if (dstSize == m_size) return true;

        if (dstSize == 0) {
            if(m_data)
                free(m_data);
            m_data = nullptr;
            m_size = 0;
            return true;
        }

        void* data = malloc(dstSize);
        if (!data) return false;
        resize(0);
        m_data = data;
        m_size = dstSize;
        m_cursor = m_cursor > m_size ? m_size : m_cursor;
        return true;
    }
}
