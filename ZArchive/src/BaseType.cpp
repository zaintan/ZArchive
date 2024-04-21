#include "BaseType.h"
#include "Macro.h"

COMPILE_ASSERT(BaseTypeCheckInt8, sizeof(Int8) == 1);
COMPILE_ASSERT(BaseTypeCheckUInt8, sizeof(UInt8) == 1);
COMPILE_ASSERT(BaseTypeCheckInt16, sizeof(Int16) == 2);
COMPILE_ASSERT(BaseTypeCheckUInt16, sizeof(UInt16) == 2);
COMPILE_ASSERT(BaseTypeCheckInt32, sizeof(Int32) == 4);
COMPILE_ASSERT(BaseTypeCheckUInt32, sizeof(UInt32) == 4);
COMPILE_ASSERT(BaseTypeCheckInt64, sizeof(Int64) == 8);
COMPILE_ASSERT(BaseTypeCheckUInt64, sizeof(UInt64) == 8);
COMPILE_ASSERT(BaseTypeCheckFloat32, sizeof(Float32) == 4);
COMPILE_ASSERT(BaseTypeCheckFloat64, sizeof(Float64) == 8);