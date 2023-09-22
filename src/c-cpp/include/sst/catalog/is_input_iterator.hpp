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

#ifndef SST_CATALOG_IS_INPUT_ITERATOR_HPP
#define SST_CATALOG_IS_INPUT_ITERATOR_HPP

#include <type_traits>
#include <utility>

#include <sst/catalog/dependent_true.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_iterator.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {

namespace guts {
namespace is_input_iterator {

template<class, class, template<class...> class, class...>
struct helper : std::false_type {};

#define SST_I sst::remove_cvref_t<I>
#define SST_i (std::declval<SST_I &>())
#define SST_D decltype(*SST_i)
#define SST_V sst::remove_cvref_t<SST_D>

template<class I, template<class...> class B, class... Args>
struct helper<sst::enable_if_t<
                  sst::is_iterator<I>::value
                  && std::is_object<sst::remove_cvref_t<SST_D>>::value
                  && B<SST_V, Args...>::value>,
              I,
              B,
              Args...> : std::true_type {};

#undef SST_V
#undef SST_D
#undef SST_i
#undef SST_I

} // namespace is_input_iterator
} // namespace guts

template<class I,
         template<class...> class B = sst::dependent_true,
         class... Args>
using is_input_iterator =
    sst::guts::is_input_iterator::helper<sst::enable_t, I, B, Args...>;

} // namespace sst

#endif // SST_CATALOG_IS_INPUT_ITERATOR_HPP
