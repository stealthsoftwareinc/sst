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

#ifndef SST_CATALOG_CEIL_LG_HPP
#define SST_CATALOG_CEIL_LG_HPP

#include <cmath>
#include <type_traits>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_CONSTEXPR_ASSERT.hpp>
#include <sst/catalog/enable_if.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/perfect_gt.hpp>
#include <sst/catalog/promote.hpp>

namespace sst {

//----------------------------------------------------------------------

template<class X, sst::enable_if_t<sst::is_integer<X>::value> = 0>
constexpr X ceil_lg(X const x, bool const b = false) noexcept {
  SST_CONSTEXPR_ASSERT((sst::perfect_gt(x, 0)));
  return X(x == X(1) ? X(b) :
                       sst::ceil_lg(x >> 1, b || (x & X(1))) + X(1));
}

//----------------------------------------------------------------------

template<class T,
         typename sst::enable_if<
             !std::is_integral<T>::value
             && !std::is_floating_point<T>::value>::type = 0>
T ceil_lg(T x) noexcept {
  SST_ASSERT((x > 0));
  T n = 0;
  bool a = false;
  bool b = (x & 1) != 0;
  while ((x >>= 1) != 0) {
    ++n;
    a = b;
    b = b || ((x & 1) != 0);
  }
  return n + a;
}

//----------------------------------------------------------------------

template<
    class T,
    typename sst::enable_if<std::is_floating_point<T>::value>::type = 0>
T ceil_lg(T const x) noexcept {
  SST_ASSERT((x > 0));
  return std::ceil(std::log2(x));
}

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_CATALOG_CEIL_LG_HPP
