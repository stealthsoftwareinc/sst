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

#ifndef SST_CATALOG_JSON_EXCEPTION_HPP
#define SST_CATALOG_JSON_EXCEPTION_HPP

#include <stdexcept>
#include <string>
#include <utility>

#include <sst/catalog/c_quote.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/json/is_nlohmann.hpp>
#include <sst/catalog/json/quote.hpp>
#include <sst/catalog/json/types.hpp>
#include <sst/catalog/to_string.hpp>
#include <sst/catalog/with_what_suffix.hpp>

namespace sst {
namespace json {

class exception : public std::runtime_error,
                  public sst::with_what_suffix {

private:

  bool leaf_;

public:

  char const * what_suffix() const override {
    return leaf_ ? ": " : "";
  }

private:

  explicit exception(char const * const message, bool const leaf)
      : std::runtime_error((SST_ASSERT(message != nullptr), message)),
        leaf_(leaf) {
  }

  explicit exception(std::string const & message, bool const leaf)
      : std::runtime_error(message),
        leaf_(leaf) {
  }

  exception add(std::string const & message) const {
    return exception(message + what_suffix(), false);
  }

  exception add(char const * const message) const {
    SST_ASSERT(message != nullptr);
    return add(std::string(message));
  }

public:

  explicit exception(char const * const message)
      : exception(message, true) {
  }

  explicit exception(std::string const & message)
      : exception(message, true) {
  }

  static exception invalid_value() {
    return exception("Invalid value");
  }

  template<class Value,
           sst::enable_if_t<sst::json::is_nlohmann<Value>::value> = 0>
  static exception invalid_value(Value const & value) {
    std::string s = "Invalid value: ";
    auto const v = value.dump(-1, ' ', true);
    s.insert(s.end(), v.begin(), v.end());
    return exception(std::move(s));
  }

  static exception missing_value() {
    return exception("Missing value");
  }

  static exception expected(sst::json::types types);

  static exception expected_array() {
    return expected(sst::json::types::array());
  }

  static exception expected_boolean() {
    return expected(sst::json::types::boolean());
  }

  static exception expected_null() {
    return expected(sst::json::types::null());
  }

  static exception expected_number() {
    return expected(sst::json::types::number());
  }

  static exception expected_object() {
    return expected(sst::json::types::object());
  }

  static exception expected_string() {
    return expected(sst::json::types::string());
  }

  static exception expected_not_null() {
    return expected(~sst::json::types::null());
  }

  template<class Integer,
           sst::enable_if_t<sst::is_integer_ish<Integer>::value> = 0>
  exception add_index(Integer && i) const {
    return add("[" + sst::to_string(std::forward<Integer>(i)) + "]");
  }

  template<class String>
  exception add_key(String && key) const {
    // TODO: "Key quote" the key instead of always quoting it.
    return add("." + sst::json::quote(std::forward<String>(key)));
  }

  template<class String>
  exception add_file(String && file) const {
    // TODO: "Path quote" the file name instead of always quoting it.
    return add(sst::c_quote(std::forward<String>(file)));
  }

}; //

} // namespace json
} // namespace sst

#endif // #ifndef SST_CATALOG_JSON_EXCEPTION_HPP
