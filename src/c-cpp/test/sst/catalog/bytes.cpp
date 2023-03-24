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
#include <sst/catalog/bytes.hpp>
// Include twice to test idempotence.
#include <sst/catalog/bytes.hpp>
//

#include <utility>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/remove_pointer_t.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([&] {
    ;

    //------------------------------------------------------------------

#define F2(T)                                                          \
  ([] {                                                                \
    SST_TEST_BOOL(([] {                                                \
      T x[] = {0};                                                     \
      return sst::bytes(x) == static_cast<void const *>(&x[0]);        \
    }()));                                                             \
    SST_TEST_BOOL(([] {                                                \
      T x[] = {0};                                                     \
      return std::is_same<decltype(sst::bytes(x)),                     \
                          unsigned char *>::value                      \
             || std::is_same<decltype(sst::bytes(x)),                  \
                             unsigned char const *>::value;            \
    }()));                                                             \
    SST_TEST_BOOL(([] {                                                \
      T x[] = {0};                                                     \
      return std::is_const<sst::remove_pointer_t<decltype(sst::bytes(  \
                 x))>>::value                                          \
             == std::is_const<                                         \
                 sst::remove_pointer_t<decltype(&x[0])>>::value;       \
    }()));                                                             \
  }())

#define F(T)                                                           \
  ([] {                                                                \
    F2(T);                                                             \
    F2(T const);                                                       \
  }())

    F(char);
    F(unsigned char);

#undef F
#undef F2

    //------------------------------------------------------------------
  });
}
