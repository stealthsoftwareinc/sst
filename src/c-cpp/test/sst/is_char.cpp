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
#include <sst/catalog/is_char.hpp>
// Include twice to test idempotence.
#include <sst/catalog/is_char.hpp>
//

#include <sst/catalog/SST_CPP20_OR_LATER.h>
#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([] {
    ;

    //------------------------------------------------------------------

#define F3(T, b)                                                       \
  ([] {                                                                \
    SST_TEST_BOOL((sst::is_char<T>::value == (b)),                     \
                  SST_TEST_SHOW((sst::is_char<T>::value)));            \
  }())

#define F2(T, b)                                                       \
  ([] {                                                                \
    F3(T, b);                                                          \
    F3(T &, b);                                                        \
  }())

#define F(T, b)                                                        \
  ([] {                                                                \
    F2(T, b);                                                          \
    F2(T const, b);                                                    \
    F2(T volatile, b);                                                 \
    F2(T const volatile, b);                                           \
  }())

    F(char, true);
#if SST_CPP20_OR_LATER
    F(char8_t, true);
#endif
    F(char16_t, true);
    F(char32_t, true);
    F(wchar_t, true);

    F(bool, false);
    F(signed char, false);
    F(unsigned char, false);
    F(short, false);
    F(int, false);
    F(long, false);
    F(long long, false);
    F(unsigned short, false);
    F(unsigned int, false);
    F(unsigned long, false);
    F(unsigned long long, false);

    struct struct_foo;
    F(struct_foo, false);

    F2(decltype(main), false);

#undef F
#undef F2
#undef F3

    //------------------------------------------------------------------
  });
}
