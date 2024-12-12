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

#ifndef SST_CATALOG_SST_TEST_THROW_HPP
#define SST_CATALOG_SST_TEST_THROW_HPP

#include <iostream>
#include <ostream>

#include <sst/catalog/test_fail.hpp>

#define SST_TEST_THROW_3(x_str, x, T_str, T, ...)                      \
  ([&]() {                                                             \
    std::cout << "Test: " << __FILE__ << ":"                           \
              << static_cast<unsigned long>(__LINE__)                  \
              << ": " x_str " throws " T_str " ..." << std::flush;     \
    try {                                                              \
      void((x));                                                       \
    } catch (T const &) {                                              \
      std::cout << " pass\n" << std::flush;                            \
      return;                                                          \
    } catch (...) {                                                    \
      std::cout << " fail?\n" << std::flush;                           \
      throw;                                                           \
    }                                                                  \
    std::cout << " fail\n" << std::flush;                              \
    throw sst::test_fail(__VA_ARGS__);                                 \
  }())

#define SST_TEST_THROW_2(x, T, ...)                                    \
  (SST_TEST_THROW_3(#x, (x), #T, T, __VA_ARGS__))

#define SST_TEST_THROW(...) (SST_TEST_THROW_2(__VA_ARGS__, 0))

#endif // SST_CATALOG_SST_TEST_THROW_HPP
