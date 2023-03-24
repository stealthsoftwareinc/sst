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

#ifndef SST_CATALOG_UNSIGNED_RAND_RANGE_HPP
#define SST_CATALOG_UNSIGNED_RAND_RANGE_HPP

#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/is_urbg.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/to_unsigned.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/unsigned_le.hpp>
#include <sst/catalog/urbg_sample.hpp>
#include <sst/catalog/urbg_width.hpp>
#include <sst/catalog/value_bits.hpp>

namespace sst {

template<class T,
         class G,
         sst::enable_if_t<sst::is_integer<T>::value
                          && sst::is_urbg<G>::value> = 0,
         class R = sst::remove_cvref_t<T>,
         class S = typename G::result_type>
R unsigned_rand_range(G & g) {
  constexpr R v = sst::value_bits<R>::value;
  constexpr S w = sst::urbg_width<G>();
  if (sst::unsigned_le(v, w)) {
    return static_cast<R>(sst::to_unsigned(sst::urbg_sample(g))
                          & sst::to_unsigned(sst::type_max<R>::value));
  }
  R const d = static_cast<R>(w);
  R x = static_cast<R>(0);
  R i = static_cast<R>(0);
  R m = sst::type_max<R>::value;
  while (i < v) {
    x = static_cast<R>(
        x | ((static_cast<R>(sst::urbg_sample(g)) & m) << i));
    i = static_cast<R>(v - i < d ? v : i + d);
    m = static_cast<R>(m >> w);
  }
  return x;
}

} // namespace sst

#endif // #ifndef SST_CATALOG_UNSIGNED_RAND_RANGE_HPP
