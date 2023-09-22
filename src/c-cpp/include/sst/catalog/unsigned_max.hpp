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

#ifndef SST_CATALOG_UNSIGNED_MAX_HPP
#define SST_CATALOG_UNSIGNED_MAX_HPP

#include <type_traits>
#include <utility>

#include <sst/catalog/SST_CONSTEXPR_ASSERT.hpp>
#include <sst/catalog/conditional_t.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/unsigned_gt.hpp>

namespace sst {

namespace guts {
namespace unsigned_max {

template<class...>
struct functor;

struct default_return_type {};

} // namespace unsigned_max
} // namespace guts

//----------------------------------------------------------------------

#define SST_r                                                          \
  (guts::unsigned_max::functor<Args...>()(std::forward<Args>(args)...))

#define SST_R                                                          \
  sst::conditional_t<                                                  \
      std::is_same<X, guts::unsigned_max::default_return_type>::value, \
      decltype(SST_r),                                                 \
      sst::remove_cvref_t<X>>

template<class X = guts::unsigned_max::default_return_type,
         class... Args>
constexpr auto unsigned_max(Args &&... args) noexcept(noexcept(SST_r))
    -> SST_R {
  return static_cast<SST_R>(SST_r);
}

#undef SST_R

#undef SST_r

//----------------------------------------------------------------------

namespace guts {
namespace unsigned_max {

//----------------------------------------------------------------------

#define SST_r (std::forward<A2>(a))

template<class A>
struct functor<A> {
  template<class A2>
  constexpr auto operator()(A2 && a) const noexcept(noexcept(SST_r))
      -> sst::remove_cvref_t<decltype(SST_r)> {
    SST_CONSTEXPR_ASSERT((!sst::is_negative(a)));
    return SST_r;
  }
};

#undef SST_r

//----------------------------------------------------------------------

#define SST_r                                                          \
  (sst::unsigned_gt(a, b) ?                                            \
       sst::unsigned_max(std::forward<A2>(a),                          \
                         std::forward<C2>(c)...) :                     \
       sst::unsigned_max(std::forward<B2>(b), std::forward<C2>(c)...))

template<class A, class B, class... C>
struct functor<A, B, C...> {
  template<class A2, class B2, class... C2>
  constexpr auto operator()(A2 && a, B2 && b, C2 &&... c) const
      noexcept(noexcept(SST_r))
          -> sst::remove_cvref_t<decltype(SST_r)> {
    SST_CONSTEXPR_ASSERT((!sst::is_negative(a)));
    SST_CONSTEXPR_ASSERT((!sst::is_negative(b)));
    return SST_r;
  }
};

#undef SST_r

//----------------------------------------------------------------------

} // namespace unsigned_max
} // namespace guts

} // namespace sst

#endif // SST_CATALOG_UNSIGNED_MAX_HPP
