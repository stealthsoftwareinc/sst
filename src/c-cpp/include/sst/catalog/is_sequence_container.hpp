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

#ifndef SST_CATALOG_IS_SEQUENCE_CONTAINER_HPP
#define SST_CATALOG_IS_SEQUENCE_CONTAINER_HPP

#include <type_traits>
#include <utility>

#include <sst/catalog/SST_DEFINE_BOOLEAN_TRAIT_1.hpp>
#include <sst/catalog/is_container.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {

SST_DEFINE_BOOLEAN_TRAIT_1(
    is_sequence_container,
    T,
    (sst::is_container<T>::value
     && std::is_same<
         decltype(std::declval<sst::remove_cvref_t<T>>().front()),
         typename sst::remove_cvref_t<T>::reference>::value))

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <sst/catalog/SST_STATIC_ASSERT.h>

#define SST_Y(...)                                                     \
  SST_STATIC_ASSERT((sst::is_sequence_container<__VA_ARGS__>::value))

#define SST_N(...)                                                     \
  SST_STATIC_ASSERT((!sst::is_sequence_container<__VA_ARGS__>::value))

SST_N(int);

SST_Y(std::array<int, 1>);
SST_Y(std::deque<int>);
SST_Y(std::forward_list<int>);
SST_Y(std::list<int>);
SST_Y(std::vector<int>);

SST_N(std::multiset<int>);
SST_N(std::set<int>);
SST_N(std::unordered_multiset<int>);
SST_N(std::unordered_set<int>);

SST_N(std::map<int, int>);
SST_N(std::multimap<int, int>);
SST_N(std::unordered_map<int, int>);
SST_N(std::unordered_multimap<int, int>);

SST_N(std::priority_queue<int>);
SST_N(std::queue<int>);
SST_N(std::stack<int>);

#undef SST_Y
#undef SST_N

#endif

//----------------------------------------------------------------------

#endif // SST_CATALOG_IS_SEQUENCE_CONTAINER_HPP
