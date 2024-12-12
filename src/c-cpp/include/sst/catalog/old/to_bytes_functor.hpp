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

#ifndef SST_CATALOG_OLD_TO_BYTES_FUNCTOR_HPP
#define SST_CATALOG_OLD_TO_BYTES_FUNCTOR_HPP

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_THROW_UNIMPLEMENTED.hpp>
#include <sst/catalog/signed_right_shift.hpp>
#include <sst/catalog/buffer_overrun.hpp>
#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/enable_if.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/integer_rep.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/perfect_ge.hpp>
#include <sst/catalog/perfect_gt.hpp>
#include <sst/catalog/remove_cvref.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/uchar_max_v.hpp>
#include <sst/catalog/uchar_msb_v.hpp>
#include <type_traits>

namespace sst {
namespace old {

//----------------------------------------------------------------------

template<class, class = sst::enable_t>
class to_bytes_functor;

//----------------------------------------------------------------------
// Fundamental integer types
//----------------------------------------------------------------------

// TODO: Allow endianness to be chosen.

template<class T1>
class to_bytes_functor<
    T1,
    typename sst::enable_if<std::is_integral<
        typename sst::remove_cvref<T1>::type>::value>::type> {

  using T = typename sst::remove_cvref<T1>::type;

public:
  template<class ByteIt, class Size>
  ByteIt operator()(T src,
                    ByteIt dst,
                    Size n,
                    sst::integer_rep const rep =
                        sst::integer_rep::twos_complement()) {
    SST_ASSERT(sst::perfect_gt(n, 0));
    switch (rep) {
      case sst::integer_rep::pure_unsigned():
      case sst::integer_rep::twos_complement(): {
        bool const negative =
            rep == sst::integer_rep::pure_unsigned() ?
                (SST_ASSERT(sst::perfect_ge(src, 0)), false) :
                sst::is_negative(src);
        unsigned char digit = 0;
        for (; n > 0; --n) {
          digit = static_cast<unsigned char>(src);
          *dst++ = digit;
          if (negative) {
            src = sst::signed_right_shift(src, sst::char_bit_v - 2);
            src = sst::signed_right_shift(src, 2);
          } else {
            src >>= sst::char_bit_v - 2;
            src >>= 2;
          }
        }
        if (negative) {
          if (src != -1) {
            throw sst::buffer_overrun("sst::old::to_bytes: buffer overrun");
          }
        } else {
          if (src != 0) {
            throw sst::buffer_overrun("sst::old::to_bytes: buffer overrun");
          }
        }
        if (rep == sst::integer_rep::twos_complement()
            && bool(digit & sst::uchar_msb_v) != negative) {
          throw sst::buffer_overrun("sst::old::to_bytes: buffer overrun");
        }
      } break;
      default: {
        SST_THROW_UNIMPLEMENTED();
      } break;
    }
    return dst;
  }
};

//----------------------------------------------------------------------

} // namespace old
} // namespace sst

#endif // SST_CATALOG_OLD_TO_BYTES_FUNCTOR_HPP
