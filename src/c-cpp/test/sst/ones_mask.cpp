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

#include <exception>
#include <iostream>
#include <string>
#include <type_traits>

#include <sst/catalog/ones_mask.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/value_bits.hpp>

#include <TEST_EXIT.h>

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

#define TEST(x) test((x), #x)

} // namespace

int main() {
  try {

    TEST((std::is_same<decltype(sst::ones_mask<bool>(0)), bool>()));
    TEST((std::is_same<decltype(sst::ones_mask<char>(0)), char>()));
    TEST((std::is_same<decltype(sst::ones_mask<signed char>(0)),
                       signed char>()));
    TEST((std::is_same<decltype(sst::ones_mask<unsigned char>(0)),
                       unsigned char>()));
    TEST((std::is_same<decltype(sst::ones_mask<short>(0)), short>()));
    TEST((std::is_same<decltype(sst::ones_mask<unsigned short>(0)),
                       unsigned short>()));
    TEST((std::is_same<decltype(sst::ones_mask<int>(0)), int>()));
    TEST((std::is_same<decltype(sst::ones_mask<unsigned int>(0)),
                       unsigned int>()));
    TEST((std::is_same<decltype(sst::ones_mask<long>(0)), long>()));
    TEST((std::is_same<decltype(sst::ones_mask<unsigned long>(0)),
                       unsigned long>()));
    TEST((std::is_same<decltype(sst::ones_mask<long long>(0)),
                       long long>()));
    TEST((std::is_same<decltype(sst::ones_mask<unsigned long long>(0)),
                       unsigned long long>()));

    TEST(sst::ones_mask<bool>(0) == false);
    TEST(sst::ones_mask<bool>(1) == true);

    TEST(sst::ones_mask<int>(0) == 0);
    TEST(sst::ones_mask<int>(1) == 1);
    TEST(sst::ones_mask<int>(2) == 3);
    TEST(sst::ones_mask<int>(3) == 7);
    TEST(sst::ones_mask<int>(4) == 15);
    TEST(sst::ones_mask<int>(5) == 31);
    TEST(sst::ones_mask<int>(6) == 63);
    TEST(sst::ones_mask<int>(7) == 127);
    TEST(sst::ones_mask<int>(8) == 255);
    TEST(sst::ones_mask<int>(9) == 511);
    TEST(sst::ones_mask<int>(10) == 1023);
    TEST(sst::ones_mask<int>(11) == 2047);
    TEST(sst::ones_mask<int>(12) == 4095);
    TEST(sst::ones_mask<int>(13) == 8191);
    TEST(sst::ones_mask<int>(14) == 16383);
    TEST(sst::ones_mask<int>(15) == 32767);
    TEST(sst::ones_mask<int>(sst::value_bits<int>::value)
         == sst::type_max<int>::value);

    TEST(sst::ones_mask<unsigned int>(0) == 0U);
    TEST(sst::ones_mask<unsigned int>(1) == 1U);
    TEST(sst::ones_mask<unsigned int>(2) == 3U);
    TEST(sst::ones_mask<unsigned int>(3) == 7U);
    TEST(sst::ones_mask<unsigned int>(4) == 15U);
    TEST(sst::ones_mask<unsigned int>(5) == 31U);
    TEST(sst::ones_mask<unsigned int>(6) == 63U);
    TEST(sst::ones_mask<unsigned int>(7) == 127U);
    TEST(sst::ones_mask<unsigned int>(8) == 255U);
    TEST(sst::ones_mask<unsigned int>(9) == 511U);
    TEST(sst::ones_mask<unsigned int>(10) == 1023U);
    TEST(sst::ones_mask<unsigned int>(11) == 2047U);
    TEST(sst::ones_mask<unsigned int>(12) == 4095U);
    TEST(sst::ones_mask<unsigned int>(13) == 8191U);
    TEST(sst::ones_mask<unsigned int>(14) == 16383U);
    TEST(sst::ones_mask<unsigned int>(15) == 32767U);
    TEST(sst::ones_mask<unsigned int>(16) == 65535U);
    TEST(sst::ones_mask<unsigned int>(
             sst::value_bits<unsigned int>::value)
         == sst::type_max<unsigned int>::value);

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
