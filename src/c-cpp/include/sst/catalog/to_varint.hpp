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

#ifndef SST_CATALOG_TO_VARINT_HPP
#define SST_CATALOG_TO_VARINT_HPP

//
// The sst::to_varint function converts an integer to varint form.
// Varint form is a variable-length binary form where another binary
// form (usually two's complement little endian with a guaranteed sign
// bit) is packed into the bottom 7 bits of each byte, and the top bit
// of each byte indicates whether there are still more bytes to come.
//
// The term "varint" and the varint form itself are inspired by varints
// from Google's Protocol Buffers.
//
// Here are some examples using two's complement little endian with a
// guaranteed sign bit as the underlying binary form.
//
//                     Value      Varint form
//                        0    00000000
//                        1    00000001
//                        2    00000010
//                        3    00000011
//                       61    00111101
//                       62    00111110
//                       63    00111111
//                       64    11000000 00000000
//                       65    11000001 00000000
//                       66    11000010 00000000
//                       67    11000011 00000000
//                      125    11111101 00000000
//                      126    11111110 00000000
//                      127    11111111 00000000
//                      128    10000000 00000001
//                      129    10000001 00000001
//                      130    10000010 00000001
//                      131    10000011 00000001
//                       -1    01111111
//                       -2    01111110
//                       -3    01111101
//                      -62    01000010
//                      -63    01000001
//                      -64    01000000
//                      -65    10111111 01111111
//                      -66    10111110 01111111
//                      -67    10111101 01111111
//                      -68    10111100 01111111
//                     -126    10000010 01111111
//                     -127    10000001 01111111
//                     -128    10000000 01111111
//                     -129    11111111 01111110
//                     -130    11111110 01111110
//                     -131    11111101 01111110
//                     -132    11111100 01111110
//

#include <iterator>
#include <utility>
#include <vector>

#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/signed_right_shift.hpp>
#include <sst/catalog/uchar_max_v.hpp>
#include <sst/catalog/uchar_msb_v.hpp>
#include <sst/catalog/value_bits.hpp>

namespace sst {

//----------------------------------------------------------------------
// Fundamental integer sources
//----------------------------------------------------------------------

template<class Src,
         class Dst,
         sst::enable_if_t<
             sst::is_integer<Src>::value
             && sst::is_output_iterator<Dst, unsigned char>::value> = 0>
Dst to_varint(Src src, Dst dst) {
  constexpr unsigned int m1 = sst::uchar_max_v >> 1;
  constexpr unsigned int m2 = sst::uchar_msb_v >> 1;
  constexpr unsigned int m3 = sst::uchar_msb_v;
  bool const negative = sst::is_negative(src);
  while (true) {
    unsigned int const b = static_cast<unsigned char>(src);
    unsigned int const x = b & m1;
    if (sst::value_bits<Src>::value > sst::char_bit_v - 1) {
      src = sst::signed_right_shift(src, sst::char_bit_v - 1);
    } else {
      src = sst::signed_right_shift(src, sst::char_bit_v - 2);
      src = sst::signed_right_shift(src, 1);
    }
    bool const t = static_cast<bool>(x & m2);
    bool const last = negative ? src == static_cast<Src>(-1) && t :
                                 src == static_cast<Src>(0) && !t;
    *dst = static_cast<unsigned char>(x | (last ? 0U : m3));
    ++dst;
    if (last) {
      break;
    }
  }
  return dst;
}

//----------------------------------------------------------------------
// Arbitrary sources into a new byte container
//----------------------------------------------------------------------

template<class Dst = std::vector<unsigned char>,
         class Src,
         sst::enable_if_t<sst::is_integer<Src>::value> = 0>
Dst to_varint(Src && src) {
  Dst dst;
  sst::to_varint(std::forward<Src>(src), std::back_inserter(dst));
  return dst;
}

//----------------------------------------------------------------------

} // namespace sst

#endif // #ifndef SST_CATALOG_TO_VARINT_HPP
