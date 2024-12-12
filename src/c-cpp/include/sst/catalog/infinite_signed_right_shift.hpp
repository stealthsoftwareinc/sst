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

#ifndef SST_CATALOG_INFINITE_SIGNED_RIGHT_SHIFT_HPP
#define SST_CATALOG_INFINITE_SIGNED_RIGHT_SHIFT_HPP

#include <sst/catalog/SST_CONSTEXPR_ASSERT.hpp>
#include <sst/catalog/SST_NODISCARD.h>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_integer_like.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/signed_right_shift.hpp>
#include <sst/catalog/unsigned_lt.hpp>
#include <sst/catalog/value_bits.hpp>
#include <sst/catalog/zero.hpp>

namespace sst {

//
// Like sst::signed_right_shift except the behavior is well-defined for
// arbitrarily large n.
//

template<class X_,
         class N_,
         sst::enable_if_t<sst::is_integer_like<X_>::value
                          && sst::is_integer_ish<N_>::value> = 0,
         class X = sst::remove_cvref_t<X_>,
         class N = sst::remove_cvref_t<N_>>
SST_NODISCARD()
constexpr X infinite_signed_right_shift(X_ const & x, N_ const & n)
    SST_NOEXCEPT(
        noexcept(static_cast<void>(sst::is_negative(n)),
                 static_cast<void>(sst::unsigned_lt(n, 0)),
                 static_cast<void>(sst::signed_right_shift(x, n)))) {
  SST_CONSTEXPR_ASSERT((!sst::is_negative(n)));
  return sst::unsigned_lt(n, sst::value_bits<X>::value) ?
             sst::signed_right_shift(x, n) :
         sst::is_negative(x) ? static_cast<X>(-1) :
                               sst::zero<X>();
}

template<class X_,
         class N_,
         sst::enable_if_t<sst::is_integer_ish<X_>::value
                          && !sst::is_integer_like<X_>::value
                          && sst::is_integer_ish<N_>::value> = 0,
         class X = sst::remove_cvref_t<X_>,
         class N = sst::remove_cvref_t<N_>>
SST_NODISCARD()
X infinite_signed_right_shift(X_ const & x, N_ const & n) {
  SST_CONSTEXPR_ASSERT((!sst::is_negative(n)));
  return sst::signed_right_shift(x, n);
}

} // namespace sst

#endif // SST_CATALOG_INFINITE_SIGNED_RIGHT_SHIFT_HPP
