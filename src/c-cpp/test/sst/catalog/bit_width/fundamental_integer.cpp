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
#include <sst/catalog/bit_width.hpp>
// Include twice to test idempotence.
#include <sst/catalog/bit_width.hpp>
//

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/value_bits.hpp>

int main() {
  return sst::test_main([] {
    ;

    //------------------------------------------------------------------

#define F1(a, b)                                                       \
  ([&] {                                                               \
    SST_TEST_BOOL((sst::bit_width((a)) == (b)), SST_TEST_SHOW((a)));   \
    SST_TEST_BOOL(                                                     \
        (std::is_same<decltype((a)), decltype((b))>::value));          \
  }())

#define F2(T, a, b) (F1(static_cast<T>((a)), static_cast<T>((b))))

#define F3(T)                                                          \
  ([&] {                                                               \
    F2(T, 0, 1);                                                       \
    F2(T, 1, 1);                                                       \
    F2(T, 2, 2);                                                       \
    F2(T, 3, 2);                                                       \
    F2(T, 4, 3);                                                       \
    F2(T, 5, 3);                                                       \
    F2(T, 6, 3);                                                       \
    F2(T, 7, 3);                                                       \
    F2(T, 8, 4);                                                       \
    F2(T, 9, 4);                                                       \
    F2(T, 10, 4);                                                      \
    F2(T, 11, 4);                                                      \
    F2(T, 12, 4);                                                      \
    F2(T, 13, 4);                                                      \
    F2(T, 14, 4);                                                      \
    F2(T, 15, 4);                                                      \
    F2(T, 16, 5);                                                      \
    F2(T, 17, 5);                                                      \
    F2(T, 18, 5);                                                      \
    F2(T, 19, 5);                                                      \
    F2(T, 20, 5);                                                      \
    F2(T, 21, 5);                                                      \
    F2(T, 22, 5);                                                      \
    F2(T, 23, 5);                                                      \
    F2(T, 24, 5);                                                      \
    F2(T, 25, 5);                                                      \
    F2(T, 26, 5);                                                      \
    F2(T, 27, 5);                                                      \
    F2(T, 28, 5);                                                      \
    F2(T, 29, 5);                                                      \
    F2(T, 30, 5);                                                      \
    F2(T, 31, 5);                                                      \
    F2(T, 32, 6);                                                      \
    F2(T, sst::type_max<T>::value, sst::value_bits<T>::value);         \
  }())

    F2(bool, false, true);
    F2(bool, true, true);

    F3(signed char);
    F3(short);
    F3(int);
    F3(long);
    F3(long long);
    F3(unsigned char);
    F3(unsigned short);
    F3(unsigned int);
    F3(unsigned long);
    F3(unsigned long long);

#undef F3
#undef F2
#undef F1

    //------------------------------------------------------------------
  });
}
