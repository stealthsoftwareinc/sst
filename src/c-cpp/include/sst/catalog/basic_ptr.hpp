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

#ifndef SST_CATALOG_BASIC_PTR_HPP
#define SST_CATALOG_BASIC_PTR_HPP

#include <algorithm>
#include <cstddef>
#include <memory>
#include <new>
#include <type_traits>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/conditional_t.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/remove_reference_t.hpp>
#include <sst/catalog/undeduced_t.hpp>

namespace sst {

//
// An sst::basic_ptr holds a pointer p and deletes it upon destruction
// by calling a function pointer d with p as the argument. d is called
// the deleter. d will not be called if p is null. d cannot be null.
//
// sst::basic_ptr is similar to std::unique_ptr but generally provides
// more primitive operations.
//

template<class RawT, class = sst::enable_t>
class basic_ptr
    : std::unique_ptr<
          sst::conditional_t<
              std::is_void<sst::remove_reference_t<RawT>>::value,
              unsigned char,
              sst::remove_reference_t<RawT>>,
          void (*)(sst::remove_reference_t<RawT> *)> {

  using T = sst::remove_reference_t<RawT>;

  using E =
      sst::conditional_t<std::is_void<T>::value, unsigned char, T>;

  using base = std::unique_ptr<E, void (*)(T *)>;

public:

  //--------------------------------------------------------------------
  // Inherited members
  //--------------------------------------------------------------------

  using base::operator bool;
  using base::release;
  using base::reset;

  //--------------------------------------------------------------------
  // basic_ptr-tmk33dfe
  //--------------------------------------------------------------------
  //
  // Creates an sst::basic_ptr with a pointer p and deleter d.
  //
  // Note that the std::unique_ptr constructor being invoked is indeed
  // noexcept, even in C++11. See C++11 (N3337) 20.7.1.2.1.
  //

public:

  explicit basic_ptr(T * const p,
                     sst::undeduced_t<void (*)(T *)> const d) noexcept
      : base(static_cast<E *>(p), (SST_ASSERT((d != nullptr)), d)) {
  }

  //--------------------------------------------------------------------
  // basic_ptr-fc16vw7e
  //--------------------------------------------------------------------

  explicit basic_ptr(T * const p) noexcept
      : basic_ptr(p, [](T * const p) { ::operator delete(p); }) {
  }

  //--------------------------------------------------------------------
  // basic_ptr-b4p6nand
  //--------------------------------------------------------------------

  explicit basic_ptr(void (*const d)(T *)) noexcept
      : basic_ptr(nullptr, d) {
  }

  //--------------------------------------------------------------------
  // construct-default
  //--------------------------------------------------------------------

  basic_ptr() noexcept : basic_ptr(static_cast<T *>(nullptr)) {
  }

  //--------------------------------------------------------------------
  // construct-nullptr
  //--------------------------------------------------------------------

  basic_ptr(std::nullptr_t) : basic_ptr() {
  }

  //--------------------------------------------------------------------
  // construct-allocate
  //--------------------------------------------------------------------
  //
  // This should normally delegate to basic_ptr(), but this fails to
  // compile on g++ on CentOS 7 as tested on 2022-02-03, likely due to
  // an old GCC bug. Repeating the delegation from basic_ptr() works.
  //

  template<class Size,
           sst::enable_if_t<sst::is_integer<Size>::value> = 0>
  explicit basic_ptr(Size const size)
      : basic_ptr(static_cast<T *>(nullptr)) {
    allocate(size);
  }

  //--------------------------------------------------------------------
  // construct-copy
  //--------------------------------------------------------------------

  template<class Size,
           sst::enable_if_t<sst::is_integer<Size>::value> = 0>
  explicit basic_ptr(T const * const p, Size const size)
      : basic_ptr(size) {
    SST_ASSERT((p != nullptr));
    std::copy_n(reinterpret_cast<unsigned char const *>(p),
                size,
                reinterpret_cast<unsigned char *>(get()));
  }

  //--------------------------------------------------------------------
  // allocate-xgopaf5j
  //--------------------------------------------------------------------

  template<class Size,
           sst::enable_if_t<sst::is_integer<Size>::value> = 0>
  void allocate(Size const size) {
    SST_ASSERT((!sst::is_negative(size)));
    *this = static_cast<T *>(
        ::operator new(sst::checked_cast<std::size_t>(size)));
  }

  //--------------------------------------------------------------------
  // allocate-wvb8wjyh
  //--------------------------------------------------------------------

  template<class T_ = T, sst::enable_if_t<!std::is_void<T_>::value> = 0>
  void allocate() {
    allocate(sizeof(T));
  }

  //--------------------------------------------------------------------
  // copy-with-explicit-size
  //--------------------------------------------------------------------

  template<class RawR = T,
           class R = sst::remove_reference_t<RawR>,
           class Size,
           sst::enable_if_t<sst::is_integer<Size>::value> = 0>
  basic_ptr<R> copy(Size const size) const {
    return get() == nullptr ?
               basic_ptr<R>() :
               basic_ptr<R>(reinterpret_cast<R const *>(get()), size);
  }

  //--------------------------------------------------------------------
  // copy-k41q7373
  //--------------------------------------------------------------------

  template<class T_ = T, sst::enable_if_t<!std::is_void<T_>::value> = 0>
  basic_ptr copy() const {
    return copy(sizeof(T));
  }

  //--------------------------------------------------------------------
  // get (opd8dxkd)
  //--------------------------------------------------------------------

  T * get() const noexcept {
    return base::get();
  }

  //--------------------------------------------------------------------

  operator T *() const noexcept {
    return get();
  }

  //--------------------------------------------------------------------

  template<class X,
           sst::enable_if_t<std::is_void<T>::value
                            && !std::is_void<X>::value> = 0>
  explicit operator X *() const noexcept {
    return static_cast<X *>(get());
  }

  //--------------------------------------------------------------------
  // operator* (x7q7hgeh)
  //--------------------------------------------------------------------
  //
  // Note that std::unique_ptr's operator* is not necessarily noexcept.
  // This is because std::unique_ptr allows its pointer type to be
  // overridden via std::remove_reference_t<Deleter>::type but doesn't
  // require that type's operator* to be noexcept. This doesn't matter
  // for us because our Deleter type is simply a function pointer type,
  // which means our underlying pointer type is simply a plain pointer
  // type, for which operator* is always noexcept.
  //
  // std::unique_ptr's operator* also uses std::add_lvalue_reference_t
  // in its return type, which is presumably to handle T = void, as T &
  // would fail to compile if T = void. We take the alternative approach
  // of simply omitting operator* via SFINAE if T = void.
  //

  template<class T_ = T, sst::enable_if_t<!std::is_void<T_>::value> = 0>
  T_ & operator*() const noexcept {
    return *get();
  }

  //--------------------------------------------------------------------
  // operator-> (tycmk8y6)
  //--------------------------------------------------------------------

  T * operator->() const noexcept {
    return get();
  }

  //--------------------------------------------------------------------
  // operator= (sqjhjr49)
  //--------------------------------------------------------------------

  basic_ptr & operator=(T * const p) noexcept {
    reset(static_cast<E *>(p));
    return *this;
  }

  //--------------------------------------------------------------------
  // operator= (m790ncv5)
  //--------------------------------------------------------------------

  basic_ptr & operator=(std::nullptr_t) noexcept {
    reset();
    return *this;
  }

  //--------------------------------------------------------------------
  // operator== (xbwr22jc)
  //--------------------------------------------------------------------

  friend bool operator==(basic_ptr const & a, std::nullptr_t) noexcept(
      noexcept(static_cast<base const &>(a) == nullptr)) {
    return static_cast<base const &>(a) == nullptr;
  }

  //--------------------------------------------------------------------
  // operator== (njwcvhhc)
  //--------------------------------------------------------------------

  friend bool operator==(std::nullptr_t, basic_ptr const & b) noexcept(
      noexcept(nullptr == static_cast<base const &>(b))) {
    return nullptr == static_cast<base const &>(b);
  }

  //--------------------------------------------------------------------
  // operator!= (u5hu00gg)
  //--------------------------------------------------------------------

  friend bool operator!=(basic_ptr const & a, std::nullptr_t) noexcept(
      noexcept(static_cast<base const &>(a) != nullptr)) {
    return static_cast<base const &>(a) != nullptr;
  }

  //--------------------------------------------------------------------
  // operator!= (qbckh3g0)
  //--------------------------------------------------------------------

  friend bool operator!=(std::nullptr_t, basic_ptr const & b) noexcept(
      noexcept(nullptr != static_cast<base const &>(b))) {
    return nullptr != static_cast<base const &>(b);
  }

  //--------------------------------------------------------------------
  // swap
  //--------------------------------------------------------------------

  friend void swap(basic_ptr & a, basic_ptr & b) noexcept {
    using std::swap;
    swap(static_cast<base &>(a), static_cast<base &>(b));
  }

  //--------------------------------------------------------------------
};

} // namespace sst

#endif // SST_CATALOG_BASIC_PTR_HPP
