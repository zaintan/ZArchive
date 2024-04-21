#include "Archive.h"
#include "Macro.h"
#include "Stream.h"

namespace ZArchive {

    void Archive::SerializeBegin(Stream* s, bool usingTag)
    {
        ZA_ASSERT(m_curState == ArchiveState::None);
        ZA_ASSERT(m_stream == nullptr);
        ZA_ASSERT(s != nullptr);

        m_stream   = s;
        m_usingTag = usingTag;
        m_curState = ArchiveState::Write;
    }

    void Archive::SerializeEnd()
    {
        ZA_ASSERT(m_curState == ArchiveState::Write);
        ZA_ASSERT(m_stream != nullptr);

        m_stream   = nullptr;
        m_curState = ArchiveState::None;
    }

    void Archive::UnSerializeBegin(Stream* s, bool usingTag)
    {
        ZA_ASSERT(m_curState == ArchiveState::None);
        ZA_ASSERT(m_stream == nullptr);
        ZA_ASSERT(s != nullptr);

        m_stream   = s;
        m_usingTag = usingTag;
        m_curState = ArchiveState::Read;
    }

    void Archive::UnSerializeEnd()
    {
        ZA_ASSERT(m_curState == ArchiveState::Read);
        ZA_ASSERT(m_stream != nullptr);

        m_stream   = nullptr;
        m_curState = ArchiveState::None;
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
}