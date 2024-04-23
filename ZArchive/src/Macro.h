#pragma once

#include <assert.h>
#include <memory>

#define ZA_ASSERT(...) assert(__VA_ARGS__)

#define ZA_MALLOC(size) malloc(size)
#define ZA_FREE(ptr) do { if(ptr) {free(ptr); ptr=nullptr;}}while(0)
#define ZA_REALLOC(ptr, size) realloc(ptr, size)

#define ZA_NEW_ARRAY(T, Num)			(new T[Num])
#define ZA_DELETE_ARRAY(p)				do { if (p) { delete[](p); (p) = nullptr; } } while (0)

template <bool b> struct COMPILE_ASSERT_FAILURE; // fwd
template <> struct COMPILE_ASSERT_FAILURE<true> { }; // specialize for "true"

#define COMPILE_ASSERT(name, expr) \
  struct name : COMPILE_ASSERT_FAILURE<(bool)(expr)> { }