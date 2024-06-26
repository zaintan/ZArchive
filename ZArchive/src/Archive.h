#pragma once
#include "BaseType.h"
#include "Macro.h"
#include "ArchiveDef.h"
#include "ByteOrder.h"
#include <string>
//序列化為大端

#define SERIALIZE_BASE_TYPE(typ) \
    inline bool Serialize(typ x) {  \
        return writeNumber(x, ArchiveTag::eTag##typ); \
    }\

#define UNSERIALIZE_BASE_TYPE(typ) \
    inline bool UnSerialize(typ& x) {  \
        return readNumber(x, ArchiveTag::eTag##typ); \
    }\

#define SERIALIZE_BYTE_ORDER_TYPE(typ) \
    inline bool Serialize(typ x) {  \
        typ orderx = ByteOrder::IsLittleEndian() ? ByteOrder::Swap##typ(x) : x; \
        return writeNumber(orderx, ArchiveTag::eTag##typ); \
    }\

#define UNSERIALIZE_BYTE_ORDER_TYPE(typ) \
    inline bool UnSerialize(typ& x) {  \
        typ readx; \
        bool ret = readNumber(readx, ArchiveTag::eTag##typ); \
        x = ByteOrder::IsLittleEndian() ? ByteOrder::Swap##typ(readx) : readx; \
        return ret;\
    }\

//
#define SERIALIZE_BYTE_ORDER_TYPE_EX(typ) \
    inline bool Serialize(typ x) {  \
        typ orderx = ByteOrder::IsLittleEndian() ? static_cast<##typ>(ByteOrder::SwapU##typ(static_cast<U##typ>(x))) : x;\
        return writeNumber(orderx, ArchiveTag::eTag##typ); \
    }\

#define UNSERIALIZE_BYTE_ORDER_TYPE_EX(typ) \
    inline bool UnSerialize(typ& x) {  \
        typ readx; \
        bool ret = readNumber(readx, ArchiveTag::eTag##typ); \
        x = ByteOrder::IsLittleEndian() ? static_cast<##typ>(ByteOrder::SwapU##typ(static_cast<U##typ>(readx))) : readx; \
        return ret;\
    }\

namespace ZArchive
{
    //extern ByteOrder::ByteOrderJudge IsLittleEndian;

    class Stream;

    class Archive
    {
    public:
        Archive() = default;
        ~Archive() = default;

        Archive(const Archive& arc) = delete;
        Archive& operator=(const Archive& arc) = delete;
        Archive(Archive&& arc) = delete;
        Archive& operator=(Archive&& arc) = delete;

        bool SerializeBegin(Stream* s, bool usingTag);
        bool SerializeEnd();
        bool UnSerializeBegin(Stream* s, bool usingTag);
        bool UnSerializeEnd();

        template<class T>
        bool Serialize(const T& obj) {
            return ArchiveHelper::Serialize(this, obj);
        }

        template<class T>
        bool UnSerialize(T& obj) {
            return ArchiveHelper::UnSerialize(this, obj);
        }


        bool SerializeCount(UInt32 cnt);
        bool UnSerializeCount(UInt32& cnt);

        template<class T>
        bool SerializeArray(const T* objArr, UInt32 nums) {
            if (nums == 0 || objArr == nullptr) 
                return true;
            if (!WriteTag(ArchiveTag::eTagArray)) 
                return false;
            if (!SerializeCount(nums)) 
                return false;
            for (UInt32 i = 0; i < nums; i++) {
                if (!Serialize(objArr[i])) {
                    return false;
                }
            }
            return true;
        }

        template<class T>
        bool UnSerializeArray(T*& objArrPtr, UInt32& nums) {

            objArrPtr = nullptr;
            if (!ReadAndCheckTag(ArchiveTag::eTagArray))
                return false;
            if (!UnSerializeCount(nums))
                return false;
            
            objArrPtr = (T*)(ZA_NEW_ARRAY(T, nums));

            for (UInt32 i = 0; i < nums; i++) {
                if (!UnSerialize(objArrPtr[i])) {
                    return false;
                }
            }
            return true;

        }

        bool SerializeRawData(const void* data, UInt32 bytes);
        bool UnSerializeRawData(void* data, UInt32 bytes);

        //基础类型支持
        bool Serialize(const char* str);
        bool Serialize(const std::string& str);
        bool UnSerialize(std::string &str);

        SERIALIZE_BASE_TYPE(Int8);
        UNSERIALIZE_BASE_TYPE(Int8);
        SERIALIZE_BASE_TYPE(UInt8);
        UNSERIALIZE_BASE_TYPE(UInt8);

        SERIALIZE_BYTE_ORDER_TYPE(UInt16);
        UNSERIALIZE_BYTE_ORDER_TYPE(UInt16);
        SERIALIZE_BYTE_ORDER_TYPE(UInt32);
        UNSERIALIZE_BYTE_ORDER_TYPE(UInt32);
        SERIALIZE_BYTE_ORDER_TYPE(UInt64);
        UNSERIALIZE_BYTE_ORDER_TYPE(UInt64);
        SERIALIZE_BYTE_ORDER_TYPE(Float32);
        UNSERIALIZE_BYTE_ORDER_TYPE(Float32);
        SERIALIZE_BYTE_ORDER_TYPE(Float64);
        UNSERIALIZE_BYTE_ORDER_TYPE(Float64);
        SERIALIZE_BYTE_ORDER_TYPE_EX(Int16);
        UNSERIALIZE_BYTE_ORDER_TYPE_EX(Int16);
        SERIALIZE_BYTE_ORDER_TYPE_EX(Int32);
        UNSERIALIZE_BYTE_ORDER_TYPE_EX(Int32);
        SERIALIZE_BYTE_ORDER_TYPE_EX(Int64);
        UNSERIALIZE_BYTE_ORDER_TYPE_EX(Int64);



        bool WriteTag(ArchiveTag tag);
        bool ReadAndCheckTag(ArchiveTag expectTag);
    private:

        template<typename T>
        bool writeNumber(const T& obj, ArchiveTag tag) {
            return WriteTag(tag) && writeBytes(&obj, sizeof(T));
        }

        template<typename T>
        bool readNumber(T& obj, ArchiveTag tag) {
            return ReadAndCheckTag(tag) && readBytes(&obj, sizeof(T));
        }

        bool writeBytes(const void* buffer, UInt32 size);
        bool readBytes(void* buffer, UInt32 size);

    private:

        enum class ArchiveState
        {
            None = 0,
            Read,
            Write
        };

        ArchiveState m_curState = ArchiveState::None;
        Stream*      m_stream   = nullptr;
        bool         m_usingTag = false;
    };
}

#undef SERIALIZE_BASE_TYPE
#undef UNSERIALIZE_BASE_TYPE
#undef SERIALIZE_BYTE_ORDER_TYPE
#undef UNSERIALIZE_BYTE_ORDER_TYPE
#undef SERIALIZE_BYTE_ORDER_TYPE_EX
#undef UNSERIALIZE_BYTE_ORDER_TYPE_EX