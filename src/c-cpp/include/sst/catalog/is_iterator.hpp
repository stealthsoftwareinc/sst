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

#ifndef SST_CATALOG_IS_ITERATOR_HPP
#define SST_CATALOG_IS_ITERATOR_HPP

#include <type_traits>
#include <utility>

#include <sst/catalog/SST_COMPILES.hpp>
#include <sst/catalog/SST_DEFINE_BOOLEAN_TRAIT_1.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_bool.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {

//
// Some compilers output warnings about ++x when x has type bool, as
// incrementing a bool was deprecated in C++98 and removed in C++17. We
// don't care about that warning here because I = bool will SFINAE fail
// anyway. We silence the warning by doing the is_iterator check in two
// stages: discard bool immediately, then do the actual check we'd like
// to have done in the first place.
//
// We don't use a const reference to check that dereferencing compiles.
// That would be a good idea for input iterators, as they must support
// that, but output iterators need not support that. The compile-time
// tests would catch this (std::ostream_iterator has operator*(), but
// not operator*() const).
//

namespace guts {
namespace is_iterator {

#define SST_I sst::remove_cvref_t<I>
#define SST_i (std::declval<SST_I &>())

SST_DEFINE_BOOLEAN_TRAIT_1(
    helper,
    I,
    (SST_COMPILES(*SST_i)
     && std::is_same<decltype(++SST_i), SST_I &>::value))

#undef SST_i
#undef SST_I

} // namespace is_iterator
} // namespace guts

template<class, class = sst::enable_t>
struct is_iterator : std::false_type {};

template<class I>
struct is_iterator<I, sst::enable_if_t<!sst::is_bool<I>::value>>
    : sst::guts::is_iterator::helper<I> {};

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <iterator>
#include <vector>

#include <sst/catalog/SST_EXPAND.h>
#include <sst/catalog/SST_STATIC_ASSERT.h>

#define SST_F2(I, N, Q)                                                \
  SST_STATIC_ASSERT((N sst::is_iterator<SST_EXPAND I Q>::value));

#define SST_F1(I, N)                                                   \
  SST_F2(I, N, )                                                       \
  SST_F2(I, N, &)                                                      \
  SST_F2(I, N, &&)                                                     \
  SST_F2(I, N, const)                                                  \
  SST_F2(I, N, const &)                                                \
  SST_F2(I, N, const &&)                                               \
  SST_F2(I, N, volatile)                                               \
  SST_F2(I, N, volatile &)                                             \
  SST_F2(I, N, volatile &&)                                            \
  SST_F2(I, N, const volatile)                                         \
  SST_F2(I, N, const volatile &)                                       \
  SST_F2(I, N, const volatile &&)

#define SST_Y(I) SST_F1(I, )

#define SST_N(I) SST_F1(I, !)

SST_Y((int *))
SST_Y((int const *))
SST_Y((std::ostream_iterator<int>))
SST_Y((std::vector<int>::const_iterator))
SST_Y((std::vector<int>::iterator))

SST_N((int))
SST_N((void *))

using SST_xuvmwnoguggfgvmu = int[1];
SST_N((SST_xuvmwnoguggfgvmu))

#undef SST_N
#undef SST_Y
#undef SST_F1
#undef SST_F2

#endif // #if SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // SST_CATALOG_IS_ITERATOR_HPP
