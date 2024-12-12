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

#ifndef SST_CATALOG_VALUE_TYPE_HPP
#define SST_CATALOG_VALUE_TYPE_HPP

#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/type_identity.hpp>

namespace sst {

template<class, class = sst::enable_t>
struct value_type : sst::type_identity<void> {};

} // namespace sst

#include <sst/private/value_type/of_input_iterable.hpp>
#include <sst/private/value_type/of_input_iterator.hpp>

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <type_traits>
#include <vector>

#include <sst/catalog/SST_STATIC_ASSERT.h>

#define SST_F(A, B)                                                    \
  SST_STATIC_ASSERT(                                                   \
      (std::is_same<typename sst::value_type<A>::type, B>::value))

SST_F(int *, int);
SST_F(int const *, int);
SST_F(int const[1], int);
SST_F(int[1], int);
SST_F(std::vector<int> const, int);
SST_F(std::vector<int>, int);
SST_F(std::vector<int>::const_iterator, int);
SST_F(std::vector<int>::iterator, int);

#undef SST_F

#endif

//----------------------------------------------------------------------

#endif // SST_CATALOG_VALUE_TYPE_HPP
