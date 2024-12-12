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

#ifndef SST_CATALOG_TEST_MAIN_HPP
#define SST_CATALOG_TEST_MAIN_HPP

#include <exception>
#include <iostream>
#include <ostream>

#include <sst/catalog/old/to_bytes_functor.hpp>
#include <sst/catalog/test_fail.hpp>
#include <sst/catalog/test_skip.hpp>
#include <sst/catalog/what.hpp>

namespace sst {

template<class Callable>
int test_main(Callable && f) {
  constexpr int pass = 0;
  constexpr int fail = 1;
  constexpr int skip = 77;
  constexpr int error = 99;
  try {
    try {
      std::cout.exceptions(std::cout.badbit | std::cout.failbit);
      f();
    } catch (sst::test_skip const &) {
      return skip;
    } catch (sst::test_fail const & e) {
      std::cout << e.what() << std::flush;
      return fail;
    }
  } catch (...) {
    try {
      std::cout << "\n" << std::flush;
    } catch (...) {
    }
    try {
      std::cerr << "Error: " << sst::what() << "\n" << std::flush;
    } catch (...) {
    }
    return error;
  }
  return pass;
}

} // namespace sst

#endif // SST_CATALOG_TEST_MAIN_HPP
