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

#ifndef SST_CATALOG_IS_ONES_COMPLEMENT_HPP
#define SST_CATALOG_IS_ONES_COMPLEMENT_HPP

#include <type_traits>

#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/dependent_false.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_signed_integer.hpp>
#include <sst/catalog/is_twos_complement.hpp>
#include <sst/catalog/promotes.hpp>

namespace sst {

template<class T, class = sst::enable_t>
struct is_ones_complement : std::false_type {};

template<class T>
struct is_ones_complement<
    T,
    sst::enable_if_t<sst::is_signed_integer<T>::value
                     && !sst::is_twos_complement<T>::value
                     && !sst::promotes<T>::value
                     && (static_cast<T>(-1) & static_cast<T>(1)) == 0>>
    : std::true_type {};

template<class T>
struct is_ones_complement<
    T,
    sst::enable_if_t<sst::is_signed_integer<T>::value
                     && !sst::is_twos_complement<T>::value
                     && sst::promotes<T>::value>> {
  // clang-format off
  SST_STATIC_ASSERT(("It cannot be determined whether a signed integer type that is affected by the integer promotions and does not use two's complement representation uses ones' complement vs. sign-magnitude representation." && sst::dependent_false<T>::value));
  // clang-format on
};

} // namespace sst

#endif // SST_CATALOG_IS_ONES_COMPLEMENT_HPP
