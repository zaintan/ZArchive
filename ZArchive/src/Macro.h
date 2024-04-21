#pragma once

#include <assert.h>

#define ZA_ASSERT(...) assert(__VA_ARGS__)

template <bool b> struct COMPILE_ASSERT_FAILURE; // fwd
template <> struct COMPILE_ASSERT_FAILURE<true> { }; // specialize for "true"

#define COMPILE_ASSERT(name, expr) \
  struct name : COMPILE_ASSERT_FAILURE<(bool)(expr)> { }