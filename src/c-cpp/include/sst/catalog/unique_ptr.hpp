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

#ifndef SST_CATALOG_UNIQUE_PTR_HPP
#define SST_CATALOG_UNIQUE_PTR_HPP

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/SST_DEFAULT_NOEXCEPT.hpp>
#include <sst/catalog/SST_NODISCARD.h>
#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/emplace.hpp>
#include <sst/catalog/emplace_t.hpp>

namespace sst {

// TODO: Don't derive from std::unique_ptr. We generally need more
//       control over the pointer and how destruction happens for
//       functions like emplace() etc.

template<class T>
class unique_ptr : std::unique_ptr<T> {

public:

  SST_STATIC_ASSERT(noexcept(std::declval<T>().~T()));

  using deleter_type = typename std::unique_ptr<T>::deleter_type;
  using element_type = typename std::unique_ptr<T>::element_type;
  using pointer = typename std::unique_ptr<T>::pointer;

  using std::unique_ptr<T>::get;
  using std::unique_ptr<T>::operator->;
  using std::unique_ptr<T>::release;
  using std::unique_ptr<T>::reset;

  //--------------------------------------------------------------------
  // Default operations
  //--------------------------------------------------------------------

public:

  unique_ptr() SST_DEFAULT_NOEXCEPT(true) = default;

  //--------------------------------------------------------------------
  // Basic construction
  //--------------------------------------------------------------------

  unique_ptr(std::nullptr_t) noexcept {
  }

  explicit unique_ptr(pointer p) noexcept
      : std::unique_ptr<T>(std::move(p)) {
  }

  template<class... Args>
  unique_ptr(sst::emplace_t, Args &&... args)
      : unique_ptr(new T(std::forward<Args>(args)...)) {
  }

  //--------------------------------------------------------------------
  // Copying
  //--------------------------------------------------------------------
  //
  // Note that std::unique_ptr does not provide any copy semantics.
  //

  unique_ptr(unique_ptr const & other)
      : unique_ptr(other.get() == nullptr ? nullptr : new T(*other)) {
  }

  unique_ptr(std::unique_ptr<T> const & other)
      : unique_ptr(other.get() == nullptr ? nullptr : new T(*other)) {
  }

  unique_ptr & operator=(unique_ptr const & other) {
    if (this != &other) {
      reset(other.get() == nullptr ? nullptr : new T(*other));
    }
    return *this;
  }

  unique_ptr & operator=(std::unique_ptr<T> const & other) {
    if (this != &other) {
      reset(other.get() == nullptr ? nullptr : new T(*other));
    }
    return *this;
  }

  //--------------------------------------------------------------------
  // Moving
  //--------------------------------------------------------------------

  unique_ptr(unique_ptr && other) noexcept
      : std::unique_ptr<T>(std::move(other)) {
  }

  unique_ptr(std::unique_ptr<T> && other) noexcept
      : std::unique_ptr<T>(std::move(other)) {
  }

  unique_ptr & operator=(unique_ptr && other) noexcept {
    if (this != &other) {
      reset(other.release());
    }
    return *this;
  }

  unique_ptr & operator=(std::unique_ptr<T> && other) noexcept {
    if (this != &other) {
      reset(other.release());
    }
    return *this;
  }

  //--------------------------------------------------------------------

  ~unique_ptr() noexcept {
  }

  //--------------------------------------------------------------------

  unique_ptr & operator=(std::nullptr_t) noexcept {
    reset();
    return *this;
  }

  //--------------------------------------------------------------------
  // emplace
  //--------------------------------------------------------------------

public:

  // TODO: If *this != nullptr and T has move assignment, then we should
  //       be able to use **this = T(std::forward<Args>(args)...).
  //       However, the move assignment MUST BE NOEXCEPT, otherwise an
  //       exception may corrupt **this, and this function should
  //       provide strong exception safety.
  // TODO: Should we provide behavior more like std::optional::emplace,
  //       where we always begin by destructing (if possible), and if an
  //       exception occurs (either from construction or allocation)
  //       then we leave ourselves reset? Does "emplace" generally mean
  //       "don't use any temporary storage, not even on the stack"? I
  //       guess then the caller can get it the above way by writing
  //       emplace(T(foo)) instead of emplace(foo). Yeah, I think
  //       "emplace" should generally mean "construct in the existing
  //       space".
  template<class... Args>
  T & emplace(Args &&... args) {
    *this = unique_ptr(sst::emplace, std::forward<Args>(args)...);
    return **this;
  }

  //--------------------------------------------------------------------
  // ensure
  //--------------------------------------------------------------------

public:

  template<class... Args>
  T & ensure(Args &&... args) {
    if (*this == nullptr) {
      emplace(std::forward<Args>(args)...);
    }
    return **this;
  }

  //--------------------------------------------------------------------
  //
  // Note that std::unique_ptr did not provide a noexcept specifier for
  // operator* until C++23.
  //

  SST_NODISCARD()
  typename std::add_lvalue_reference<T>::type operator*() const
      noexcept(noexcept(*std::declval<pointer>())) {
    SST_ASSERT(get() != nullptr);
    return *get();
  }

  //--------------------------------------------------------------------
  // Comparisons
  //--------------------------------------------------------------------

public:

  explicit operator bool() const noexcept {
    return get() != nullptr;
  }

  friend bool operator==(unique_ptr const & a,
                         std::nullptr_t) noexcept {
    return a.get() == nullptr;
  }

  friend bool operator==(std::nullptr_t,
                         unique_ptr const & b) noexcept {
    return nullptr == b.get();
  }

  friend bool operator!=(unique_ptr const & a,
                         std::nullptr_t) noexcept {
    return a.get() != nullptr;
  }

  friend bool operator!=(std::nullptr_t,
                         unique_ptr const & b) noexcept {
    return nullptr != b.get();
  }

  //--------------------------------------------------------------------
};

} // namespace sst

#endif // #ifndef SST_CATALOG_UNIQUE_PTR_HPP
