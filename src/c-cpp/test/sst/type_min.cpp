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
#include <iostream>
#include <limits>
#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/type_min.hpp>
#include <string>
#include <type_traits>

namespace {

struct fail {};

void test3(bool const x, std::string const & x_str) {
  if (x) {
    std::cout << "pass: " << x_str << std::endl;
  } else {
    std::cout << "fail: " << x_str << std::endl;
    throw fail();
  }
}

#define TEST2(x) test3(x, #x)

#define TEST(T)                                                        \
  do {                                                                 \
    TEST2((std::is_same<decltype(sst::type_min<T>::value),             \
                        T const>::value));                             \
    TEST2(sst::type_min<T>::value == std::numeric_limits<T>::min());   \
  } while (false)

} // namespace

int main() {
  try {

    TEST(bool);
    TEST(char);
    TEST(signed char);
    TEST(unsigned char);
    TEST(short);
    TEST(unsigned short);
    TEST(int);
    TEST(unsigned int);
    TEST(long);
    TEST(unsigned long);
    TEST(long long);
    TEST(unsigned long long);

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
