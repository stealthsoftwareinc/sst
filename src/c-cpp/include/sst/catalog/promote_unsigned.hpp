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

#ifndef SST_CATALOG_PROMOTE_UNSIGNED_HPP
#define SST_CATALOG_PROMOTE_UNSIGNED_HPP

#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/make_unsigned.hpp>
#include <sst/catalog/promote.hpp>
#include <sst/catalog/promote_t.hpp>

namespace sst {

template<class T, class = sst::enable_t>
struct promote_unsigned : sst::promote<T> {};

template<class T>
struct promote_unsigned<
    T,
    sst::enable_if_t<sst::is_integer<sst::promote_t<T>>::value>>
    : sst::make_unsigned<sst::promote_t<T>> {};

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <type_traits>

#include <sst/catalog/SST_STATIC_ASSERT.h>

#define SST_F3(A, B)                                                   \
  SST_STATIC_ASSERT(                                                   \
      (std::is_same<sst::promote_unsigned<A>::type, B>::value));

#define SST_F2(A, B)                                                   \
  SST_F3(A, B)                                                         \
  SST_F3(A &, B)                                                       \
  SST_F3(A &&, B)

#define SST_F1(A, B)                                                   \
  SST_F2(A, B)                                                         \
  SST_F2(A const, B)                                                   \
  SST_F2(A volatile, B)                                                \
  SST_F2(A const volatile, B)

SST_F1(bool, unsigned int)
SST_F1(char, unsigned int)
SST_F1(signed char, unsigned int)
SST_F1(unsigned char, unsigned int)
SST_F1(short, unsigned int)
SST_F1(unsigned short, unsigned int)
SST_F1(int, unsigned int)
SST_F1(unsigned int, unsigned int)
SST_F1(long, unsigned long)
SST_F1(unsigned long, unsigned long)
SST_F1(long long, unsigned long long)
SST_F1(unsigned long long, unsigned long long)

enum SST_zgebdnghvlzhsipa { SST_zgebdnghvlzhsipa_a };
SST_F1(SST_zgebdnghvlzhsipa,
       sst::promote_unsigned<decltype(+SST_zgebdnghvlzhsipa_a)>::type)

#undef SST_F1
#undef SST_F2
#undef SST_F3

#endif // #if SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // SST_CATALOG_PROMOTE_UNSIGNED_HPP
