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

#ifndef SST_CATALOG_MAKE_UNIQUE_HPP
#define SST_CATALOG_MAKE_UNIQUE_HPP

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/dependent_false.hpp>
#include <sst/catalog/enable_if_t.hpp>

namespace sst {

//----------------------------------------------------------------------

template<class T,
         class... Args,
         sst::enable_if_t<!std::is_array<T>::value> = 0>
std::unique_ptr<T> make_unique(Args &&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

//----------------------------------------------------------------------

template<class T,
         sst::enable_if_t<std::is_array<T>::value
                          && std::extent<T>::value == 0> = 0>
std::unique_ptr<T> make_unique(std::size_t const n) {
  using E = typename std::remove_extent<T>::type;
  return std::unique_ptr<T>(new E[n]());
}

//----------------------------------------------------------------------

template<class T,
         class... Args,
         sst::enable_if_t<std::is_array<T>::value
                          && std::extent<T>::value != 0> = 0>
std::unique_ptr<T> make_unique(Args &&...) {
  // clang-format off
  SST_STATIC_ASSERT("sst::make_unique is not defined for arrays of known bound." && (sst::dependent_false<T>::value));
  // clang-format on
  return std::unique_ptr<T>();
}

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_CATALOG_MAKE_UNIQUE_HPP
