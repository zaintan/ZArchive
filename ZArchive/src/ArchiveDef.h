#pragma once

namespace ZArchive {

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
        //stl
        eTagSTLVector,
        eTagSTLList,
        eTagSTLDeque,

        eTagPair,
        eTagSTLMap,
        eTagSTLSet,
        eTagSTLUnOrderedMap,
        eTagSTLUnOrderedSet,

        eTagEnd
    };


    
}