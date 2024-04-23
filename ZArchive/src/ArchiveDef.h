#pragma once

#define ARCHIVE_DECLARE_SERIALIZE(typ) \
    namespace ZArchive{ \
        namespace ArchiveHelper { \
            bool Serialize(Archive* , const typ& ); \
            bool UnSerialize(Archive* , typ& ); \
        }\
    }\

#define ARCHIVE_DECLARE_FRIEND(typ) \
    friend bool ZArchive::ArchiveHelper::Serialize(Archive*, const typ&); \
    friend bool ZArchive::ArchiveHelper::UnSerialize(Archive*, typ&)

#define ARCHIVE_IMPLEMENT_SERIALIZE(typ) bool ZArchive::ArchiveHelper::Serialize(Archive* ar, const typ& obj)
#define ARCHIVE_IMPLEMENT_UNSERIALIZE(typ) bool ZArchive::ArchiveHelper::UnSerialize(Archive* ar, typ& obj)  

namespace ZArchive {
    class Archive;
    namespace ArchiveHelper {};

    enum class ArchiveTag
    {
        eTagInt8 = 0,
        eTagUInt8,
        eTagInt16,
        eTagUInt16,
        eTagInt32,
        eTagUInt32,
        eTagInt64,
        eTagUInt64,
        eTagFloat32,
        eTagFloat64,
        
        eTagString,
        eTagArray,
        eTagRawBytes,
        eTagStream,
        //stl
        eTagSTLVector,
        eTagSTLList,
        eTagSTLDeque,

        eTagSTLPair,
        eTagSTLSet,
        eTagSTLMultiSet,
        eTagSTLUnOrderedSet,
        eTagSTLMap,
        eTagSTLMultiMap,
        eTagSTLUnOrderedMap,

        eTagEnd
    };
}
  