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

#ifndef SST_CATALOG_COPY_CVREF_HPP
#define SST_CATALOG_COPY_CVREF_HPP

#include <sst/catalog/copy_cv_t.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/type_identity.hpp>

namespace sst {

template<class A, class B>
struct copy_cvref
    : sst::type_identity<sst::copy_cv_t<A, sst::remove_cvref_t<B>>> {};

template<class A, class B>
struct copy_cvref<A &, B>
    : sst::type_identity<typename sst::copy_cvref<A, B>::type &> {};

template<class A, class B>
struct copy_cvref<A &&, B>
    : sst::type_identity<typename sst::copy_cvref<A, B>::type &&> {};

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <type_traits>

#include <sst/catalog/SST_STATIC_ASSERT.h>

#define SST_F3(A, B, R)                                                \
  SST_STATIC_ASSERT(                                                   \
      (std::is_same<sst::copy_cvref<A, B>::type, R>::value));

#define SST_F2(A, B, R)                                                \
  SST_F3(A, B, R)                                                      \
  SST_F3(A, B const, R)                                                \
  SST_F3(A, B volatile, R)                                             \
  SST_F3(A, B const volatile, R)                                       \
  SST_F3(A, B &, R)                                                    \
  SST_F3(A, B const &, R)                                              \
  SST_F3(A, B volatile &, R)                                           \
  SST_F3(A, B const volatile &, R)                                     \
  SST_F3(A, B &&, R)                                                   \
  SST_F3(A, B const &&, R)                                             \
  SST_F3(A, B volatile &&, R)                                          \
  SST_F3(A, B const volatile &&, R)

#define SST_F1(A, B)                                                   \
  SST_F2(A, B, B)                                                      \
  SST_F2(A const, B, B const)                                          \
  SST_F2(A volatile, B, B volatile)                                    \
  SST_F2(A const volatile, B, B const volatile)                        \
  SST_F2(A &, B, B &)                                                  \
  SST_F2(A const &, B, B const &)                                      \
  SST_F2(A volatile &, B, B volatile &)                                \
  SST_F2(A const volatile &, B, B const volatile &)                    \
  SST_F2(A &&, B, B &&)                                                \
  SST_F2(A const &&, B, B const &&)                                    \
  SST_F2(A volatile &&, B, B volatile &&)                              \
  SST_F2(A const volatile &&, B, B const volatile &&)

SST_F1(int, long)

#undef SST_F1
#undef SST_F2
#undef SST_F3

#endif // #if SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // SST_CATALOG_COPY_CVREF_HPP
