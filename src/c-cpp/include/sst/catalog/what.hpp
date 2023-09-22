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

#ifndef SST_CATALOG_WHAT_HPP
#define SST_CATALOG_WHAT_HPP

#include <exception>
#include <memory>
#include <string>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_NODISCARD.hpp>
#include <sst/private/SST_DLL_EXPORT.h>

namespace sst {

class SST_DLL_EXPORT what final {

  SST_NODISCARD()
  static std::string message(std::exception const & exception,
                             char const * const separator);

  SST_NODISCARD()
  static std::string message(std::exception const & exception,
                             std::string const & separator) {
    return message(exception, separator.c_str());
  }

  std::shared_ptr<std::string> str_;
  std::exception_ptr ptr_;
  char const * msg_ = "Unknown error.";

  void init(std::exception const & exception,
            char const * const separator) noexcept;

  void init(std::exception const & exception,
            std::string const & separator) noexcept {
    try {
      init(exception, separator.c_str());
    } catch (...) {
    }
  }

  void init(std::exception_ptr && ptr,
            char const * const separator) noexcept {
    try {
      if (ptr) {
        try {
          std::rethrow_exception(std::move(ptr));
        } catch (std::exception const & exception) {
          init(exception, separator);
        }
      }
    } catch (...) {
    }
  }

  void init(std::exception_ptr && ptr,
            std::string const & separator) noexcept {
    try {
      init(std::move(ptr), separator.c_str());
    } catch (...) {
    }
  }

public:

  explicit what(std::exception const & exception,
                char const * const separator = nullptr) noexcept {
    init(exception, separator);
  }

  explicit what(std::exception const & exception,
                std::string const & separator) noexcept {
    init(exception, separator);
  }

  explicit what(char const * const separator) noexcept {
    init(std::current_exception(), separator);
  }

  what() noexcept {
    init(std::current_exception(), nullptr);
  }

  explicit what(std::string const & separator) noexcept {
    init(std::current_exception(), separator);
  }

  what(what const &) noexcept = default;
  what & operator=(what const &) noexcept = default;
  what(what &&) = delete;
  what & operator=(what &&) = delete;
  ~what() noexcept = default;

  char const * c_str() const noexcept {
    SST_ASSERT((msg_ != nullptr));
    return msg_;
  }

  operator char const *() const noexcept {
    SST_ASSERT((msg_ != nullptr));
    return msg_;
  }

  friend std::string operator+(what const & a, std::string const & b) {
    SST_ASSERT((a.msg_ != nullptr));
    return a.msg_ + b;
  }

  friend std::string operator+(std::string const & a, what const & b) {
    SST_ASSERT((b.msg_ != nullptr));
    return a + b.msg_;
  }

}; //

} // namespace sst

#endif // SST_CATALOG_WHAT_HPP
