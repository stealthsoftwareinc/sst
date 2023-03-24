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

#ifndef SST_CATALOG_JSON_EXPECT_NUMBER_HPP
#define SST_CATALOG_JSON_EXPECT_NUMBER_HPP

#include <type_traits>
#include <utility>

#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/json/expect.hpp>
#include <sst/catalog/json/types.hpp>

namespace sst {
namespace json {

//----------------------------------------------------------------------

#define SST_r                                                          \
  (sst::json::expect(std::forward<Json>(json),                         \
                     sst::json::types::number()))

template<class Json>
auto expect_number(Json && json) noexcept(SST_NOEXCEPT(SST_r))
    -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

//----------------------------------------------------------------------

#define SST_r                                                          \
  (sst::json::expect(std::forward<Json>(json),                         \
                     std::forward<Key>(key),                           \
                     sst::json::types::number()))

template<class Json,
         class Key,
         sst::enable_if_t<
             !std::is_convertible<Key, sst::json::types>::value> = 0>
auto expect_number(Json && json,
                   Key && key) noexcept(SST_NOEXCEPT(SST_r))
    -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

//----------------------------------------------------------------------

} // namespace json
} // namespace sst

#endif // #ifndef SST_CATALOG_JSON_EXPECT_NUMBER_HPP
