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

#ifndef SST_CATALOG_FORWARD_HPP
#define SST_CATALOG_FORWARD_HPP

#include <type_traits>

#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/remove_reference_t.hpp>

namespace sst {

//
// The sst::forward function is provided because std::forward is not
// constexpr in C++11.
//

template<class T>
constexpr T && forward(sst::remove_reference_t<T> & t) noexcept {
  return static_cast<T &&>(t);
}

template<class T>
constexpr T && forward(sst::remove_reference_t<T> && t) noexcept {
  // clang-format off
  SST_STATIC_ASSERT("T must not be an lvalue reference type. See C++11 (N3337) 20.2.3p3, C++14 (N4140) 20.2.4p3, C++17 (N4659) 23.2.5p3, C++20 (N4860) 20.2.4p2, and N2951." && (!std::is_lvalue_reference<T>::value));
  // clang-format on
  return static_cast<T &&>(t);
}

} // namespace sst

#endif // SST_CATALOG_FORWARD_HPP
