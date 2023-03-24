//
// Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
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
#include <sst/catalog/unsigned_max.hpp>
// Include twice to test idempotence.
#include <sst/catalog/unsigned_max.hpp>
//

#include <type_traits>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/perfect_eq.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([&] {
    ;

    //------------------------------------------------------------------

#define F(R, V, ...)                                                   \
  ([&] {                                                               \
    SST_TEST_BOOL(                                                     \
        (sst::perfect_eq(sst::unsigned_max(__VA_ARGS__), V)));         \
    SST_TEST_BOOL(                                                     \
        (std::is_same<decltype(sst::unsigned_max(__VA_ARGS__)),        \
                      R>::value));                                     \
  }())

    F(int, 1, 1);
    F(int, 2, 1, 2);
    F(int, 2, 2, 1);
    F(unsigned int, 1, 1U);
    F(unsigned int, 2, 1U, 2);
    F(unsigned int, 2, 2U, 1);
    F(long, 1, 1L);
    F(long, 2, 1L, 2);
    F(long, 2, 2L, 1);

#undef F

    //------------------------------------------------------------------

#define F(R, V, ...)                                                   \
  ([&] {                                                               \
    SST_TEST_BOOL(                                                     \
        (sst::perfect_eq(sst::unsigned_max<R>(__VA_ARGS__), V)));      \
    SST_TEST_BOOL(                                                     \
        (std::is_same<decltype(sst::unsigned_max<R>(__VA_ARGS__)),     \
                      R>::value));                                     \
  }())

    F(char, 1, 1);
    F(char, 2, 1, 2);
    F(char, 2, 2, 1);
    F(int, 1, 1);
    F(int, 2, 1, 2);
    F(int, 2, 2, 1);
    F(unsigned int, 1, 1);
    F(unsigned int, 2, 1, 2);
    F(unsigned int, 2, 2, 1);
    F(long, 1, 1);
    F(long, 2, 1, 2);
    F(long, 2, 2, 1);

#undef F

    //------------------------------------------------------------------
  });
}
