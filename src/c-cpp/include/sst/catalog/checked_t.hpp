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

#ifndef SST_CATALOG_CHECKED_T_HPP
#define SST_CATALOG_CHECKED_T_HPP

#include <sst/catalog/checked_class.hpp>
#include <sst/catalog/type_identity.hpp>

namespace sst {

namespace guts {
namespace checked_t {

template<class T>
struct helper : sst::type_identity<sst::checked_class<T>> {};

template<class T>
struct helper<sst::checked_class<T>>
    : sst::type_identity<sst::checked_class<T>> {};

template<class T>
struct helper<sst::checked_class<T> const>
    : sst::type_identity<sst::checked_class<T>> {};

template<class T>
struct helper<sst::checked_class<T> volatile>
    : sst::type_identity<sst::checked_class<T>> {};

template<class T>
struct helper<sst::checked_class<T> const volatile>
    : sst::type_identity<sst::checked_class<T>> {};

template<class T>
struct helper<sst::checked_class<T> const &>
    : sst::type_identity<sst::checked_class<T>> {};

template<class T>
struct helper<sst::checked_class<T> volatile &>
    : sst::type_identity<sst::checked_class<T>> {};

template<class T>
struct helper<sst::checked_class<T> const volatile &>
    : sst::type_identity<sst::checked_class<T>> {};

} // namespace checked_t
} // namespace guts

template<class T>
using checked_t = typename guts::checked_t::helper<T>::type;

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <type_traits>

#include <sst/catalog/SST_STATIC_ASSERT.h>

#define SST_F(A, B) SST_STATIC_ASSERT((std::is_same<A, B>::value))

// clang-format off

SST_F(sst::checked_t<int>, sst::checked_class<int>);
SST_F(sst::checked_t<sst::checked_t<int>>, sst::checked_t<int>);
SST_F(sst::checked_t<sst::checked_t<int> const>, sst::checked_t<int>);
SST_F(sst::checked_t<sst::checked_t<int> volatile>, sst::checked_t<int>);
SST_F(sst::checked_t<sst::checked_t<int> const volatile>, sst::checked_t<int>);
SST_F(sst::checked_t<sst::checked_t<int> const &>, sst::checked_t<int>);
SST_F(sst::checked_t<sst::checked_t<int> volatile &>, sst::checked_t<int>);
SST_F(sst::checked_t<sst::checked_t<int> const volatile &>, sst::checked_t<int>);

// clang-format on

#undef SST_F

#endif

//----------------------------------------------------------------------

#endif // #ifndef SST_CATALOG_CHECKED_T_HPP
