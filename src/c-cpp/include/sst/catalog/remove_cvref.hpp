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

#ifndef SST_CATALOG_REMOVE_CVREF_HPP
#define SST_CATALOG_REMOVE_CVREF_HPP

#include <type_traits>

#include <sst/catalog/type_identity.hpp>

namespace sst {

namespace guts {
namespace remove_cvref {

template<class T>
struct x {
  using R1 = T;
  using R2 = typename std::remove_reference<R1>::type;
  using R3 = typename std::remove_cv<R2>::type;
  using type = R3;
};

template<class T>
using x_t = typename x<T>::type;

} // namespace remove_cvref
} // namespace guts

template<class T>
struct remove_cvref
    : sst::type_identity<sst::guts::remove_cvref::x_t<T>> {};

} // namespace sst

#endif // SST_CATALOG_REMOVE_CVREF_HPP
