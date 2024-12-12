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

#ifndef SST_CATALOG_I2OSP_HPP
#define SST_CATALOG_I2OSP_HPP

#include <stdexcept>
#include <vector>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/SST_NODISCARD.h>
#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/checked_resize.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {

template<
    class Src_,
    class Len_,
    class Dst_,
    sst::enable_if_t<
        sst::char_bit_v == 8 && sst::is_integer_ish<Src_>::value
        && sst::is_integer_ish<Len_>::value
        && sst::is_output_iterator<Dst_, unsigned char>::value> = 0,
    class Src = sst::remove_cvref_t<Src_>,
    class Len = sst::remove_cvref_t<Len_>,
    class Dst = sst::remove_cvref_t<Dst_>>
Dst i2osp(Src_ const & src, Len_ len, Dst_ dst) {
  SST_ASSERT((!sst::is_negative(src)));
  SST_ASSERT((!sst::is_negative(len)));
  bool first_loop = true;
  while (len--) {
    Src x = src;
    for (Len i = 0; i < len; ++i) {
      x >>= 7;
      x >>= 1;
    }
    if (first_loop && x > 255) {
      throw std::runtime_error("sst::i2osp: Integer too large");
    }
    *dst = static_cast<unsigned char>(x);
    ++dst;
    first_loop = false;
  }
  return dst;
}

template<class Dst_ = std::vector<unsigned char>,
         class Src_,
         class Len_,
         sst::enable_if_t<sst::char_bit_v == 8
                          && sst::is_integer_ish<Src_>::value
                          && sst::is_integer_ish<Len_>::value> = 0,
         class Dst = sst::remove_cvref_t<Dst_>,
         class Src = sst::remove_cvref_t<Src_>,
         class Len = sst::remove_cvref_t<Len_>>
SST_NODISCARD()
Dst i2osp(Src_ const & src, Len_ const & len) {
  SST_ASSERT((!sst::is_negative(src)));
  SST_ASSERT((!sst::is_negative(len)));
  Dst dst;
  sst::checked_resize(dst, len);
  sst::i2osp(src, len, &dst[0]);
  return dst;
}

} // namespace sst

#endif // SST_CATALOG_I2OSP_HPP
