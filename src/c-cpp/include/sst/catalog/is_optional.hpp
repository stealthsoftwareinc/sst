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

#ifndef SST_CATALOG_IS_OPTIONAL_HPP
#define SST_CATALOG_IS_OPTIONAL_HPP

#include <utility>

#include <sst/catalog/SST_COMPILES.hpp>
#include <sst/catalog/SST_DEFINE_BOOLEAN_TRAIT_1.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {

#define SST_T sst::remove_cvref_t<T>
#define SST_t (std::declval<SST_T &>())

SST_DEFINE_BOOLEAN_TRAIT_1(is_optional,
                           T,
                           (SST_COMPILES(SST_t.has_value())
                            && SST_COMPILES(SST_t.value())))

#undef SST_t
#undef SST_T

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/optional.hpp>

#define SST_Y(...)                                                     \
  SST_STATIC_ASSERT((sst::is_optional<__VA_ARGS__>::value));

#define SST_N(...)                                                     \
  SST_STATIC_ASSERT((!sst::is_optional<__VA_ARGS__>::value));

SST_Y(sst::optional<int>)

SST_N(int)

#undef SST_N
#undef SST_Y

#endif

//----------------------------------------------------------------------

#endif // SST_CATALOG_IS_OPTIONAL_HPP
