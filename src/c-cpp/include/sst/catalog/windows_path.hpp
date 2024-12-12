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

#ifndef SST_CATALOG_WINDOWS_PATH_HPP
#define SST_CATALOG_WINDOWS_PATH_HPP

#include <sst/catalog/SST_WITH_WINDOWS_KERNEL32.h>

#if SST_WITH_WINDOWS_KERNEL32

#include <cstdint>
#include <string>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_NODISCARD.hpp>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/cbegin.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_input_iterator.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_iterable.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/catalog/is_value_sentinel.hpp>
#include <sst/catalog/optional.hpp>
#include <sst/catalog/peek.hpp>
#include <sst/catalog/pos.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/size.hpp>
#include <sst/catalog/step.hpp>
#include <sst/catalog/value_sentinel.hpp>
#include <sst/catalog/value_type_t.hpp>
#include <sst/private/SST_DLL_EXPORT.h>
#include <sst/private/guts/common_path.hpp>

namespace sst {

template<class CharT>
class windows_path
    : public guts::common_path<windows_path<CharT>, CharT> {

  SST_STATIC_ASSERT((std::is_same<CharT, char>::value
                     || std::is_same<CharT, wchar_t>::value));

  using base = guts::common_path<windows_path<CharT>, CharT>;

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

  ~windows_path() SST_NOEXCEPT(true) = default;

  windows_path(windows_path const &) = default;

  windows_path(windows_path &&) SST_NOEXCEPT(true) = default;

  windows_path & operator=(windows_path const &) = default;

  windows_path & operator=(windows_path &&)
      SST_NOEXCEPT(true) = default;

  //--------------------------------------------------------------------
  // Construction
  //--------------------------------------------------------------------

public:

  using base::base;

  //--------------------------------------------------------------------
  // Attribute querying
  //--------------------------------------------------------------------

private:

  template<class GetFileAttributesExFunc,
           class CreateFileFunc,
           class GetFinalPathNameByHandleFunc>
  void query_core(
      GetFileAttributesExFunc * GetFileAttributesEx_func,
      char const * GetFileAttributesEx_name,
      CreateFileFunc * CreateFile_func,
      char const * CreateFile_name,
      GetFinalPathNameByHandleFunc * GetFinalPathNameByHandle_func,
      char const * GetFinalPathNameByHandle_name) const;

  template<class Win32FindData>
  void query_from_find_core(void const * data) const;

public:

  windows_path const & query() const;

  windows_path const & query_from_attr(void const * data) const;

  windows_path const & query_from_find(void const * data) const;

  windows_path & query() {
    static_cast<windows_path const &>(*this).query();
    return *this;
  }

  windows_path & query_from_attr(void const * const data) {
    static_cast<windows_path const &>(*this).query_from_attr(data);
    return *this;
  }

  windows_path & query_from_find(void const * const data) {
    static_cast<windows_path const &>(*this).query_from_find(data);
    return *this;
  }

  //--------------------------------------------------------------------
  // mv_onto
  //--------------------------------------------------------------------

private:

  template<class MoveFileExFunc>
  void mv_onto_core(MoveFileExFunc * MoveFileEx_func,
                    char const * MoveFileEx_name,
                    windows_path const & dst) const;

  void mv_onto(windows_path const & dst) const;

  //--------------------------------------------------------------------

public:

  SST_NODISCARD()
  static constexpr bool is_dir_char(char_t const c) noexcept {
    return c == char_t('\\') || c == char_t('/');
  }

  SST_NODISCARD() static constexpr char_t dir_char() noexcept {
    return char_t('\\');
  }

  SST_NODISCARD() static constexpr char_t list_char() noexcept {
    return char_t(';');
  }

  //--------------------------------------------------------------------
};

//----------------------------------------------------------------------
// Forward declarations
//----------------------------------------------------------------------

#define SST_F(CharT)                                                   \
                                                                       \
  template<>                                                           \
  SST_DLL_EXPORT windows_path<CharT> const &                           \
  windows_path<CharT>::query() const;                                  \
                                                                       \
  extern template SST_DLL_EXPORT windows_path<CharT> const &           \
  windows_path<CharT>::query_from_attr(void const * data) const;       \
                                                                       \
  template<>                                                           \
  SST_DLL_EXPORT windows_path<CharT> const &                           \
  windows_path<CharT>::query_from_find(void const * data) const;       \
                                                                       \
  template<>                                                           \
  SST_DLL_EXPORT void windows_path<CharT>::mv_onto(                    \
      windows_path<CharT> const & dst) const;

SST_F(char)
SST_F(wchar_t)

#undef SST_F

//----------------------------------------------------------------------

} // namespace sst

#endif // #if SST_WITH_WINDOWS_KERNEL32

#endif // SST_CATALOG_WINDOWS_PATH_HPP
