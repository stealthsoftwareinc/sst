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

#ifndef SST_CATALOG_RAND_RANGE_HPP
#define SST_CATALOG_RAND_RANGE_HPP

#include <type_traits>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/conditional_t.hpp>
#include <sst/catalog/crypto_rng.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/is_representable_as.hpp>
#include <sst/catalog/is_twos_complement.hpp>
#include <sst/catalog/is_urbg.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/undeduced_t.hpp>
#include <sst/catalog/unsigned_rand_range.hpp>

namespace sst {

//----------------------------------------------------------------------

template<class T,
         class G,
         sst::enable_if_t<sst::is_integer<T>::value
                          && sst::is_urbg<G>::value> = 0,
         class R = sst::remove_cvref_t<T>,
         class S = typename G::result_type>
R rand_range(G & g) {
retry:
  R r = sst::unsigned_rand_range<R>(g);
  if (std::is_signed<R>::value && (g() & static_cast<S>(1))) {
    if (!sst::is_twos_complement<R>::value
        && r == sst::type_max<R>::value) {
      goto retry;
    }
    r = static_cast<R>(static_cast<R>(-1) - r);
  }
  return r;
}

//----------------------------------------------------------------------

template<
    class T = void,
    class Max,
    class G,
    sst::enable_if_t<
        (std::is_void<T>::value || sst::is_integer<T>::value)
        && sst::is_integer<Max>::value && sst::is_urbg<G>::value> = 0,
    class R = sst::conditional_t<std::is_same<T, void>::value,
                                 sst::remove_cvref_t<Max>,
                                 sst::remove_cvref_t<T>>>
R rand_range(Max const max, G & g) {
  SST_ASSERT((!sst::is_negative(max)));
  SST_ASSERT((sst::is_representable_as<R>(max)));
  R const b = static_cast<R>(max);
  if (b == sst::type_max<R>::value) {
    return sst::unsigned_rand_range<R>(g);
  }
  R const m = static_cast<R>(b + static_cast<R>(1));
  R r;
  do {
    r = sst::unsigned_rand_range<R>(g);
  } while (r >= sst::type_max<R>::value / m * m);
  return static_cast<R>(r % m);
}

//----------------------------------------------------------------------

template<
    class T = void,
    class Min,
    class Max,
    class G,
    sst::enable_if_t<
        (std::is_void<T>::value || sst::is_integer<T>::value)
        && sst::is_integer<Min>::value && sst::is_integer<Max>::value
        && sst::is_urbg<G>::value> = 0,
    class R = sst::conditional_t<
        std::is_same<T, void>::value,
        typename std::common_type<sst::remove_cvref_t<Min>,
                                  sst::remove_cvref_t<Max>>::type,
        sst::remove_cvref_t<T>>>
R rand_range(Min const min, Max const max, G & g) {
  SST_ASSERT((sst::is_representable_as<R>(min)));
  SST_ASSERT((sst::is_representable_as<R>(max)));
  R const a = static_cast<R>(min);
  R const b = static_cast<R>(max);
  SST_ASSERT((a <= b));
  if (std::is_signed<R>::value && sst::is_negative(a)
      && a + sst::type_max<R>::value < b) {
    R r;
    do {
      r = sst::rand_range<R>(g);
    } while (r < a || r > b);
    return r;
  }
  return static_cast<R>(a + sst::rand_range<R>(b - a, g));
}

//----------------------------------------------------------------------

#define SST_r (sst::rand_range<R>(sst::crypto_rng()))

template<class T,
         sst::enable_if_t<sst::is_integer<T>::value> = 0,
         class R = sst::remove_cvref_t<T>>
R rand_range() noexcept(noexcept(SST_r)) {
  return SST_r;
}

#undef SST_r

//----------------------------------------------------------------------

#define SST_r (sst::rand_range<R>(max, sst::crypto_rng()))

template<class T = void,
         class Max,
         sst::enable_if_t<(std::is_void<T>::value
                           || sst::is_integer<T>::value)
                          && sst::is_integer<Max>::value> = 0,
         class R = sst::conditional_t<std::is_same<T, void>::value,
                                      sst::remove_cvref_t<Max>,
                                      sst::remove_cvref_t<T>>>
R rand_range(Max const max) noexcept(noexcept(SST_r)) {
  return SST_r;
}

#undef SST_r

//----------------------------------------------------------------------

#define SST_r (sst::rand_range<R>(min, max, sst::crypto_rng()))

template<class T = void,
         class Min,
         class Max,
         sst::enable_if_t<(std::is_void<T>::value
                           || sst::is_integer<T>::value)
                          && sst::is_integer<Min>::value
                          && sst::is_integer<Max>::value> = 0,
         class R = sst::conditional_t<
             std::is_same<T, void>::value,
             typename std::common_type<sst::remove_cvref_t<Min>,
                                       sst::remove_cvref_t<Max>>::type,
             sst::remove_cvref_t<T>>>
R rand_range(Min const min, Max const max) noexcept(noexcept(SST_r)) {
  return SST_r;
}

#undef SST_r

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_CATALOG_RAND_RANGE_HPP
