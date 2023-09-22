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

#ifndef SST_CATALOG_IS_ITERABLE_HPP
#define SST_CATALOG_IS_ITERABLE_HPP

#include <type_traits>
#include <utility>

#include <sst/catalog/begin.hpp>
#include <sst/catalog/dependent_true.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/end.hpp>
#include <sst/catalog/is_input_iterator.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {

namespace guts {
namespace is_iterable {

template<class, class, template<class...> class, class...>
struct x : std::false_type {};

#define SST_C sst::remove_cvref_t<C>
#define SST_c (std::declval<SST_C &>())
#define SST_I decltype(sst::begin(SST_c))
#define SST_S decltype(sst::end(SST_c))

template<class C, template<class...> class T, class... Args>
struct x<
    sst::enable_if_t<sst::is_input_iterator<SST_I, T, Args...>::value
                     && sst::is_sentinel<SST_S, SST_I>::value>,
    C,
    T,
    Args...> : std::true_type {};

#undef SST_S
#undef SST_I
#undef SST_c
#undef SST_C

} // namespace is_iterable
} // namespace guts

template<class C,
         template<class...> class T = sst::dependent_true,
         class... Args>
using is_iterable =
    sst::guts::is_iterable::x<sst::enable_t, C, T, Args...>;

} // namespace sst

#endif // SST_CATALOG_IS_ITERABLE_HPP
