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

#ifndef SST_CATALOG_CEIL_SQRT_HPP
#define SST_CATALOG_CEIL_SQRT_HPP

#include <cmath>
#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_CPP14_CONSTEXPR.hpp>
#include <sst/catalog/enable_if.hpp>
#include <sst/catalog/perfect_ge.hpp>
#include <sst/catalog/unsigned_le.hpp>
#include <type_traits>

namespace sst {

template<class T,
         typename sst::enable_if<std::is_integral<T>::value>::type = 0>
SST_CPP14_CONSTEXPR T ceil_sqrt(T const x) noexcept {
  SST_ASSERT(sst::perfect_ge(x, 0));
  if (sst::unsigned_le(x, 1)) {
    return x;
  }
  T a = 1;
  T b = x;
  while (a < b) {
    T const m = a / 2 + b / 2;
    if (m > x / m) {
      b = m;
    } else if (m * m < x) {
      a = m + 1;
    } else {
      return m;
    }
  }
  return a;
}

template<class T,
         typename sst::enable_if<
             !std::is_integral<T>::value
             && !std::is_floating_point<T>::value>::type = 0>
T ceil_sqrt(T const & x) {
  SST_ASSERT(x >= 0);
  if (x <= 1) {
    return x;
  }
  T a = 1;
  T b = x;
  while (a < b) {
    T const m = a / 2 + b / 2;
    if (m > x / m) {
      b = m;
    } else if (m * m < x) {
      a = m + 1;
    } else {
      return m;
    }
  }
  return a;
}

template<
    class T,
    typename sst::enable_if<std::is_floating_point<T>::value>::type = 0>
T ceil_sqrt(T const x) {
  return std::ceil(std::sqrt(x));
}

} // namespace sst

#endif // SST_CATALOG_CEIL_SQRT_HPP
