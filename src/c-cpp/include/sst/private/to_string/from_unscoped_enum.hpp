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

#ifndef SST_PRIVATE_TO_STRING_FROM_UNSCOPED_ENUM_HPP
#define SST_PRIVATE_TO_STRING_FROM_UNSCOPED_ENUM_HPP

#include <iterator>
#include <type_traits>
#include <utility>

#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/integer_to_string_options.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/is_unscoped_enum.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/private/to_string.hpp>

namespace sst {

//----------------------------------------------------------------------
// src, dst, options
//----------------------------------------------------------------------

template<class X, class Src, class Dst, class Options>
class to_string_functor<
    sst::enable_if_t<
        sst::is_unscoped_enum<Src>::value
        && sst::is_output_iterator<Dst, char>::value
        && std::is_convertible<Options,
                               sst::integer_to_string_options>::value>,
    X,
    Src,
    Dst,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using int_t = typename std::underlying_type<src_t>::type;

public:

  dst_t operator()(
      src_t const src,
      dst_t dst,
      sst::integer_to_string_options const & options = {}) const {
    return sst::to_string(static_cast<int_t>(src),
                          std::move(dst),
                          options);
  }

}; //

//----------------------------------------------------------------------
// src, dst
//----------------------------------------------------------------------

template<class X, class Src, class Dst>
class to_string_functor<
    sst::enable_if_t<sst::is_unscoped_enum<Src>::value
                     && sst::is_output_iterator<Dst, char>::value>,
    X,
    Src,
    Dst> : public to_string_functor<sst::enable_t,
                                    X,
                                    Src,
                                    Dst,
                                    sst::integer_to_string_options> {};

//----------------------------------------------------------------------
// src, options
//----------------------------------------------------------------------

template<class Dst, class Src, class Options>
class to_string_functor<
    sst::enable_if_t<
        sst::is_unscoped_enum<Src>::value
        && std::is_convertible<Options,
                               sst::integer_to_string_options>::value>,
    Dst,
    Src,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;

public:

  sst::remove_cvref_t<Dst> operator()(
      src_t const src,
      sst::integer_to_string_options const & options = {}) const {
    sst::remove_cvref_t<Dst> dst;
    sst::to_string(src, std::back_inserter(dst), options);
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src
//----------------------------------------------------------------------

template<class X, class Src>
class to_string_functor<
    sst::enable_if_t<sst::is_unscoped_enum<Src>::value>,
    X,
    Src> : public to_string_functor<sst::enable_t,
                                    X,
                                    Src,
                                    sst::integer_to_string_options> {};

//----------------------------------------------------------------------

} // namespace sst

#endif // #ifndef SST_PRIVATE_TO_STRING_FROM_UNSCOPED_ENUM_HPP
