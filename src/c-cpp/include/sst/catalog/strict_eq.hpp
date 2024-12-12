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

#ifndef SST_CATALOG_STRICT_EQ_HPP
#define SST_CATALOG_STRICT_EQ_HPP

#include <type_traits>

#include <sst/catalog/SST_CONSTEVAL.hpp>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {

template<
    class X,
    class Y,
    sst::enable_if_t<std::is_same<sst::remove_cvref_t<X>,
                                  sst::remove_cvref_t<Y>>::value> = 0>
constexpr bool strict_eq(X && x, Y && y)
    SST_NOEXCEPT(noexcept(x == y)) {
  return x == y;
}

template<
    class X,
    class Y,
    sst::enable_if_t<!std::is_same<sst::remove_cvref_t<X>,
                                   sst::remove_cvref_t<Y>>::value> = 0>
SST_CONSTEVAL bool strict_eq(X &&, Y &&) SST_NOEXCEPT(true) {
  return false;
}

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <sst/catalog/SST_STATIC_ASSERT.h>

SST_STATIC_ASSERT((sst::strict_eq(0, 0)));
SST_STATIC_ASSERT((!sst::strict_eq(0, 0L)));
SST_STATIC_ASSERT((!sst::strict_eq(0L, 0)));
SST_STATIC_ASSERT((sst::strict_eq(0L, 0L)));

SST_STATIC_ASSERT((sst::strict_eq(nullptr, nullptr)));
SST_STATIC_ASSERT((!sst::strict_eq(nullptr, 0)));
SST_STATIC_ASSERT((!sst::strict_eq(nullptr, 1)));

#endif // SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // SST_CATALOG_STRICT_EQ_HPP
