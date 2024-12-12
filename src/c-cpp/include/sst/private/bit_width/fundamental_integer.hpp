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

#ifndef SST_PRIVATE_BIT_WIDTH_FUNDAMENTAL_INTEGER_HPP
#define SST_PRIVATE_BIT_WIDTH_FUNDAMENTAL_INTEGER_HPP

#include <type_traits>

#include <sst/catalog/SST_CONSTEXPR_ASSERT.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/floor_lg.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/promote_t.hpp>

namespace sst {

//----------------------------------------------------------------------

template<class X,
         sst::enable_if_t<sst::is_integer<X>::value
                          && !std::is_reference<X>::value> = 0>
constexpr X bit_width(X const x) noexcept {
  using Y = sst::promote_t<X>;
  SST_CONSTEXPR_ASSERT((!sst::is_negative(x)));
  return Y(Y(x) == Y(0) ? Y(1) : Y(1) + sst::floor_lg(Y(x)));
}

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_PRIVATE_BIT_WIDTH_FUNDAMENTAL_INTEGER_HPP
