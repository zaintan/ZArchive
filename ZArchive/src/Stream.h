#pragma once
#include "BaseType.h"
#include "ArchiveDef.h"
#include <algorithm>

namespace ZArchive {
    class Stream;
};

ARCHIVE_DECLARE_SERIALIZE(Stream);

namespace ZArchive {


    class Stream
    {
    public:
        virtual bool WriteBytes(const void* buffer, UInt32 capacity) = 0;
        virtual bool ReadBytes(void* buffer, UInt32 capacity) = 0;
        virtual bool ReCapacity(UInt32 dstCapacity) = 0;


        UInt32 GetAvailableReadSize() const {
            return m_len - m_readPos;
        }

        UInt32 GetAvailableWriteSize() const {
            return m_len - m_writePos;
        }

        void ResetReadPos(UInt32 pos) {
            m_readPos = std::min(m_len, pos);
        }

        void ResetWritePos(UInt32 pos) {
            m_writePos = std::min(m_len, pos);
        }

        void* GetRawData() const {
            return m_data;
        }

        UInt32 GetRawDataSize() const {
            return m_len;
        }

        inline void ResetLen(UInt32 len) {
            ReCapacity(len);
            m_len = len;
            ResetReadPos(m_readPos);
            ResetWritePos(m_writePos);
        }

        ARCHIVE_DECLARE_FRIEND(Stream);
    protected:
        UInt32  m_len      = 0;
        UInt32  m_capacity = 0;
        UInt32  m_readPos  = 0;
        UInt32  m_writePos = 0;
        void*   m_data = nullptr;
    };


}