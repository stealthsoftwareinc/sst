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

#include <TEST_EXIT.h>
#include <climits>
#include <exception>
#include <iostream>
#include <sst/integer.h>
#include <string>

namespace {

struct fail {};

void test(bool const x, std::string const & x_str) {
  if (x) {
    std::cout << "pass: " << x_str << std::endl;
  } else {
    std::cout << "fail: " << x_str << std::endl;
    throw fail();
  }
}

#define TEST3(x) test(x, #x)

#define TEST2(T, U, v) \
  ((v) ? TEST3((sst::can_represent_all<T, U>::value)) : \
         TEST3((!sst::can_represent_all<T, U>::value)))

#define TEST(T, U, v) \
  do { \
    TEST2(T, U, (v)); \
    TEST2(T, U const, (v)); \
    TEST2(T, U volatile, (v)); \
    TEST2(T, U const volatile, (v)); \
    TEST2(T const, U, (v)); \
    TEST2(T const, U const, (v)); \
    TEST2(T const, U volatile, (v)); \
    TEST2(T const, U const volatile, (v)); \
    TEST2(T volatile, U, (v)); \
    TEST2(T volatile, U const, (v)); \
    TEST2(T volatile, U volatile, (v)); \
    TEST2(T volatile, U const volatile, (v)); \
    TEST2(T const volatile, U, (v)); \
    TEST2(T const volatile, U const, (v)); \
    TEST2(T const volatile, U volatile, (v)); \
    TEST2(T const volatile, U const volatile, (v)); \
  } while (false)

template<class T, class U>
constexpr bool eq(T const t, U const u) noexcept {
  return sst::unsigned_eq(t, u);
}

template<class T, class U>
constexpr bool ge(T const t, U const u) noexcept {
  return sst::unsigned_ge(t, u);
}

} // namespace

int main() {
  try {

    TEST(bool, bool, true);
    TEST(bool, signed char, false);
    TEST(bool, short, false);
    TEST(bool, int, false);
    TEST(bool, long, false);
    TEST(bool, long long, false);
    TEST(bool, unsigned char, false);
    TEST(bool, unsigned short, false);
    TEST(bool, unsigned int, false);
    TEST(bool, unsigned long, false);
    TEST(bool, unsigned long long, false);

    TEST(signed char, bool, true);
    TEST(signed char, signed char, true);
    TEST(signed char, short, eq(SCHAR_MAX, SHRT_MAX));
    TEST(signed char, int, eq(SCHAR_MAX, INT_MAX));
    TEST(signed char, long, eq(SCHAR_MAX, LONG_MAX));
    TEST(signed char, long long, eq(SCHAR_MAX, LLONG_MAX));
    TEST(signed char, unsigned char, false);
    TEST(signed char, unsigned short, false);
    TEST(signed char, unsigned int, false);
    TEST(signed char, unsigned long, false);
    TEST(signed char, unsigned long long, false);

    TEST(short, bool, true);
    TEST(short, signed char, true);
    TEST(short, short, true);
    TEST(short, int, eq(SHRT_MAX, INT_MAX));
    TEST(short, long, eq(SHRT_MAX, LONG_MAX));
    TEST(short, long long, eq(SHRT_MAX, LLONG_MAX));
    TEST(short, unsigned char, ge(SHRT_MAX, UCHAR_MAX));
    TEST(short, unsigned short, false);
    TEST(short, unsigned int, false);
    TEST(short, unsigned long, false);
    TEST(short, unsigned long long, false);

    TEST(int, bool, true);
    TEST(int, signed char, true);
    TEST(int, short, true);
    TEST(int, int, true);
    TEST(int, long, eq(INT_MAX, LONG_MAX));
    TEST(int, long long, eq(INT_MAX, LLONG_MAX));
    TEST(int, unsigned char, ge(INT_MAX, UCHAR_MAX));
    TEST(int, unsigned short, ge(INT_MAX, USHRT_MAX));
    TEST(int, unsigned int, false);
    TEST(int, unsigned long, false);
    TEST(int, unsigned long long, false);

    TEST(long, bool, true);
    TEST(long, signed char, true);
    TEST(long, short, true);
    TEST(long, int, true);
    TEST(long, long, true);
    TEST(long, long long, eq(LONG_MAX, LLONG_MAX));
    TEST(long, unsigned char, ge(LONG_MAX, UCHAR_MAX));
    TEST(long, unsigned short, ge(LONG_MAX, USHRT_MAX));
    TEST(long, unsigned int, ge(LONG_MAX, UINT_MAX));
    TEST(long, unsigned long, false);
    TEST(long, unsigned long long, false);

    TEST(long long, bool, true);
    TEST(long long, signed char, true);
    TEST(long long, short, true);
    TEST(long long, int, true);
    TEST(long long, long, true);
    TEST(long long, long long, true);
    TEST(long long, unsigned char, ge(LLONG_MAX, UCHAR_MAX));
    TEST(long long, unsigned short, ge(LLONG_MAX, USHRT_MAX));
    TEST(long long, unsigned int, ge(LLONG_MAX, UINT_MAX));
    TEST(long long, unsigned long, ge(LLONG_MAX, ULONG_MAX));
    TEST(long long, unsigned long long, false);

    TEST(unsigned char, bool, true);
    TEST(unsigned char, signed char, false);
    TEST(unsigned char, short, false);
    TEST(unsigned char, int, false);
    TEST(unsigned char, long, false);
    TEST(unsigned char, long long, false);
    TEST(unsigned char, unsigned char, true);
    TEST(unsigned char, unsigned short, eq(UCHAR_MAX, USHRT_MAX));
    TEST(unsigned char, unsigned int, eq(UCHAR_MAX, UINT_MAX));
    TEST(unsigned char, unsigned long, eq(UCHAR_MAX, ULONG_MAX));
    TEST(unsigned char, unsigned long long, eq(UCHAR_MAX, ULLONG_MAX));

    TEST(unsigned short, bool, true);
    TEST(unsigned short, signed char, false);
    TEST(unsigned short, short, false);
    TEST(unsigned short, int, false);
    TEST(unsigned short, long, false);
    TEST(unsigned short, long long, false);
    TEST(unsigned short, unsigned char, true);
    TEST(unsigned short, unsigned short, true);
    TEST(unsigned short, unsigned int, eq(USHRT_MAX, UINT_MAX));
    TEST(unsigned short, unsigned long, eq(USHRT_MAX, ULONG_MAX));
    TEST(unsigned short, unsigned long long, eq(USHRT_MAX, ULLONG_MAX));

    TEST(unsigned int, bool, true);
    TEST(unsigned int, signed char, false);
    TEST(unsigned int, short, false);
    TEST(unsigned int, int, false);
    TEST(unsigned int, long, false);
    TEST(unsigned int, long long, false);
    TEST(unsigned int, unsigned char, true);
    TEST(unsigned int, unsigned short, true);
    TEST(unsigned int, unsigned int, true);
    TEST(unsigned int, unsigned long, eq(UINT_MAX, ULONG_MAX));
    TEST(unsigned int, unsigned long long, eq(UINT_MAX, ULLONG_MAX));

    TEST(unsigned long, bool, true);
    TEST(unsigned long, signed char, false);
    TEST(unsigned long, short, false);
    TEST(unsigned long, int, false);
    TEST(unsigned long, long, false);
    TEST(unsigned long, long long, false);
    TEST(unsigned long, unsigned char, true);
    TEST(unsigned long, unsigned short, true);
    TEST(unsigned long, unsigned int, true);
    TEST(unsigned long, unsigned long, true);
    TEST(unsigned long, unsigned long long, eq(ULONG_MAX, ULLONG_MAX));

    TEST(unsigned long long, bool, true);
    TEST(unsigned long long, signed char, false);
    TEST(unsigned long long, short, false);
    TEST(unsigned long long, int, false);
    TEST(unsigned long long, long, false);
    TEST(unsigned long long, long long, false);
    TEST(unsigned long long, unsigned char, true);
    TEST(unsigned long long, unsigned short, true);
    TEST(unsigned long long, unsigned int, true);
    TEST(unsigned long long, unsigned long, true);
    TEST(unsigned long long, unsigned long long, true);

  } catch (fail const &) {
    return TEST_EXIT_FAIL;
  } catch (std::exception const & e) {
    std::cerr << "error: " << e.what() << std::endl;
    return TEST_EXIT_ERROR;
  } catch (...) {
    return TEST_EXIT_ERROR;
  }
  return TEST_EXIT_PASS;
}
