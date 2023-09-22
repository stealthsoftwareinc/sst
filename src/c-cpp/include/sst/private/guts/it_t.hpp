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

#ifndef SST_PRIVATE_GUTS_IT_T_HPP
#define SST_PRIVATE_GUTS_IT_T_HPP

#include <iterator>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_DEBUG.h>
#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/checked_t.hpp>
#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/is_unsigned_integer.hpp>
#include <sst/catalog/checked.hpp>
#include <sst/catalog/perfect_eq.hpp>
#include <sst/catalog/perfect_ge.hpp>
#include <sst/catalog/perfect_gt.hpp>
#include <sst/catalog/perfect_le.hpp>
#include <sst/catalog/perfect_lt.hpp>
#include <sst/catalog/perfect_ne.hpp>
#include <sst/catalog/promote_t.hpp>
#include <sst/catalog/promote_unsigned_t.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/unsigned_ge.hpp>
#include <sst/catalog/unsigned_le.hpp>

#if SST_DEBUG
#include <atomic>
#endif

namespace sst {
namespace guts {

// TODO: This class needs a lot of work. It shouldn't really need to be
//       restricted to unique-pass algorithms. I can store a pointer to
//       the original iterator in only the initial copy, and, if the
//       underlying iterator is copiable, provide copy operations that
//       discard the original iterator pointer and instead store an
//       actual copy (in an sst::optional so things still work even if
//       the iterator isn't copiable or default constructible etc).
//
//       Hopefully the overall interface to this class (sst::track_it
//       and friends) is still OK, and it's only the class innards that
//       need lots of work.

template<class Iterator, class Count>
class it_t {

  //--------------------------------------------------------------------
  // traits_t
  //--------------------------------------------------------------------

private:

  using traits_t = typename std::iterator_traits<Iterator>;

  //--------------------------------------------------------------------
  // difference_type
  //--------------------------------------------------------------------

public:

  using difference_type = typename traits_t::difference_type;

  //--------------------------------------------------------------------
  // iterator_category
  //--------------------------------------------------------------------

public:

  using iterator_category = typename traits_t::iterator_category;

  //--------------------------------------------------------------------
  // pointer
  //--------------------------------------------------------------------

public:

  using pointer = typename traits_t::pointer;

  //--------------------------------------------------------------------
  // reference
  //--------------------------------------------------------------------

public:

  using reference = typename traits_t::reference;

  //--------------------------------------------------------------------
  // value_type
  //--------------------------------------------------------------------

public:

  using value_type = typename traits_t::value_type;

  //--------------------------------------------------------------------

private:

  // count_t may be signed or unsigned depending on what kind of n the
  // caller passed to sst::count_it(x, n).
  SST_STATIC_ASSERT((sst::is_integer<Count>::value));
  using count_t = sst::promote_t<sst::remove_cvref_t<Count>>;

  // delta_t is always unsigned, and we'll manually interpret it as
  // two's complement when doing iterator subtraction. This provides
  // imperfect wrap-around tracking, but it avoids undefined behavior
  // when wrap-around does occur.
  using delta_t = sst::promote_unsigned_t<
      typename std::common_type<count_t, std::size_t>::type>;

  Iterator * ptr_;
  Iterator it_;

  //--------------------------------------------------------------------
  // is_count_
  //--------------------------------------------------------------------
  //
  // is_count_ indicates whether this iterator was created with
  // sst::count_it.
  //

private:

  bool is_count_;

  //--------------------------------------------------------------------

private:

  count_t count_;
  delta_t delta_;
#if SST_DEBUG
  std::atomic<bool> is_newest_;
#else
  bool is_newest_;
#endif

  //--------------------------------------------------------------------

private:

  bool is_bound_ = false;

  //--------------------------------------------------------------------

private:

  count_t * p_avail_ = nullptr;

  //--------------------------------------------------------------------

private:

  void assert_invariants() {
    SST_ASSERT((!is_count_ || !is_bound_));
  }

  //--------------------------------------------------------------------

private:

  it_t();

public:

  explicit it_t(Iterator * const ptr,
                Iterator const it,
                bool const is_count,
                count_t const count,
                delta_t const delta,
                bool const is_newest)
      : ptr_(ptr),
        it_(it),
        is_count_(is_count),
        count_(count),
        delta_(delta),
        is_newest_(is_newest) {
  }

  //--------------------------------------------------------------------
  // Constructors for sst::track_it
  //--------------------------------------------------------------------

public:

  struct track_it_tag {};

  explicit it_t(track_it_tag, Iterator & i)
      : ptr_(&i),
        it_(i),
        is_count_(false),
        count_(0),
        delta_(0),
        is_newest_(true),
        is_bound_(false),
        p_avail_(nullptr) {
    assert_invariants();
  }

  explicit it_t(track_it_tag, Iterator & i, count_t const n)
      : ptr_(&i),
        it_(i),
        is_count_(false),
        count_(n),
        delta_(0),
        is_newest_(true),
        is_bound_(true),
        p_avail_(nullptr) {
    assert_invariants();
  }

  explicit it_t(track_it_tag, Iterator & i, count_t * const n)
      : ptr_(&i),
        it_(i),
        is_count_(false),
        count_(*n),
        delta_(0),
        is_newest_(true),
        is_bound_(true),
        p_avail_(n) {
    assert_invariants();
  }

  //--------------------------------------------------------------------
  // Constructors for sst::wrap_it
  //--------------------------------------------------------------------

public:

  struct wrap_it_tag {};

  explicit it_t(wrap_it_tag, Iterator i)
      : ptr_(nullptr),
        it_(std::move(i)),
        is_count_(false),
        count_(0),
        delta_(0),
        is_newest_(true),
        is_bound_(false),
        p_avail_(nullptr) {
    assert_invariants();
  }

  explicit it_t(wrap_it_tag, Iterator i, count_t const n)
      : ptr_(nullptr),
        it_(std::move(i)),
        is_count_(false),
        count_(n),
        delta_(0),
        is_newest_(true),
        is_bound_(true),
        p_avail_(nullptr) {
    assert_invariants();
  }

  explicit it_t(wrap_it_tag, Iterator i, count_t * const n)
      : ptr_(nullptr),
        it_(std::move(i)),
        is_count_(false),
        count_(*n),
        delta_(0),
        is_newest_(true),
        is_bound_(true),
        p_avail_(n) {
    assert_invariants();
  }

  //--------------------------------------------------------------------
  // Rule of five for the debug atomic
  //--------------------------------------------------------------------

#if SST_DEBUG

  it_t(it_t const & other)
      : ptr_(other.ptr_),
        it_(other.it_),
        is_count_(other.is_count_),
        count_(other.count_),
        delta_(other.delta_),
        is_newest_(other.is_newest_.load()),
        is_bound_(other.is_bound_),
        p_avail_(other.p_avail_) {
  }

  it_t & operator=(it_t const & other) {
    ptr_ = other.ptr_;
    it_ = other.it_;
    is_count_ = other.is_count_;
    count_ = other.count_;
    delta_ = other.delta_;
    is_newest_ = other.is_newest_.load();
    is_bound_ = other.is_bound_;
    p_avail_ = other.p_avail_;
    return *this;
  }

  it_t(it_t && other)
      : ptr_(std::move(other.ptr_)),
        it_(std::move(other.it_)),
        is_count_(std::move(other.is_count_)),
        count_(std::move(other.count_)),
        delta_(std::move(other.delta_)),
        is_newest_(other.is_newest_.load()),
        is_bound_(std::move(other.is_bound_)),
        p_avail_(std::move(other.p_avail_)) {
  }

  it_t & operator=(it_t && other) {
    ptr_ = std::move(other.ptr_);
    it_ = std::move(other.it_);
    is_count_ = std::move(other.is_count_);
    count_ = std::move(other.count_);
    delta_ = std::move(other.delta_);
    is_newest_ = other.is_newest_.load();
    is_bound_ = std::move(other.is_bound_);
    p_avail_ = std::move(other.p_avail_);
    return *this;
  }

  ~it_t() = default;

#endif

  //--------------------------------------------------------------------
  // Dereference and arrow operators
  //--------------------------------------------------------------------

  reference operator*() const {
    // clang-format off
    SST_ASSERT((!is_count_) && "operator* cannot be used on an sst::count_it.");
    // clang-format on
    if (is_bound_ && count_ == 0) {
      throw std::runtime_error("Buffer overflow or underflow.");
    }
    return *it_;
  }

  pointer operator->() const {
    // clang-format off
    SST_ASSERT((!is_count_) && "operator-> cannot be used on an sst::count_it.");
    // clang-format on
    if (is_bound_ && count_ == 0) {
      throw std::runtime_error("Buffer overflow or underflow.");
    }
    return &*it_;
  }

  //--------------------------------------------------------------------
  // Increment operators
  //--------------------------------------------------------------------

  it_t & operator++() {
    // clang-format off
    SST_ASSERT((!is_count_) && "operator++() cannot be used on an sst::count_it.");
    SST_ASSERT((is_newest_) && "operator++() on an sst::track_it or sst::wrap_it detected a non-unique-pass algorithm.");
    // clang-format on
    ++it_;
    if (ptr_ != nullptr) {
      *ptr_ = it_;
    }
    if (is_bound_) {
      if (count_ == 0) {
        throw std::runtime_error("Buffer overflow or underflow.");
      }
      --count_;
      if (p_avail_ != nullptr) {
        *p_avail_ = count_;
      }
    }
    ++delta_;
    return *this;
  }

  it_t operator++(int) {
    // clang-format off
    SST_ASSERT((!is_count_) && "operator++(int) cannot be used on an sst::count_it.");
    SST_ASSERT((is_newest_) && "operator++(int) on an sst::track_it or sst::wrap_it detected a non-unique-pass algorithm.");
    // clang-format on
    it_t old = *this;
    old.ptr_ = nullptr;
    old.is_newest_ = false;
    old.p_avail_ = nullptr;
    operator++();
    return old;
  }

  //--------------------------------------------------------------------
  // Decrement operators
  //--------------------------------------------------------------------

  it_t & operator--() {
    // clang-format off
    SST_ASSERT((!is_count_) && "operator--() cannot be used on an sst::count_it.");
    SST_ASSERT((is_newest_) && "operator--() on an sst::track_it or sst::wrap_it detected a non-unique-pass algorithm.");
    SST_ASSERT((!is_bound_));
    // clang-format on
    --it_;
    if (ptr_ != nullptr) {
      *ptr_ = it_;
    }
    --delta_;
    return *this;
  }

  it_t operator--(int) {
    // clang-format off
    SST_ASSERT((!is_count_) && "operator--(int) cannot be used on an sst::count_it.");
    SST_ASSERT((is_newest_) && "operator--(int) on an sst::track_it or sst::wrap_it detected a non-unique-pass algorithm.");
    SST_ASSERT((!is_bound_));
    // clang-format on
    it_t old(nullptr, it_, false, 0, delta_, false);
    operator--();
    return old;
  }

  //--------------------------------------------------------------------
  // Integer addition operators
  //--------------------------------------------------------------------

private:

  template<class Integer>
  static constexpr delta_t move_add(delta_t const a,
                                    Integer const b) noexcept {
    return sst::is_negative(b) ?
               a - static_cast<delta_t>(-(b + 1)) - 1U :
               a + static_cast<delta_t>(b);
  }

public:

  template<class Integer,
           sst::enable_if_t<!std::is_same<sst::remove_cvref_t<Integer>,
                                          it_t>::value> = 0>
  it_t operator+(Integer && n) const {
    // clang-format off
    SST_ASSERT((!is_count_) && "operator+ cannot be used on an sst::count_it.");
    SST_ASSERT((is_newest_) && "operator+ on an sst::track_it or sst::wrap_it detected a non-unique-pass algorithm.");
    SST_ASSERT((!is_bound_));
    // clang-format on
    difference_type const k = n;
    return it_t(ptr_, it_ + k, false, 0, move_add(delta_, k), true);
  }

  template<class Integer,
           sst::enable_if_t<!std::is_same<sst::remove_cvref_t<Integer>,
                                          it_t>::value> = 0>
  friend it_t operator+(Integer && n, it_t const & a) {
    return a + std::forward<Integer>(n);
  }

#if SST_DEBUG

  template<class Integer,
           sst::enable_if_t<!std::is_same<sst::remove_cvref_t<Integer>,
                                          it_t>::value> = 0>
  it_t operator+(Integer && n) {
    auto r =
        static_cast<it_t const &>(*this) + std::forward<Integer>(n);
    is_newest_ = false;
    return r;
  }

  template<class Integer,
           sst::enable_if_t<!std::is_same<sst::remove_cvref_t<Integer>,
                                          it_t>::value> = 0>
  friend it_t operator+(Integer && n, it_t & a) {
    return a + std::forward<Integer>(n);
  }

#endif

  template<class Integer,
           sst::enable_if_t<!std::is_same<sst::remove_cvref_t<Integer>,
                                          it_t>::value> = 0>
  it_t & operator+=(Integer && n) {
    // clang-format off
    SST_ASSERT((!is_count_) && "operator+= cannot be used on an sst::count_it.");
    SST_ASSERT((is_newest_) && "operator+= on an sst::track_it or sst::wrap_it detected a non-unique-pass algorithm.");
    SST_ASSERT((!is_bound_));
    // clang-format on
    difference_type const k = n;
    it_ += k;
    if (ptr_ != nullptr) {
      *ptr_ = it_;
    }
    delta_ = move_add(delta_, k);
    return *this;
  }

  //--------------------------------------------------------------------
  // Integer subtraction operators
  //--------------------------------------------------------------------

private:

  template<class Integer>
  static constexpr delta_t move_sub(delta_t const a,
                                    Integer const b) noexcept {
    SST_ASSERT((sst::is_unsigned_integer<delta_t>::value));
    return sst::is_negative(b) ?
               a + static_cast<delta_t>(-(b + 1)) + 1U :
               a - static_cast<delta_t>(b);
  }

public:

  template<class Integer,
           sst::enable_if_t<!std::is_same<sst::remove_cvref_t<Integer>,
                                          it_t>::value> = 0>
  it_t operator-(Integer && n) const {
    // clang-format off
    SST_ASSERT((!is_count_) && "operator- cannot be used on an sst::count_it.");
    SST_ASSERT((is_newest_) && "operator- on an sst::track_it or sst::wrap_it detected a non-unique-pass algorithm.");
    SST_ASSERT((!is_bound_));
    // clang-format on
    difference_type const k = n;
    return it_t(ptr_, it_ - k, false, 0, move_sub(delta_, k), true);
  }

#if SST_DEBUG

  template<class Integer,
           sst::enable_if_t<!std::is_same<sst::remove_cvref_t<Integer>,
                                          it_t>::value> = 0>
  it_t operator-(Integer && n) {
    auto r =
        static_cast<it_t const &>(*this) - std::forward<Integer>(n);
    is_newest_ = false;
    return r;
  }

#endif

  template<class Integer,
           sst::enable_if_t<!std::is_same<sst::remove_cvref_t<Integer>,
                                          it_t>::value> = 0>
  it_t & operator-=(Integer && n) {
    // clang-format off
    SST_ASSERT((!is_count_) && "operator-= cannot be used on an sst::count_it.");
    SST_ASSERT((is_newest_) && "operator-= on an sst::track_it or sst::wrap_it detected a non-unique-pass algorithm.");
    SST_ASSERT((!is_bound_));
    // clang-format on
    difference_type const k = n;
    it_ -= k;
    if (ptr_ != nullptr) {
      *ptr_ = it_;
    }
    delta_ = move_sub(delta_, k);
    return *this;
  }

  //--------------------------------------------------------------------
  // Iterator subtraction operator
  //--------------------------------------------------------------------

  template<class Count2>
  difference_type operator-(it_t<Iterator, Count2> const & b) const {
    auto const & a = *this;
    if (&a == &b) {
      return 0;
    }
    // clang-format off
    SST_ASSERT((!a.is_count_ || !b.is_count_) && "operator- cannot be used to subtract an sst::count_it from a different sst::count_it.");
    // clang-format on
    if (!a.is_count_ && !b.is_count_) {
      return a.it_ - b.it_;
    }
    using d_t = difference_type;
    if (a.is_count_) {
      using a_t = count_t;
      using b_t = typename it_t<Iterator, Count2>::delta_t;
      constexpr auto a_max = sst::type_max<a_t>::value;
      constexpr auto b_max = sst::type_max<b_t>::value;
      if (b.delta_ > b_max / 2U) {
        b_t const b_abs = b_max - b.delta_ + 1U;
        if (!sst::is_negative(a.count_)) {
          return SST_DEBUG ?
                     sst::checked_cast<d_t>(sst::checked_t<d_t>(a.count_)
                                            + b_abs) :
                     static_cast<d_t>(static_cast<d_t>(a.count_)
                                      + static_cast<d_t>(b_abs));
        }
        if (sst::unsigned_le(b_abs, a_max)) {
          return SST_DEBUG ? sst::checked_cast<d_t>(
                     a.count_ + static_cast<a_t>(b_abs)) :
                             static_cast<d_t>(
                                 a.count_ + static_cast<a_t>(b_abs));
        }
        return SST_DEBUG ?
                   sst::checked_cast<d_t>(
                       sst::checked_t<d_t>(a.count_ + a_max + 1)
                       + (b_abs - static_cast<b_t>(a_max) - 1U)) :
                   static_cast<d_t>(
                       static_cast<d_t>(a.count_ + a_max + 1)
                       + static_cast<d_t>(
                           b_abs - static_cast<b_t>(a_max) - 1U));
      }
      if (sst::is_negative(a.count_)) {
        return SST_DEBUG ?
                   sst::checked_cast<d_t>(
                       sst::checked_t<d_t>(a.count_)
                       - sst::checked_t<d_t>(b.delta_)) :
                   static_cast<d_t>(static_cast<d_t>(a.count_)
                                    - static_cast<d_t>(b.delta_));
      }
      if (sst::unsigned_ge(a.count_, b.delta_)) {
        return SST_DEBUG ? sst::checked_cast<d_t>(
                   a.count_ - static_cast<a_t>(b.delta_)) :
                           static_cast<d_t>(
                               a.count_ - static_cast<a_t>(b.delta_));
      }
      return SST_DEBUG ?
                 sst::checked_cast<d_t>(
                     -sst::checked_t<d_t>(
                         b.delta_ - static_cast<b_t>(a.count_) - 1U)
                     - 1) :
                 static_cast<d_t>(
                     -static_cast<d_t>(
                         b.delta_ - static_cast<b_t>(a.count_) - 1U)
                     - 1);
    }
    SST_ASSERT((b.is_count_));
    using a_t = delta_t;
    using b_t = typename it_t<Iterator, Count2>::count_t;
    constexpr auto a_max = sst::type_max<a_t>::value;
    constexpr auto b_max = sst::type_max<b_t>::value;
    if (a.delta_ > a_max / 2U) {
      a_t const a_abs = a_max - a.delta_ + 1U;
      if (!sst::is_negative(b.count_)) {
        return SST_DEBUG ?
                   sst::checked_cast<d_t>(
                       -sst::checked_t<d_t>(a_abs - 1U) - 1
                       - sst::checked_t<d_t>(b.count_ / 2)
                       - sst::checked_t<d_t>(b.count_ - b.count_ / 2)) :
                   static_cast<d_t>(
                       -static_cast<d_t>(a_abs - 1U) - 1
                       - static_cast<d_t>(b.count_ / 2)
                       - static_cast<d_t>(b.count_ - b.count_ / 2));
      }
      if (sst::unsigned_le(a_abs, b_max)) {
        return SST_DEBUG ? sst::checked_cast<d_t>(
                   -static_cast<b_t>(a_abs) - b.count_) :
                           static_cast<d_t>(-static_cast<b_t>(a_abs)
                                            - b.count_);
      }
      a_t const x = (a_abs - static_cast<a_t>(b_max) - 1U);
      b_t const y = (b.count_ + b_max + 1);
      if (x > 0) {
        return SST_DEBUG ?
                   sst::checked_cast<d_t>(-sst::checked_t<d_t>(x - 1U) - 1
                                          - sst::checked_t<d_t>(y)) :
                   static_cast<d_t>(-static_cast<d_t>(x - 1U) - 1
                                    - static_cast<d_t>(y));
      }
      if (y > 0) {
        return SST_DEBUG ?
                   sst::checked_cast<d_t>(-sst::checked_t<d_t>(y - 1) - 1
                                          - sst::checked_t<d_t>(x)) :
                   static_cast<d_t>(-static_cast<d_t>(y - 1) - 1
                                    - static_cast<d_t>(x));
      }
      return 0;
    }
    if (sst::is_negative(b.count_)) {
      return SST_DEBUG ?
                 sst::checked_cast<d_t>(sst::checked_t<d_t>(a.delta_)
                                        - sst::checked_t<d_t>(b.count_)) :
                 static_cast<d_t>(static_cast<d_t>(a.delta_)
                                  - static_cast<d_t>(b.count_));
    }
    if (sst::unsigned_ge(a.delta_, b.count_)) {
      return SST_DEBUG ? sst::checked_cast<d_t>(
                 a.delta_ - static_cast<a_t>(b.count_)) :
                         static_cast<d_t>(a.delta_
                                          - static_cast<a_t>(b.count_));
    }
    return SST_DEBUG ? sst::checked_cast<d_t>(
               -sst::checked_t<d_t>(b.count_ - static_cast<b_t>(a.delta_)
                                  - static_cast<b_t>(1))
               - 1) :
                       static_cast<d_t>(-static_cast<d_t>(
                                            b.count_
                                            - static_cast<b_t>(a.delta_)
                                            - static_cast<b_t>(1))
                                        - 1);
  }

  //--------------------------------------------------------------------
  // Subscript operator
  //--------------------------------------------------------------------

  template<class Integer>
  auto operator[](Integer && n) const -> decltype(it_[0]) {
    // clang-format off
    SST_ASSERT((!is_count_) && "operator[] cannot be used on an sst::count_it.");
    SST_ASSERT((!is_bound_));
    // clang-format on
    difference_type const k = n;
    return it_[k];
  }

  //--------------------------------------------------------------------
  // Comparison operators
  //--------------------------------------------------------------------

#define SST_F(op, perfect_op)                                          \
  friend bool operator op(it_t const & a, it_t const & b) {            \
    SST_ASSERT((!a.is_count_ || !b.is_count_)                          \
               && "The " #op " operator cannot be used to compare "    \
                  "two sst::count_it iterators.");                     \
    if (!a.is_count_ && !b.is_count_) {                                \
      return a.it_ op b.it_;                                           \
    }                                                                  \
    if (a.is_count_) {                                                 \
      return perfect_op(a.count_, b.delta_);                           \
    }                                                                  \
    return perfect_op(a.delta_, b.count_);                             \
  }

  SST_F(<, sst::perfect_lt)
  SST_F(>, sst::perfect_gt)
  SST_F(<=, sst::perfect_le)
  SST_F(>=, sst::perfect_ge)
  SST_F(==, sst::perfect_eq)
  SST_F(!=, sst::perfect_ne)

#undef SST_F

  //--------------------------------------------------------------------
};

} // namespace guts
} // namespace sst

#endif // SST_PRIVATE_GUTS_IT_T_HPP
