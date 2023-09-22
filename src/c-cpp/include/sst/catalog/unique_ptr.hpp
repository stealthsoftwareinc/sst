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

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_COMPILES.hpp>
#include <sst/catalog/SST_DEFINE_BOOLEAN_TRAIT.hpp>
#include <sst/catalog/SST_NODISCARD.hpp>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/SST_NOEXCEPT_OR.hpp>
#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/in_place_t.hpp>

namespace sst {

template<class T>
class unique_ptr {

  //--------------------------------------------------------------------
  // Types
  //--------------------------------------------------------------------

public:

  SST_STATIC_ASSERT((std::is_object<T>::value));
  SST_STATIC_ASSERT((!std::is_const<T>::value));
  SST_STATIC_ASSERT((!std::is_volatile<T>::value));

  using element_type = T;

  using pointer = T *;

  //--------------------------------------------------------------------
  // Data
  //--------------------------------------------------------------------

private:

  T * p_ = nullptr;

  //--------------------------------------------------------------------
  // copy
  //--------------------------------------------------------------------

private:

  template<class PointerIsh>
  SST_NODISCARD()
  static T * copy(PointerIsh const & p) {
    return p ? new T(*p) : nullptr;
  }

  //--------------------------------------------------------------------
  // emplace
  //--------------------------------------------------------------------
  //
  // If the pointer is null, allocates and constructs the object,
  // forwarding the arguments to the constructor. Otherwise, if the
  // arguments are valid for operator=, calls operator=, forwarding the
  // arguments to the call. Otherwise, deconstructs and reconstructs the
  // object in place, forwarding the arguments to the constructor. If
  // any exception is thrown, destructs and deallocates the object
  // before rethrowing. Returns a reference to the object.
  //

private:

  SST_DEFINE_BOOLEAN_TRAIT(can_assign,
                           (class(X), class(Args, ...)),
                           (SST_COMPILES(std::declval<X &>().operator=(
                               std::declval<Args>()...))));

public:

  template<class X = T,
           class... Args,
           sst::enable_if_t<can_assign<X, Args...>::value> = 0>
  T & emplace(Args &&... args) {
    if (p_ == nullptr) {
      p_ = new T(std::forward<Args>(args)...);
    } else {
      try {
        p_->operator=(std::forward<Args>(args)...);
      } catch (...) {
        try {
          p_->~T();
        } catch (...) {
        }
        ::operator delete(p_);
        p_ = nullptr;
        throw;
      }
    }
    return *p_;
  }

  template<class X = T,
           class... Args,
           sst::enable_if_t<!can_assign<X, Args...>::value> = 0>
  T & emplace(Args &&... args) {
    if (p_ == nullptr) {
      p_ = new T(std::forward<Args>(args)...);
    } else {
      try {
        p_->~T();
      } catch (...) {
      }
      try {
        new (p_) T(std::forward<Args>(args)...);
      } catch (...) {
        ::operator delete(p_);
        p_ = nullptr;
        throw;
      }
    }
    return *p_;
  }

  //--------------------------------------------------------------------
  // ensure
  //--------------------------------------------------------------------
  //
  // If the pointer is null, allocates and constructs the object,
  // forwarding the arguments to the constructor. Otherwise, does
  // nothing. Returns a reference to the object.
  //

public:

  template<class... Args>
  T & ensure(Args &&... args) {
    if (p_ == nullptr) {
      p_ = new T(std::forward<Args>(args)...);
    }
    return *p_;
  }

  //--------------------------------------------------------------------
  // get
  //--------------------------------------------------------------------
  //
  // Returns the pointer.
  //

public:

  SST_NODISCARD() T * get() const SST_NOEXCEPT(true) {
    return p_;
  }

  //--------------------------------------------------------------------
  // operator->
  //--------------------------------------------------------------------
  //
  // Returns the pointer. The pointer must not be null.
  //

public:

  SST_NODISCARD() T * operator->() const SST_NOEXCEPT(true) {
    SST_ASSERT((p_ != nullptr));
    return p_;
  }

  //--------------------------------------------------------------------
  // operator*
  //--------------------------------------------------------------------
  //
  // Returns a reference to the object. The pointer must not be null.
  //

public:

  SST_NODISCARD() T & operator*() const SST_NOEXCEPT(true) {
    SST_ASSERT((p_ != nullptr));
    return *p_;
  }

  //--------------------------------------------------------------------
  // operator bool
  //--------------------------------------------------------------------

public:

  SST_NODISCARD() explicit operator bool() const SST_NOEXCEPT(true) {
    return p_ != nullptr;
  }

  //--------------------------------------------------------------------
  // release
  //--------------------------------------------------------------------

public:

  SST_NODISCARD() T * release() SST_NOEXCEPT(true) {
    T * const p = p_;
    p_ = nullptr;
    return p;
  }

  //--------------------------------------------------------------------
  // reset
  //--------------------------------------------------------------------

public:

  void reset(T * const p = nullptr) SST_NOEXCEPT(true) {
    try {
      delete p_;
    } catch (...) {
    }
    p_ = p;
  }

  //--------------------------------------------------------------------
  // swap
  //--------------------------------------------------------------------

public:

  void swap(unique_ptr & other) SST_NOEXCEPT(true) {
    T * const p = p_;
    p_ = other.p_;
    other.p_ = p;
  }

  //--------------------------------------------------------------------
  // Default operations
  //--------------------------------------------------------------------

public:

  unique_ptr() SST_NOEXCEPT(true) = default;

  ~unique_ptr() SST_NOEXCEPT(true) {
    try {
      delete p_;
    } catch (...) {
    }
  }

  unique_ptr(unique_ptr const & other) : p_(copy(other)) {
  }

  unique_ptr & operator=(unique_ptr const & other) {
    if (SST_NOEXCEPT_OR(false, *p_ = *other.p_) && p_ && other.p_) {
      *p_ = *other.p_;
    } else {
      reset(copy(other));
    }
    return *this;
  }

  unique_ptr(unique_ptr && other) SST_NOEXCEPT(true)
      : p_(other.release()) {
  }

  unique_ptr & operator=(unique_ptr && other) SST_NOEXCEPT(true) {
    reset(other.release());
    return *this;
  }

  //--------------------------------------------------------------------
  // Other constructors
  //--------------------------------------------------------------------

public:

  explicit unique_ptr(T * const p) SST_NOEXCEPT(true) : p_(p) {
  }

  template<class... Args>
  explicit unique_ptr(sst::in_place_t, Args &&... args)
      : p_(new T(std::forward<Args>(args)...)) {
  }

  //--------------------------------------------------------------------
  // Operations with std::nullptr_t
  //--------------------------------------------------------------------

public:

  unique_ptr(std::nullptr_t) SST_NOEXCEPT(true) {
  }

  unique_ptr & operator=(std::nullptr_t) SST_NOEXCEPT(true) {
    reset();
    return *this;
  }

  friend bool operator==(unique_ptr const & a, std::nullptr_t)
      SST_NOEXCEPT(true) {
    return a.p_ == nullptr;
  }

  friend bool operator==(std::nullptr_t, unique_ptr const & b)
      SST_NOEXCEPT(true) {
    return nullptr == b.p_;
  }

  friend bool operator!=(unique_ptr const & a, std::nullptr_t)
      SST_NOEXCEPT(true) {
    return a.p_ != nullptr;
  }

  friend bool operator!=(std::nullptr_t, unique_ptr const & b)
      SST_NOEXCEPT(true) {
    return nullptr != b.p_;
  }

  //--------------------------------------------------------------------
  // Operations with std::unique_ptr
  //--------------------------------------------------------------------

public:

  template<class Deleter>
  unique_ptr(std::unique_ptr<T, Deleter> const & other)
      : p_(copy(other)) {
  }

  template<class Deleter>
  unique_ptr & operator=(std::unique_ptr<T, Deleter> const & other) {
    reset(copy(other));
    return *this;
  }

  unique_ptr(std::unique_ptr<T> && other) SST_NOEXCEPT(true)
      : p_(other.release()) {
  }

  unique_ptr & operator=(std::unique_ptr<T> && other)
      SST_NOEXCEPT(true) {
    reset(other.release());
    return *this;
  }

  //--------------------------------------------------------------------
};

} // namespace sst

#endif // SST_CATALOG_UNIQUE_PTR_HPP
