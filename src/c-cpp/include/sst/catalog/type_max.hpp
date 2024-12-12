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

#ifndef SST_CATALOG_TYPE_MAX_HPP
#define SST_CATALOG_TYPE_MAX_HPP

#include <limits>

#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/has_numeric_limits.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {

namespace guts {
namespace type_max {

template<class, class = sst::enable_t>
struct helper;

#define SST_A                                                          \
  helper<T,                                                            \
         sst::enable_if_t<std::numeric_limits<T>::is_specialized       \
                          && std::numeric_limits<T>::is_bounded>>

template<class T>
struct SST_A {
  static constexpr T value = std::numeric_limits<T>::max();
};

template<class T>
constexpr T SST_A::value;

#undef SST_A

} // namespace type_max
} // namespace guts

template<class, class = sst::enable_t>
struct type_max;

template<class T>
struct type_max<T,
                sst::enable_if_t<sst::has_numeric_limits<
                    sst::remove_cvref_t<T>>::value>>
    : guts::type_max::helper<sst::remove_cvref_t<T>> {};

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <type_traits>

#include <sst/catalog/SST_COMPILES.hpp>
#include <sst/catalog/SST_STATIC_ASSERT.h>

#define SST_F2(T)                                                      \
  SST_STATIC_ASSERT(                                                   \
      (std::is_same<decltype(sst::type_max<T>::value),                 \
                    sst::remove_cvref_t<T> const>::value));            \
  SST_STATIC_ASSERT(                                                   \
      (sst::type_max<T>::value                                         \
       == std::numeric_limits<sst::remove_cvref_t<T>>::max()));        \
  SST_STATIC_ASSERT((SST_COMPILES(&sst::type_max<T>::value)))

#define SST_F(T)                                                       \
  SST_F2(T);                                                           \
  SST_F2(T const);                                                     \
  SST_F2(T volatile);                                                  \
  SST_F2(T const volatile);                                            \
  SST_F2(T const &);                                                   \
  SST_F2(T volatile &);                                                \
  SST_F2(T const volatile &)

SST_F(bool);
SST_F(char);
SST_F(char16_t);
SST_F(char32_t);
SST_F(double);
SST_F(float);
SST_F(int);
SST_F(long);
SST_F(long double);
SST_F(long long);
SST_F(short);
SST_F(signed char);
SST_F(unsigned char);
SST_F(unsigned int);
SST_F(unsigned long);
SST_F(unsigned long long);
SST_F(unsigned short);
SST_F(wchar_t);

#undef SST_F
#undef SST_F2

#endif

//----------------------------------------------------------------------

#endif // SST_CATALOG_TYPE_MAX_HPP
