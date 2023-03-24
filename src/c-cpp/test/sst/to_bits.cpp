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
#include <sst/integer.h>
#include <sst/representation.h>
#include <sst/catalog/to_hex.hpp>
#include <string>
#include <type_traits>
#include <vector>

namespace {

struct fail {};

// Checks the return value and checks for agreement across all q,r.
template<
    class Y,
    bool SignExtend = std::is_signed<Y>::value,
    class R,
    class N>
std::vector<unsigned char> my_to_bits_2(
    std::string const & y_type,
    std::vector<unsigned char> const & x,
    R const r,
    Y const y,
    N const n) {
  std::vector<unsigned char> fx = x;
  void * const ret = sst::to_bits<Y, SignExtend>(fx.data(), r, y, n);
  if (ret != fx.data()) {
    std::cerr << "sst::to_bits(ptr, r, y, n) did not return ptr"
              << std::endl;
    throw fail();
  }
  using UR = typename sst::promote_unsigned<R>::type;
  UR const ur = static_cast<UR>(r);
  constexpr unsigned int cb = static_cast<unsigned int>(CHAR_BIT);
  for (UR q2 = 0; q2 != ur / cb + 1U; ++q2) {
    UR const r2 = ur - q2 * cb;
    std::vector<unsigned char> fx2 = x;
    void * const ret2 =
        sst::to_bits<Y, SignExtend>(fx2.data(), q2, r2, y, n);
    if (ret2 != fx2.data()) {
      std::cerr << "sst::to_bits(ptr, q, r, y, n) did not return ptr"
                << std::endl;
      throw fail();
    }
    if (fx2 != fx) {
      std::cerr << "sst::to_bits<" << y_type << ", "
                << (SignExtend ? "true" : "false") << ">({0x"
                << sst::to_hex(x) << "}, " << std::to_string(r)
                << ", " << std::to_string(y) << ", "
                << std::to_string(n) << ") = {0x"
                << sst::to_hex(fx)
                << "} does not match sst::to_bits<" << y_type << ", "
                << (SignExtend ? "true" : "false") << ">({0x"
                << sst::to_hex(x) << "}, " << std::to_string(q2)
                << ", " << std::to_string(r2) << ", "
                << std::to_string(y) << ", " << std::to_string(n)
                << ") = {0x" << sst::to_hex(fx2) << "}"
                << std::endl;
      throw fail();
    }
  }
  return fx;
}

// Checks for idempotence.
template<
    class Y,
    bool SignExtend = std::is_signed<Y>::value,
    class R,
    class N>
std::vector<unsigned char> my_to_bits(
    std::string const & y_type,
    std::vector<unsigned char> const & x,
    R const r,
    Y const y,
    N const n) {
  auto const fx = my_to_bits_2<Y, SignExtend>(y_type, x, r, y, n);
  auto const ffx = my_to_bits_2<Y, SignExtend>(y_type, fx, r, y, n);
  if (ffx != fx) {
    std::cerr << "sst::to_bits<" << y_type << ", "
              << (SignExtend ? "true" : "false") << ">({0x"
              << sst::to_hex(x) << "}, " << std::to_string(r)
              << ", " << std::to_string(y) << ", " << std::to_string(n)
              << ") = {0x" << sst::to_hex(fx)
              << "} is not idempotent (sst::to_bits<" << y_type << ", "
              << (SignExtend ? "true" : "false") << ">({0x"
              << sst::to_hex(fx) << "}, " << std::to_string(r)
              << ", " << std::to_string(y) << ", " << std::to_string(n)
              << ") = {0x" << sst::to_hex(ffx) << "})"
              << std::endl;
    throw fail();
  }
  return fx;
}

template<
    class Y,
    bool SignExtend = std::is_signed<Y>::value,
    class R,
    class N>
void test(
    std::string const & y_type,
    std::vector<unsigned char> const & x,
    R const r,
    Y const y,
    N const n,
    std::vector<unsigned char> const & expect) {
  auto const actual = my_to_bits<Y, SignExtend>(y_type, x, r, y, n);
  if (actual != expect) {
    std::cerr << "sst::to_bits<" << y_type << ", "
              << (SignExtend ? "true" : "false") << ">({0x"
              << sst::to_hex(x) << "}, " << std::to_string(r)
              << ", " << std::to_string(y) << ", " << std::to_string(n)
              << ") = {0x" << sst::to_hex(actual)
              << "} is expected to be {0x" << sst::to_hex(expect)
              << "}" << std::endl;
    ;
    throw fail();
  }
}

} // namespace

int main() {
  try {

    {
      std::vector<unsigned char> const x = {0, 0};
      constexpr unsigned int cb = static_cast<unsigned int>(CHAR_BIT);
      constexpr unsigned int cm = static_cast<unsigned int>(UCHAR_MAX);
      for (unsigned int r = 0; r != cb; ++r) {
        unsigned int const rc = cb - r;
        for (unsigned int n = 1; n != 9; ++n) {
          unsigned int const nc = cb - n;
          std::vector<unsigned char> const expect = {
              static_cast<unsigned char>(
                  (cm >> (n >= rc ? r : nc)) << r),
              static_cast<unsigned char>(
                  n <= rc ? 0U : cm >> (rc + nc))};
          test<bool, true>("bool", x, r, 1, n, expect);
          test<int>("int", x, r, -1, n, expect);
          test<int, true>("int", x, r, -1, n, expect);
          test<unsigned int, true>(
              "unsigned int", x, r, UINT_MAX, n, expect);
        }
      }
    }

    {
      std::vector<unsigned char> const x = {UCHAR_MAX, UCHAR_MAX};
      constexpr unsigned int cb = static_cast<unsigned int>(CHAR_BIT);
      constexpr unsigned int cm = static_cast<unsigned int>(UCHAR_MAX);
      for (unsigned int r = 0; r != cb; ++r) {
        unsigned int const rc = cb - r;
        for (unsigned int n = 1; n != 9; ++n) {
          unsigned int const nc = cb - n;
          std::vector<unsigned char> const expect = {
              static_cast<unsigned char>(
                  ~((cm >> (n >= rc ? r : nc)) << r)),
              static_cast<unsigned char>(
                  ~(n <= rc ? 0U : cm >> (rc + nc)))};
          test<bool>("bool", x, r, 0, n, expect);
          test<bool, false>("bool", x, r, 0, n, expect);
          test<int, false>("int", x, r, 0, n, expect);
          test<unsigned int>("unsigned int", x, r, 0, n, expect);
          test<unsigned int, false>("unsigned int", x, r, 0, n, expect);
        }
      }
    }

  } catch (fail const &) {
    return TEST_EXIT_FAIL;
  } catch (...) {
    return TEST_EXIT_ERROR;
  }
  return TEST_EXIT_PASS;
}
