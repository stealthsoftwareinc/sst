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

#ifndef SST_PRIVATE_ASCII_UPPER_FROM_CHAR_INPUT_ITERATOR_HPP
#define SST_PRIVATE_ASCII_UPPER_FROM_CHAR_INPUT_ITERATOR_HPP

#include <iterator>
#include <utility>

#include <sst/catalog/ascii_upper.hpp>
#include <sst/catalog/ascii_upper_functor.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_byte_input_iterator.hpp>
#include <sst/catalog/is_char_input_iterator.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/catalog/is_value_sentinel.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/value_type_t.hpp>

namespace sst {

//----------------------------------------------------------------------
// src, end, dst
//----------------------------------------------------------------------

template<class X, class Src, class End, class Dst>
class ascii_upper_functor<
    sst::enable_if_t<
        (sst::is_char_input_iterator<Src>::value
         || sst::is_byte_input_iterator<Src>::value)
        && sst::is_sentinel<End, Src>::value
        && sst::is_output_iterator<
            Dst,
            sst::value_type_t<sst::remove_cvref_t<Src>>>::value>,
    X,
    Src,
    End,
    Dst> {

  using src_t = sst::remove_cvref_t<Src>;
  using end_t = sst::remove_cvref_t<End>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using src_value_t = sst::value_type_t<src_t>;

public:

  dst_t operator()(src_t src, end_t const end, dst_t dst) const {
    for (; !(src == end); ++src) {
      src_value_t const x = *src;
      if (x == 0) {
        break;
      }
      *dst = sst::ascii_upper(x);
      ++dst;
    }
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, sen, dst
//----------------------------------------------------------------------

template<class X, class Src, class Sen, class Dst>
class ascii_upper_functor<
    sst::enable_if_t<
        (sst::is_char_input_iterator<Src>::value
         || sst::is_byte_input_iterator<Src>::value)
        && sst::is_value_sentinel<Sen, Src>::value
        && sst::is_output_iterator<
            Dst,
            sst::value_type_t<sst::remove_cvref_t<Src>>>::value>,
    X,
    Src,
    Sen,
    Dst> {

  using src_t = sst::remove_cvref_t<Src>;
  using sen_t = sst::remove_cvref_t<Sen>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using src_value_t = sst::value_type_t<src_t>;

public:

  dst_t operator()(src_t src, sen_t const & sen, dst_t dst) const {
    for (;; ++src) {
      src_value_t const x = *src;
      if (x == sen) {
        break;
      }
      *dst = sst::ascii_upper(x);
      ++dst;
    }
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, end
//----------------------------------------------------------------------

template<class Dst, class Src, class End>
class ascii_upper_functor<
    sst::enable_if_t<(sst::is_char_input_iterator<Src>::value
                      || sst::is_byte_input_iterator<Src>::value)
                     && sst::is_sentinel<End, Src>::value>,
    Dst,
    Src,
    End> {

  using src_t = sst::remove_cvref_t<Src>;
  using end_t = sst::remove_cvref_t<End>;

public:

  sst::remove_cvref_t<Dst> operator()(src_t src, end_t end) const {
    sst::remove_cvref_t<Dst> dst;
    sst::ascii_upper(std::move(src),
                     std::move(end),
                     std::back_inserter(dst));
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, sen
//----------------------------------------------------------------------

template<class Dst, class Src, class Sen>
class ascii_upper_functor<
    sst::enable_if_t<(sst::is_char_input_iterator<Src>::value
                      || sst::is_byte_input_iterator<Src>::value)
                     && sst::is_value_sentinel<Sen, Src>::value>,
    Dst,
    Src,
    Sen> {

  using src_t = sst::remove_cvref_t<Src>;
  using sen_t = sst::remove_cvref_t<Sen>;

public:

  sst::remove_cvref_t<Dst> operator()(src_t src,
                                      sen_t const & sen = {}) const {
    sst::remove_cvref_t<Dst> dst;
    sst::ascii_upper(std::move(src), sen, std::back_inserter(dst));
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src
//----------------------------------------------------------------------

template<class Dst, class Src>
class ascii_upper_functor<
    sst::enable_if_t<(sst::is_char_input_iterator<Src>::value
                      || sst::is_byte_input_iterator<Src>::value)>,
    Dst,
    Src> : public ascii_upper_functor<sst::enable_t,
                                      Dst,
                                      Src,
                                      sst::value_type_t<Src>> {};

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_PRIVATE_ASCII_UPPER_FROM_CHAR_INPUT_ITERATOR_HPP
