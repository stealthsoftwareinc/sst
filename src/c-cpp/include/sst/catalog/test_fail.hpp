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

#ifndef SST_CATALOG_TEST_FAIL_HPP
#define SST_CATALOG_TEST_FAIL_HPP

#include <stdexcept>
#include <string>
#include <utility>

#include <sst/catalog/to_string.hpp>

namespace sst {

class test_fail final : public std::runtime_error {

  // This allows default construction (e.g., sst::test_fail()).
  static std::string build() {
    return "";
  }

  // This allows a dummy int parameter to also be used for default
  // construction (e.g., sst::test_fail(0)). This is needed by the
  // SST_TEST_BOOL and SST_TEST_THROW macros.
  static std::string build(int) {
    return "";
  }

  template<class T, class... Args>
  static std::string build(std::pair<std::string, T> const & x,
                           Args &&... args) {
    return "  (" + x.first + "): " + sst::to_string(x.second) + "\n"
           + build(std::forward<Args>(args)...);
  }

public:

  template<class... Args>
  test_fail(Args &&... args)
      : std::runtime_error(build(std::forward<Args>(args)...)) {
  }

}; //

} // namespace sst

#endif // SST_CATALOG_TEST_FAIL_HPP
