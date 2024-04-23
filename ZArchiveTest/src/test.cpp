
#include "BufferStream.h"
#include "Archive.h"
#include "ArchiveSTL.h"
#include <string>

#include <assert.h>
#include <iostream>
#include <iomanip>
#include "Macro.h"

void Dump(ZArchive::Stream& buffer)
{
    buffer.ResetRead();
    void* data = buffer.GetRawData();
    UInt32 size = buffer.GetAvailableReadSize();
    std::cout << "buffer size ["<< size<<"]:" << std::endl << "[";
   
    UInt8 temp;
    for (int i = 0; i < size; i++) {
        temp = *((UInt8*)data + i);
        //std::cout <<(int) temp<< " ";//std::setw(2) << std::setfill('0') <<
        printf("0x%02x ", temp);
    }
    std::cout << "]" << std::endl;
}

void TestRawData(const void* data, UInt32 len, bool useTagging) 
{
   
    std::cout << "rawdata size:" << len << std::endl;

    ZArchive::Archive s;
    ZArchive::BufferStream buf;
    // write
    assert(s.SerializeBegin(&buf, useTagging));
    assert(s.SerializeRawData(data, len));
    assert(s.SerializeEnd());

    Dump(buf);
    // read
    void* readdata = nullptr;
    UInt32 readlen = 0;
    assert(s.UnSerializeBegin(&buf, useTagging));
    assert(s.UnSerializeRawData(readdata, readlen));//need free memory
    assert(s.UnSerializeEnd());

    assert(readdata != nullptr);
    assert(readlen == len);

    const UInt8* data_orgin = (const UInt8*)data;
    const UInt8* data_read = (const UInt8*)readdata;
    for (UInt32 i = 0; i < len; ++i)
        assert(data_orgin[i] == data_read[i]);

    ZA_FREE(readdata);
};

template<class T>
bool TestSingleObject(const T& v, bool useTagging)
{  
    //std::cout << "origin:"<< v << std::endl;

    ZArchive::Archive tool;
    ZArchive::BufferStream buffer;

    buffer.ResetWrite();
    assert(tool.SerializeBegin(&buffer, useTagging));
    assert(tool.Serialize(v));
    assert(tool.SerializeEnd());

    Dump(buffer);

    T other;
    buffer.ResetRead();
    assert(tool.UnSerializeBegin(&buffer, useTagging));
    assert(tool.UnSerialize(other));
    assert(tool.UnSerializeEnd());

    //std::cout << "read:" << other << std::endl;

    assert(other == v);
    return other == v;
}

template <typename T>
void TestArray(const T* arr, UInt32 numItems, bool useTagging)
{
    std::cout << "arr:size:"<< numItems << std::endl;

    ZArchive::Archive s;
    ZArchive::BufferStream buf;

    // write
    assert(s.SerializeBegin(&buf, useTagging));
    assert(s.SerializeArray(arr, numItems));
    assert(s.SerializeEnd());

    Dump(buf);

    // read
    T* arr_read = nullptr;
    UInt32 nums_read = numItems; // in/out
    assert(s.UnSerializeBegin(&buf, useTagging));
    assert(s.UnSerializeArray(arr_read, nums_read));
    assert(s.UnSerializeEnd());

    // we read what we wrote
    assert(numItems == nums_read);
    for (UInt32 i = 0; i < numItems; ++i)
        assert(arr[i] == arr_read[i]);

    ZA_DELETE_ARRAY(arr_read);
}

void test_base_types(bool useTagging)
{
    std::cout << "======base types:======" << std::endl;

    TestSingleObject<Int8>(-0x01, useTagging);
    TestSingleObject<UInt8>(0x01, useTagging);

    TestSingleObject<Int16>(-0x0102, useTagging);
    TestSingleObject<UInt16>(0x0102, useTagging);

    TestSingleObject<Int32>(-0x01020304, useTagging);
    TestSingleObject<UInt32>(0x01020304, useTagging);

    TestSingleObject<Int64>(-0x0102030405060708, useTagging);
    TestSingleObject<UInt64>(0x0102030405060708, useTagging);

    TestSingleObject<Float32>(0.123456f, useTagging);
    TestSingleObject<Float64>(0.123456789, useTagging);

    //TestSingleObject<const char*>("abcdefg hijklmn");
    TestSingleObject<std::string>("opq rst uvw xyz", useTagging);
}

void test_array(bool useTagging)
{
    std::cout << "======arr:======" << std::endl;
    UInt32 a1[4] = { 1, 2, 3, 4 };
    TestArray(a1, 4, useTagging);

    Float32 a2[5] = { 0.5f, -1.5f, 33.44f, 120.3f, 100.1f };
    TestArray(a2, 5, useTagging);

    Float64 a3[5] = { 0.5, -1.5, 33.44, 120.3, 100.1 };
    TestArray(a3, 5, useTagging);

    std::string a4[3];
    a4[0] = "zero";
    a4[1] = "one";
    a4[2] = "two";
    TestArray(a4, 3, useTagging);
}

void test_stl(bool useTagging)
{
    std::cout << "======stl:======" << std::endl;
    {//vector
        std::cout << "vector:" << std::endl;
        std::vector<int> v = { 1,2,3,4,5 };
        TestSingleObject(v, useTagging);
        v.push_back(99);
        TestSingleObject(v, useTagging);
    }

    {//list
        std::cout << "list:" << std::endl;
        std::list<int> v = { 1,1 };
        TestSingleObject(v, useTagging);
        v.push_back(2);
        TestSingleObject(v, useTagging);
    }

    {//deque
        std::cout << "deque:" << std::endl;
        std::list<Float32> v = { 0.01f, 0.99f };
        TestSingleObject(v, useTagging);
        v.push_back(100.123f);
        TestSingleObject(v, useTagging);
    }

    {//pair
        std::cout << "pair:" << std::endl;
        std::pair<int, std::string> v = { 123, "abc"};
        TestSingleObject(v, useTagging);
        v.first = 990;
        TestSingleObject(v, useTagging);
        v.second = "xxo";
        TestSingleObject(v, useTagging);
    }

    {//set
        std::cout << "set:" << std::endl;
        std::set<std::string> v = { "dd", "abc"};
        TestSingleObject(v, useTagging);
        v.insert("abad");
        TestSingleObject(v, useTagging);
    }

    {//multiset
        std::cout << "multiset:" << std::endl;
        std::multiset<std::string> v = { "x1", "x2" };
        TestSingleObject(v, useTagging);
        v.insert("x1");
        TestSingleObject(v, useTagging);
    }

    {//unordered_set
        std::cout << "unordered_set:" << std::endl;
        std::unordered_set<std::string> v = { "1", "2" };
        TestSingleObject(v, useTagging);
        v.insert("3");
        TestSingleObject(v, useTagging);
    }

    {//map
        std::cout << "map:" << std::endl;
        std::map<std::string, int> v = { {"dd",1}, { "abc",99} };
        TestSingleObject(v, useTagging);
        v["000"] = 0;
        TestSingleObject(v, useTagging);
    }

    {//multimap
        std::cout << "multimap:" << std::endl;
        std::multimap<std::string, int> v = { {"dd",1}, { "abc",99}, { "abc",100 } };
        TestSingleObject(v, useTagging);
        v.insert(std::make_pair<std::string, int>("abc", 101));
        TestSingleObject(v, useTagging);
    }

    {//unordered_map
        std::cout << "unordered_map:" << std::endl;
        std::unordered_map<std::string, int> v = { {"dd",1}, { "abc",99} };
        TestSingleObject(v, useTagging);
        v.insert(std::make_pair<std::string, int>("xx", 101));
        TestSingleObject(v, useTagging);
    }
}

void test_buffer(bool useTagging)
{
    std::cout << "======buffer:======" << std::endl;
}

void test_custom(bool useTagging)
{
    std::cout << "======custom:======" << std::endl;
}

void test_rawdata(bool useTagging)
{
    std::cout << "======rawdata:======" << std::endl;
    {
        UInt8 v[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
        TestRawData(v, 8, useTagging);
    }
    {
        Float64 v = 1.23456789;
        TestRawData(&v, sizeof(v), useTagging);
    }
}

int main(int argc, char** argv)
{
    bool useTagging = true;
    test_base_types(useTagging);

    test_array(useTagging);

    test_buffer(useTagging);

    test_stl(useTagging);

    test_custom(useTagging);

    test_rawdata(useTagging);

    return 0;
}