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

#ifndef SST_PRIVATE_JSON_QUOTE_ITERABLE_QAPSUP3D_HPP
#define SST_PRIVATE_JSON_QUOTE_ITERABLE_QAPSUP3D_HPP

#include <iterator>
#include <utility>

#include <sst/catalog/cbegin.hpp>
#include <sst/catalog/cend.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_iterable.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/json/quote_options.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/private/json/quote.hpp>
#include <sst/private/json/quote/iterator-qa94410w.hpp>

namespace sst {
namespace json {

//----------------------------------------------------------------------
// src, dst, options
//----------------------------------------------------------------------

template<class Unused, class Src, class Dst, class Options>
class quote_functor<
    sst::enable_if_t<sst::is_iterable<Src, sst::is_integer_ish>::value
                     && sst::is_output_iterator<Dst, char>::value
                     && !sst::is_output_iterator<Options, char>::value>,
    Unused,
    Src,
    Dst,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using options_t = sst::remove_cvref_t<Options>;

public:

  dst_t operator()(src_t const & src,
                   dst_t dst,
                   options_t const & options) const {
    return sst::json::quote(sst::cbegin(src),
                            sst::cend(src),
                            std::move(dst),
                            options);
  }

}; //

//----------------------------------------------------------------------
// src, dst
//----------------------------------------------------------------------

template<class Unused, class Src, class Dst>
class quote_functor<
    sst::enable_if_t<sst::is_iterable<Src, sst::is_integer_ish>::value
                     && sst::is_output_iterator<Dst, char>::value>,
    Unused,
    Src,
    Dst> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;

public:

  dst_t operator()(src_t const & src, dst_t dst) const {
    return sst::json::quote(sst::cbegin(src),
                            sst::cend(src),
                            std::move(dst),
                            sst::json::quote_options());
  }

}; //

//----------------------------------------------------------------------
// src, options
//----------------------------------------------------------------------

template<class Dst, class Src, class Options>
class quote_functor<
    sst::enable_if_t<sst::is_iterable<Src, sst::is_integer_ish>::value
                     && !sst::is_output_iterator<Options, char>::value>,
    Dst,
    Src,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using options_t = sst::remove_cvref_t<Options>;

public:

  dst_t operator()(src_t const & src, options_t const & options) const {
    dst_t dst;
    sst::json::quote(src, std::back_inserter(dst), options);
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src
//----------------------------------------------------------------------

template<class Dst, class Src>
class quote_functor<
    sst::enable_if_t<sst::is_iterable<Src, sst::is_integer_ish>::value>,
    Dst,
    Src> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;

public:

  dst_t operator()(src_t const & src) const {
    dst_t dst;
    sst::json::quote(src,
                     std::back_inserter(dst),
                     sst::json::quote_options());
    return dst;
  }

}; //

//----------------------------------------------------------------------

} // namespace json
} // namespace sst

#endif // SST_PRIVATE_JSON_QUOTE_ITERABLE_QAPSUP3D_HPP
