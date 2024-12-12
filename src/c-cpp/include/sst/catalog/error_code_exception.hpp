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

#ifndef SST_CATALOG_ERROR_CODE_EXCEPTION_HPP
#define SST_CATALOG_ERROR_CODE_EXCEPTION_HPP

#include <stdexcept>
#include <string>
#include <type_traits>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/to_string.hpp>

namespace sst {

template<class CodeType,
         class CodeToString = void,
         class DefaultCode = void,
         class BaseClass = std::runtime_error>
class error_code_exception : public BaseClass {

public:

  using code_t = sst::remove_cvref_t<CodeType>;

private:

  template<
      class Enable = sst::enable_t,
      sst::enable_if_t<std::is_void<CodeToString>::value, Enable> = 0>
  static void add_code_string(std::string & message,
                              code_t const & code) {
    message += "Unknown error (errno error code ";
    message += sst::to_string(code);
    message += ")";
  }

  template<
      class Enable = sst::enable_t,
      sst::enable_if_t<!std::is_void<CodeToString>::value, Enable> = 0>
  static void add_code_string(std::string & message,
                              code_t const & code) {
    message += CodeToString()(code);
  }

  static bool should_add_failed(std::string const & s) {
    auto const n = s.size();
    if (n >= 2 && s[n - 2] == '(' && s[n - 1] == ')') {
      return true;
    }
    return false;
  }

  static std::string adjust_message(std::string message,
                                    code_t const & code) {
    if (should_add_failed(message)) {
      message += " failed: ";
    } else if (!message.empty()) {
      message += ": ";
    }
    add_code_string(message, code);
    return message;
  }

  code_t code_;

public:

  explicit error_code_exception(std::string const & message,
                                code_t const & code)
      : BaseClass(adjust_message(message, code)),
        code_(code) {
  }

  explicit error_code_exception(char const * const message,
                                code_t const & code)
      : error_code_exception(
          (SST_ASSERT((message != nullptr)), std::string(message)),
          code) {
  }

  template<
      class Enable = sst::enable_t,
      sst::enable_if_t<!std::is_void<DefaultCode>::value, Enable> = 0>
  explicit error_code_exception(std::string const & message)
      : error_code_exception(message, DefaultCode()()) {
  }

  template<
      class Enable = sst::enable_t,
      sst::enable_if_t<!std::is_void<DefaultCode>::value, Enable> = 0>
  explicit error_code_exception(char const * const message)
      : error_code_exception(message, DefaultCode()()) {
  }

  explicit error_code_exception(code_t const & code)
      : error_code_exception(std::string(), code) {
  }

  template<
      class Enable = sst::enable_t,
      sst::enable_if_t<!std::is_void<DefaultCode>::value, Enable> = 0>
  explicit error_code_exception()
      : error_code_exception(DefaultCode()()) {
  }

  code_t const & code() const noexcept {
    return code_;
  }

}; //

} // namespace sst

#endif // SST_CATALOG_ERROR_CODE_EXCEPTION_HPP
