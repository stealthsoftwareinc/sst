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

#ifndef SST_CATALOG_IS_INTEGER_LIKE_HPP
#define SST_CATALOG_IS_INTEGER_LIKE_HPP

#include <limits>

#include <sst/catalog/SST_DEFINE_BOOLEAN_TRAIT_1.hpp>
#include <sst/catalog/SST_DEFINE_FORWARD_TRAIT_1.hpp>
#include <sst/catalog/has_numeric_limits.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {

namespace guts {
namespace is_integer_like {

SST_DEFINE_BOOLEAN_TRAIT_1(helper,
                           T,
                           (std::numeric_limits<T>::is_specialized
                            && std::numeric_limits<T>::is_integer
                            && std::numeric_limits<T>::is_bounded))

} // namespace is_integer_like
} // namespace guts

SST_DEFINE_FORWARD_TRAIT_1(
    is_integer_like,
    T,
    (sst::has_numeric_limits<sst::remove_cvref_t<T>>::value),
    guts::is_integer_like::helper<sst::remove_cvref_t<T>>)

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <sst/catalog/SST_STATIC_ASSERT.h>

#define SST_Y(...)                                                     \
  SST_STATIC_ASSERT((sst::is_integer_like<__VA_ARGS__>::value))

#define SST_N(...)                                                     \
  SST_STATIC_ASSERT((!sst::is_integer_like<__VA_ARGS__>::value))

SST_Y(bool);
SST_Y(char);
SST_Y(char16_t);
SST_Y(char32_t);
SST_Y(int);
SST_Y(long long);
SST_Y(long);
SST_Y(short);
SST_Y(signed char);
SST_Y(unsigned char);
SST_Y(unsigned int);
SST_Y(unsigned long long);
SST_Y(unsigned long);
SST_Y(unsigned short);
SST_Y(wchar_t);

SST_N(decltype(nullptr));
SST_N(double);
SST_N(float);
SST_N(int(int));
SST_N(int[1]);

#undef SST_Y
#undef SST_N

#endif // #if SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // SST_CATALOG_IS_INTEGER_LIKE_HPP
