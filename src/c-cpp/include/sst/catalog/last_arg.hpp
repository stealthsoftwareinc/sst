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

#ifndef SST_CATALOG_LAST_ARG_HPP
#define SST_CATALOG_LAST_ARG_HPP

#include <cstddef>

#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/forward.hpp>

namespace sst {

//----------------------------------------------------------------------

namespace guts {
namespace last_arg {

template<std::size_t, class...>
struct functor;

} // namespace last_arg
} // namespace guts

//----------------------------------------------------------------------

#define SST_r                                                          \
  (guts::last_arg::functor<I, sst::enable_t, Args...>()(               \
      sst::forward<Args>(args)...))

template<std::size_t I = 1, class... Args>
constexpr auto last_arg(Args &&... args) noexcept(noexcept(SST_r))
    -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

//----------------------------------------------------------------------

namespace guts {
namespace last_arg {

#define SST_r (sst::forward<First>(first))

template<std::size_t I, class First2, class... Rest2>
struct functor<I,
               sst::enable_if_t<(I == 1U + sizeof...(Rest2))>,
               First2,
               Rest2...> {
  template<class First, class... Rest>
  constexpr auto operator()(First && first, Rest &&...) const
      noexcept(noexcept(SST_r)) -> decltype(SST_r) {
    return SST_r;
  }
};

#undef SST_r

} // namespace last_arg
} // namespace guts

//----------------------------------------------------------------------

namespace guts {
namespace last_arg {

#define SST_r (sst::last_arg<I>(sst::forward<Rest>(rest)...))

template<std::size_t I, class First2, class... Rest2>
struct functor<I,
               sst::enable_if_t<(I < 1U + sizeof...(Rest2)) && (I > 0)>,
               First2,
               Rest2...> {
  template<class First, class... Rest>
  constexpr auto operator()(First &&, Rest &&... rest) const
      noexcept(noexcept(SST_r)) -> decltype(SST_r) {
    return SST_r;
  }
};

#undef SST_r

} // namespace last_arg
} // namespace guts

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_CATALOG_LAST_ARG_HPP
