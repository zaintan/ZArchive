
#include "BufferStream.h"
#include "Archive.h"
#include "ArchiveSTL.h"
#include <string>

#include <assert.h>
//#pragma comment(lib, "ZArchive.lib")

template<class T>
bool test(ZArchive::Archive& tool, ZArchive::Stream* buffer, const T& v)
{
    buffer->Seek(0);
    tool.SerializeBegin(buffer, true);
    tool.Serialize(v);
    tool.SerializeEnd();

    T other;
    buffer->Seek(0);
    tool.UnSerializeBegin(buffer, true);
    tool.UnSerialize(other);
    tool.UnSerializeEnd();

    assert(other == v);
    return other == v;
}


int main(int argc, char** argv)
{
    ZArchive::BufferStream buffer;
    ZArchive::Archive tool;

    Int8 v1   = -0x01;
    UInt8 v2  = 0x01;
    Int16 v3  = -0x0102;
    UInt16 v4 = 0x0102;
  
    Int32 v5  = -0x01020304;
    UInt32 v6 = 0x01020304;
    Int64 v7  = -0x0102030405060708;
    UInt64 v8 = 0x0102030405060708;

    Float32 v9  = 0.123456f;
    Float64 v10 = 0.123456789;
    //base
    test(tool, &buffer, v1);
    test(tool, &buffer, v2);
    test(tool, &buffer, v3);
    test(tool, &buffer, v4);
    test(tool, &buffer, v5);
    test(tool, &buffer, v6);
    test(tool, &buffer, v7);
    test(tool, &buffer, v8);
    test(tool, &buffer, v9);
    test(tool, &buffer, v10);
    
    std::string v11 = "abcdefg";
    std::vector<int> v13 = { 1,2,3,4,5 };
    test(tool, &buffer, v11);
    test(tool, &buffer, v13);

    std::list<int> v12 = { 1,2,3 };
    std::deque<int> v17 = { 1,2,3 };
    std::vector<std::vector<int>> v18= { {1},{1,2},{1,2,3} };

    test(tool, &buffer, v12);
    test(tool, &buffer, v17);
    test(tool, &buffer, v18);

    std::pair<int, std::string> v19 = { 0, "abc" };
    test(tool, &buffer, v19);

    std::set<char> v14 = { 'a', 'b', 'o' };
    std::map<int, std::string> v15 = { {1,"111"}, {2, "222"} };
    //std::unordered_map<int, std::string> v16 = { {3,"333"}, {4, "4444"} };
    //////////////////////////////////////////////////
    //test(tool, &buffer, v14);

    return 0;
}