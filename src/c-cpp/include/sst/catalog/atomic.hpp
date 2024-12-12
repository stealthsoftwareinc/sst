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

#ifndef SST_CATALOG_ATOMIC_HPP
#define SST_CATALOG_ATOMIC_HPP

#include <atomic>
#include <memory>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_CPP20_OR_LATER.h>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/unique_ptr.hpp>

namespace sst {

namespace guts {
namespace atomic {

template<class T, class = sst::enable_t>
struct copy_construct : std::atomic<T> {
  using std::atomic<T>::atomic;
};

template<class T>
struct copy_construct<
    T,
    sst::enable_if_t<std::is_copy_constructible<T>::value>>
    : std::atomic<T> {
  using std::atomic<T>::atomic;
  copy_construct(copy_construct const & other) noexcept(
      noexcept(std::atomic<T>(other.load())))
      : std::atomic<T>(other.load()) {
  }
};

template<class T, class = sst::enable_t>
struct copy_assign : copy_construct<T> {
  using copy_construct<T>::copy_construct;
};

template<class T>
struct copy_assign<T,
                   sst::enable_if_t<std::is_copy_assignable<T>::value>>
    : copy_construct<T> {
  using copy_construct<T>::copy_construct;
  copy_assign & operator=(copy_assign const & other) noexcept(
      noexcept(std::declval<copy_assign &>().store(other.load()))) {
    this->store(other.load());
    return *this;
  }
};

} // namespace atomic
} // namespace guts

template<class T>
class atomic : sst::guts::atomic::copy_assign<T> {

  using base = sst::guts::atomic::copy_assign<T>;

public:

  using base::base;
  using base::compare_exchange_strong;
  using base::compare_exchange_weak;
  using base::exchange;
  using base::is_lock_free;
  using base::load;
  using base::operator T;
  using base::operator=;
  using base::store;

  atomic() noexcept(noexcept(base(T()))) : base(T()) {
  }

}; //

//----------------------------------------------------------------------

template<class T>
class atomic<sst::unique_ptr<T>> : sst::atomic<T *> {

  using base = sst::atomic<T *>;

  static T * copy(T const * const p) {
    return p ? new T(*p) : nullptr;
  }

public:

  using base::base;
  using base::load;

  atomic(atomic const & other) : base(copy(other.load())) {
  }

  atomic & operator=(atomic const & other) {
    if (this != &other) {
      T * const p = other.load();
      T * const q = base::exchange(copy(p));
      SST_ASSERT((!p || p != q));
      delete q;
    }
    return *this;
  }

  ~atomic() {
    delete load();
  }

  T * store(sst::unique_ptr<T> desired) {
    T * const p = desired.release();
    T * const q = base::exchange(p);
    SST_ASSERT((!p || p != q));
    delete q;
    return p;
  }

  bool compare_exchange_strong(T *& expected,
                               sst::unique_ptr<T> && desired) {
    T * const p = desired.get();
    if (!base::compare_exchange_strong(expected, p)) {
      return false;
    }
    desired.release();
    delete expected;
    expected = p;
    return true;
  }

}; //

//----------------------------------------------------------------------

template<class T>
class atomic<std::shared_ptr<T>> {

#if SST_CPP20_OR_LATER
  std::atomic<std::shared_ptr<T>> ptr_;
#else
  std::shared_ptr<T> ptr_;
#endif

  //--------------------------------------------------------------------
  // Default operations
  //--------------------------------------------------------------------
  //
  // Move construction and move assignment are intentionally undeclared.
  //

public:

  atomic() SST_NOEXCEPT(true) = default;

  atomic(atomic const & other) SST_NOEXCEPT(true)
      :
#if SST_CPP20_OR_LATER
        ptr_(other.ptr_.load())
#else
        ptr_(std::atomic_load(&other.ptr_))
#endif
  {
  }

  atomic & operator=(atomic const & other) SST_NOEXCEPT(true) {
    this->store(other.load());
    return *this;
  }

  //--------------------------------------------------------------------

public:

  atomic(std::shared_ptr<T> ptr) SST_NOEXCEPT(true)
      : ptr_(std::move(ptr)) {
  }

  atomic & operator=(std::shared_ptr<T> ptr) SST_NOEXCEPT(true) {
    this->store(std::move(ptr));
    return *this;
  }

  //--------------------------------------------------------------------
  // load
  //--------------------------------------------------------------------

public:

  std::shared_ptr<T>
  load(std::memory_order const order = std::memory_order_seq_cst) const
      SST_NOEXCEPT(true) {
#if SST_CPP20_OR_LATER
    return this->ptr_.load(order);
#else
    return std::atomic_load_explicit(&this->ptr_, order);
#endif
  }

  //--------------------------------------------------------------------
  // operator std::shared_ptr<T>
  //--------------------------------------------------------------------

public:

  operator std::shared_ptr<T>() const SST_NOEXCEPT(true) {
    return this->load();
  }

  //--------------------------------------------------------------------
  // store
  //--------------------------------------------------------------------

public:

  void store(std::shared_ptr<T> ptr,
             std::memory_order const order = std::memory_order_seq_cst)
      SST_NOEXCEPT(true) {
#if SST_CPP20_OR_LATER
    this->ptr_.store(std::move(ptr), order);
#else
    std::atomic_store_explicit(&this->ptr_, std::move(ptr), order);
#endif
  }

  //--------------------------------------------------------------------
};

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_CATALOG_ATOMIC_HPP
