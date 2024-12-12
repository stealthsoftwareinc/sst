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

#ifndef SST_CATALOG_POSIX_PATH_HPP
#define SST_CATALOG_POSIX_PATH_HPP

#include <sst/catalog/SST_WITH_POSIX.h>

#if SST_WITH_POSIX

#include <string>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_DEFINE_BOOLEAN_TRAIT_1.hpp>
#include <sst/catalog/SST_NODISCARD.hpp>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/cbegin.hpp>
#include <sst/catalog/cend.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_byte.hpp>
#include <sst/catalog/is_input_iterator.hpp>
#include <sst/catalog/is_iterable.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/private/SST_DLL_EXPORT.h>
#include <sst/private/guts/common_path.hpp>

namespace sst {

class posix_path : public guts::common_path<posix_path, char> {

  using base = guts::common_path<posix_path, char>;

  template<class, class>
  friend class guts::common_path;

  //--------------------------------------------------------------------
  // Types
  //--------------------------------------------------------------------

public:

  using char_t = typename base::char_t;
  using string_t = typename base::string_t;
  using value_type = typename base::value_type;

  //--------------------------------------------------------------------
  // Default operations
  //--------------------------------------------------------------------

public:

  posix_path() SST_NOEXCEPT(true) = default;

  ~posix_path() SST_NOEXCEPT(true) = default;

  posix_path(posix_path const &) = default;

  posix_path(posix_path &&) SST_NOEXCEPT(true) = default;

  posix_path & operator=(posix_path const &) = default;

  posix_path & operator=(posix_path &&) SST_NOEXCEPT(true) = default;

  //--------------------------------------------------------------------
  // Construction
  //--------------------------------------------------------------------

public:

  using base::base;

  //--------------------------------------------------------------------
  // directory_char
  //--------------------------------------------------------------------

public:

  static constexpr value_type directory_char() noexcept {
    return value_type('/');
  }

  static constexpr value_type path_list_char() noexcept {
    return value_type(':');
  }

  //--------------------------------------------------------------------
  // Attribute querying
  //--------------------------------------------------------------------

public:

  posix_path const & query() const;

  posix_path const & query_from_dirent(void const * data) const;

  posix_path const & query_from_stat(void const * data) const;

  posix_path & query() {
    static_cast<posix_path const &>(*this).query();
    return *this;
  }

  posix_path & query_from_dirent(void const * const data) {
    static_cast<posix_path const &>(*this).query_from_dirent(data);
    return *this;
  }

  posix_path & query_from_stat(void const * const data) {
    static_cast<posix_path const &>(*this).query_from_stat(data);
    return *this;
  }

  //--------------------------------------------------------------------
  // mv_onto
  //--------------------------------------------------------------------

private:

  void mv_onto(posix_path const & dst) const;

  //--------------------------------------------------------------------

public:

  SST_NODISCARD()
  static constexpr bool is_dir_char(char_t const c) noexcept {
    return c == char_t('/');
  }

  SST_NODISCARD() static constexpr char_t dir_char() noexcept {
    return char_t('/');
  }

  SST_NODISCARD() static constexpr char_t list_char() noexcept {
    return char_t(':');
  }

  //--------------------------------------------------------------------
};

} // namespace sst

#endif // #if SST_WITH_POSIX

#endif // SST_CATALOG_POSIX_PATH_HPP
