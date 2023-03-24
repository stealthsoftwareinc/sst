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

#ifndef SST_CATALOG_URBG_WIDTH_HPP
#define SST_CATALOG_URBG_WIDTH_HPP

#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/floor_lg.hpp>
#include <sst/catalog/is_urbg.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/type_min.hpp>
#include <sst/catalog/width_bits.hpp>

namespace sst {

//
// Returns the "width" of the uniform random bit generator (URBG) G.
// This is the largest number of bits k that can be safely extracted
// from each sample x = g() - G::min(), provided x >= 2^k is rejected
// and resampled. The "modulus" m = G::max() - G::min() + 1 is rounded
// down to a power of two, and k is the exponent of that power of two,
// i.e., k = floor(lg(m)). Note that G::min() is required to be less
// than G::max(), so k is at least 1.
//
// Most generators will set G::min() and G::max() to the full range of
// G::result_type, in which case m = 2^k, where k is the number of width
// bits in G::result_type. Note that G::result_type is required to be an
// unsigned integer type, so k is also the number of value bits.
//
// When m is a power of two, samples will never need to be rejected, as
// x >= 2^k will not be possible.
//

template<class G,
         sst::enable_if_t<sst::is_urbg<G>::value> = 0,
         class S = typename G::result_type>
constexpr S urbg_width() noexcept {
  return static_cast<S>(
      G::min() == sst::type_min<S>::value
              && G::max() == sst::type_max<S>::value ?
          sst::width_bits<S>::value :
          sst::floor_lg(G::max() - G::min() + static_cast<S>(1)));
}

} // namespace sst

#endif // #ifndef SST_CATALOG_URBG_WIDTH_HPP
