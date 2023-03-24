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

#ifndef SST_PRIVATE_FROM_HEX_FROM_CHAR_INPUT_ITERABLE_HPP
#define SST_PRIVATE_FROM_HEX_FROM_CHAR_INPUT_ITERABLE_HPP

#include <iterator>
#include <type_traits>
#include <utility>

#include <sst/catalog/cbegin.hpp>
#include <sst/catalog/cend.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/from_hex.hpp>
#include <sst/catalog/from_hex_functor.hpp>
#include <sst/catalog/from_hex_options.hpp>
#include <sst/catalog/is_char_input_iterable.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {

//----------------------------------------------------------------------
// src, dst, options
//----------------------------------------------------------------------

template<class X, class Src, class Dst, class Options>
class from_hex_functor<
    sst::enable_if_t<
        sst::is_char_input_iterable<Src>::value
        && sst::is_output_iterator<Dst, char>::value
        && std::is_convertible<Options, sst::from_hex_options>::value>,
    X,
    Src,
    Dst,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;

public:

  dst_t operator()(src_t const & src,
                   dst_t dst,
                   sst::from_hex_options const & options = {}) const {
    return sst::from_hex(sst::cbegin(src),
                         sst::cend(src),
                         std::move(dst),
                         options);
  }

}; //

//----------------------------------------------------------------------
// src, dst
//----------------------------------------------------------------------

template<class X, class Src, class Dst>
class from_hex_functor<
    sst::enable_if_t<sst::is_char_input_iterable<Src>::value
                     && sst::is_output_iterator<Dst, char>::value>,
    X,
    Src,
    Dst> : public from_hex_functor<sst::enable_t,
                                   X,
                                   Src,
                                   Dst,
                                   sst::from_hex_options> {};

//----------------------------------------------------------------------
// src, options
//----------------------------------------------------------------------

template<class Dst, class Src, class Options>
class from_hex_functor<
    sst::enable_if_t<
        sst::is_char_input_iterable<Src>::value
        && std::is_convertible<Options, sst::from_hex_options>::value>,
    Dst,
    Src,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;

public:

  sst::remove_cvref_t<Dst>
  operator()(src_t const & src,
             sst::from_hex_options const & options = {}) const {
    sst::remove_cvref_t<Dst> dst;
    sst::from_hex(src, std::back_inserter(dst), options);
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src
//----------------------------------------------------------------------

template<class X, class Src>
class from_hex_functor<
    sst::enable_if_t<sst::is_char_input_iterable<Src>::value>,
    X,
    Src> : public from_hex_functor<sst::enable_t,
                                   X,
                                   Src,
                                   sst::from_hex_options> {};

//----------------------------------------------------------------------

} // namespace sst

#endif // #ifndef SST_PRIVATE_FROM_HEX_FROM_CHAR_INPUT_ITERABLE_HPP
