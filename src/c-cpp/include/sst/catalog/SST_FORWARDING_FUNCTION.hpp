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

#ifndef SST_CATALOG_SST_FORWARDING_FUNCTION_HPP
#define SST_CATALOG_SST_FORWARDING_FUNCTION_HPP

#include <utility>

#include <sst/catalog/SST_COMPILES.hpp>
#include <sst/catalog/enable_if_t.hpp>

#define SST_FORWARDING_FUNCTION(f, g)                                  \
  template<class... SST_Args,                                          \
           ::sst::enable_if_t<SST_COMPILES(                            \
               g(::std::declval<SST_Args &&>()...))> = 0>              \
  auto f(SST_Args &&... SST_args) noexcept(                            \
      noexcept(g(::std::forward<SST_Args>(SST_args)...)))              \
      ->decltype(g(::std::forward<SST_Args>(SST_args)...)) {           \
    return g(::std::forward<SST_Args>(SST_args)...);                   \
  }

#endif // SST_CATALOG_SST_FORWARDING_FUNCTION_HPP
