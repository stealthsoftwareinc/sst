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

#ifndef SST_PRIVATE_ASCII_LOWER_FROM_CHAR_INPUT_ITERABLE_HPP
#define SST_PRIVATE_ASCII_LOWER_FROM_CHAR_INPUT_ITERABLE_HPP

#include <iterator>
#include <utility>

#include <sst/catalog/ascii_lower.hpp>
#include <sst/catalog/ascii_lower_functor.hpp>
#include <sst/catalog/cbegin.hpp>
#include <sst/catalog/cend.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_byte_input_iterable.hpp>
#include <sst/catalog/is_char_input_iterable.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/value_type_t.hpp>

namespace sst {

//----------------------------------------------------------------------
// src, dst
//----------------------------------------------------------------------

template<class X, class Src, class Dst>
class ascii_lower_functor<
    sst::enable_if_t<
        (sst::is_char_input_iterable<Src>::value
         || sst::is_byte_input_iterable<Src>::value)
        && sst::is_output_iterator<Dst, sst::value_type_t<Src>>::value>,
    X,
    Src,
    Dst> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;

public:

  dst_t operator()(src_t const & src, dst_t dst) const {
    return sst::ascii_lower(sst::cbegin(src),
                            sst::cend(src),
                            std::move(dst));
  }

}; //

//----------------------------------------------------------------------
// src
//----------------------------------------------------------------------

template<class Dst, class Src>
class ascii_lower_functor<
    sst::enable_if_t<(sst::is_char_input_iterable<Src>::value
                      || sst::is_byte_input_iterable<Src>::value)>,
    Dst,
    Src> {

  using src_t = sst::remove_cvref_t<Src>;

public:

  sst::remove_cvref_t<Dst> operator()(src_t const & src) const {
    sst::remove_cvref_t<Dst> dst;
    sst::ascii_lower(src, std::back_inserter(dst));
    return dst;
  }

}; //

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_PRIVATE_ASCII_LOWER_FROM_CHAR_INPUT_ITERABLE_HPP
