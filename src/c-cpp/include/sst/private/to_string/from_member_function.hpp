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

#ifndef SST_PRIVATE_TO_STRING_FROM_MEMBER_FUNCTION_HPP
#define SST_PRIVATE_TO_STRING_FROM_MEMBER_FUNCTION_HPP

#include <utility>

#include <sst/catalog/SST_COMPILES.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/private/guts/to_string/has_member_function.hpp>
#include <sst/private/to_string.hpp>

namespace sst {

//----------------------------------------------------------------------
// src, args...
//----------------------------------------------------------------------

template<class X, class Src, class... Args>
class to_string_functor<
    sst::enable_if_t<sst::guts::to_string::
                         has_member_function<X, Src, Args...>::value>,
    X,
    Src,
    Args...> {

public:

#define SST_X (src.template to_string<X>(std::forward<Args2>(args)...))

  template<class... Args2>
  auto operator()(Src const & src, Args2 &&... args) const
      noexcept(noexcept(SST_X)) -> decltype(SST_X) {
    return SST_X;
  }

#undef SST_X

}; //

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_PRIVATE_TO_STRING_FROM_MEMBER_FUNCTION_HPP
