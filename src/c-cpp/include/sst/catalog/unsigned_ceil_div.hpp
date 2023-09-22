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
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/if_chain_t.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/is_positive.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/to_unsigned.hpp>

namespace sst {

//----------------------------------------------------------------------
// unsigned_ceil_div-p7gqqhwq
//----------------------------------------------------------------------

template<class R_ = void,
         class A_,
         class A = sst::remove_cvref_t<A_>,
         class B_,
         class B = sst::remove_cvref_t<B_>,
         class R =
             sst::remove_cvref_t<sst::if_chain_t<std::is_same<R_, void>,
                                                 decltype(A() / B()),
                                                 R_>>,
         sst::enable_if_t<sst::is_integer<A>::value
                          && sst::is_integer<B>::value> = 0>
constexpr R unsigned_ceil_div(A_ const a, B_ const b) noexcept {
  SST_CONSTEXPR_ASSERT((!sst::is_negative(a)));
  SST_CONSTEXPR_ASSERT((sst::is_positive(b)));
  return static_cast<R>(
      sst::to_unsigned(a) / sst::to_unsigned(b)
      + (sst::to_unsigned(a) % sst::to_unsigned(b) ? 1U : 0U));
}

//----------------------------------------------------------------------

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/unsigned_eq.hpp>

#define SST_F(A, B)                                                    \
  SST_STATIC_ASSERT(                                                   \
      (sst::unsigned_eq((A), (B))                                      \
       && std::is_same<decltype((A)), decltype((B))>::value));

SST_F((sst::unsigned_ceil_div(0, 1)), (0))
SST_F((sst::unsigned_ceil_div(1, 1)), (1))
SST_F((sst::unsigned_ceil_div(1, 2)), (1))
SST_F((sst::unsigned_ceil_div(2, 1)), (2))
SST_F((sst::unsigned_ceil_div(2, 2)), (1))
SST_F((sst::unsigned_ceil_div(2, 3)), (1))
SST_F((sst::unsigned_ceil_div(3, 1)), (3))
SST_F((sst::unsigned_ceil_div(3, 2)), (2))
SST_F((sst::unsigned_ceil_div(3, 3)), (1))
SST_F((sst::unsigned_ceil_div(3, 4)), (1))
SST_F((sst::unsigned_ceil_div(4, 1)), (4))
SST_F((sst::unsigned_ceil_div(4, 2)), (2))
SST_F((sst::unsigned_ceil_div(4, 3)), (2))
SST_F((sst::unsigned_ceil_div(4, 4)), (1))
SST_F((sst::unsigned_ceil_div(4, 5)), (1))
SST_F((sst::unsigned_ceil_div(9, 4L)), (3L))
SST_F((sst::unsigned_ceil_div<int>(9, 4L)), (3))

#undef SST_F

#endif // #if SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // SST_CATALOG_UNSIGNED_CEIL_DIV_HPP
