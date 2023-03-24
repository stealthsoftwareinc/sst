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
#include <sst/catalog/is_floating.hpp>
// Include twice to test idempotence.
#include <sst/catalog/is_floating.hpp>
//

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([]() {
  //------------------------------------------------------------------

#define F2(T, v)                                                       \
  ([&] {                                                               \
    SST_TEST_BOOL((sst::is_floating<T>::value == v));                  \
    SST_TEST_BOOL((sst::is_floating<T &>::value == v));                \
  }())

#define F1(T, v)                                                       \
  ([&] {                                                               \
    F2(T, v);                                                          \
    F2(T const, v);                                                    \
    F2(T volatile, v);                                                 \
    F2(T const volatile, v);                                           \
  }())
    F1(float, true);
    F1(double, true);
    F1(long double, true);
    F1(float *, false);
    F1(double *, false);
    F1(long double *, false);
    F1(int, false);
    F1(int *, false);

#undef F1
#undef F2

    //------------------------------------------------------------------
  });
}
