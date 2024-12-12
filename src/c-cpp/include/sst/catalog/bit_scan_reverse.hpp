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

#ifndef SST_CATALOG_BIT_SCAN_REVERSE_HPP
#define SST_CATALOG_BIT_SCAN_REVERSE_HPP

#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_CONSTEXPR_ASSERT.hpp>
#include <sst/catalog/SST_DEFINE_BOOLEAN_TRAIT_1.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/ones_mask.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/value_bits.hpp>
#include <sst/catalog/width_bits.hpp>
#include <sst/config.h>

#if SST_WITH_X86
#include <x86intrin.h>
#endif

namespace sst {

namespace guts {
namespace bit_scan_reverse {

//----------------------------------------------------------------------

SST_DEFINE_BOOLEAN_TRAIT_1(use_x86_intrinsic_1,
                           X,
                           ((true)
                            && (SST_WITH_X86
                                && sst::is_integer<X>::value
                                && !std::is_reference<X>::value
                                && sst::width_bits<X>::value == 32)))

#if SST_WITH_X86

template<class X>
X x86_intrinsic_1(X const x) noexcept {
  SST_ASSERT((x != 0));
  return static_cast<X>(_bit_scan_reverse(static_cast<int>(x)));
}

#endif

//----------------------------------------------------------------------

SST_DEFINE_BOOLEAN_TRAIT_1(use_x86_intrinsic_2,
                           X,
                           ((!use_x86_intrinsic_1<X>::value)
                            && (SST_WITH_X86
                                && sst::is_integer<X>::value
                                && !std::is_reference<X>::value
                                && sst::width_bits<X>::value < 32)))

#if SST_WITH_X86

template<class X>
X x86_intrinsic_2(X const x) noexcept {
  SST_ASSERT((x != 0));
  return static_cast<X>(_bit_scan_reverse(static_cast<int>(
      static_cast<unsigned int>(x)
      & sst::ones_mask<unsigned int>(sst::width_bits<X>::value))));
}

#endif

//----------------------------------------------------------------------

SST_DEFINE_BOOLEAN_TRAIT_1(
    use_fundamental_fallback,
    X,
    ((!use_x86_intrinsic_1<X>::value && !use_x86_intrinsic_2<X>::value)
     && (sst::is_integer<X>::value && !std::is_reference<X>::value)))

template<class X>
constexpr X fundamental_fallback(
    X const x,
    X const m = static_cast<X>(sst::type_max<X>::value >> 1),
    X const i = static_cast<X>(sst::value_bits<X>::value
                               - static_cast<X>(1))) noexcept {
  SST_CONSTEXPR_ASSERT((x != 0));
  return static_cast<X>(sst::is_negative(x) ?
                            sst::value_bits<X>::value :
                        (x & m) == x ? fundamental_fallback(
                            x,
                            static_cast<X>(m >> 1),
                            static_cast<X>(i - static_cast<X>(1))) :
                                       i);
}

//----------------------------------------------------------------------

} // namespace bit_scan_reverse
} // namespace guts

template<class X,
         sst::enable_if_t<
             guts::bit_scan_reverse::use_x86_intrinsic_1<X>::value> = 0>
X bit_scan_reverse(X && x) noexcept {
  return guts::bit_scan_reverse::x86_intrinsic_1(std::forward<X>(x));
}

template<class X,
         sst::enable_if_t<
             guts::bit_scan_reverse::use_x86_intrinsic_2<X>::value> = 0>
X bit_scan_reverse(X && x) noexcept {
  return guts::bit_scan_reverse::x86_intrinsic_2(std::forward<X>(x));
}

template<
    class X,
    sst::enable_if_t<
        guts::bit_scan_reverse::use_fundamental_fallback<X>::value> = 0>
X bit_scan_reverse(X && x) noexcept {
  return guts::bit_scan_reverse::fundamental_fallback(
      std::forward<X>(x));
}

} // namespace sst

#endif // SST_CATALOG_BIT_SCAN_REVERSE_HPP
