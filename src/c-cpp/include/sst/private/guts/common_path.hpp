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

#ifndef SST_PRIVATE_GUTS_COMMON_PATH_HPP
#define SST_PRIVATE_GUTS_COMMON_PATH_HPP

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_DEFINE_BOOLEAN_TRAIT_1.hpp>
#include <sst/catalog/SST_NODISCARD.hpp>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/c_quote.hpp>
#include <sst/catalog/c_str.hpp>
#include <sst/catalog/cbegin.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_bool.hpp>
#include <sst/catalog/is_byte.hpp>
#include <sst/catalog/is_input_iterator.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_iterable.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/catalog/is_value_sentinel.hpp>
#include <sst/catalog/moved_from.hpp>
#include <sst/catalog/optional.hpp>
#include <sst/catalog/peek.hpp>
#include <sst/catalog/pos.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/size.hpp>
#include <sst/catalog/step.hpp>
#include <sst/catalog/value_sentinel.hpp>
#include <sst/catalog/value_type_t.hpp>

namespace sst {
namespace guts {

template<class Path, class CharT>
class common_path {

  //--------------------------------------------------------------------
  // Types
  //--------------------------------------------------------------------

public:

  using char_t = CharT;
  using string_t = std::basic_string<char_t>;
  using value_type = char_t;

private:

  // Determines whether a type T makes sense to convert to char_t.
  SST_DEFINE_BOOLEAN_TRAIT_1(is_char_t_ish,
                             T,
                             (std::is_same<T, char_t>::value
                              || (std::is_same<char_t, char>::value
                                  && sst::is_byte<T>::value)))

  //--------------------------------------------------------------------
  // Moved-from detection
  //--------------------------------------------------------------------

protected:

  sst::moved_from moved_from_;

  //--------------------------------------------------------------------
  // String storage
  //--------------------------------------------------------------------
  //
  // A path object either stores its own string (str_) or wraps a C
  // string (c_str_). If c_str_ is null, then str_ applies. Otherwise,
  // c_str_ applies, in which case str_ may have leftover memory ready
  // to use if str() is called. Calling str() when c_str_ applies will
  // copy c_str_ into str_ and set c_str_ to null.
  //
  // The reason for having c_str_ is for performance when there's no
  // need to make a copy of the string. This is typically only used by
  // code that needs to do large numbers of file operations. Most code
  // can get away with the simpler approach of just making copies.
  //

private:

  mutable string_t str_;
  mutable char_t const * c_str_ = nullptr;

public:

  SST_NODISCARD() string_t const & str() const {
    SST_ASSERT((!this->moved_from_));
    if (this->c_str_ != nullptr) {
      this->str_ = this->c_str_;
      this->c_str_ = nullptr;
    }
    return this->str_;
  }

  SST_NODISCARD() char_t const * c_str() const noexcept {
    SST_ASSERT((!this->moved_from_));
    if (this->c_str_ != nullptr) {
      return this->c_str_;
    }
    return this->str_.c_str();
  }

  //--------------------------------------------------------------------
  // Symbolic link behavior
  //--------------------------------------------------------------------
  //
  // This value controls whether symbolic links will be followed when
  // attributes are queried from disk. Changing this value will clear
  // all cached attributes.
  //

private:

  bool follow_links_ = true;

public:

  SST_NODISCARD() bool follow_links() const noexcept {
    SST_ASSERT((!this->moved_from_));
    return follow_links_;
  }

  Path & follow_links(bool const x) noexcept {
    SST_ASSERT((!this->moved_from_));
    if (x != this->follow_links_) {
      this->follow_links_ = x;
      this->clear_cache();
    }
    return static_cast<Path &>(*this);
  }

  //--------------------------------------------------------------------
  // Default operations
  //--------------------------------------------------------------------

protected:

  common_path() noexcept : moved_from_(true) {
  }

  ~common_path() SST_NOEXCEPT(true) = default;

  common_path(common_path const &) = default;

  common_path(common_path &&) SST_NOEXCEPT(true) = default;

  common_path & operator=(common_path const &) = default;

  common_path & operator=(common_path &&) SST_NOEXCEPT(true) = default;

  //--------------------------------------------------------------------
  // Construction
  //--------------------------------------------------------------------

private:

  struct wrap_tag {};

  explicit common_path(wrap_tag,
                       char_t const * const src,
                       bool const follow_links)
      : c_str_((SST_ASSERT((src != nullptr)), src)),
        follow_links_(follow_links) {
  }

public:

  template<
      class Src,
      class End,
      sst::enable_if_t<sst::is_input_iterator<Src, is_char_t_ish>::value
                       && (sst::is_sentinel<End, Src>::value
                           || sst::is_value_sentinel<End, Src>::value
                           || (sst::is_integer_ish<End>::value
                               && !sst::is_bool<End>::value))> = 0>
  explicit common_path(Src src,
                       End const & end,
                       bool const follow_links = true)
      : follow_links_(follow_links) {
    sst::pos<Src, End> pos;
    while (true) {
      auto const p = sst::peek(src, end, pos);
      if (!p) {
        break;
      }
      this->str_ += static_cast<char_t>(*p);
      sst::step(src, end, pos);
    }
  }

  template<class Src,
           sst::enable_if_t<
               sst::is_input_iterator<Src, is_char_t_ish>::value> = 0>
  explicit common_path(Src src, bool const follow_links)
      : common_path(std::move(src),
                    sst::value_sentinel(sst::value_type_t<Src>()),
                    follow_links) {
  }

  template<class Src,
           sst::enable_if_t<
               sst::is_input_iterator<Src, is_char_t_ish>::value
               && !std::is_convertible<Src, string_t &&>::value> = 0>
  common_path(Src src) : common_path(std::move(src), true) {
  }

  template<
      class Src,
      class End,
      sst::enable_if_t<sst::is_iterable<Src, is_char_t_ish>::value
                       && (sst::is_sentinel<End, Src>::value
                           || sst::is_value_sentinel<End, Src>::value
                           || (sst::is_integer_ish<End>::value
                               && !sst::is_bool<End>::value))> = 0>
  explicit common_path(Src const & src,
                       End const & end,
                       bool const follow_links = true)
      : common_path(sst::cbegin(src), end, follow_links) {
  }

  template<
      class Src,
      sst::enable_if_t<sst::is_iterable<Src, is_char_t_ish>::value> = 0>
  explicit common_path(Src const & src, bool const follow_links)
      : common_path(src, sst::size(src), follow_links) {
  }

  template<
      class Src,
      sst::enable_if_t<
          sst::is_iterable<Src, is_char_t_ish>::value
          && !std::is_convertible<Src const &, string_t &&>::value> = 0>
  common_path(Src const & src) : common_path(src, true) {
  }

  explicit common_path(string_t && path, bool follow_links)
      : str_(std::move(path)),
        follow_links_(follow_links) {
  }

  common_path(string_t && path) : common_path(std::move(path), true) {
  }

  template<class Src,
           class P = decltype(sst::c_str(std::declval<Src &&>())),
           sst::enable_if_t<
               std::is_convertible<P, char_t const *>::value> = 0>
  SST_NODISCARD()
  static Path wrap(Src && src, bool const follow_links = true) {
    char_t const * const p = sst::c_str(std::forward<Src>(src));
    SST_ASSERT((p != nullptr));
    return Path(wrap_tag(), p, follow_links);
  }

  //--------------------------------------------------------------------
  // Attributes
  //--------------------------------------------------------------------
  //
  // A path object caches attributes about the path, which are lazily
  // queried from disk by the getter functions defined below. A cache
  // miss for a single attribute always causes all attributes to be
  // queried from disk, not just that single attribute.
  //
  // The query*() functions, which are defined by subclasses of this
  // class, can be used to force various subsets of attributes to be
  // queried from disk, with each attribute being either added to or
  // validated against the cache. Calling query() with no parameters
  // always queries all attributes from disk.
  //
  // The clear_cache() function, which is defined below, can be used to
  // clear all cached attributes.
  //
  // The attributes are as follows:
  //
  //    test_e
  //       True if this path exists.
  //
  //    test_d
  //       True if this path exists and is a directory.
  //
  //    test_f
  //       True if this path exists and is a regular file.
  //
  //    f_size
  //       The size of this file. If test_e is false, this value
  //       is zero. Otherwise, if test_f is true, this value is
  //       the size of the file. Otherwise, the meaning of this
  //       value is unspecified.
  //

protected:

  mutable sst::optional<bool> test_e_;
  mutable sst::optional<bool> test_d_;
  mutable sst::optional<bool> test_f_;
  mutable sst::optional<std::uintmax_t> f_size_;

public:

#define SST_F(X)                                                       \
                                                                       \
  SST_NODISCARD()                                                      \
  auto X() const->sst::remove_cvref_t<decltype(*this->X##_)> {         \
    SST_ASSERT((!this->moved_from_));                                  \
    if (!this->X##_) {                                                 \
      const_cast<Path &>(static_cast<Path const &>(*this)).query();    \
    }                                                                  \
    SST_ASSERT((this->X##_));                                          \
    return *this->X##_;                                                \
  }

  SST_F(test_e)
  SST_F(test_d)
  SST_F(test_f)
  SST_F(f_size)

#undef SST_F

  Path & clear_cache() noexcept {
    SST_ASSERT((!this->moved_from_));
    this->test_e_.reset();
    this->test_d_.reset();
    this->test_f_.reset();
    this->f_size_.reset();
    return static_cast<Path &>(*this);
  }

  //--------------------------------------------------------------------
  // mv
  //--------------------------------------------------------------------

private:

  void mv_into(Path dst) const {
    Path const & src = static_cast<Path const &>(*this);
    SST_ASSERT((!src.moved_from_));
    SST_ASSERT((!dst.moved_from_));
    SST_ASSERT((dst.test_d()));
    char_t const * const a = src.c_str();
    string_t & b = const_cast<string_t &>(dst.str());
    SST_ASSERT((!b.empty()));
    if (!Path::is_dir_char(b.back())) {
      b += Path::dir_char();
    }
    std::size_t i = std::size_t(0);
    while (Path::is_dir_char(a[i])) {
      ++i;
    }
    if (a[i] == char_t('\0')) {
      throw std::runtime_error("Unable to infer path basename: "
                               + sst::c_quote(a));
    }
    while (true) {
      std::size_t j = i;
      while (!Path::is_dir_char(a[j]) && a[j] != char_t('\0')) {
        ++j;
      }
      std::size_t k = j;
      while (Path::is_dir_char(a[k])) {
        ++k;
      }
      if (a[k] == char_t('\0')) {
        b.insert(b.end(), &a[i], &a[j]);
        break;
      }
      i = k;
    }
    dst.clear_cache();
    if (dst.test_d()) {
      throw std::runtime_error("Directory already exists: "
                               + sst::c_quote(b));
    }
    src.mv_onto(std::move(dst));
  }

  template<class Dst>
  Path const & mv_helper(Dst && dst) const {
    Path const & src = static_cast<Path const &>(*this);
    SST_ASSERT((!src.moved_from_));
    SST_ASSERT((!dst.moved_from_));
    if (dst.test_d()) {
      src.mv_into(std::forward<Dst>(dst));
    } else {
      src.mv_onto(std::forward<Dst>(dst));
    }
    return src;
  }

  Path & mv_out() {
    Path & src = static_cast<Path &>(*this);
    SST_ASSERT((!src.moved_from_));
    src.test_e_.emplace(false);
    src.test_d_.emplace(false);
    src.test_f_.emplace(false);
    src.f_size_.emplace(std::uintmax_t(0));
    return src;
  }

public:

  Path const & mv(Path & dst) const {
    Path const & src = static_cast<Path const &>(*this);
    SST_ASSERT((!src.moved_from_));
    SST_ASSERT((!dst.moved_from_));
    src.mv_helper(dst);
    dst.test_e_ = src.test_e_;
    dst.test_d_ = src.test_d_;
    dst.test_f_ = src.test_f_;
    dst.f_size_ = src.f_size_;
    return src;
  }

  Path const & mv(Path const & dst) const {
    return this->mv_helper(dst);
  }

  Path const & mv(Path && dst) const {
    return this->mv_helper(std::move(dst));
  }

  template<class Dst,
           class P = decltype(sst::c_str(std::declval<Dst &&>())),
           sst::enable_if_t<
               !std::is_same<sst::remove_cvref_t<Dst &&>, Path>::value
               && std::is_convertible<P, char_t const *>::value> = 0>
  Path const & mv(Dst && dst) const {
    char_t const * const p = sst::c_str(std::forward<Dst>(dst));
    SST_ASSERT((p != nullptr));
    return this->mv(Path::wrap(p));
  }

  Path & mv(Path & dst) {
    const_cast<common_path const &>(*this).mv(dst);
    return this->mv_out();
  }

  Path & mv(Path const & dst) {
    const_cast<common_path const &>(*this).mv(dst);
    return this->mv_out();
  }

  Path & mv(Path && dst) {
    const_cast<common_path const &>(*this).mv(std::move(dst));
    return this->mv_out();
  }

  template<class Dst,
           class P = decltype(sst::c_str(std::declval<Dst &&>())),
           sst::enable_if_t<
               !std::is_same<sst::remove_cvref_t<Dst &&>, Path>::value
               && std::is_convertible<P, char_t const *>::value> = 0>
  Path & mv(Dst && dst) {
    const_cast<common_path const &>(*this).mv(std::forward<Dst>(dst));
    return this->mv_out();
  }

  //--------------------------------------------------------------------
};

} // namespace guts
} // namespace sst

#endif // SST_PRIVATE_GUTS_COMMON_PATH_HPP
