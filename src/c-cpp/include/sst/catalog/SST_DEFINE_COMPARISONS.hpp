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

#ifndef SST_CATALOG_SST_DEFINE_COMPARISONS_HPP
#define SST_CATALOG_SST_DEFINE_COMPARISONS_HPP

#include <utility>

#include <sst/catalog/SST_DISPATCH.h>
#include <sst/catalog/SST_NOEXCEPT.hpp>

//
// Friend functions are avoided because T would have incomplete type in
// the noexcept specifier.
//
// std::declval is used instead of "this" in the noexcept specifiers to
// cater to compiler bugs such as
// <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=52869>.
//

#define SST_DEFINE_COMPARISONS_3(T, SPECS, FUNC)                       \
                                                                       \
  SPECS bool operator<(T const & SST_other) const SST_NOEXCEPT(        \
      noexcept(std::declval<T const &>().FUNC(SST_other) < 0)) {       \
    return this->FUNC(SST_other) < 0;                                  \
  }                                                                    \
                                                                       \
  SPECS bool operator>(T const & SST_other) const SST_NOEXCEPT(        \
      noexcept(std::declval<T const &>().FUNC(SST_other) > 0)) {       \
    return this->FUNC(SST_other) > 0;                                  \
  }                                                                    \
                                                                       \
  SPECS bool operator<=(T const & SST_other) const SST_NOEXCEPT(       \
      noexcept(std::declval<T const &>().FUNC(SST_other) <= 0)) {      \
    return this->FUNC(SST_other) <= 0;                                 \
  }                                                                    \
                                                                       \
  SPECS bool operator>=(T const & SST_other) const SST_NOEXCEPT(       \
      noexcept(std::declval<T const &>().FUNC(SST_other) >= 0)) {      \
    return this->FUNC(SST_other) >= 0;                                 \
  }                                                                    \
                                                                       \
  SPECS bool operator==(T const & SST_other) const SST_NOEXCEPT(       \
      noexcept(std::declval<T const &>().FUNC(SST_other) == 0)) {      \
    return this->FUNC(SST_other) == 0;                                 \
  }                                                                    \
                                                                       \
  SPECS bool operator!=(T const & SST_other) const SST_NOEXCEPT(       \
      noexcept(std::declval<T const &>().FUNC(SST_other) != 0)) {      \
    return this->FUNC(SST_other) != 0;                                 \
  }                                                                    \
                                                                       \
  class SST_semicolon

#define SST_DEFINE_COMPARISONS_2(T, SPECS)                             \
  SST_DEFINE_COMPARISONS_3(T, SPECS, compare)

#define SST_DEFINE_COMPARISONS_1(T) SST_DEFINE_COMPARISONS_2(T, )

#define SST_DEFINE_COMPARISONS(...)                                    \
  SST_DISPATCH(SST_DEFINE_COMPARISONS_, __VA_ARGS__)(__VA_ARGS__)

#endif // SST_CATALOG_SST_DEFINE_COMPARISONS_HPP
