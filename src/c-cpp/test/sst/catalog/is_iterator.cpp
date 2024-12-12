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
#include <sst/catalog/is_iterator.hpp>
// Include twice to test idempotence.
#include <sst/catalog/is_iterator.hpp>
//

#include <vector>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([] {
    ;

    //------------------------------------------------------------------

#define F2(T, b)                                                       \
  ([] {                                                                \
    SST_TEST_BOOL((sst::is_iterator<T>::value == (b)));                \
    SST_TEST_BOOL((sst::is_iterator<T &>::value == (b)));              \
  }())

#define F(T, b)                                                        \
  ([] {                                                                \
    F2(T, b);                                                          \
    F2(T const, b);                                                    \
    F2(T volatile, b);                                                 \
    F2(T const volatile, b);                                           \
  }())

    int array[1];

    F(int, false);
    F(int *, true);
    F(void *, false);
    F2(decltype(main), false);
    F2(decltype(&main), false);
    F(decltype(array), false);
    F(decltype(&array), true);
    F(std::vector<int>, false);
    F(std::vector<int>::iterator, true);
    F(std::vector<int>::const_iterator, true);

#undef F
#undef F2

    //------------------------------------------------------------------
  });
}
