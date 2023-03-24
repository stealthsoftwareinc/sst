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

#ifndef SST_PRIVATE_IS_NEGATIVE_ARITHMETIC_HPP
#define SST_PRIVATE_IS_NEGATIVE_ARITHMETIC_HPP

#include <sst/catalog/SST_CONSTEVAL.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_arithmetic_ish.hpp>
#include <sst/catalog/is_unsigned_integer.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/zero.hpp>
#include <sst/private/is_negative.hpp>

namespace sst {

//----------------------------------------------------------------------

template<class T>
class is_negative_functor<
    sst::enable_if_t<sst::is_unsigned_integer<T>::value>,
    void,
    T> {

public:

  SST_CONSTEVAL bool operator()(sst::remove_cvref_t<T>) const noexcept {
    return false;
  }

}; //

//----------------------------------------------------------------------

#define SST_r (x < sst::zero<T>())

template<class T>
class is_negative_functor<
    sst::enable_if_t<!sst::is_unsigned_integer<T>::value
                     && sst::is_arithmetic_ish<T>::value>,
    void,
    T> {

public:

  constexpr bool operator()(sst::remove_cvref_t<T> const & x) const
      noexcept(noexcept(SST_r)) {
    return SST_r;
  }

}; //

#undef SST_r

//----------------------------------------------------------------------

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <sst/catalog/SST_STATIC_ASSERT.h>

SST_STATIC_ASSERT(!sst::is_negative(false));
SST_STATIC_ASSERT(!sst::is_negative(true));
SST_STATIC_ASSERT(sst::is_negative(-1));
SST_STATIC_ASSERT(!sst::is_negative(0));
SST_STATIC_ASSERT(!sst::is_negative(1));
SST_STATIC_ASSERT(!sst::is_negative(0U));
SST_STATIC_ASSERT(!sst::is_negative(1U));

SST_STATIC_ASSERT(noexcept(sst::is_negative(false)));
SST_STATIC_ASSERT(noexcept(sst::is_negative(0)));
SST_STATIC_ASSERT(noexcept(sst::is_negative(0U)));

#endif // #if SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // #ifndef SST_PRIVATE_IS_NEGATIVE_ARITHMETIC_HPP
