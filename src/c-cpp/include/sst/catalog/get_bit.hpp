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

#ifndef SST_CATALOG_GET_BIT_HPP
#define SST_CATALOG_GET_BIT_HPP

#include <cassert>
#include <limits>
#include <sst/catalog/ones_mask.hpp>
#include <sst/catalog/type_msb.hpp>
#include <sst/catalog/uchar_msb.hpp>
#include <sst/integer.h>
#include <sst/language.h>
#include <sst/limits.h>
#include <type_traits>

namespace sst {

template<
    class X,
    class Q,
    class R,
    typename std::enable_if<std::is_integral<X>::value, int>::type = 0>
constexpr bool get_bit(X const x, Q const q, R const r) noexcept {
  SST_STATIC_ASSERT(std::is_integral<X>::value);
  SST_STATIC_ASSERT(std::is_integral<Q>::value);
  SST_STATIC_ASSERT(std::is_integral<R>::value);
  SST_CONSTEXPR_ASSERT(!is_negative(q));
  SST_CONSTEXPR_ASSERT(!is_negative(r));
  using UX = typename promote_unsigned<X>::type;
#define SST_X_is_signed (std::is_signed<X>::value)
#define SST_X_width (std::numeric_limits<X>::digits + SST_X_is_signed)
#define SST_char_bit (std::numeric_limits<unsigned char>::digits)
  SST_CONSTEXPR_ASSERT(unsigned_le(r, SST_X_width - 1));
  SST_CONSTEXPR_ASSERT(unsigned_le(
      q,
      (SST_X_width - 1 - static_cast<int>(r)) / SST_char_bit));
#define SST_i (static_cast<int>(q) * SST_char_bit + static_cast<int>(r))
#define SST_mask (static_cast<UX>(1) << SST_i)
  return SST_X_is_signed && SST_i == SST_X_width - 1 ?
             is_negative(x) :
             static_cast<bool>(static_cast<UX>(x) & SST_mask);
#undef SST_mask
#undef SST_i
#undef SST_char_bit
#undef SST_X_width
#undef SST_X_is_signed
}

template<
    class X,
    class R,
    typename std::enable_if<std::is_integral<X>::value, int>::type = 0>
constexpr bool get_bit(X const x, R const r) noexcept {
  return get_bit(x, 0, r);
}

template<class Q, class R>
bool get_bit(void const * const x, Q const q, R const r) noexcept {
  SST_STATIC_ASSERT(std::is_integral<Q>::value);
  SST_STATIC_ASSERT(std::is_integral<R>::value);
  assert(x != nullptr);
  assert(!is_negative(q));
  assert(!is_negative(r));
  auto const rq = r / std::numeric_limits<unsigned char>::digits;
  auto const rr = r % std::numeric_limits<unsigned char>::digits;
  return static_cast<bool>(
      *(static_cast<unsigned char const *>(x) + q + rq)
      & static_cast<unsigned char>(1U << rr));
}

template<class R>
bool get_bit(void const * const x, R const r) noexcept {
  return get_bit(x, 0, r);
}

} // namespace sst

#endif // SST_CATALOG_GET_BIT_HPP
