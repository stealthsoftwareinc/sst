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

#ifndef SST_PRIVATE_TO_INTEGER_FROM_CHAR_INPUT_ITERABLE_HPP
#define SST_PRIVATE_TO_INTEGER_FROM_CHAR_INPUT_ITERABLE_HPP

#include <sst/catalog/cbegin.hpp>
#include <sst/catalog/cend.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_char.hpp>
#include <sst/catalog/is_iterable.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/string_to_integer_options.hpp>
#include <sst/private/to_integer.hpp>
#include <sst/private/to_integer/from_char_input_iterable.hpp>

namespace sst {

//----------------------------------------------------------------------
// src, options
//----------------------------------------------------------------------

template<class Dst, class Src, class Options>
class to_integer_functor<
    sst::enable_if_t<sst::is_iterable<Src, sst::is_char>::value>,
    Dst,
    Src,
    Options> {

  using dst_t = sst::remove_cvref_t<Dst>;
  using src_t = sst::remove_cvref_t<Src>;
  using options_t = sst::remove_cvref_t<Options>;

public:

  dst_t operator()(src_t const & src, options_t const & options) const {
    return sst::to_integer<dst_t>(sst::cbegin(src),
                                  sst::cend(src),
                                  options);
  }

}; //

//----------------------------------------------------------------------
// src
//----------------------------------------------------------------------

template<class Dst, class Src>
class to_integer_functor<
    sst::enable_if_t<sst::is_iterable<Src, sst::is_char>::value>,
    Dst,
    Src> {

  using dst_t = sst::remove_cvref_t<Dst>;
  using src_t = sst::remove_cvref_t<Src>;

public:

  dst_t operator()(src_t const & src) const {
    return sst::to_integer<dst_t>(sst::cbegin(src),
                                  sst::cend(src),
                                  sst::string_to_integer_options());
  }

}; //

//----------------------------------------------------------------------

} // namespace sst

#endif // #ifndef SST_PRIVATE_TO_INTEGER_FROM_CHAR_INPUT_ITERABLE_HPP
