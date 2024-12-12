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

#ifndef SST_PRIVATE_TO_HEX_FROM_BYTE_HPP
#define SST_PRIVATE_TO_HEX_FROM_BYTE_HPP

#include <iterator>
#include <type_traits>
#include <utility>

#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_byte.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/to_hex.hpp>
#include <sst/catalog/to_hex_functor.hpp>
#include <sst/catalog/to_hex_options.hpp>

namespace sst {

//----------------------------------------------------------------------
// src, dst, options
//----------------------------------------------------------------------

template<class X, class Src, class Dst, class Options>
class to_hex_functor<
    sst::enable_if_t<
        sst::is_byte<Src>::value
        && sst::is_output_iterator<Dst, char>::value
        && std::is_convertible<Options, sst::to_hex_options>::value>,
    X,
    Src,
    Dst,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;

public:

  dst_t operator()(src_t const src,
                   dst_t dst,
                   sst::to_hex_options options = {}) const {
    options.allow_zero(true);
    return sst::to_hex(&src, &src + 1, std::move(dst), options);
  }

}; //

//----------------------------------------------------------------------
// src, dst
//----------------------------------------------------------------------

template<class X, class Src, class Dst>
class to_hex_functor<
    sst::enable_if_t<sst::is_byte<Src>::value
                     && sst::is_output_iterator<Dst, char>::value>,
    X,
    Src,
    Dst> : public to_hex_functor<sst::enable_t,
                                 X,
                                 Src,
                                 Dst,
                                 sst::to_hex_options> {};

//----------------------------------------------------------------------
// src, options
//----------------------------------------------------------------------

template<class Dst, class Src, class Options>
class to_hex_functor<
    sst::enable_if_t<
        sst::is_byte<Src>::value
        && std::is_convertible<Options, sst::to_hex_options>::value>,
    Dst,
    Src,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;

public:

  sst::remove_cvref_t<Dst>
  operator()(src_t const src,
             sst::to_hex_options const & options = {}) const {
    sst::remove_cvref_t<Dst> dst;
    sst::to_hex(src, std::back_inserter(dst), options);
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src
//----------------------------------------------------------------------

template<class X, class Src>
class to_hex_functor<sst::enable_if_t<sst::is_byte<Src>::value>, X, Src>
    : public to_hex_functor<sst::enable_t,
                            X,
                            Src,
                            sst::to_hex_options> {};

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_PRIVATE_TO_HEX_FROM_BYTE_HPP
