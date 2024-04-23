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
        template<class Iterator>
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

        template<class Iterator, class T>
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
        template<class T>
        bool Serialize(Archive* archive, const std::vector<T>& obj) {
            return archive->WriteTag(ArchiveTag::eTagSTLVector)
                && SerializeContainer(archive, obj.begin(), obj.end(), obj.size());
        }

        template<class T>
        bool UnSerialize(Archive* archive, std::vector<T>& obj) {
            obj.clear();
            return archive->ReadAndCheckTag(ArchiveTag::eTagSTLVector)
                && UnSerializeContainer(archive, std::back_inserter(obj), (T*)nullptr);
        }

        //list
        template<class T>
        bool Serialize(Archive* archive, const std::list<T>& obj) {
            return archive->WriteTag(ArchiveTag::eTagSTLList)
                && SerializeContainer(archive, obj.begin(), obj.end(), obj.size());
        }

        template<class T>
        bool UnSerialize(Archive* archive, std::list<T>& obj) {
            obj.clear();
            return archive->ReadAndCheckTag(ArchiveTag::eTagSTLList)
                && UnSerializeContainer(archive, std::back_inserter(obj), (T*)nullptr);
        }

        //deque
        template<class T>
        bool Serialize(Archive* archive, const std::deque<T>& obj) {
            return archive->WriteTag(ArchiveTag::eTagSTLDeque)
                && SerializeContainer(archive, obj.begin(), obj.end(), obj.size());
        }

        template<class T>
        bool UnSerialize(Archive* archive, std::deque<T>& obj) {
            obj.clear();
            return archive->ReadAndCheckTag(ArchiveTag::eTagSTLDeque)
                && UnSerializeContainer(archive, std::back_inserter(obj), (T*)nullptr);
        }

        //pair
        template<class T1, class T2>
        bool Serialize(Archive* archive, const std::pair<T1, T2>& obj) {
            return archive->WriteTag(ArchiveTag::eTagSTLPair)
                && archive->Serialize(obj.first)
                && archive->Serialize(obj.second);
        }

        template<class T1, class T2>
        bool UnSerialize(Archive* archive, std::pair<T1, T2>& obj) {
            return archive->ReadAndCheckTag(ArchiveTag::eTagSTLPair)
                && archive->UnSerialize(obj.first)
                && archive->UnSerialize(obj.second);
        }

        //set
        template<class T1, class T2>
        bool Serialize(Archive* archive, const std::set<T1, T2>& obj) {
            return archive->WriteTag(ArchiveTag::eTagSTLSet)
                && SerializeContainer(archive, obj.begin(), obj.end(), obj.size());
        }

        template<class T1, class T2>
        bool UnSerialize(Archive* archive, std::set<T1, T2>& obj) {
            obj.clear();
            return archive->ReadAndCheckTag(ArchiveTag::eTagSTLSet)
                && UnSerializeContainer(archive, std::inserter(obj, obj.end()), (T1*)nullptr);
        }

        //multiset
        template<class T1, class T2>
        bool Serialize(Archive* archive, const std::multiset<T1, T2>& obj) {
            return archive->WriteTag(ArchiveTag::eTagSTLMultiSet)
                && SerializeContainer(archive, obj.begin(), obj.end(), obj.size());
        }

        template<class T1, class T2>
        bool UnSerialize(Archive* archive, std::multiset<T1, T2>& obj) {
            obj.clear();
            return archive->ReadAndCheckTag(ArchiveTag::eTagSTLMultiSet)
                && UnSerializeContainer(archive, std::inserter(obj, obj.end()), (T1*)nullptr);
        }

        //unordered_set
        template<typename T, typename HASH, typename EQ>
        bool Serialize(Archive* archive, const std::unordered_set<T, HASH, EQ>& obj) {
            return archive->WriteTag(ArchiveTag::eTagSTLUnOrderedSet)
                && SerializeContainer(archive, obj.begin(), obj.end(), obj.size());
        }

        template<typename T, typename HASH, typename EQ>
        bool UnSerialize(Archive* archive, std::unordered_set<T, HASH, EQ>& obj) {
            obj.clear();
            return archive->ReadAndCheckTag(ArchiveTag::eTagSTLUnOrderedSet)
                && UnSerializeContainer(archive, std::inserter(obj, obj.end()), (T*)nullptr);
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

        //multimap
        template<typename TKEY, typename TVAL, typename TCOMPARE>
        bool Serialize(Archive* archive, const std::multimap<TKEY, TVAL, TCOMPARE>& obj) {
            return archive->WriteTag(ArchiveTag::eTagSTLMultiMap)
                && SerializeContainer(archive, obj.begin(), obj.end(), obj.size());
        }

        template<typename TKEY, typename TVAL, typename TCOMPARE>
        bool UnSerialize(Archive* archive, std::multimap<TKEY, TVAL, TCOMPARE>& obj) {
            obj.clear();
            return archive->ReadAndCheckTag(ArchiveTag::eTagSTLMultiMap)
                && UnSerializeContainer(archive, std::inserter(obj, obj.end()), (std::pair<TKEY, TVAL>*)nullptr);
        }

        //unordered_map
        template<typename TKEY, typename TVAL, typename HASH, typename EQ>
        bool Serialize(Archive* archive, const std::unordered_map<TKEY, TVAL, HASH, EQ>& obj) {
            return archive->WriteTag(ArchiveTag::eTagSTLUnOrderedMap)
                && SerializeContainer(archive, obj.begin(), obj.end(), obj.size());
        }

        template<typename TKEY, typename TVAL, typename HASH, typename EQ>
        bool UnSerialize(Archive* archive, std::unordered_map<TKEY, TVAL, HASH, EQ>& obj) {
            obj.clear();
            return archive->ReadAndCheckTag(ArchiveTag::eTagSTLUnOrderedMap)
                && UnSerializeContainer(archive, std::inserter(obj, obj.end()), (std::pair<TKEY, TVAL>*)nullptr);
        }



    };
};