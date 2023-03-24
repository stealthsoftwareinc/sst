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

#ifndef SST_CATALOG_OPTIONAL_HPP
#define SST_CATALOG_OPTIONAL_HPP

#include <type_traits>
#include <utility>

#include <sst/catalog/SST_CONSTEXPR_ASSERT.hpp>
#include <sst/catalog/SST_CPP14_CONSTEXPR.hpp>
#include <sst/catalog/SST_NODISCARD.h>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/monostate.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {

namespace guts {
namespace optional {

//----------------------------------------------------------------------

template<class, class = sst::enable_t>
struct storage;

template<class T>
struct storage<
    T,
    sst::enable_if_t<std::is_trivially_destructible<T>::value>> {
  union {
    T value_;
    sst::monostate dummy_;
  };
  bool has_value_ = false;
  constexpr storage() noexcept : dummy_() {
  }
protected:
  void destruct_value() noexcept {
    // A trivial destructor never needs to be called.
  }
};

template<class T>
struct storage<
    T,
    sst::enable_if_t<!std::is_trivially_destructible<T>::value>> {
  union {
    T value_;
    sst::monostate dummy_;
  };
  bool has_value_ = false;
  constexpr storage() noexcept : dummy_() {
  }
  ~storage() noexcept {
    if (has_value_) {
      destruct_value();
    }
  }
protected:
  void destruct_value() noexcept {
    // Avoid a try block when the destructor is noexcept.
    if (noexcept(value_.~T())) {
      value_.~T();
    } else {
      try {
        value_.~T();
      } catch (...) {
      }
    }
  }
};

//----------------------------------------------------------------------

template<class T>
struct add_reset : storage<T> {
  void reset() noexcept {
    if (this->has_value_) {
      this->destruct_value();
      this->has_value_ = false;
    }
  }
};

//----------------------------------------------------------------------

template<class, class = sst::enable_t>
struct copy_construct;

template<class T>
struct copy_construct<
    T,
    sst::enable_if_t<!std::is_copy_constructible<T>::value>>
    : add_reset<T> {
  copy_construct() = default;
  copy_construct(copy_construct const &) = delete;
  copy_construct & operator=(copy_construct const &) = default;
  copy_construct(copy_construct &&) = default;
  copy_construct & operator=(copy_construct &&) = default;
  ~copy_construct() = default;
};

template<class T>
struct copy_construct<
    T,
    sst::enable_if_t<std::is_trivially_copy_constructible<T>::value>>
    : add_reset<T> {};

template<class T>
struct copy_construct<
    T,
    sst::enable_if_t<
        std::is_copy_constructible<T>::value
        && !std::is_trivially_copy_constructible<T>::value>>
    : add_reset<T> {
  copy_construct() = default;
  copy_construct(copy_construct const & other) noexcept(
      SST_NOEXCEPT(T(std::declval<T &>()))) {
    if (other.has_value_) {
      new (&this->value_) T(other.value_);
      this->has_value_ = true;
    }
  }
  copy_construct & operator=(copy_construct const &) = default;
  copy_construct(copy_construct &&) = default;
  copy_construct & operator=(copy_construct &&) = default;
  ~copy_construct() = default;
};

//----------------------------------------------------------------------

template<class, class = sst::enable_t>
struct copy_assign;

template<class T>
struct copy_assign<T,
                   sst::enable_if_t<!std::is_copy_assignable<T>::value>>
    : copy_construct<T> {
  copy_assign() = default;
  copy_assign(copy_assign const &) = default;
  copy_assign & operator=(copy_assign const &) = delete;
  copy_assign(copy_assign &&) = default;
  copy_assign & operator=(copy_assign &&) = default;
  ~copy_assign() = default;
};

template<class T>
struct copy_assign<
    T,
    sst::enable_if_t<std::is_trivially_copy_assignable<T>::value>>
    : copy_construct<T> {};

template<class T>
struct copy_assign<
    T,
    sst::enable_if_t<std::is_copy_assignable<T>::value
                     && !std::is_trivially_copy_assignable<T>::value>>
    : copy_construct<T> {
  copy_assign() = default;
  copy_assign(copy_assign const &) = default;
  copy_assign & operator=(copy_assign const & other) noexcept(
      SST_NOEXCEPT(std::declval<T &>() = std::declval<T &>(),
                   T(std::declval<T &>()))) {
    if (this->has_value_) {
      if (other.has_value_) {
        this->value_ = other.value_;
      } else {
        this->reset();
      }
    } else if (other.has_value_) {
      new (&this->value_) T(other.value_);
      this->has_value_ = true;
    }
  }
  copy_assign(copy_assign &&) = default;
  copy_assign & operator=(copy_assign &&) = default;
  ~copy_assign() = default;
};

//----------------------------------------------------------------------

template<class, class = sst::enable_t>
struct move_construct;

template<class T>
struct move_construct<
    T,
    sst::enable_if_t<!std::is_move_constructible<T>::value>>
    : copy_assign<T> {
  move_construct() = default;
  move_construct(move_construct const &) = default;
  move_construct & operator=(move_construct const &) = default;
  move_construct(move_construct &&) = delete;
  move_construct & operator=(move_construct &&) = default;
  ~move_construct() = default;
};

template<class T>
struct move_construct<
    T,
    sst::enable_if_t<std::is_trivially_move_constructible<T>::value>>
    : copy_assign<T> {};

template<class T>
struct move_construct<
    T,
    sst::enable_if_t<
        std::is_move_constructible<T>::value
        && !std::is_trivially_move_constructible<T>::value>>
    : copy_assign<T> {
  move_construct() = default;
  move_construct(move_construct const &) = default;
  move_construct & operator=(move_construct const &) = default;
  move_construct(move_construct && other) noexcept(
      SST_NOEXCEPT(T(std::declval<T &&>()))) {
    if (other.has_value_) {
      new (&this->value_) T(std::move(other.value_));
      this->has_value_ = true;
      other.reset();
    }
  }
  move_construct & operator=(move_construct &&) = default;
  ~move_construct() = default;
};

//----------------------------------------------------------------------

template<class, class = sst::enable_t>
struct move_assign;

template<class T>
struct move_assign<T,
                   sst::enable_if_t<!std::is_move_assignable<T>::value>>
    : move_construct<T> {
  move_assign() = default;
  move_assign(move_assign const &) = default;
  move_assign & operator=(move_assign const &) = default;
  move_assign(move_assign &&) = default;
  move_assign & operator=(move_assign &&) = delete;
  ~move_assign() = default;
};

template<class T>
struct move_assign<
    T,
    sst::enable_if_t<std::is_trivially_move_assignable<T>::value>>
    : move_construct<T> {};

template<class T>
struct move_assign<
    T,
    sst::enable_if_t<std::is_move_assignable<T>::value
                     && !std::is_trivially_move_assignable<T>::value>>
    : move_construct<T> {
  move_assign() = default;
  move_assign(move_assign const &) = default;
  move_assign & operator=(move_assign const &) = default;
  move_assign(move_assign &&) = default;
  move_assign & operator=(move_assign && other) noexcept(
      SST_NOEXCEPT(std::declval<T &>() = std::declval<T &&>(),
                   T(std::declval<T &&>()))) {
    if (this->has_value_) {
      if (other.has_value_) {
        this->value_ = std::move(other.value_);
      } else {
        this->reset();
      }
    } else if (other.has_value_) {
      new (&this->value_) T(std::move(other.value_));
      this->has_value_ = true;
      other.reset();
    }
  }
  ~move_assign() = default;
};

//----------------------------------------------------------------------

} // namespace optional
} // namespace guts

template<class T>
class optional : sst::guts::optional::move_assign<T> {

  using base = sst::guts::optional::move_assign<T>;

  //--------------------------------------------------------------------

  template<class>
  struct is_optional : std::false_type {};

  template<class U>
  struct is_optional<optional<U>> : std::true_type {};

  //--------------------------------------------------------------------

public:

  using value_type = T;

  //--------------------------------------------------------------------
  // Default operations
  //--------------------------------------------------------------------

public:

  optional() = default;
  optional(optional const &) = default;
  optional & operator=(optional const &) = default;
  optional(optional &&) = default;
  optional & operator=(optional &&) = default;
  ~optional() = default;

  //--------------------------------------------------------------------
  // Existence retrieval
  //--------------------------------------------------------------------

public:

  SST_NODISCARD() constexpr bool has_value() const noexcept {
    return this->has_value_;
  }

  SST_NODISCARD() constexpr explicit operator bool() const noexcept {
    return this->has_value_;
  }

  //--------------------------------------------------------------------
  // Value retrieval
  //--------------------------------------------------------------------

public:

  SST_CPP14_CONSTEXPR
  T & value() noexcept {
    SST_CONSTEXPR_ASSERT((this->has_value_));
    return this->value_;
  }

  constexpr T const & value() const noexcept {
    SST_CONSTEXPR_ASSERT((this->has_value_));
    return this->value_;
  }

  SST_NODISCARD()
  SST_CPP14_CONSTEXPR
  T & operator*() noexcept {
    SST_CONSTEXPR_ASSERT((this->has_value_));
    return this->value_;
  }

  SST_NODISCARD() constexpr T const & operator*() const noexcept {
    SST_CONSTEXPR_ASSERT((this->has_value_));
    return this->value_;
  }

  SST_NODISCARD()
  SST_CPP14_CONSTEXPR
  T * operator->() noexcept {
    SST_CONSTEXPR_ASSERT((this->has_value_));
    return &this->value_;
  }

  SST_NODISCARD() constexpr T const * operator->() const noexcept {
    SST_CONSTEXPR_ASSERT((this->has_value_));
    return &this->value_;
  }

  //--------------------------------------------------------------------
  // Construction from a value
  //--------------------------------------------------------------------

public:

  template<class U,
           sst::enable_if_t<
               std::is_convertible<U &&, T>::value
               && !is_optional<sst::remove_cvref_t<U>>::value> = 0>
  SST_CPP14_CONSTEXPR optional(U && value) noexcept(
      SST_NOEXCEPT(T(std::forward<U>(value)))) {
    new (&this->value_) T(std::forward<U>(value));
    this->has_value_ = true;
  }

  template<class U,
           sst::enable_if_t<
               !std::is_convertible<U &&, T>::value
               && std::is_constructible<T, U &&>::value
               && !is_optional<sst::remove_cvref_t<U>>::value> = 0>
  SST_CPP14_CONSTEXPR explicit optional(U && value) noexcept(
      SST_NOEXCEPT(T(std::forward<U>(value)))) {
    new (&this->value_) T(std::forward<U>(value));
    this->has_value_ = true;
  }

  //--------------------------------------------------------------------
  // Assignment from a value
  //--------------------------------------------------------------------

public:

  template<class U,
           sst::enable_if_t<
               std::is_assignable<T &, U &&>::value
               && !is_optional<sst::remove_cvref_t<U>>::value> = 0>
  optional & operator=(U && value) {
    if (this->has_value_) {
      this->value_ = std::forward<U>(value);
    } else {
      new (&this->value_) T(std::forward<U>(value));
      this->has_value_ = true;
    }
    return *this;
  }

  //--------------------------------------------------------------------
  // emplace
  //--------------------------------------------------------------------
  //
  // Resets, then tries to construct in-place.
  //

public:

  template<class... Args>
  T & emplace(Args &&... args) {
    this->reset();
    new (&this->value_) T(std::forward<Args>(args)...);
    this->has_value_ = true;
    return this->value_;
  }

  //--------------------------------------------------------------------
  // reset
  //--------------------------------------------------------------------

public:

  using base::reset;

  //--------------------------------------------------------------------
};

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <type_traits>
#include <vector>

#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/monostate.hpp>

SST_STATIC_ASSERT(
    (!std::is_trivially_constructible<sst::optional<int>>::value));
SST_STATIC_ASSERT(
    (std::is_trivially_copy_constructible<sst::optional<int>>::value));
SST_STATIC_ASSERT(
    (std::is_trivially_copy_assignable<sst::optional<int>>::value));
SST_STATIC_ASSERT(
    (std::is_trivially_move_constructible<sst::optional<int>>::value));
SST_STATIC_ASSERT(
    (std::is_trivially_move_assignable<sst::optional<int>>::value));
SST_STATIC_ASSERT(
    (std::is_trivially_destructible<sst::optional<int>>::value));

SST_STATIC_ASSERT((!std::is_trivially_constructible<
                   sst::optional<sst::monostate>>::value));
SST_STATIC_ASSERT((std::is_trivially_copy_constructible<
                   sst::optional<sst::monostate>>::value));
SST_STATIC_ASSERT((std::is_trivially_copy_assignable<
                   sst::optional<sst::monostate>>::value));
SST_STATIC_ASSERT((std::is_trivially_move_constructible<
                   sst::optional<sst::monostate>>::value));
SST_STATIC_ASSERT((std::is_trivially_move_assignable<
                   sst::optional<sst::monostate>>::value));
SST_STATIC_ASSERT((std::is_trivially_destructible<
                   sst::optional<sst::monostate>>::value));

SST_STATIC_ASSERT((!std::is_trivially_constructible<
                   sst::optional<std::vector<int>>>::value));
SST_STATIC_ASSERT((!std::is_trivially_copy_constructible<
                   sst::optional<std::vector<int>>>::value));
SST_STATIC_ASSERT((!std::is_trivially_copy_assignable<
                   sst::optional<std::vector<int>>>::value));
SST_STATIC_ASSERT((!std::is_trivially_move_constructible<
                   sst::optional<std::vector<int>>>::value));
SST_STATIC_ASSERT((!std::is_trivially_move_assignable<
                   sst::optional<std::vector<int>>>::value));
SST_STATIC_ASSERT((!std::is_trivially_destructible<
                   sst::optional<std::vector<int>>>::value));

#endif // #if SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // #ifndef SST_CATALOG_OPTIONAL_HPP
