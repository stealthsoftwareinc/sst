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

#ifndef SST_CATALOG_OS2IP_HPP
#define SST_CATALOG_OS2IP_HPP

#include <stdexcept>
#include <utility>

#include <sst/catalog/SST_NODISCARD.h>
#include <sst/catalog/cbegin.hpp>
#include <sst/catalog/cend.hpp>
#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_byte.hpp>
#include <sst/catalog/is_input_iterator.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_iterable.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/catalog/is_value_sentinel.hpp>
#include <sst/catalog/numeric_limits.hpp>
#include <sst/catalog/peek.hpp>
#include <sst/catalog/pos.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/step.hpp>

namespace sst {

template<class Dst_,
         class Src_,
         class End_,
         sst::enable_if_t<
             sst::char_bit_v == 8 && sst::is_integer_ish<Dst_>::value
             && sst::is_input_iterator<Src_, sst::is_byte>::value
             && (sst::is_sentinel<End_, Src_>::value
                 || sst::is_value_sentinel<End_, Src_>::value
                 || sst::is_integer_ish<End_>::value)> = 0,
         class Dst = sst::remove_cvref_t<Dst_>,
         class Src = sst::remove_cvref_t<Src_>,
         class End = sst::remove_cvref_t<End_>>
SST_NODISCARD()
Dst os2ip(Src_ src, End_ const & end) {
  Dst dst{};
  Dst const & max7 = sst::numeric_limits<Dst>::max() >> 7;
  Dst const & max1 = sst::numeric_limits<Dst>::max() >> 1;
  sst::pos<Src, End> pos;
  while (true) {
    auto const p = sst::peek(src, end, pos);
    if (p == nullptr) {
      break;
    }
    if (sst::numeric_limits<Dst>::is_bounded && dst > max7) {
      throw std::runtime_error("sst::os2ip: Integer too large");
    }
    dst <<= 7;
    if (sst::numeric_limits<Dst>::is_bounded && dst > max1) {
      throw std::runtime_error("sst::os2ip: Integer too large");
    }
    dst <<= 1;
    dst += Dst(static_cast<unsigned char>(*p));
    sst::step(src, end, pos);
  }
  return dst;
}

template<
    class Dst_,
    class Src_,
    class End_,
    sst::enable_if_t<
        sst::char_bit_v == 8 && sst::is_integer_ish<Dst_>::value
        && sst::is_iterable<Src_, sst::is_byte>::value
        && (sst::is_sentinel<
                End_,
                decltype(sst::cbegin(std::declval<Src_ &>()))>::value
            || sst::is_value_sentinel<
                End_,
                decltype(sst::cbegin(std::declval<Src_ &>()))>::value
            || sst::is_integer_ish<End_>::value)> = 0,
    class Dst = sst::remove_cvref_t<Dst_>,
    class Src = sst::remove_cvref_t<Src_>,
    class End = sst::remove_cvref_t<End_>>
SST_NODISCARD()
Dst os2ip(Src_ const & src, End_ const & end) {
  return sst::os2ip<Dst>(sst::cbegin(src), end);
}

template<class Dst_,
         class Src_,
         sst::enable_if_t<
             sst::char_bit_v == 8 && sst::is_integer_ish<Dst_>::value
             && sst::is_iterable<Src_, sst::is_byte>::value> = 0,
         class Dst = sst::remove_cvref_t<Dst_>,
         class Src = sst::remove_cvref_t<Src_>>
SST_NODISCARD()
Dst os2ip(Src_ const & src) {
  return sst::os2ip<Dst>(src, sst::cend(src));
}

} // namespace sst

#endif // SST_CATALOG_OS2IP_HPP
