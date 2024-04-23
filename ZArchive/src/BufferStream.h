#pragma once

#include "Stream.h"

//#include <vector>

namespace ZArchive {

    class BufferStream : public Stream
    {
    public:
        BufferStream(UInt32 initCapacity = 1024);
        ~BufferStream();

        virtual bool WriteBytes(const void* buffer, UInt32 capacity) override;
        virtual bool ReadBytes(void* buffer, UInt32 capacity) override;

        virtual UInt32 GetAvailableReadSize() const override {
            return m_size - m_cursor;
        }
        virtual void ResetRead() override {
            m_cursor = 0;
        }
        virtual void ResetWrite() override {
            m_cursor = 0;
            m_size = 0;
        }

        virtual void* GetRawData() override {
            return m_data;
        }
    private:
        bool reCapacity(UInt32 dstCapacity);
        void clear();

        UInt32              m_cursor = 0;
        UInt32              m_size = 0;
        UInt32              m_Capacity = 0;
        void*               m_data = nullptr;
    };


}