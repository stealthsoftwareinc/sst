//
// Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
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

#ifndef SST_CATALOG_IF_CHAIN_HPP
#define SST_CATALOG_IF_CHAIN_HPP

#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/type_identity.hpp>

namespace sst {

namespace guts {
namespace if_chain {

template<class, class, class, class, class... Args>
struct helper;

template<class B, class T, class F>
struct helper<sst::enable_if_t<!!B::value>, B, T, F>
    : sst::type_identity<T> {};

template<class B, class T, class F>
struct helper<sst::enable_if_t<!B::value>, B, T, F>
    : sst::type_identity<F> {};

template<class B1, class T1, class B2, class T2, class... Args>
struct helper<sst::enable_if_t<!!B1::value>, B1, T1, B2, T2, Args...>
    : sst::type_identity<T1> {};

template<class B1, class T1, class B2, class T2, class... Args>
struct helper<sst::enable_if_t<!B1::value>, B1, T1, B2, T2, Args...>
    : helper<sst::enable_t, B2, T2, Args...> {};

} // namespace if_chain
} // namespace guts

template<class... Args>
struct if_chain : guts::if_chain::helper<sst::enable_t, Args...> {};

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <type_traits>

#include <sst/catalog/SST_STATIC_ASSERT.h>

namespace sst {
namespace guts {
namespace if_chain {
namespace compile_time_tests {

using T = std::true_type;
using F = std::false_type;

#define SST_F(A, ...)                                                  \
  SST_STATIC_ASSERT(                                                   \
      (std::is_same<A, typename __VA_ARGS__::type>::value))

SST_F(char, sst::if_chain<T, char, long>);
SST_F(long, sst::if_chain<F, char, long>);
SST_F(long, sst::if_chain<F, char, T, long, void>);
SST_F(void, sst::if_chain<F, char, F, long, void>);

#undef SST_F

} // namespace compile_time_tests
} // namespace if_chain
} // namespace guts
} // namespace sst

#endif // #if SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // SST_CATALOG_IF_CHAIN_HPP
