#pragma once

#include "Archive.h"
#include "ArchiveDef.h"

#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iterator>

namespace ZArchive {

    namespace ArchiveHelper {
        //helper base
        template<typename Iterator>
        bool SerializeContainer(Archive* archive, const Iterator& begin, const Iterator& end, UInt32 size) {

            if (!archive->SerializeCount(size))
                return false;

            UInt32 checkSize = 0;
            for (auto it = begin; it != end; it++, checkSize++ ) {
                if (!archive->Serialize(*it))
                    return false;
            }

            return checkSize == size;
        }

        template<typename Iterator, typename T>
        bool UnSerializeContainer(Archive* archive, Iterator& insertor, T*) {
            UInt32 size = 0;
            if (!archive->UnSerializeCount(size))
                return false;
            
            if (size == 0) return true;
            for (UInt32 i = 0; i < size; i++)
            {
                T obj;
                if (!archive->UnSerialize(obj)) return false;
                *insertor = std::move(obj);
            }

            return true;
        }

        //vector
        template<typename T>
        bool Serialize(Archive* archive, const std::vector<T>& obj) {
            return archive->WriteTag(ArchiveTag::eTagSTLVector)
                && SerializeContainer(archive, obj.begin(), obj.end(), obj.size());
        }

        template<typename T>
        bool UnSerialize(Archive* archive, std::vector<T>& obj) {
            obj.clear();
            return archive->ReadAndCheckTag(ArchiveTag::eTagSTLVector)
                && UnSerializeContainer(archive, std::back_inserter(obj), (T*)nullptr);
        }

        //list
        template<typename T>
        bool Serialize(Archive* archive, const std::list<T>& obj) {
            return archive->WriteTag(ArchiveTag::eTagSTLList)
                && SerializeContainer(archive, obj.begin(), obj.end(), obj.size());
        }

        template<typename T>
        bool UnSerialize(Archive* archive, std::list<T>& obj) {
            obj.clear();
            return archive->ReadAndCheckTag(ArchiveTag::eTagSTLList)
                && UnSerializeContainer(archive, std::back_inserter(obj), (T*)nullptr);
        }

        //deque
        template<typename T>
        bool Serialize(Archive* archive, const std::deque<T>& obj) {
            return archive->WriteTag(ArchiveTag::eTagSTLDeque)
                && SerializeContainer(archive, obj.begin(), obj.end(), obj.size());
        }

        template<typename T>
        bool UnSerialize(Archive* archive, std::deque<T>& obj) {
            obj.clear();
            return archive->ReadAndCheckTag(ArchiveTag::eTagSTLDeque)
                && UnSerializeContainer(archive, std::back_inserter(obj), (T*)nullptr);
        }

        //pair
        template<typename T1, typename T2>
        bool Serialize(Archive* archive, const std::pair<T1, T2>& obj) {
            return archive->WriteTag(ArchiveTag::eTagPair)
                && archive->Serialize(obj.first)
                && archive->Serialize(obj.second);
        }

        template<typename T1, typename T2>
        bool UnSerialize(Archive* archive, std::pair<T1, T2>& obj) {
            return archive->ReadAndCheckTag(ArchiveTag::eTagPair)
                && archive->UnSerialize(obj.first)
                && archive->UnSerialize(obj.second);
        }

        //map
        template<typename TKEY, typename TVAL, typename TCOMPARE>
        bool Serialize(Archive* archive, const std::map<TKEY, TVAL, TCOMPARE>& obj) {
            return archive->WriteTag(ArchiveTag::eTagSTLMap)
                && SerializeContainer(archive, obj.begin(), obj.end(), obj.size());
        }

        template<typename TKEY, typename TVAL, typename TCOMPARE>
        bool UnSerialize(Archive* archive, std::map<TKEY, TVAL, TCOMPARE>& obj) {
            obj.clear();
            return archive->ReadAndCheckTag(ArchiveTag::eTagSTLMap)
                && UnSerializeContainer(archive, std::inserter(obj, obj.end()), (std::pair<TKEY, TVAL>*)nullptr);
        }

        //unordered_map
        template<typename _Key, typename _Val, typename _Hash, typename _KeyEq>
        bool Serialize(Archive* archive, const std::unordered_map<_Key, _Val, _Hash, _KeyEq>& obj) {
            return archive->WriteTag(ArchiveTag::eTagSTLUnOrderedMap)
                && SerializeContainer(archive, obj.begin(), obj.end(), obj.size());
        }

        template<typename _Key, typename _Val, typename _Hash, typename _KeyEq>
        bool UnSerialize(Archive* archive, std::unordered_map<_Key, _Val, _Hash, _KeyEq>& obj) {
            obj.clear();
            return archive->ReadAndCheckTag(ArchiveTag::eTagSTLUnOrderedMap)
                && UnSerializeContainer(archive, std::inserter(obj, obj.end()), (std::pair<_Key, _Val>*)nullptr);
        }


        //set
        template<typename _Val, typename _Compare>
        bool Serialize(Archive* archive, const std::set<_Val, _Compare>& obj) {
            return archive->WriteTag(ArchiveTag::eTagSTLSet)
                && SerializeContainer(archive, obj.begin(), obj.end(), obj.size());
        }

        template<typename _Val, typename _Compare>
        bool UnSerialize(Archive* archive, std::set<_Val, _Compare>& obj) {
            obj.clear();
            return archive->ReadAndCheckTag(ArchiveTag::eTagSTLSet)
                && UnSerializeContainer(archive, std::inserter(obj, obj.end()), (_Val*)nullptr);
        }

        //unordered_set
        template<typename _Val, typename _Hash, typename _KeyEq>
        bool Serialize(Archive* archive, const std::unordered_set<_Val, _Hash, _KeyEq>& obj) {
            return archive->WriteTag(ArchiveTag::eTagSTLUnOrderedSet)
                && SerializeContainer(archive, obj.begin(), obj.end(), obj.size());
        }

        template<typename _Val, typename _Hash, typename _KeyEq>
        bool UnSerialize(Archive* archive, std::unordered_set<_Val, _Hash, _KeyEq>& obj) {
            obj.clear();
            return archive->ReadAndCheckTag(ArchiveTag::eTagSTLUnOrderedSet)
                && UnSerializeContainer(archive, std::inserter(obj, obj.end()), (_Val*)nullptr);
        }
    };
};