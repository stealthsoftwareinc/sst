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

#ifndef SST_CATALOG_IS_VALUE_SENTINEL_HPP
#define SST_CATALOG_IS_VALUE_SENTINEL_HPP

#include <type_traits>
#include <utility>

#include <sst/catalog/begin.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_bool.hpp>
#include <sst/catalog/is_input_iterator.hpp>
#include <sst/catalog/is_iterable.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/value_sentinel_t.hpp>
#include <sst/catalog/value_type_t.hpp>

namespace sst {

namespace guts {
namespace is_value_sentinel {

template<class, class, class = sst::enable_t>
struct helper : std::false_type {};

template<class S, class I>
struct helper<
    sst::value_sentinel_t<S>,
    I,
    sst::enable_if_t<
        sst::is_input_iterator<I>::value
        && sst::is_bool<decltype(std::declval<sst::value_type_t<I>>()
                                 == std::declval<S>())>::value>>
    : std::true_type {};

template<class S, class I>
struct helper<
    sst::value_sentinel_t<S>,
    I,
    sst::enable_if_t<
        sst::is_input_iterator<decltype(sst::begin(
            std::declval<I &>()))>::value
        && sst::is_bool<
            decltype(std::declval<sst::value_type_t<decltype(sst::begin(
                         std::declval<I &>()))>>()
                     == std::declval<S>())>::value>> : std::true_type {
};

} // namespace is_value_sentinel
} // namespace guts

template<class S, class I>
using is_value_sentinel =
    sst::guts::is_value_sentinel::helper<sst::remove_cvref_t<S>,
                                         sst::remove_cvref_t<I>>;

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <sst/catalog/SST_EXPAND.h>
#include <sst/catalog/SST_STATIC_ASSERT.h>

#define SST_Y(S, I)                                                    \
  SST_STATIC_ASSERT(                                                   \
      (sst::is_value_sentinel<sst::value_sentinel_t<SST_EXPAND S>,     \
                              SST_EXPAND I>::value))

#define SST_N(S, I)                                                    \
  SST_STATIC_ASSERT(                                                   \
      (!sst::is_value_sentinel<sst::value_sentinel_t<SST_EXPAND S>,    \
                               SST_EXPAND I>::value))

SST_Y((int), (int *));
SST_Y((int), (int[1]));
SST_Y((int), (std::vector<int>));
SST_Y((int), (std::vector<int>::iterator));
SST_Y((int), (std::vector<int>::const_iterator));
SST_Y((int *), (int **));
SST_Y((int *), (int * [1]));
SST_Y((int *), (std::vector<int *>));
SST_Y((int *), (std::vector<int *>::iterator));
SST_Y((int *), (std::vector<int *>::const_iterator));
SST_N((long *), (std::vector<int *>::iterator));

#undef SST_N
#undef SST_Y

#endif // #if SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // #ifndef SST_CATALOG_IS_VALUE_SENTINEL_HPP
