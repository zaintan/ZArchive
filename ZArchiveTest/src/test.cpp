
#include "BufferStream.h"
#include "Archive.h"
#include "ArchiveSTL.h"
#include <string>

//#pragma comment(lib, "ZArchive.lib")

int main(int argc, char** argv)
{
    ZArchive::BufferStream buffer;

    ZArchive::Archive tool;
    tool.SerializeBegin(&buffer, true);

    int first = 0x1;
    short second = 0x2;
    float third = 0.01f; 
    std::vector<int> four = {1,2,3,4,5};
    std::set<char> five = { 'a', 'b', 'o' };
    std::map<int, std::string> six =  { {1,"111"}, {2, "222"} };
    std::unordered_map<int, std::string> se = { {3,"333"}, {4, "4444"} };
    tool.Serialize(first);
    tool.Serialize(second);
    tool.Serialize(third);
    tool.Serialize(four);
    //tool.Serialize(five);
    //tool.Serialize(six);
    //tool.Serialize(se);
    tool.SerializeEnd();

    buffer.Seek(0);
    tool.UnSerializeBegin(&buffer, true);
    {
        int u1; short u2; float u3; std::vector<int> u4; std::set<char> u5;
        std::map<int, std::string> u6;
        std::unordered_map<int, std::string> u7;

        tool.UnSerialize(u1);
        tool.UnSerialize(u2);
        tool.UnSerialize(u3);
        tool.UnSerialize(u4);
        //tool.UnSerialize(u5);
        //tool.UnSerialize(u6);
       // tool.UnSerialize(u7);
        tool.UnSerializeEnd();
    }
    return 0;
}