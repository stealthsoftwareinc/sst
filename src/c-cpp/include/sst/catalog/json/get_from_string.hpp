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

#ifndef SST_CATALOG_JSON_GET_FROM_STRING_HPP
#define SST_CATALOG_JSON_GET_FROM_STRING_HPP

#include <exception>
#include <utility>

#include <sst/catalog/cbegin.hpp>
#include <sst/catalog/cend.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_byte_input_iterable.hpp>
#include <sst/catalog/is_byte_input_iterator.hpp>
#include <sst/catalog/is_char_input_iterable.hpp>
#include <sst/catalog/is_char_input_iterator.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/catalog/json/exception.hpp>
#include <sst/catalog/json/get_as.hpp>

// TODO: Use SST_DEFINE_ALGORITHM

namespace sst {
namespace json {

template<class T,
         class Json = T,
         class Src,
         class End,
         sst::enable_if_t<(sst::is_char_input_iterator<Src>::value
                           || sst::is_byte_input_iterator<Src>::value)
                          && sst::is_sentinel<End, Src>::value> = 0>
T get_from_string(Src && src, End && end) {
  try {
    return sst::json::get_as<T>(
        Json::parse(std::forward<Src>(src), std::forward<End>(end)));
  } catch (...) {
    std::throw_with_nested(
        sst::json::exception("Error parsing JSON string"));
  }
}

template<
    class T,
    class Json = T,
    class Src,
    sst::enable_if_t<sst::is_char_input_iterable<Src>::value
                     || sst::is_byte_input_iterable<Src>::value> = 0>
T get_from_string(Src const & src) {
  return sst::json::get_from_string<T, Json>(sst::cbegin(src),
                                             sst::cend(src));
}

} // namespace json
} // namespace sst

#endif // #ifndef SST_CATALOG_JSON_GET_FROM_STRING_HPP
