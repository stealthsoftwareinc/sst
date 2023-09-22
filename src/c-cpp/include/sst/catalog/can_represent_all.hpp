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

#ifndef SST_CATALOG_CAN_REPRESENT_ALL_HPP
#define SST_CATALOG_CAN_REPRESENT_ALL_HPP

#include <limits>
#include <type_traits>

#include <sst/catalog/bool_constant.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/perfect_ge.hpp>
#include <sst/catalog/perfect_le.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/type_min.hpp>
#include <sst/private/checked_class/decl.hpp>

namespace sst {

namespace guts {
namespace can_represent_all {

template<class, class, class = sst::enable_t>
struct integer_ish_integer_ish : std::false_type {};

template<class A, class B>
struct integer_ish_integer_ish<
    A,
    B,
    sst::enable_if_t<(std::numeric_limits<A>::is_signed
                      || !std::numeric_limits<B>::is_signed)
                     && std::numeric_limits<A>::is_bounded
                     && std::numeric_limits<B>::is_bounded>>
    : sst::bool_constant<sst::perfect_le(sst::type_min<A>::value,
                                         sst::type_min<B>::value)
                         && sst::perfect_ge(sst::type_max<A>::value,
                                            sst::type_max<B>::value)> {
};

template<class A, class B>
struct integer_ish_integer_ish<
    A,
    B,
    sst::enable_if_t<(std::numeric_limits<A>::is_signed
                      || !std::numeric_limits<B>::is_signed)
                     && !std::numeric_limits<A>::is_bounded>>
    : std::true_type {};

} // namespace can_represent_all
} // namespace guts

template<class, class, class = sst::enable_t>
struct can_represent_all : std::false_type {};

template<class A, class B>
struct can_represent_all<
    A,
    B,
    sst::enable_if_t<sst::is_integer_ish<A>::value
                     && sst::is_integer_ish<B>::value>>
    : guts::can_represent_all::integer_ish_integer_ish<
          sst::remove_cvref_t<A>,
          sst::remove_cvref_t<B>> {};

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <sst/catalog/SST_STATIC_ASSERT.h>

#define SST_Y(A, B)                                                    \
  SST_STATIC_ASSERT((sst::can_represent_all<A, B>::value))

#define SST_N(A, B)                                                    \
  SST_STATIC_ASSERT((!sst::can_represent_all<A, B>::value))

SST_Y(bool, bool);
SST_N(bool, char);
SST_N(bool, char16_t);
SST_N(bool, char32_t);
SST_N(bool, int);
SST_N(bool, long);
SST_N(bool, long long);
SST_N(bool, short);
SST_N(bool, signed char);
SST_N(bool, unsigned char);
SST_N(bool, unsigned int);
SST_N(bool, unsigned long);
SST_N(bool, unsigned long long);
SST_N(bool, unsigned short);
SST_N(bool, wchar_t);

SST_Y(int, bool);
SST_Y(int, int);
SST_Y(int, short);
SST_Y(int, signed char);

SST_Y(unsigned int, bool);
SST_Y(unsigned int, char16_t);
SST_Y(unsigned int, unsigned char);
SST_Y(unsigned int, unsigned int);
SST_Y(unsigned int, unsigned short);

SST_Y(unsigned long, bool);
SST_Y(unsigned long, char16_t);
SST_Y(unsigned long, char32_t);
SST_Y(unsigned long, unsigned char);
SST_Y(unsigned long, unsigned int);
SST_Y(unsigned long, unsigned long);
SST_Y(unsigned long, unsigned short);

#undef SST_Y
#undef SST_N

#endif

//----------------------------------------------------------------------

#endif // SST_CATALOG_CAN_REPRESENT_ALL_HPP
