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

#ifndef SST_CATALOG_TO_UNSIGNED_HPP
#define SST_CATALOG_TO_UNSIGNED_HPP

#include <utility>

#include <sst/catalog/SST_NODISCARD.hpp>
#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_floating_ish.hpp>
#include <sst/catalog/is_floating_like.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_integer_like.hpp>
#include <sst/catalog/is_unscoped_enum.hpp>
#include <sst/catalog/make_unsigned_t.hpp>
#include <sst/catalog/numeric_limits.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {

//----------------------------------------------------------------------

#define SST_r (static_cast<sst::make_unsigned_t<decltype(+x)>>(+x))

template<class T,
         sst::enable_if_t<sst::is_integer<T>::value
                          || sst::is_unscoped_enum<T>::value> = 0>
SST_NODISCARD()
constexpr auto to_unsigned(T const x) noexcept -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

//----------------------------------------------------------------------

template<class T,
         sst::enable_if_t<(sst::is_integer_like<T>::value
                           && !sst::is_integer<T>::value)
                          || sst::is_floating_like<T>::value> = 0>
SST_NODISCARD()
constexpr sst::remove_cvref_t<T> to_unsigned(T const x) noexcept {
  SST_STATIC_ASSERT((!sst::is_integer_ish<T>::value
                     || !sst::numeric_limits<T>::is_signed),
                    "Non-fundamental signed integer-ish types are "
                    "unsupported because there is no convention for "
                    "mapping them to a corresponding unsigned type");
  SST_STATIC_ASSERT((!sst::is_floating_ish<T>::value
                     || sst::numeric_limits<T>::is_signed),
                    "Unsigned floating-ish types are unsupported "
                    "because they are too unconventional");
  return x;
}

//----------------------------------------------------------------------

template<class T,
         sst::enable_if_t<(sst::is_integer_ish<T>::value
                           && !sst::is_integer_like<T>::value)
                          || (sst::is_floating_ish<T>::value
                              && !sst::is_floating_like<T>::value)> = 0>
SST_NODISCARD()
constexpr T && to_unsigned(T && x) noexcept {
  SST_STATIC_ASSERT((!sst::is_integer_ish<T>::value
                     || !sst::numeric_limits<T>::is_signed),
                    "Non-fundamental signed integer-ish types are "
                    "unsupported because there is no convention for "
                    "mapping them to a corresponding unsigned type");
  SST_STATIC_ASSERT((!sst::is_floating_ish<T>::value
                     || sst::numeric_limits<T>::is_signed),
                    "Unsigned floating-ish types are unsupported "
                    "because they are too unconventional");
  return std::forward<T>(x);
}

//----------------------------------------------------------------------

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <type_traits>

#include <sst/catalog/SST_EXPAND.h>

#define SST_F(A, B)                                                    \
  SST_STATIC_ASSERT((std::is_same<decltype(sst::to_unsigned(A)),       \
                                  SST_EXPAND B>::value));

enum { SST_pfbwxbmozvfyepgx };

SST_F((static_cast<signed char>(0)), (unsigned int))
SST_F((static_cast<short>(0)), (unsigned int))
SST_F((0), (unsigned int))
SST_F((0U), (unsigned int))
SST_F((0L), (unsigned long))
SST_F((0UL), (unsigned long))
SST_F((0LL), (unsigned long long))
SST_F((0ULL), (unsigned long long))
SST_F((0.0F), (float))
SST_F((0.0), (double))
SST_F((0.0L), (long double))
SST_F((SST_pfbwxbmozvfyepgx), (unsigned int))

#undef SST_F

#endif // #if SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // SST_CATALOG_TO_UNSIGNED_HPP
