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

#ifndef SST_CATALOG_FROM_VARINT_HPP
#define SST_CATALOG_FROM_VARINT_HPP

#include <stdexcept>

#include <sst/catalog/cbegin.hpp>
#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_byte_input_iterable.hpp>
#include <sst/catalog/is_byte_input_iterator.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/is_unsigned_integer.hpp>
#include <sst/catalog/promote_t.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/type_min.hpp>
#include <sst/catalog/uchar_max_v.hpp>
#include <sst/catalog/uchar_msb_v.hpp>
#include <sst/catalog/unsigned_gt.hpp>
#include <sst/catalog/value_bits.hpp>

namespace sst {

//----------------------------------------------------------------------

template<
    class Dst,
    class Src,
    sst::enable_if_t<sst::is_integer<Dst>::value
                     && sst::is_byte_input_iterator<Src>::value> = 0>
sst::remove_cvref_t<Dst> from_varint(Src src) {
  constexpr unsigned int m1 = sst::uchar_max_v >> 1;
  constexpr unsigned int m2 = sst::uchar_msb_v >> 1;
  constexpr unsigned int m3 = sst::uchar_msb_v;
  using D = sst::remove_cvref_t<Dst>;
  using T = sst::promote_t<D>;
  T y = 0;
  T flip_mask = 0;
  bool flip = false;
  int i = 0;
  while (true) {
    unsigned int const b = static_cast<unsigned char>(*src);
    ++src;
    bool const last = !static_cast<bool>(b & m3);
    unsigned int const m = m1 >> (last ? 1 : 0);
again:
    unsigned int const x = (flip ? ~b : b) & m;
    if (x > 0
        && (sst::unsigned_gt(x, sst::type_max<D>::value)
            || i >= sst::value_bits<T>::value
            || sst::unsigned_gt(x, sst::type_max<D>::value >> i))) {
      if (flip) {
        throw std::overflow_error("");
      }
      y ^= flip_mask;
      flip = true;
      goto again;
    }
    y |= static_cast<T>(x) << i;
    flip_mask |= static_cast<T>(m) << i;
    if (last) {
      if (!(b & m2)) {
        if (flip) {
          throw std::overflow_error("");
        }
        return static_cast<D>(y);
      }
      if (!flip) {
        y ^= flip_mask;
      }
      if (sst::is_unsigned_integer<D>::value) {
        throw std::overflow_error("");
      }
      if (-y == sst::type_min<D>::value) {
        throw std::overflow_error("");
      }
      return static_cast<D>(-y - static_cast<T>(1));
    }
    i += sst::char_bit_v - 1;
  }
}

//----------------------------------------------------------------------

#define SST_r (sst::from_varint<Dst>(sst::cbegin(src)))

template<
    class Dst,
    class Src,
    sst::enable_if_t<sst::is_integer<Dst>::value
                     && sst::is_byte_input_iterable<Src>::value> = 0>
auto from_varint(Src const & src) noexcept(noexcept(SST_r))
    -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

//----------------------------------------------------------------------

} // namespace sst

#endif // #ifndef SST_CATALOG_FROM_VARINT_HPP
