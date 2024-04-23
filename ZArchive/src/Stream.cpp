#include "Stream.h"
#include "Archive.h"

ARCHIVE_IMPLEMENT_SERIALIZE(ZArchive::Stream)//(Archive* ar, const typ& obj)
{
	void* data = obj.GetRawData();
	UInt32 len = obj.GetRawDataSize();

	return ar->WriteTag(ZArchive::ArchiveTag::eTagStream)
		&& ar->SerializeCount(len)
		&& ar->SerializeRawData(data, len);
}

ARCHIVE_IMPLEMENT_UNSERIALIZE(ZArchive::Stream)//(Archive* ar, typ& obj)  
{
	if (!ar->ReadAndCheckTag(ZArchive::ArchiveTag::eTagStream))
		return false;

	UInt32 size = 0;
	if (!ar->UnSerializeCount(size))
		return false;

	obj.ResetLen(size);
	if (!ar->UnSerializeRawData(obj.GetRawData(), size))
		return false;
	obj.ResetWritePos(size);
	return true;
}

