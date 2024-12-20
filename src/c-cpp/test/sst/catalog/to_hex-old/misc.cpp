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
#include <iterator>
#include <sst/catalog/to_hex.hpp>
#include <string>
#include <vector>

namespace {

template<class Src>
std::string to_string(Src src, Src const src_end) {
  std::string dst = "{";
  bool first = true;
  for (; src != src_end; ++src) {
    if (first) {
      first = false;
    } else {
      dst += ", ";
    }
    dst += std::to_string(*src);
  }
  dst += "}";
  return dst;
}

template<class Line, class Src>
bool test(
    std::string const & file,
    Line const line,
    Src const & src,
    std::string const & expect) {
  try {
    std::string dst = sst::to_hex(src);
    if (dst == expect) {
      return true;
    }
    std::cerr << file << ":" << std::to_string(line) << ": "
              << "sst::to_hex("
              << to_string(src.cbegin(), src.cend()) << ") "
              << "returned \"" << dst << "\" "
              << "(expected \"" << expect << "\")" << std::endl;
    return false;
  } catch (std::exception const & e) {
    std::cerr << file << ":" << std::to_string(line) << ": "
              << "sst::to_hex("
              << to_string(src.cbegin(), src.cend()) << ") "
              << "threw an exception "
              << "(expected \"" << expect << "\"): " << e.what()
              << std::endl;
    throw;
  } catch (...) {
    std::cerr << file << ":" << std::to_string(line) << ": "
              << "sst::to_hex("
              << to_string(src.cbegin(), src.cend()) << ") "
              << "threw an exception "
              << "(expected \"" << expect << "\")" << std::endl;
    throw;
  }
}

} // namespace

#define test(src, expect) test(__FILE__, __LINE__, src, expect)

int main() {
  try {
    using Src = std::vector<unsigned char>;
    bool pass = true;
    pass &= test(Src({}), "");
    pass &= test(Src({0x00}), "00");
    pass &= test(Src({0x01}), "01");
    pass &= test(Src({0x23}), "23");
    pass &= test(Src({0x45}), "45");
    pass &= test(Src({0x67}), "67");
    pass &= test(Src({0x89}), "89");
    pass &= test(Src({0xAB}), "AB");
    pass &= test(Src({0xCD}), "CD");
    pass &= test(Src({0xEF}), "EF");
    pass &= test(Src({0xFF}), "FF");
    pass &= test(Src({0x00, 0x00}), "0000");
    pass &= test(Src({0x01, 0x23}), "0123");
    pass &= test(Src({0x45, 0x67}), "4567");
    pass &= test(Src({0x89, 0xAB}), "89AB");
    pass &= test(Src({0xCD, 0xEF}), "CDEF");
    pass &= test(Src({0xFF, 0xFF}), "FFFF");
    return pass ? TEST_EXIT_PASS : TEST_EXIT_FAIL;
  } catch (...) {
    return TEST_EXIT_ERROR;
  }
}
