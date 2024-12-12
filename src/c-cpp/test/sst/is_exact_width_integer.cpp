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
#include <exception>
#include <iostream>
#include <sst/catalog/is_exact_width_integer.hpp>
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

#define TEST2(T, v) \
  ((v) ? TEST3(sst::is_exact_width_integer<T>::value) : \
         TEST3(!sst::is_exact_width_integer<T>::value))

#define TEST(T, v) \
  do { \
    TEST2(T, (v)); \
    TEST2(T const, (v)); \
    TEST2(T volatile, (v)); \
    TEST2(T const volatile, (v)); \
  } while (false)

} // namespace

int main() {
  try {

    TEST(bool, false);
    TEST(void, false);
    TEST(float, false);
    TEST(double, false);
    TEST(std::exception, false);
#ifdef INT8_MAX
    TEST(std::int8_t, true);
#endif
#ifdef UINT8_MAX
    TEST(std::uint8_t, true);
#endif
#ifdef INT16_MAX
    TEST(std::int16_t, true);
#endif
#ifdef UINT16_MAX
    TEST(std::uint16_t, true);
#endif
#ifdef INT32_MAX
    TEST(std::int32_t, true);
#endif
#ifdef UINT32_MAX
    TEST(std::uint32_t, true);
#endif
#ifdef INT64_MAX
    TEST(std::int64_t, true);
#endif
#ifdef UINT64_MAX
    TEST(std::uint64_t, true);
#endif

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
