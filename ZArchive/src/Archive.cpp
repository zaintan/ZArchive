#include "Archive.h"
#include "Macro.h"
#include "Stream.h"

namespace ZArchive {

    bool Archive::SerializeBegin(Stream* s, bool usingTag)
    {
        if (m_curState != ArchiveState::None
            || s == nullptr
            || m_stream != nullptr)
            return false;

        m_stream   = s;
        m_usingTag = usingTag;
        m_curState = ArchiveState::Write;
        return true;
    }

    bool Archive::SerializeEnd()
    {
        if (m_curState != ArchiveState::Write
            || m_stream == nullptr)
            return false;

        m_stream   = nullptr;
        m_curState = ArchiveState::None;
        return true;
    }

    bool Archive::UnSerializeBegin(Stream* s, bool usingTag)
    {
        if (m_curState != ArchiveState::None
            || s == nullptr
            || m_stream != nullptr)
            return false;


        m_stream   = s;
        m_usingTag = usingTag;
        m_curState = ArchiveState::Read;
        return true;
    }

    bool Archive::UnSerializeEnd()
    {
        if (m_curState != ArchiveState::Read
            || m_stream == nullptr)
            return false;

        m_stream   = nullptr;
        m_curState = ArchiveState::None;
        return true;
    }

    
    bool Archive::writeBytes(const void* buffer, UInt32 size)
    {
        ZA_ASSERT(buffer != nullptr);
        ZA_ASSERT(m_curState == ArchiveState::Write);

        return m_stream->WriteBytes(buffer, size);
    }

    bool Archive::readBytes(void* buffer, UInt32 size)
    {
        ZA_ASSERT(buffer != nullptr);
        ZA_ASSERT(m_curState == ArchiveState::Read);

        return m_stream->ReadBytes(buffer, size);
    }

    bool Archive::WriteTag(ArchiveTag tag)
    {
        ZA_ASSERT(m_stream != nullptr);
        ZA_ASSERT(m_curState == ArchiveState::Write);

        if (m_usingTag) {
            UInt8 t = static_cast<UInt8>(tag);
            return writeBytes(&t, 1);
        }
        return true;
    }

    bool Archive::ReadAndCheckTag(ArchiveTag expectTag)
    {
        ZA_ASSERT(m_stream != nullptr);
        ZA_ASSERT(m_curState == ArchiveState::Read);

        if (m_usingTag) {
            UInt8 readTag;
            bool ret = readBytes(&readTag, 1);
            return ret && (static_cast<ArchiveTag>(readTag) == expectTag);
        }
        return true;
    }

    bool Archive::Serialize(const char* str)
    {
        UInt32 size = str == nullptr ? 0 : strlen(str);
        if (!WriteTag(ArchiveTag::eTagString)) return false;
        if (!writeNumber(size, ArchiveTag::eTagUInt32)) return false;
        return writeBytes(str, size);
    }

    bool Archive::Serialize(const std::string& str)
    {
        UInt32 size = str.size();
        if (!WriteTag(ArchiveTag::eTagString)) return false;
        if (!SerializeCount(size)) return false;
        return size == 0 || writeBytes(str.c_str(), size);
    }

    bool Archive::UnSerialize(std::string& str)
    {
        //str.clear();
        if(!ReadAndCheckTag(ArchiveTag::eTagString)) return false;
        UInt32 size = 0;
        if(!UnSerializeCount(size)) return false;
        str.resize(size);
        return size == 0 || readBytes(const_cast<char*>(str.c_str()), size);
    }

    bool Archive::SerializeCount(UInt32 cnt)
    {
        return writeNumber(cnt, ArchiveTag::eTagUInt32);
    }
    bool Archive::UnSerializeCount(UInt32& cnt)
    {
        return readNumber(cnt, ArchiveTag::eTagUInt32);
    }

    bool Archive::SerializeRawData(const void* data, UInt32 bytes)
    {
        if (!WriteTag(ArchiveTag::eTagRawBytes)) return false;
        //if (!SerializeCount(bytes)) return false;
        return writeBytes(data, bytes);
    }

    bool Archive::UnSerializeRawData(void* data, UInt32 bytes)
    {
        if (!ReadAndCheckTag(ArchiveTag::eTagRawBytes)) return false;
        //if (!UnSerializeCount(bytes)) return false;
        return readBytes(data, bytes);
    }
}