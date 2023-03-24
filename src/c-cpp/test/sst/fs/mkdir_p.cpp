/*
 * Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice (including
 * the next paragraph) shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

/* begin_includes */

#include <TEST_EXIT.h>
#include <ios>
#include <iostream>
#include <sst/catalog/mkdir_p.hpp>
#include <stdexcept>
#include <string>

/* end_includes */

// Make sure sst::mkdir_p(path) returns expect.
template<class Line>
static bool test(
  std::string const & file,
  Line const line,
  std::string const & path,
  bool const expect
) {
  try {
    bool const actual = sst::mkdir_p(path);
    if (actual == expect) {
      return true;
    }
    std::cerr
      << std::boolalpha
      << file << ":" << std::to_string(line) << ": "
      << "sst::mkdir_p(\"" << path << "\") "
      << "returned " << actual << " "
      << "(expected " << expect << ")"
      << std::endl;
    ;
    return false;
  } catch (std::exception const & e) {
    std::cerr
      << std::boolalpha
      << file << ":" << std::to_string(line) << ": "
      << "sst::mkdir_p(\"" << path << "\") "
      << "threw an exception "
      << "(expected " << expect << "): "
      << e.what()
      << std::endl;
    ;
    throw;
  } catch (...) {
    std::cerr
      << std::boolalpha
      << file << ":" << std::to_string(line) << ": "
      << "sst::mkdir_p(\"" << path << "\") "
      << "threw an exception "
      << "(expected " << expect << ")"
      << std::endl;
    ;
    throw;
  }
}

#define test(path, expect) test(__FILE__, __LINE__, path, expect)

int main(
) {
  try {
    bool pass = true;
    pass &= test(".", false);
    pass &= test("..", false);
    return pass ? TEST_EXIT_PASS : TEST_EXIT_FAIL;
  } catch (...) {
    return TEST_EXIT_ERROR;
  }
}
