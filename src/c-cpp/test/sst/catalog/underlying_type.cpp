//
// Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice (including
// the next paragraph) shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// SPDX-License-Identifier: MIT
//

#undef SST_COMPILE_TIME_TESTS
#define SST_COMPILE_TIME_TESTS 1

// Include first to test independence.
#include <sst/catalog/underlying_type.hpp>
// Include twice to test idempotence.
#include <sst/catalog/underlying_type.hpp>
//

#include <type_traits>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([]() {
  //------------------------------------------------------------------

#define F2(a, q, b)                                                    \
  ([&] {                                                               \
    SST_TEST_BOOL(                                                     \
        (std::is_same<typename sst::underlying_type<a q>::type,        \
                      b>::value));                                     \
    SST_TEST_BOOL(                                                     \
        (std::is_same<typename sst::underlying_type<a q &>::type,      \
                      b>::value));                                     \
  }())

#define F(a, b)                                                        \
  ([&] {                                                               \
    F2(a, , b);                                                        \
    F2(a, const, b);                                                   \
    F2(a, volatile, b);                                                \
    F2(a, const volatile, b);                                          \
  }())
    {
      enum unscoped_plain_enum { x };
      F(unscoped_plain_enum,
        typename std::underlying_type<unscoped_plain_enum>::type);
    }

    {
      enum unscoped_int_enum : int { x };
      F(unscoped_int_enum, int);
    }

    {
      enum unscoped_long_enum : long { x };
      F(unscoped_long_enum, long);
    }

    {
      enum class scoped_int_enum : int { x };
      F(scoped_int_enum, int);
    }

    {
      enum class scoped_long_enum : long { x };
      F(scoped_long_enum, long);
    }

#undef F
#undef F2

    //------------------------------------------------------------------
  });
}
