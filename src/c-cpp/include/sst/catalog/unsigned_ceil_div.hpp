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

#ifndef SST_CATALOG_UNSIGNED_CEIL_DIV_HPP
#define SST_CATALOG_UNSIGNED_CEIL_DIV_HPP

#include <sst/catalog/SST_CONSTEXPR_ASSERT.hpp>
#include <sst/catalog/decay_t.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/to_unsigned.hpp>

namespace sst {

//----------------------------------------------------------------------
// unsigned_ceil_div-p7gqqhwq
//----------------------------------------------------------------------

template<class A,
         class B,
         sst::enable_if_t<sst::is_integer<A>::value
                          && sst::is_integer<B>::value> = 0>
constexpr sst::decay_t<A> unsigned_ceil_div(A const a,
                                            B const b) noexcept {
  SST_CONSTEXPR_ASSERT((!sst::is_negative(a)));
  SST_CONSTEXPR_ASSERT((!sst::is_negative(b)));
  SST_CONSTEXPR_ASSERT((sst::to_unsigned(b) > 0U));
  return static_cast<sst::decay_t<A>>(
      sst::to_unsigned(a) / sst::to_unsigned(b)
      + (sst::to_unsigned(a) % sst::to_unsigned(b) > 0U ? 1U : 0U));
}

//----------------------------------------------------------------------

} // namespace sst

#endif // #ifndef SST_CATALOG_UNSIGNED_CEIL_DIV_HPP
