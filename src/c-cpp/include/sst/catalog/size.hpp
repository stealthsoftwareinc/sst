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

#ifndef SST_CATALOG_SIZE_HPP
#define SST_CATALOG_SIZE_HPP

#include <cstddef>
#include <iterator>
#include <utility>

#include <sst/catalog/SST_CPP17_OR_LATER.h>

namespace SST_GUTS {
namespace size {

#if SST_CPP17_OR_LATER

using std::size;

#else

#define SST_x (c.size())

template<class C>
constexpr auto size(C const & c) noexcept(noexcept(SST_x))
    -> decltype(SST_x) {
  return SST_x;
}

#undef SST_x

template<class T, std::size_t N>
constexpr std::size_t size(T const (&)[N]) noexcept {
  return N;
}

#endif

#define SST_x (size(std::forward<C>(c)))

template<class C>
constexpr auto f(C && c) noexcept(noexcept(SST_x)) -> decltype(SST_x) {
  return SST_x;
}

#undef SST_x

} // namespace size
} // namespace SST_GUTS

namespace sst {

namespace guts {
namespace size {

#define SST_x (SST_GUTS::size::f(std::forward<C>(c)))

template<class C>
constexpr auto size(C && c) noexcept(noexcept(SST_x))
    -> decltype(SST_x) {
  return SST_x;
}

#undef SST_x

} // namespace size
} // namespace guts

// ADL never matches functions imported with "using namespace".
using namespace guts::size;

} // namespace sst

#endif // #ifndef SST_CATALOG_SIZE_HPP
