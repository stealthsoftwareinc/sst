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

#ifndef SST_CATALOG_VALUE_SENTINEL_HPP
#define SST_CATALOG_VALUE_SENTINEL_HPP

#include <type_traits>
#include <utility>

#include <sst/catalog/SST_NODISCARD.h>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/value_sentinel_t.hpp>

namespace sst {

//----------------------------------------------------------------------

#define SST_R sst::value_sentinel_t<sst::remove_cvref_t<Value> const>
#define SST_r (SST_R{std::move(value)})

template<
    class Value,
    sst::enable_if_t<std::is_rvalue_reference<Value &&>::value> = 0>
SST_NODISCARD()
constexpr SST_R
    value_sentinel(Value && value) noexcept(SST_NOEXCEPT(SST_r)) {
  return SST_r;
}

#undef SST_r
#undef SST_R

//----------------------------------------------------------------------

#define SST_R sst::value_sentinel_t<sst::remove_cvref_t<Value> const &>
#define SST_r (SST_R{value})

template<
    class Value,
    sst::enable_if_t<!std::is_rvalue_reference<Value &&>::value> = 0>
SST_NODISCARD()
constexpr SST_R
    value_sentinel(Value && value) noexcept(SST_NOEXCEPT(SST_r)) {
  return SST_r;
}

#undef SST_r
#undef SST_R

//----------------------------------------------------------------------

} // namespace sst

#endif // #ifndef SST_CATALOG_VALUE_SENTINEL_HPP
