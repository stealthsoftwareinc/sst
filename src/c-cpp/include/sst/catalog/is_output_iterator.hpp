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

#ifndef SST_CATALOG_IS_OUTPUT_ITERATOR_HPP
#define SST_CATALOG_IS_OUTPUT_ITERATOR_HPP

#include <type_traits>
#include <utility>

#include <sst/catalog/SST_COMPILES.hpp>
#include <sst/catalog/decay_t.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_iterator.hpp>

namespace sst {

template<class I, class T = void, class = sst::enable_t>
struct is_output_iterator : std::false_type {};

template<class I, class T>
struct is_output_iterator<I,
                          T,
                          sst::enable_if_t<sst::is_iterator<I>::value
                                           && std::is_void<T>::value>>
    : std::true_type {};

template<class I, class T>
struct is_output_iterator<
    I,
    T,
    sst::enable_if_t<
        sst::is_iterator<I>::value && !std::is_void<T>::value
        && SST_COMPILES(*std::declval<sst::decay_t<I> &>() =
                            std::forward<T>(std::declval<T>()))>>
    : std::true_type {};

} // namespace sst

#endif // #ifndef SST_CATALOG_IS_OUTPUT_ITERATOR_HPP
