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

#include <TEST_EXIT.h>
#include <climits>
#include <iostream>
#include <limits>
#include <sst/bit.h>
#include <sst/integer.h>
#include <sst/catalog/to_hex.hpp>
#include <string>
#include <type_traits>
#include <vector>

namespace {

struct fail {};

// Checks for agreement across all q,r.
template<class X, class R>
X my_set_bit_int_2(
    std::string const & x_type, X const x, R const r, bool const b) {
  X const ret = sst::set_bit(x, r, b);
  using UR = typename sst::promote_unsigned<R>::type;
  UR const ur = static_cast<UR>(r);
  constexpr unsigned int cb = static_cast<unsigned int>(CHAR_BIT);
  for (UR q2 = 0; q2 != ur / cb + 1U; ++q2) {
    UR const r2 = ur - q2 * cb;
    X const ret2 = sst::set_bit(x, q2, r2, b);
    if (ret2 != ret) {
      std::cerr << "sst::set_bit((" << x_type << ")"
                << std::to_string(x) << ", " << std::to_string(r)
                << ", " << std::to_string(b)
                << ") = " << std::to_string(ret)
                << " does not match sst::set_bit((" << x_type << ")"
                << std::to_string(x) << ", " << std::to_string(q2)
                << ", " << std::to_string(r2) << ", "
                << std::to_string(b) << ") = " << std::to_string(ret2)
                << std::endl;
      throw fail();
    }
  }
  return ret;
}

// Checks for idempotence.
template<class X, class R>
X my_set_bit_int(
    std::string const & x_type, X const x, R const r, bool const b) {
  X const fx = my_set_bit_int_2(x_type, x, r, b);
  X const ffx = my_set_bit_int_2(x_type, fx, r, b);
  if (ffx != fx) {
    std::cerr << "sst::set_bit((" << x_type << ")" << std::to_string(x)
              << ", " << std::to_string(r) << ", " << std::to_string(b)
              << ") = " << std::to_string(fx)
              << " is not idempotent (sst::set_bit((" << x_type << ")"
              << std::to_string(fx) << ", " << std::to_string(r) << ", "
              << std::to_string(b) << ") = " << std::to_string(ffx)
              << ")" << std::endl;
    throw fail();
  }
  return fx;
}

template<class X>
void test_int(std::string const & x_type) {
  constexpr bool X_is_signed = std::is_signed<X>::value;
  constexpr int X_width = std::numeric_limits<X>::digits + X_is_signed;
  X x = 0;
  X expect = 0;
  for (int r = 0; r != X_width; ++r) {
    X const actual = my_set_bit_int(x_type, x, r, 1);
    if (X_is_signed && r == X_width - 1) {
      expect = X(-1);
    } else {
      expect = (expect << 1) | X(1);
    }
    if (actual != expect) {
      std::cerr << "sst::set_bit((" << x_type << ")"
                << std::to_string(x) << ", " << std::to_string(r)
                << ", 1) = " << std::to_string(actual)
                << " is expected to be " << std::to_string(expect)
                << std::endl;
      throw fail();
    }
    x = actual;
  }
  for (int r = X_width - 1; r != -1; --r) {
    X const actual = my_set_bit_int(x_type, x, r, 0);
    if (X_is_signed && r == X_width - 1) {
      expect = std::numeric_limits<X>::max();
    } else {
      expect >>= 1;
    }
    if (actual != expect) {
      std::cerr << "sst::set_bit((" << x_type << ")"
                << std::to_string(x) << ", " << std::to_string(r)
                << ", 0) = " << std::to_string(actual)
                << " is expected to be " << std::to_string(expect)
                << std::endl;
      throw fail();
    }
    x = actual;
  }
}
#define TEST_INT(X) test_int<X>(#X)

// Checks the return value and checks for agreement across all q,r.
template<class R>
std::vector<unsigned char> my_set_bit_mem_2(
    std::vector<unsigned char> const & x, R const r, bool const b) {
  std::vector<unsigned char> fx = x;
  void * const ret = sst::set_bit(fx.data(), r, b);
  if (ret != fx.data()) {
    std::cerr << "sst::set_bit(ptr, r, b) did not return ptr"
              << std::endl;
    throw fail();
  }
  using UR = typename sst::promote_unsigned<R>::type;
  UR const ur = static_cast<UR>(r);
  constexpr unsigned int cb = static_cast<unsigned int>(CHAR_BIT);
  for (UR q2 = 0; q2 != ur / cb + 1U; ++q2) {
    UR const r2 = ur - q2 * cb;
    std::vector<unsigned char> fx2 = x;
    void * const ret2 = sst::set_bit(fx2.data(), q2, r2, b);
    if (ret2 != fx2.data()) {
      std::cerr << "sst::set_bit(ptr, q, r, b) did not return ptr"
                << std::endl;
      throw fail();
    }
    if (fx2 != fx) {
      std::cerr << "sst::set_bit({0x" << sst::to_hex(x) << "}, "
                << std::to_string(r) << ", " << std::to_string(b)
                << ") = {0x" << sst::to_hex(fx)
                << "} does not match sst::set_bit({0x"
                << sst::to_hex(x) << "}, " << std::to_string(q2)
                << ", " << std::to_string(r2) << ", "
                << std::to_string(b) << ") = {0x"
                << sst::to_hex(fx2) << "}" << std::endl;
      throw fail();
    }
  }
  return fx;
}

// Checks for idempotence.
template<class R>
std::vector<unsigned char> my_set_bit_mem(
    std::vector<unsigned char> const & x, R const r, bool const b) {
  auto const fx = my_set_bit_mem_2(x, r, b);
  auto const ffx = my_set_bit_mem_2(fx, r, b);
  if (ffx != fx) {
    std::cerr << "sst::set_bit({0x" << sst::to_hex(x) << "}, "
              << std::to_string(r) << ", " << std::to_string(b)
              << ") = {0x" << sst::to_hex(fx)
              << "} is not idempotent (sst::set_bit({0x"
              << sst::to_hex(fx) << "}, " << std::to_string(r)
              << ", " << std::to_string(b) << ") = {0x"
              << sst::to_hex(ffx) << "})" << std::endl;
    throw fail();
  }
  return fx;
}

template<class R>
void test_mem(
    std::vector<unsigned char> const & x,
    R const r,
    bool const b,
    std::vector<unsigned char> const & expect) {
  auto const actual = my_set_bit_mem(x, r, b);
  if (actual != expect) {
    std::cerr << "sst::set_bit({0x" << sst::to_hex(x) << "}, "
              << std::to_string(r) << ", " << std::to_string(b)
              << ") = {0x" << sst::to_hex(actual)
              << "} is expected to be {0x" << sst::to_hex(expect)
              << "}" << std::endl;
    throw fail();
  }
}

} // namespace

int main() {
  try {

    TEST_INT(bool);
    TEST_INT(signed char);
    TEST_INT(unsigned char);
    TEST_INT(short);
    TEST_INT(unsigned short);
    TEST_INT(int);
    TEST_INT(unsigned int);
    TEST_INT(long);
    TEST_INT(unsigned long);
    TEST_INT(long long);
    TEST_INT(unsigned long long);

    test_mem({0xAA, 0x55}, CHAR_BIT * 0U + 0, 1, {0xAB, 0x55});
    test_mem({0xAB, 0x55}, CHAR_BIT * 1U + 0, 0, {0xAB, 0x54});

  } catch (fail const &) {
    return TEST_EXIT_FAIL;
  } catch (...) {
    return TEST_EXIT_ERROR;
  }
  return TEST_EXIT_PASS;
}
