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

#ifndef SST_CATALOG_MIN_REP_BITS_HPP
#define SST_CATALOG_MIN_REP_BITS_HPP

#include <type_traits>

#include <sst/catalog/ceil_lg.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/integer_rep.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/type_min.hpp>

namespace sst {

namespace guts {
namespace min_rep_bits {

template<class, class, class = sst::enable_t>
struct options;

template<class X>
struct options<void, X, sst::enable_if_t<std::is_integral<X>::value>> {

  static constexpr sst::integer_rep rep() {
    return sst::integer_rep::twos_complement();
  }

  using return_type = X;

}; //

} // namespace min_rep_bits
} // namespace guts

//----------------------------------------------------------------------
// Fundamental integer -> two's complement
//----------------------------------------------------------------------

template<
    class Options = void,
    class X,
    class O = guts::min_rep_bits::options<Options, X>,
    sst::enable_if_t<O::rep() == sst::integer_rep::twos_complement()
                     && std::is_integral<X>::value> = 0>
constexpr typename O::return_type min_rep_bits(X const x) noexcept {
  return static_cast<typename O::return_type>(
      static_cast<X>(1)
      + sst::ceil_lg(
          sst::is_negative(x) ?
              -(x + static_cast<X>(x == sst::type_min<X>::value)) :
              x + static_cast<X>(x != sst::type_max<X>::value)));
}

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_CATALOG_MIN_REP_BITS_HPP
