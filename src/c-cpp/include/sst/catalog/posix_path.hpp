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

#ifndef SST_CATALOG_POSIX_PATH_HPP
#define SST_CATALOG_POSIX_PATH_HPP

#include <sst/catalog/SST_WITH_POSIX.h>

#if SST_WITH_POSIX

#include <string>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/SST_DEFINE_BOOLEAN_TRAIT_1.hpp>
#include <sst/catalog/cbegin.hpp>
#include <sst/catalog/cend.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_byte.hpp>
#include <sst/catalog/is_input_iterator.hpp>
#include <sst/catalog/is_iterable.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/catalog/moved_from.hpp>
#include <sst/private/SST_DLL_EXPORT.h>

namespace sst {

class posix_path {

  //--------------------------------------------------------------------
  // value_type
  //--------------------------------------------------------------------

public:

  using value_type = char;

  //--------------------------------------------------------------------
  // value_type_ok
  //--------------------------------------------------------------------
  //
  // Determines whether a type T is OK to convert to value_type.
  //

private:

  SST_DEFINE_BOOLEAN_TRAIT_1(value_type_ok,
                             T,
                             (std::is_convertible<T, value_type>::value
                              || (std::is_same<value_type, char>::value
                                  && sst::is_byte<T>::value)))

  //--------------------------------------------------------------------
  // construct-from-iterable
  //--------------------------------------------------------------------

public:

  template<
      class Src,
      sst::enable_if_t<sst::is_iterable<Src, value_type_ok>::value> = 0>
  posix_path(Src const & src, bool const follow_links = true)
      : posix_path(sst::cbegin(src), sst::cend(src), follow_links) {
  }

  //--------------------------------------------------------------------
  // construct-from-iterator
  //--------------------------------------------------------------------

public:

  template<
      class Src,
      class End,
      sst::enable_if_t<sst::is_input_iterator<Src, value_type_ok>::value
                       && sst::is_sentinel<End, Src>::value> = 0>
  posix_path(Src src, End const & end, bool const follow_links = true)
      : follow_links_(follow_links) {
    for (; !(src == end); ++src) {
      value_type const c = static_cast<value_type>(*src);
      if (c == 0) {
        break;
      }
      str_ += c;
    }
  }

  //--------------------------------------------------------------------
  // construct-from-pointer
  //--------------------------------------------------------------------

public:

  template<class T, sst::enable_if_t<value_type_ok<T>::value> = 0>
  posix_path(T const * const path, bool const follow_links = true)
      : follow_links_(follow_links),
        str_((SST_ASSERT((path != nullptr)),
              reinterpret_cast<value_type const *>(path))) {
  }

  //--------------------------------------------------------------------
  // construct-from-std-string-lvalue
  //--------------------------------------------------------------------

public:

  posix_path(std::basic_string<value_type> const & path,
             bool const follow_links = true)
      : follow_links_(follow_links),
        str_(path) {
  }

  //--------------------------------------------------------------------
  // construct-from-std-string-rvalue
  //--------------------------------------------------------------------

public:

  posix_path(std::basic_string<value_type> && path,
             bool follow_links = true)
      : follow_links_(follow_links),
        str_(std::move(path)) {
  }

  //--------------------------------------------------------------------
  // construct-moved-from
  //--------------------------------------------------------------------

public:

  posix_path() : moved_from_(true) {
  }

  //--------------------------------------------------------------------
  // copy-assign
  //--------------------------------------------------------------------

public:

  posix_path & operator=(posix_path const & other) {
    if (this != &other) {
      *this = posix_path(other);
    }
    return *this;
  }

  //--------------------------------------------------------------------
  // copy-construct
  //--------------------------------------------------------------------

public:

  posix_path(posix_path const & other)
      : follow_links_(other.follow_links_),
        moved_from_(other.moved_from_),
        str_(other.str_),
        have_test_d_(other.have_test_d_),
        test_d_(other.test_d_),
        have_test_e_(other.have_test_e_),
        test_e_(other.test_e_),
        have_test_f_(other.have_test_f_),
        test_f_(other.test_f_),
        will_refresh_(other.will_refresh_) {
  }

  //--------------------------------------------------------------------
  // destruct
  //--------------------------------------------------------------------

public:

  ~posix_path() noexcept {
  }

  //--------------------------------------------------------------------
  // directory_char
  //--------------------------------------------------------------------

public:

  static constexpr value_type directory_char() noexcept {
    return value_type('/');
  }

  //--------------------------------------------------------------------
  // follow_links
  //--------------------------------------------------------------------
  //
  // Indicates whether this path object will follow symbolic links when
  // performing a refresh.
  //

private:

  bool follow_links_ = true;

public:

  bool follow_links() const {
    SST_ASSERT((!moved_from_));
    return follow_links_;
  }

  posix_path & follow_links(bool const x) {
    SST_ASSERT((!moved_from_));
    if (x != follow_links_) {
      follow_links_ = x;
      will_refresh_ = true;
    }
    return *this;
  }

  //--------------------------------------------------------------------
  // move-assign
  //--------------------------------------------------------------------

public:

  posix_path & operator=(posix_path && other) noexcept {
    if (this != &other) {
      follow_links_ = std::move(other.follow_links_);
      moved_from_ = std::move(other.moved_from_);
      str_ = std::move(other.str_);
      have_test_d_ = std::move(other.have_test_d_);
      test_d_ = std::move(other.test_d_);
      have_test_e_ = std::move(other.have_test_e_);
      test_e_ = std::move(other.test_e_);
      have_test_f_ = std::move(other.have_test_f_);
      test_f_ = std::move(other.test_f_);
      will_refresh_ = std::move(other.will_refresh_);
    }
    return *this;
  }

  //--------------------------------------------------------------------
  // move-construct
  //--------------------------------------------------------------------

public:

  posix_path(posix_path && other) noexcept
      : follow_links_(std::move(other.follow_links_)),
        moved_from_(std::move(other.moved_from_)),
        str_(std::move(other.str_)),
        have_test_d_(std::move(other.have_test_d_)),
        test_d_(std::move(other.test_d_)),
        have_test_e_(std::move(other.have_test_e_)),
        test_e_(std::move(other.test_e_)),
        have_test_f_(std::move(other.have_test_f_)),
        test_f_(std::move(other.test_f_)),
        will_refresh_(std::move(other.will_refresh_)) {
  }

  //--------------------------------------------------------------------
  // moved_from_
  //--------------------------------------------------------------------

private:

  sst::moved_from moved_from_;

  //--------------------------------------------------------------------
  // operator-std-string
  //--------------------------------------------------------------------

public:

  operator std::basic_string<value_type> const &() const {
    SST_ASSERT((!moved_from_));
    return str_;
  }

  //--------------------------------------------------------------------
  // path_list_char
  //--------------------------------------------------------------------
  //
  // The character that is conventionally used to separate paths in a
  // list of paths. This is ';' on Windows and ':' elsewhere.
  //

  static constexpr value_type path_list_char() noexcept {
    return value_type(':');
  }

  //--------------------------------------------------------------------
  // refresh
  //--------------------------------------------------------------------

private:

  template<class GetFileAttributesExFunc,
           class CreateFileFunc,
           class GetFinalPathNameByHandleFunc>
  posix_path & refresh_core(
      GetFileAttributesExFunc && GetFileAttributesEx_func,
      char const * const GetFileAttributesEx_name,
      CreateFileFunc && CreateFile_func,
      char const * const CreateFile_name,
      GetFinalPathNameByHandleFunc && GetFinalPathNameByHandle_func,
      char const * const GetFinalPathNameByHandle_name);

public:

  posix_path & refresh();

  //--------------------------------------------------------------------
  // refresh_from_dirent
  //--------------------------------------------------------------------

public:

  posix_path & refresh_from_dirent(void const * data);

  //--------------------------------------------------------------------
  // refresh_from_stat
  //--------------------------------------------------------------------

public:

  posix_path & refresh_from_stat(void const * data);

  //--------------------------------------------------------------------
  // str
  //--------------------------------------------------------------------
  //
  // TODO: Add a non-const variant so we can steal just the path?
  //

private:

  std::basic_string<value_type> str_;

public:

  std::basic_string<value_type> const & str() const {
    SST_ASSERT((!moved_from_));
    return str_;
  }

  //--------------------------------------------------------------------
  // test_d
  //--------------------------------------------------------------------

private:

  bool have_test_d_ = false;
  bool test_d_{};

public:

  bool test_d() {
    SST_ASSERT((!moved_from_));
    if (!have_test_d_ || will_refresh_) {
      refresh();
    }
    SST_ASSERT((have_test_d_));
    return test_d_;
  }

  //--------------------------------------------------------------------
  // test_e
  //--------------------------------------------------------------------

private:

  bool have_test_e_ = false;
  bool test_e_{};

public:

  bool test_e() {
    SST_ASSERT((!moved_from_));
    if (!have_test_e_ || will_refresh_) {
      refresh();
    }
    SST_ASSERT((have_test_e_));
    return test_e_;
  }

  //--------------------------------------------------------------------
  // test_f
  //--------------------------------------------------------------------

private:

  bool have_test_f_ = false;
  bool test_f_{};

public:

  bool test_f() {
    SST_ASSERT((!moved_from_));
    if (!have_test_f_ || will_refresh_) {
      refresh();
    }
    SST_ASSERT((have_test_f_));
    return test_f_;
  }

  //--------------------------------------------------------------------
  // will_refresh
  //--------------------------------------------------------------------

private:

  bool will_refresh_ = true;

public:

  bool will_refresh() const {
    SST_ASSERT((!moved_from_));
    return will_refresh_;
  }

  posix_path & will_refresh(bool const x) {
    SST_ASSERT((!moved_from_));
    will_refresh_ = x;
    return *this;
  }

}; //

} // namespace sst

#endif // #if SST_WITH_POSIX

#endif // #ifndef SST_CATALOG_POSIX_PATH_HPP
