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

#ifndef SST_PRIVATE_IS_NEGATIVE_ENUM_HPP
#define SST_PRIVATE_IS_NEGATIVE_ENUM_HPP

#include <sst/catalog/SST_CONSTEVAL.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_unscoped_enum.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/underlying_type_t.hpp>
#include <sst/private/is_negative.hpp>
#include <sst/private/is_negative/arithmetic.hpp>

namespace sst {

//----------------------------------------------------------------------

template<class A>
class is_negative_functor<
    sst::enable_if_t<sst::is_unscoped_enum<A>::value>,
    void,
    A> {

public:

  SST_CONSTEVAL bool
  operator()(sst::remove_cvref_t<A> const a) const noexcept {
    return sst::is_negative(static_cast<sst::underlying_type_t<A>>(a));
  }

}; //

//----------------------------------------------------------------------

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <sst/catalog/SST_STATIC_ASSERT.h>

enum SST_W34Y4Q3LH4NQ6465 {
  SST_W34Y4Q3LH4NQ6465_A = -1,
  SST_W34Y4Q3LH4NQ6465_B
};
SST_STATIC_ASSERT((sst::is_negative(SST_W34Y4Q3LH4NQ6465_A)));
SST_STATIC_ASSERT((!sst::is_negative(SST_W34Y4Q3LH4NQ6465_B)));

#endif // #if SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // SST_PRIVATE_IS_NEGATIVE_ENUM_HPP
