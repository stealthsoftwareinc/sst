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

#ifndef SST_CATALOG_ONES_MASK_HPP
#define SST_CATALOG_ONES_MASK_HPP

#include <type_traits>

#include <sst/catalog/SST_CONSTEXPR_ASSERT.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/unsigned_le.hpp>
#include <sst/catalog/value_bits.hpp>

namespace sst {

template<class IntType1,
         class IntType2,
         typename std::enable_if<std::is_integral<IntType1>()
                                     && std::is_integral<IntType2>(),
                                 int>::type = 0>
constexpr IntType1 ones_mask(IntType2 const n) noexcept {
  SST_CONSTEXPR_ASSERT(!sst::is_negative(n));
  SST_CONSTEXPR_ASSERT(
      sst::unsigned_le(n, sst::value_bits<IntType1>::value));
  return n == 0 ? static_cast<IntType1>(0) :
                  static_cast<IntType1>(sst::type_max<IntType1>::value
                                        >> (sst::value_bits<IntType1>()
                                            - static_cast<int>(n)));
}

template<class IntType1,
         class IntType2,
         class IntType3,
         typename std::enable_if<std::is_integral<IntType1>()
                                     && std::is_integral<IntType2>()
                                     && std::is_integral<IntType3>(),
                                 int>::type = 0>
constexpr IntType1 ones_mask(IntType2 const n,
                             IntType3 const k) noexcept {
  SST_CONSTEXPR_ASSERT(!sst::is_negative(n));
  SST_CONSTEXPR_ASSERT(!sst::is_negative(k));
  SST_CONSTEXPR_ASSERT(
      sst::unsigned_le(n, sst::value_bits<IntType1>::value));
  SST_CONSTEXPR_ASSERT(sst::unsigned_le(k,
                                        sst::value_bits<IntType1>()
                                            - static_cast<int>(n)));
  return static_cast<IntType1>(sst::ones_mask<IntType1>(n) << k);
}

} // namespace sst

#endif // SST_CATALOG_ONES_MASK_HPP
