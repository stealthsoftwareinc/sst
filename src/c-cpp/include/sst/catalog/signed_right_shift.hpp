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

#ifndef SST_CATALOG_SIGNED_RIGHT_SHIFT_HPP
#define SST_CATALOG_SIGNED_RIGHT_SHIFT_HPP

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/SST_CONSTEXPR_ASSERT.hpp>
#include <sst/catalog/SST_NODISCARD.h>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_integer_like.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/perfect_lt.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/value_bits.hpp>
#include <sst/catalog/zero.hpp>

namespace sst {

//
// The sst::signed_right_shift function returns x shifted right by n bit
// positions, performing a "signed" shift when x is negative.
//
// When x is negative, the result is the value obtained by shifting the
// infinite two's complement representation of x to the right by n bit
// positions. For example:
//
//       // -1 is ...11111 in infinite two's complement.
//       sst::signed_right_shift(-1, 0) -> -1
//       sst::signed_right_shift(-1, 1) -> -1
//       sst::signed_right_shift(-1, 2) -> -1
//
//       // -2 is ...11110 in infinite two's complement.
//       sst::signed_right_shift(-2, 0) -> -2
//       sst::signed_right_shift(-2, 1) -> -1
//       sst::signed_right_shift(-2, 2) -> -1
//
//       // -3 is ...11101 in infinite two's complement.
//       sst::signed_right_shift(-3, 0) -> -3
//       sst::signed_right_shift(-3, 1) -> -2
//       sst::signed_right_shift(-3, 2) -> -1
//
//       // -4 is ...11100 in infinite two's complement.
//       sst::signed_right_shift(-4, 0) -> -4
//       sst::signed_right_shift(-4, 1) -> -2
//       sst::signed_right_shift(-4, 2) -> -1
//
// Mathematically, the result is always floor(x / 2^n), regardless of
// whether x is negative.
//
// If n is negative or not less than the number of value bits in the
// type of x, the behavior is undefined.
//

// TODO: Change static_cast<X>(1) to sst::one<X>() once it's
//       implemented.

template<class X_,
         class N_,
         sst::enable_if_t<sst::is_integer_like<X_>::value
                          && sst::is_integer_ish<N_>::value> = 0,
         class X = sst::remove_cvref_t<X_>,
         class N = sst::remove_cvref_t<N_>>
SST_NODISCARD()
constexpr X signed_right_shift(X_ const & x, N_ const & n)
    SST_NOEXCEPT(noexcept(static_cast<void>(sst::is_negative(n)),
                          static_cast<void>(sst::perfect_lt(n, 0)),
                          static_cast<void>(static_cast<int>(n)))) {
  SST_CONSTEXPR_ASSERT((!sst::is_negative(n)));
  SST_CONSTEXPR_ASSERT((sst::perfect_lt(n, sst::value_bits<X>::value)));
  return sst::is_negative(x) ?
             x / (static_cast<X>(1) << static_cast<int>(n))
                 - (x % (static_cast<X>(1) << static_cast<int>(n)) ?
                        static_cast<X>(1) :
                        sst::zero<X>()) :
             x >> static_cast<int>(n);
}

template<class X_,
         class N_,
         sst::enable_if_t<sst::is_integer_ish<X_>::value
                          && !sst::is_integer_like<X_>::value
                          && sst::is_integer_ish<N_>::value> = 0,
         class X = sst::remove_cvref_t<X_>,
         class N = sst::remove_cvref_t<N_>>
SST_NODISCARD()
X signed_right_shift(X_ const & x, N_ const & n) {
  SST_ASSERT((!sst::is_negative(n)));
  return sst::is_negative(x) ?
             x / (static_cast<X>(1) << n)
                 - (x % (static_cast<X>(1) << n) ? static_cast<X>(1) :
                                                   sst::zero<X>()) :
             x >> n;
}

} // namespace sst

#endif // SST_CATALOG_SIGNED_RIGHT_SHIFT_HPP
