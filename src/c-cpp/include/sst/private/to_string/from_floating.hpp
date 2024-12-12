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

#ifndef SST_PRIVATE_TO_STRING_FROM_FLOATING_HPP
#define SST_PRIVATE_TO_STRING_FROM_FLOATING_HPP

#include <iterator>
#include <locale>
#include <sstream>
#include <string>

#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_floating.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/private/guts/to_string/has_member_function.hpp>
#include <sst/private/to_string.hpp>

namespace sst {

//----------------------------------------------------------------------
// src, dst
//----------------------------------------------------------------------

template<class X, class Src, class Dst>
class to_string_functor<
    sst::enable_if_t<
        !sst::guts::to_string::has_member_function<X, Src, Dst>::value
        && sst::is_floating<Src>::value
        && sst::is_output_iterator<Dst, char>::value>,
    X,
    Src,
    Dst> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;

public:

  dst_t operator()(src_t const src, dst_t dst) const {
    std::ostringstream a;
    a.imbue(std::locale::classic());
    a << src;
    std::string const b = a.str();
    for (char const c : b) {
      *dst = c;
      ++dst;
    }
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src
//----------------------------------------------------------------------

template<class Dst, class Src>
class to_string_functor<
    sst::enable_if_t<
        !sst::guts::to_string::has_member_function<Dst, Src>::value
        && sst::is_floating<Src>::value>,
    Dst,
    Src> {

  using src_t = sst::remove_cvref_t<Src>;

public:

  sst::remove_cvref_t<Dst> operator()(src_t const src) const {
    sst::remove_cvref_t<Dst> dst;
    sst::to_string(src, std::back_inserter(dst));
    return dst;
  }

}; //

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_PRIVATE_TO_STRING_FROM_FLOATING_HPP
