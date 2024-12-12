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
#include <sst/catalog/to_string.hpp>
// Include twice to test idempotence.
#include <sst/catalog/to_string.hpp>
//

#include <climits>
#include <string>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/integer_to_string_options.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/type_min.hpp>

int main() {
  return sst::test_main([]() {
    //------------------------------------------------------------------

    SST_TEST_BOOL((sst::to_string(false) == "0"));
    SST_TEST_BOOL((sst::to_string(true) == "1"));

    SST_TEST_BOOL((sst::to_string(sst::type_min<char>::value)
                   == std::to_string(sst::type_min<char>::value)));
    SST_TEST_BOOL((sst::to_string(static_cast<char>(0)) == "0"));
    SST_TEST_BOOL((sst::to_string(static_cast<char>(12)) == "12"));
    SST_TEST_BOOL((sst::to_string(sst::type_max<char>::value)
                   == std::to_string(sst::type_max<char>::value)));

    SST_TEST_BOOL(
        (sst::to_string(sst::type_min<signed char>::value)
         == std::to_string(sst::type_min<signed char>::value)));
    SST_TEST_BOOL((sst::to_string(static_cast<signed char>(0)) == "0"));
    SST_TEST_BOOL(
        (sst::to_string(static_cast<signed char>(12)) == "12"));
    SST_TEST_BOOL(
        (sst::to_string(sst::type_max<signed char>::value)
         == std::to_string(sst::type_max<signed char>::value)));

    SST_TEST_BOOL(
        (sst::to_string(static_cast<unsigned char>(0)) == "0"));
    SST_TEST_BOOL(
        (sst::to_string(static_cast<unsigned char>(12)) == "12"));
    SST_TEST_BOOL(
        (sst::to_string(sst::type_max<unsigned char>::value)
         == std::to_string(sst::type_max<unsigned char>::value)));

    SST_TEST_BOOL((sst::to_string(sst::type_min<int>::value)
                   == std::to_string(sst::type_min<int>::value)));
    SST_TEST_BOOL((sst::to_string(-12345) == "-12345"));
    SST_TEST_BOOL((sst::to_string(0) == "0"));
    SST_TEST_BOOL((sst::to_string(12345) == "12345"));
    SST_TEST_BOOL((sst::to_string(sst::type_max<int>::value)
                   == std::to_string(sst::type_max<int>::value)));

    SST_TEST_BOOL((sst::to_string(0U) == "0"));
    SST_TEST_BOOL((sst::to_string(12345U) == "12345"));
    SST_TEST_BOOL(
        (sst::to_string(sst::type_max<unsigned int>::value)
         == std::to_string(sst::type_max<unsigned int>::value)));

    SST_TEST_BOOL((sst::to_string(sst::type_min<long>::value)
                   == std::to_string(sst::type_min<long>::value)));
    SST_TEST_BOOL((sst::to_string(-12345L) == "-12345"));
    SST_TEST_BOOL((sst::to_string(0L) == "0"));
    SST_TEST_BOOL((sst::to_string(12345L) == "12345"));
    SST_TEST_BOOL((sst::to_string(sst::type_max<long>::value)
                   == std::to_string(sst::type_max<long>::value)));

    SST_TEST_BOOL((sst::to_string(0UL) == "0"));
    SST_TEST_BOOL((sst::to_string(12345UL) == "12345"));
    SST_TEST_BOOL(
        (sst::to_string(sst::type_max<unsigned long>::value)
         == std::to_string(sst::type_max<unsigned long>::value)));

    //------------------------------------------------------------------
    // Hexadecimal
    //------------------------------------------------------------------

#define F(a, b)                                                        \
  ([&] {                                                               \
    SST_TEST_BOOL(                                                     \
        (sst::to_string(a, sst::integer_to_string_options().base(16))  \
         == b));                                                       \
  }())

    F(-17, "-11");
    F(-16, "-10");
    F(-15, "-F");
    F(-14, "-E");
    F(-13, "-D");
    F(-12, "-C");
    F(-11, "-B");
    F(-10, "-A");
    F(-9, "-9");
    F(-8, "-8");
    F(-7, "-7");
    F(-6, "-6");
    F(-5, "-5");
    F(-4, "-4");
    F(-3, "-3");
    F(-2, "-2");
    F(-1, "-1");
    F(0, "0");
    F(1, "1");
    F(2, "2");
    F(3, "3");
    F(4, "4");
    F(5, "5");
    F(6, "6");
    F(7, "7");
    F(8, "8");
    F(9, "9");
    F(10, "A");
    F(11, "B");
    F(12, "C");
    F(13, "D");
    F(14, "E");
    F(15, "F");
    F(16, "10");
    F(17, "11");

#undef F

#define F(a, b)                                                        \
  ([&] {                                                               \
    SST_TEST_BOOL((sst::to_string(a,                                   \
                                  sst::integer_to_string_options()     \
                                      .base(16)                        \
                                      .uppercase_digits(false))        \
                   == b));                                             \
  }())

    F(-17, "-11");
    F(-16, "-10");
    F(-15, "-f");
    F(-14, "-e");
    F(-13, "-d");
    F(-12, "-c");
    F(-11, "-b");
    F(-10, "-a");
    F(-9, "-9");
    F(-8, "-8");
    F(-7, "-7");
    F(-6, "-6");
    F(-5, "-5");
    F(-4, "-4");
    F(-3, "-3");
    F(-2, "-2");
    F(-1, "-1");
    F(0, "0");
    F(1, "1");
    F(2, "2");
    F(3, "3");
    F(4, "4");
    F(5, "5");
    F(6, "6");
    F(7, "7");
    F(8, "8");
    F(9, "9");
    F(10, "a");
    F(11, "b");
    F(12, "c");
    F(13, "d");
    F(14, "e");
    F(15, "f");
    F(16, "10");
    F(17, "11");

#undef F

#define F(a, b)                                                        \
  ([&] {                                                               \
    SST_TEST_BOOL(                                                     \
        (sst::to_string(                                               \
             a,                                                        \
             sst::integer_to_string_options().prefix(true).base(16))   \
         == b));                                                       \
  }())

    F(-17, "-0x11");
    F(-16, "-0x10");
    F(-15, "-0xF");
    F(-14, "-0xE");
    F(-13, "-0xD");
    F(-12, "-0xC");
    F(-11, "-0xB");
    F(-10, "-0xA");
    F(-9, "-0x9");
    F(-8, "-0x8");
    F(-7, "-0x7");
    F(-6, "-0x6");
    F(-5, "-0x5");
    F(-4, "-0x4");
    F(-3, "-0x3");
    F(-2, "-0x2");
    F(-1, "-0x1");
    F(0, "0x0");
    F(1, "0x1");
    F(2, "0x2");
    F(3, "0x3");
    F(4, "0x4");
    F(5, "0x5");
    F(6, "0x6");
    F(7, "0x7");
    F(8, "0x8");
    F(9, "0x9");
    F(10, "0xA");
    F(11, "0xB");
    F(12, "0xC");
    F(13, "0xD");
    F(14, "0xE");
    F(15, "0xF");
    F(16, "0x10");
    F(17, "0x11");

#undef F

#define F(a, b)                                                        \
  ([&] {                                                               \
    SST_TEST_BOOL((sst::to_string(a,                                   \
                                  sst::integer_to_string_options()     \
                                      .base(16)                        \
                                      .prefix(true)                    \
                                      .uppercase_prefix(true))         \
                   == b));                                             \
  }())

    F(-17, "-0X11");
    F(-16, "-0X10");
    F(-15, "-0XF");
    F(-14, "-0XE");
    F(-13, "-0XD");
    F(-12, "-0XC");
    F(-11, "-0XB");
    F(-10, "-0XA");
    F(-9, "-0X9");
    F(-8, "-0X8");
    F(-7, "-0X7");
    F(-6, "-0X6");
    F(-5, "-0X5");
    F(-4, "-0X4");
    F(-3, "-0X3");
    F(-2, "-0X2");
    F(-1, "-0X1");
    F(0, "0X0");
    F(1, "0X1");
    F(2, "0X2");
    F(3, "0X3");
    F(4, "0X4");
    F(5, "0X5");
    F(6, "0X6");
    F(7, "0X7");
    F(8, "0X8");
    F(9, "0X9");
    F(10, "0XA");
    F(11, "0XB");
    F(12, "0XC");
    F(13, "0XD");
    F(14, "0XE");
    F(15, "0XF");
    F(16, "0X10");
    F(17, "0X11");

#undef F

    //------------------------------------------------------------------
  });
}
