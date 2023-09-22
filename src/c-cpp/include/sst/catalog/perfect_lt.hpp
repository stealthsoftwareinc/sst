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

#ifndef SST_CATALOG_PERFECT_LT_HPP
#define SST_CATALOG_PERFECT_LT_HPP

#include <sst/catalog/SST_CONSTEVAL.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/is_unscoped_enum.hpp>
#include <sst/catalog/make_signed_t.hpp>
#include <sst/catalog/promote_t.hpp>
#include <sst/catalog/unsigned_lt.hpp>

namespace sst {

//----------------------------------------------------------------------

#define SST_r                                                          \
  (sst::is_negative(a) ?                                               \
       !sst::is_negative(b)                                            \
           || static_cast<sst::make_signed_t<sst::promote_t<A>>>(a)    \
                  < static_cast<                                       \
                      sst::make_signed_t<sst::promote_t<B>>>(b) :      \
       !sst::is_negative(b) && sst::unsigned_lt(a, b))

template<class A,
         class B,
         sst::enable_if_t<(sst::is_integer<A>::value
                           || sst::is_unscoped_enum<A>::value)
                          && (sst::is_integer<B>::value
                              || sst::is_unscoped_enum<B>::value)> = 0>
SST_CONSTEVAL bool perfect_lt(A const a,
                              B const b) noexcept(noexcept(SST_r)) {
  return SST_r;
}

#undef SST_r

//----------------------------------------------------------------------

#define SST_r                                                          \
  (sst::is_negative(a) ?                                               \
       !sst::is_negative(b) || a < b :                                 \
       !sst::is_negative(b) && sst::unsigned_lt(a, b))

template<class A,
         class B,
         sst::enable_if_t<(!sst::is_integer<A>::value
                           && !sst::is_unscoped_enum<A>::value)
                          || (!sst::is_integer<B>::value
                              && !sst::is_unscoped_enum<B>::value)> = 0>
constexpr bool perfect_lt(A const & a,
                          B const & b) noexcept(noexcept(SST_r)) {
  return SST_r;
}

#undef SST_r

//----------------------------------------------------------------------

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <sst/catalog/SST_STATIC_ASSERT.h>

SST_STATIC_ASSERT((!sst::perfect_lt(0, -1)));
SST_STATIC_ASSERT((!sst::perfect_lt(0, 0)));
SST_STATIC_ASSERT((!sst::perfect_lt(0U, -1)));
SST_STATIC_ASSERT((!sst::perfect_lt(0U, 0)));
SST_STATIC_ASSERT((sst::perfect_lt(-1, 0)));
SST_STATIC_ASSERT((sst::perfect_lt(-1, 0U)));

enum SST_grwvygxkcqvhhscs { SST_grwvygxkcqvhhscs_a = -1 };
SST_STATIC_ASSERT((!sst::perfect_lt(SST_grwvygxkcqvhhscs_a, -1)));
SST_STATIC_ASSERT((sst::perfect_lt(SST_grwvygxkcqvhhscs_a, 0)));
SST_STATIC_ASSERT((sst::perfect_lt(SST_grwvygxkcqvhhscs_a, 0U)));

#endif // #if SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // SST_CATALOG_PERFECT_LT_HPP
