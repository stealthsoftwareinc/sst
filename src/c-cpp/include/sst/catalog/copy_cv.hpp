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

#ifndef SST_CATALOG_COPY_CV_HPP
#define SST_CATALOG_COPY_CV_HPP

#include <type_traits>

#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/remove_cv_t.hpp>
#include <sst/catalog/type_identity.hpp>

namespace sst {

template<class, class, class = sst::enable_t>
struct copy_cv;

#define SST_F(C, V, Q)                                                 \
  template<class Src, class Dst>                                       \
  struct copy_cv<Src,                                                  \
                 Dst,                                                  \
                 sst::enable_if_t<C(std::is_const<Src>::value)         \
                                  && V(std::is_volatile<Src>::value)>> \
      : sst::type_identity<sst::remove_cv_t<Dst> Q> {}

SST_F(!, !, );
SST_F(+, !, const);
SST_F(!, +, volatile);
SST_F(+, +, const volatile);

#undef SST_F

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <sst/catalog/SST_STATIC_ASSERT.h>

#define SST_F3(A, B, R)                                                \
  SST_STATIC_ASSERT((std::is_same<sst::copy_cv<A, B>::type, R>::value))

#define SST_F2(A, B, R)                                                \
  SST_F3(A, B, R);                                                     \
  SST_F3(A, B const, R);                                               \
  SST_F3(A, B volatile, R);                                            \
  SST_F3(A, B const volatile, R)

#define SST_F1(A, B)                                                   \
  SST_F2(A, B, B);                                                     \
  SST_F2(A const, B, B const);                                         \
  SST_F2(A volatile, B, B volatile);                                   \
  SST_F2(A const volatile, B, B const volatile);                       \
  SST_F2(A &, B, B);                                                   \
  SST_F2(A const &, B, B);                                             \
  SST_F2(A volatile &, B, B);                                          \
  SST_F2(A const volatile &, B, B);                                    \
  SST_F2(A &&, B, B);                                                  \
  SST_F2(A const &&, B, B);                                            \
  SST_F2(A volatile &&, B, B);                                         \
  SST_F2(A const volatile &&, B, B);                                   \
  SST_F3(A, B &, B &);                                                 \
  SST_F3(A const, B &, B &);                                           \
  SST_F3(A volatile, B &, B &);                                        \
  SST_F3(A const volatile, B &, B &);                                  \
  SST_F3(A, B &&, B &&);                                               \
  SST_F3(A const, B &&, B &&);                                         \
  SST_F3(A volatile, B &&, B &&);                                      \
  SST_F3(A const volatile, B &&, B &&)

SST_F1(int, long);

#undef SST_F1
#undef SST_F2
#undef SST_F3

#endif // #if SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // SST_CATALOG_COPY_CV_HPP
