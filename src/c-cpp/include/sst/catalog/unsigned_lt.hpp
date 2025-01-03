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

#ifndef SST_CATALOG_UNSIGNED_LT_HPP
#define SST_CATALOG_UNSIGNED_LT_HPP

#include <sst/catalog/SST_CONSTEVAL.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/is_unscoped_enum.hpp>
#include <sst/catalog/to_unsigned.hpp>

namespace sst {

//----------------------------------------------------------------------

#define SST_r (sst::to_unsigned(a) < sst::to_unsigned(b))

template<class A,
         class B,
         sst::enable_if_t<(sst::is_integer<A>::value
                           || sst::is_unscoped_enum<A>::value)
                          && (sst::is_integer<B>::value
                              || sst::is_unscoped_enum<B>::value)> = 0>
SST_CONSTEVAL bool unsigned_lt(A const a,
                               B const b) noexcept(noexcept(SST_r)) {
  return SST_r;
}

#undef SST_r

//----------------------------------------------------------------------

#define SST_r (a < b)

template<class A,
         class B,
         sst::enable_if_t<(!sst::is_integer<A>::value
                           && !sst::is_unscoped_enum<A>::value)
                          || (!sst::is_integer<B>::value
                              && !sst::is_unscoped_enum<B>::value)> = 0>
constexpr bool unsigned_lt(A const & a,
                           B const & b) noexcept(noexcept(SST_r)) {
  return SST_r;
}

#undef SST_r

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_CATALOG_UNSIGNED_LT_HPP
