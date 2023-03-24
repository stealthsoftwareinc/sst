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
#include <exception>
#include <iostream>
#include <sst/rep/from_hex.h>
#include <string>
#include <vector>

namespace {

std::string to_string(std::vector<unsigned char> const & src) {
  std::string dst = "{";
  bool first = true;
  for (unsigned char const x : src) {
    if (first) {
      first = false;
    } else {
      dst += ", ";
    }
    dst += std::to_string(x);
  }
  dst += "}";
  return dst;
}

template<class Line>
bool test(
    std::string const & file,
    Line const line,
    std::string const & src,
    std::vector<unsigned char> const & ref) {
  try {
    std::vector<unsigned char> const dst = sst::rep::from_hex(src);
    if (dst == ref) {
      return true;
    }
    std::cerr << file << ":" << std::to_string(line) << ": "
              << "sst::rep::from_hex(\"" << src << "\") "
              << "returned " << to_string(dst) << " "
              << "(expected " << to_string(ref) << ")" << std::endl;
    return false;
  } catch (std::exception const & e) {
    std::cerr << file << ":" << std::to_string(line) << ": "
              << "sst::rep::from_hex(\"" << src << "\") "
              << "threw an exception (expected " << to_string(ref)
              << "): " << e.what() << std::endl;
    throw;
  } catch (...) {
    std::cerr << file << ":" << std::to_string(line) << ": "
              << "sst::rep::from_hex(\"" << src << "\") "
              << "threw an exception (expected " << to_string(ref)
              << ")" << std::endl;
    throw;
  }
}

} // namespace

#define test(src, expect) test(__FILE__, __LINE__, src, expect)

int main() {
  try {
    using v = std::vector<unsigned char>;
    bool pass = true;
    pass &= test("", v({}));
    pass &= test("00", v({0x00}));
    pass &= test("01", v({0x01}));
    pass &= test("23", v({0x23}));
    pass &= test("45", v({0x45}));
    pass &= test("67", v({0x67}));
    pass &= test("89", v({0x89}));
    pass &= test("AB", v({0xAB}));
    pass &= test("CD", v({0xCD}));
    pass &= test("EF", v({0xEF}));
    pass &= test("FF", v({0xFF}));
    pass &= test("ab", v({0xAB}));
    pass &= test("cd", v({0xCD}));
    pass &= test("ef", v({0xEF}));
    pass &= test("ff", v({0xFF}));
    pass &= test("0000", v({0x00, 0x00}));
    pass &= test("0123", v({0x01, 0x23}));
    pass &= test("4567", v({0x45, 0x67}));
    pass &= test("89AB", v({0x89, 0xAB}));
    pass &= test("CDEF", v({0xCD, 0xEF}));
    pass &= test("FFFF", v({0xFF, 0xFF}));
    pass &= test("89ab", v({0x89, 0xAB}));
    pass &= test("cdef", v({0xCD, 0xEF}));
    pass &= test("ffff", v({0xFF, 0xFF}));
    return pass ? TEST_EXIT_PASS : TEST_EXIT_FAIL;
  } catch (...) {
    return TEST_EXIT_ERROR;
  }
}
