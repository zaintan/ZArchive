#include "ArchiveDef.h"
#include "Macro.h"


COMPILE_ASSERT(ArchiveTagCheck, (unsigned)ZArchive::ArchiveTag::eTagEnd <= 256);