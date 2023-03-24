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

#ifndef SST_CATALOG_JSON_EXPECT_HPP
#define SST_CATALOG_JSON_EXPECT_HPP

#include <exception>
#include <utility>

#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/json/exception.hpp>
#include <sst/catalog/json/is_nlohmann.hpp>
#include <sst/catalog/json/types.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {
namespace json {

//----------------------------------------------------------------------
// nlohmann/json
//----------------------------------------------------------------------

template<class Json,
         sst::enable_if_t<sst::json::is_nlohmann<Json>::value> = 0>
Json && expect(Json && json,
               sst::json::types const types = sst::json::types::all()) {
  SST_ASSERT(types != sst::json::types::none());
  bool b = false;
  b = b || ((types & sst::json::types::array()) && json.is_array());
  b = b || ((types & sst::json::types::boolean()) && json.is_boolean());
  b = b || ((types & sst::json::types::null()) && json.is_null());
  b = b || ((types & sst::json::types::number()) && json.is_number());
  b = b || ((types & sst::json::types::object()) && json.is_object());
  b = b || ((types & sst::json::types::string()) && json.is_string());
  if (!b) {
    throw sst::json::exception::expected(types);
  }
  return std::forward<Json>(json);
}

template<class Json,
         sst::enable_if_t<sst::json::is_nlohmann<Json>::value> = 0>
Json && expect(
    Json && json,
    typename sst::remove_cvref_t<Json>::object_t::key_type const & key,
    sst::json::types const types = sst::json::types::all()) {
  sst::json::expect(json, sst::json::types::object());
  try {
    auto const p = json.find(key);
    if (p == json.end()) {
      throw sst::json::exception::missing_value();
    }
    return sst::json::expect(std::forward<Json>(*p), types);
  } catch (sst::json::exception const & e) {
    std::throw_with_nested(e.add_key(key));
  }
}

} // namespace json
} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>
#include <sst/catalog/SST_WITH_NLOHMANN_JSON.h>

#if SST_COMPILE_TIME_TESTS
#if SST_WITH_NLOHMANN_JSON

#include <type_traits>
#include <utility>

#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/json/types.hpp>

#include <nlohmann/json.hpp>

#define SST_F(T)                                                       \
                                                                       \
  SST_STATIC_ASSERT((std::is_same<decltype(sst::json::expect(          \
                                      std::declval<T>(),               \
                                      sst::json::types::null())),      \
                                  T>::value));                         \
                                                                       \
  SST_STATIC_ASSERT((std::is_same<decltype(sst::json::expect(          \
                                      std::declval<T>(),               \
                                      "",                              \
                                      sst::json::types::null())),      \
                                  T>::value));

SST_F(nlohmann::json &)
SST_F(nlohmann::json const &)
SST_F(nlohmann::json &&)

#undef SST_F

#endif // #if SST_WITH_NLOHMANN_JSON
#endif // #if SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // #ifndef SST_CATALOG_JSON_EXPECT_HPP
