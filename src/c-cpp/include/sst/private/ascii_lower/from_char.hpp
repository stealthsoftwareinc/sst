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

#ifndef SST_PRIVATE_ASCII_LOWER_FROM_CHAR_HPP
#define SST_PRIVATE_ASCII_LOWER_FROM_CHAR_HPP

#include <sst/catalog/ascii_lower.hpp>
#include <sst/catalog/ascii_lower_functor.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_byte.hpp>
#include <sst/catalog/is_char.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {

//----------------------------------------------------------------------
// src, dst
//----------------------------------------------------------------------

template<class X, class Src, class Dst>
class ascii_lower_functor<
    sst::enable_if_t<
        (sst::is_char<Src>::value || sst::is_byte<Src>::value)
        && sst::is_output_iterator<Dst,
                                   sst::remove_cvref_t<Src>>::value>,
    X,
    Src,
    Dst> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;

public:

  dst_t operator()(src_t const src, dst_t dst) const {
    *dst = sst::ascii_lower(src);
    ++dst;
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src
//----------------------------------------------------------------------

template<class X, class Src>
class ascii_lower_functor<
    sst::enable_if_t<(sst::is_char<Src>::value
                      || sst::is_byte<Src>::value)>,
    X,
    Src> {

  using src_t = sst::remove_cvref_t<Src>;

public:

  src_t operator()(src_t const src) const {
    constexpr src_t A = static_cast<src_t>('A');
    constexpr src_t Z = static_cast<src_t>('Z');
    constexpr src_t a = static_cast<src_t>('a');
    if (src >= A && src <= Z) {
      return a + (src - A);
    }
    return src;
  }

}; //

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_PRIVATE_ASCII_LOWER_FROM_CHAR_HPP
