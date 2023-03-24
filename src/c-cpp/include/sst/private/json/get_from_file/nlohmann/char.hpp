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

#ifndef SST_PRIVATE_JSON_GET_FROM_FILE_NLOHMANN_CHAR_HPP
#define SST_PRIVATE_JSON_GET_FROM_FILE_NLOHMANN_CHAR_HPP

#include <exception>
#include <fstream>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/json/exception.hpp>
#include <sst/catalog/json/is_nlohmann.hpp>
#include <sst/catalog/optional.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/private/json/get_from_file.hpp>

namespace sst {
namespace json {

template<class T, class Json, class Path>
class get_from_file_functor<
    sst::enable_if_t<sst::json::is_nlohmann<Json>::value
                     && std::is_convertible<Path, char const *>::value>,
    T,
    Json,
    Path> {

public:

  sst::remove_cvref_t<T> operator()(char const * const path) const {
    try {
      SST_ASSERT((path != nullptr));
      std::ifstream stream;
      stream.exceptions(stream.badbit | stream.failbit);
      try {
        stream.open(path);
      } catch (...) {
        std::throw_with_nested(
            sst::json::exception("Error opening file for reading"));
      }
      try {
        sst::optional<sst::remove_cvref_t<T>> json =
            sst::json::get_from_file<T, Json>(stream);
        if (!json) {
          throw std::runtime_error("File is empty");
        }
        return std::move(*json);
      } catch (typename Json::parse_error const &) {
        std::throw_with_nested(
            sst::json::exception("Error parsing file"));
      } catch (...) {
        std::throw_with_nested(
            sst::json::exception("Error reading file"));
      }
    } catch (sst::json::exception const & e) {
      std::throw_with_nested(e.add_file(path));
    }
  }

}; //

} // namespace json
} // namespace sst

#endif // #ifndef SST_PRIVATE_JSON_GET_FROM_FILE_NLOHMANN_CHAR_HPP
