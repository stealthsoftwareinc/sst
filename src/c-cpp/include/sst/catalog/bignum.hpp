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

#ifndef SST_CATALOG_BIGNUM_HPP
#define SST_CATALOG_BIGNUM_HPP

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_CONSTEXPR_ASSERT.hpp>
#include <sst/catalog/SST_NODISCARD.hpp>
#include <sst/catalog/SST_THROW_UNIMPLEMENTED.hpp>
#include <sst/catalog/SST_WITH_NTL.h>
#include <sst/catalog/bigint_marker.hpp>
#include <sst/catalog/bignum_error.hpp>
#include <sst/catalog/buffer_overrun.hpp>
#include <sst/catalog/buffer_underrun.hpp>
#include <sst/catalog/can_represent_all.hpp>
#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/checked_t.hpp>
#include <sst/catalog/enable_if.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/indeterminate.hpp>
#include <sst/catalog/indeterminate_t.hpp>
#include <sst/catalog/int_max_v.hpp>
#include <sst/catalog/integer_rep.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/is_zero.hpp>
#include <sst/catalog/max.hpp>
#include <sst/catalog/remove_cvref.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/to_string.hpp>
#include <sst/catalog/to_unsigned.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/uchar_max_v.hpp>
#include <sst/catalog/uchar_msb_v.hpp>
#include <sst/catalog/unsigned_gt.hpp>
#include <sst/catalog/unsigned_le.hpp>
#include <sst/catalog/unsigned_lt.hpp>
#include <sst/catalog/value_bits.hpp>
#include <sst/private/SST_DLL_EXPORT.h>
#include <sst/private/bignum_st.h>
#include <sst/private/guts/bignum/bignum_pool.hpp>
#include <sst/private/guts/bignum/bignum_ptr_t.hpp>
#include <sst/private/guts/bignum/zero.hpp>

#include <openssl/bn.h>

#if SST_WITH_NTL
#include <NTL/ZZ.h>
#endif

//----------------------------------------------------------------------
// std::numeric_limits specialization (part 1 of 2)
//----------------------------------------------------------------------

namespace sst {

class bignum;

} // namespace sst

namespace std {

template<>
class SST_DLL_EXPORT numeric_limits<sst::bignum> {

public:

  static constexpr bool is_specialized = true;

  static constexpr sst::bignum const & min() noexcept;

  static constexpr sst::bignum const & max() noexcept;

  static constexpr sst::bignum const & lowest() noexcept;

  static constexpr int digits = 0;

  static constexpr int digits10 = 0;

  static constexpr int max_digits10 = 0;

  static constexpr bool is_signed = true;

  static constexpr bool is_integer = true;

  static constexpr bool is_exact = true;

  static constexpr int radix = 2;

  static constexpr sst::bignum const & epsilon() noexcept;

  static constexpr sst::bignum const & round_error() noexcept;

  static constexpr int min_exponent = 0;

  static constexpr int min_exponent10 = 0;

  static constexpr int max_exponent = 0;

  static constexpr int max_exponent10 = 0;

  static constexpr bool has_infinity = false;

  static constexpr bool has_quiet_NaN = false;

  static constexpr bool has_signaling_NaN = false;

  static constexpr std::float_denorm_style has_denorm =
      std::float_denorm_style::denorm_indeterminate;

  static constexpr bool has_denorm_loss = false;

  static constexpr sst::bignum const & infinity() noexcept;

  static constexpr sst::bignum const & quiet_NaN() noexcept;

  static constexpr sst::bignum const & signaling_NaN() noexcept;

  static constexpr sst::bignum const & denorm_min() noexcept;

  static constexpr bool is_iec559 = false;

  static constexpr bool is_bounded = false;

  static constexpr bool is_modulo = false;

  static constexpr bool traps = false;

  static constexpr bool tinyness_before = false;

  static constexpr std::float_round_style round_style =
      std::float_round_style::round_indeterminate;

}; //

template<>
class numeric_limits<sst::bignum const>
    : public numeric_limits<sst::bignum> {};

template<>
class numeric_limits<sst::bignum volatile>
    : public numeric_limits<sst::bignum> {};

template<>
class numeric_limits<sst::bignum const volatile>
    : public numeric_limits<sst::bignum> {};

} // namespace std

//----------------------------------------------------------------------

namespace sst {

namespace guts {
namespace bignum {

//----------------------------------------------------------------------
// bignum_bn_ctx_t
//----------------------------------------------------------------------
//
// A BN_CTX that allocates itself on first use and frees itself on
// destruction.
//

class bignum_bn_ctx_t final {
  mutable BN_CTX * p_ = nullptr;

public:
  bignum_bn_ctx_t() noexcept = default;

  ~bignum_bn_ctx_t() noexcept {
    if (p_ != nullptr) {
      BN_CTX_free(p_);
    }
  }

  bignum_bn_ctx_t(bignum_bn_ctx_t const &) = delete;
  bignum_bn_ctx_t & operator=(bignum_bn_ctx_t const &) = delete;

  bignum_bn_ctx_t(bignum_bn_ctx_t &&) = delete;
  bignum_bn_ctx_t & operator=(bignum_bn_ctx_t &&) = delete;

  operator BN_CTX *() const {
    if (p_ == nullptr) {
      p_ = BN_CTX_new();
      if (p_ == nullptr) {
        throw sst::bignum_error("BN_CTX_new() failed");
      }
    }
    return p_;
  }

  BN_CTX * operator->() const {
    return *this;
  }
};

//----------------------------------------------------------------------

extern SST_DLL_EXPORT bignum_bn_ctx_t & bignum_bn_ctx();

//----------------------------------------------------------------------
//
// The buffer_t class provides a thread-local pool of byte buffers that
// can be used for temporary purposes. Constructing a buffer_t acquires
// a buffer from the pool, calling the get() function retrieves a
// reference to the acquired buffer, and destructing the buffer_t
// releases the buffer back to the pool.
//
// The reason buffer_t exists is so that sst::bignum functions that use
// temporary byte buffers aren't constantly allocating and deallocating
// memory.
//

class SST_DLL_EXPORT buffer_t final {
  std::vector<unsigned char> buffer;

public:
  using size_type = decltype(buffer)::size_type;

  buffer_t();

  buffer_t(size_type const size) : buffer_t() {
    buffer.resize(size);
  }

  buffer_t(buffer_t const &) = delete;
  buffer_t(buffer_t &&) = delete;
  buffer_t & operator=(buffer_t const &) = default;
  buffer_t & operator=(buffer_t &&) = delete;

  ~buffer_t() noexcept;

  auto begin() -> decltype(buffer.begin()) {
    return buffer.begin();
  }

  auto begin() const -> decltype(buffer.begin()) {
    return buffer.begin();
  }

  auto data() -> decltype(buffer.data()) {
    return buffer.data();
  }

  auto data() const -> decltype(buffer.data()) {
    return buffer.data();
  }

  auto end() -> decltype(buffer.end()) {
    return buffer.end();
  }

  auto end() const -> decltype(buffer.end()) {
    return buffer.end();
  }

  auto operator[](size_type const i) -> decltype(buffer[i]) {
    return buffer[i];
  }

  auto operator[](size_type const i) const -> decltype(buffer[i]) {
    return buffer[i];
  }

  auto size() const -> decltype(buffer.size()) {
    return buffer.size();
  }
};

} // namespace bignum
} // namespace guts

//----------------------------------------------------------------------

class SST_DLL_EXPORT bignum : public sst::bigint_marker {

  static constexpr BN_ULONG bn_ulong_max() noexcept {
    return sst::type_max<BN_ULONG>::value;
  }

  // A fixed maximum number of BIGNUM's in the pool should be okay for
  // now. Let's not go crazy on designing the pooling system without
  // concrete experience motivating us.
  static constexpr std::size_t pool_max = 1000;

  guts::bignum::bignum_ptr_t p_;
  bool recycle_ = true;

  explicit bignum(sst::indeterminate_t, bool const indeterminate) {
    auto & pool = guts::bignum::bignum_pool();
    while (!pool.empty()) {
      p_ = std::move(pool.back());
      pool.pop_back();
      if (p_ == nullptr) {
        // This case means pop_back() threw an exception in a previous
        // call and left a null at the end of the pool. Discard it and
        // try again.
        continue;
      }
      if (!indeterminate) {
        set_zero();
      }
      return;
    }
    p_ = BN_new();
    if (p_ == nullptr) {
      throw sst::bignum_error("BN_new() failed");
    }
  }

public:
  //--------------------------------------------------------------------

  bignum() : bignum(sst::indeterminate, false) {
  }

  explicit bignum(sst::indeterminate_t)
      : bignum(sst::indeterminate, true) {
  }

  struct static_data {};
  explicit constexpr bignum(BIGNUM const & a, static_data)
      : p_(const_cast<BIGNUM *>(&a)),
        recycle_(false) {
    SST_CONSTEXPR_ASSERT(a.flags & BN_FLG_STATIC_DATA);
  }

  //--------------------------------------------------------------------

  ~bignum() noexcept {
    // p_ will be null if we're moved-from.
    if (recycle_ && p_ != nullptr) {
      // Note that p_'s destructor will free the BIGNUM if the pool is
      // full or an exception prevents us from moving it into the pool.
      try {
        if (guts::bignum::bignum_pool().size() < pool_max) {
          guts::bignum::bignum_pool().push_back(std::move(p_));
        }
      } catch (...) {
      }
    }
  }

  bignum(bignum const & b) : bignum() {
    if (!BN_copy(p_, b.p_)) {
      // We could (try to) move the BIGNUM into the pool by calling
      // this->~bignum() in non-default constructor failure cases like
      // this, but we'll generally let p_'s destructor free it instead.
      throw sst::bignum_error("BN_copy() failed");
    }
  }

  bignum & operator=(bignum const & b) {
    if (!BN_copy(p_, b.p_)) {
      // We'll generally zero ourselves when non-const operations fail.
      // We could do without it, but it's so exceptional that we might
      // as well be friendly about it.
      set_zero();
      throw sst::bignum_error("BN_copy() failed");
    }
    return *this;
  }

  bignum(bignum &&) noexcept = default;
  bignum & operator=(bignum &&) noexcept = default;

  BIGNUM const * peek() const noexcept {
    return p_;
  }

  BIGNUM * peek() noexcept {
    return p_;
  }

  BIGNUM * take() noexcept {
    BIGNUM * const p = p_;
    p_ = nullptr;
    return p;
  }

  static BN_CTX * ctx() {
    return guts::bignum::bignum_bn_ctx();
  }

  //--------------------------------------------------------------------

  // Prefix increment.
  bignum & operator++() {
    return *this += static_cast<BN_ULONG>(1);
  }

  // Prefix decrement.
  bignum & operator--() {
    return *this -= static_cast<BN_ULONG>(1);
  }

  // Postfix increment.
  bignum operator++(int) {
    bignum r = *this;
    ++*this;
    return r;
  }

  // Postfix decrement.
  bignum operator--(int) {
    bignum r = *this;
    --*this;
    return r;
  }

  // Unary plus.
  bignum operator+() const {
    return *this;
  }

  // Unary minus.
  bignum operator-() const {
    bignum r = *this;
    r.set_neg();
    return r;
  }

  // Contextual conversion to bool.
  explicit operator bool() const noexcept {
    return !BN_is_zero(p_);
  }

  //--------------------------------------------------------------------
  // Multiplication
  //--------------------------------------------------------------------

  friend bignum operator*(bignum const & a, bignum const & b) {
    bignum r(sst::indeterminate);
    if (BN_mul(r.p_, a.p_, b.p_, ctx()) != 1) {
      throw sst::bignum_error("BN_mul() failed");
    }
    return r;
  }

  friend bignum operator*(bignum && a, bignum const & b) {
    if (BN_mul(a.p_, a.p_, b.p_, ctx()) != 1) {
      throw sst::bignum_error("BN_mul() failed");
    }
    return std::move(a);
  }

  friend bignum operator*(bignum const & a, bignum && b) {
    return std::move(b) * a;
  }

  friend bignum operator*(bignum && a, bignum && b) {
    return std::move(a) * b;
  }

  //--------------------------------------------------------------------
  // Division
  //--------------------------------------------------------------------

  friend bignum operator/(bignum const & a, bignum const & b) {
    SST_ASSERT((!b.is_zero()));
    bignum r(sst::indeterminate);
    if (BN_div(r.p_, nullptr, a.p_, b.p_, ctx()) != 1) {
      throw sst::bignum_error("BN_div() failed");
    }
    return r;
  }

  friend bignum operator/(bignum && a, bignum const & b) {
    SST_ASSERT((!b.is_zero()));
    if (BN_div(a.p_, nullptr, a.p_, b.p_, ctx()) != 1) {
      throw sst::bignum_error("BN_div() failed");
    }
    return std::move(a);
  }

  friend bignum operator/(bignum const & a, bignum && b) {
    SST_ASSERT((!b.is_zero()));
    if (BN_div(b.p_, nullptr, a.p_, b.p_, ctx()) != 1) {
      throw sst::bignum_error("BN_div() failed");
    }
    return std::move(b);
  }

  friend bignum operator/(bignum && a, bignum && b) {
    SST_ASSERT((!b.is_zero()));
    return std::move(a) / b;
  }

  //--------------------------------------------------------------------
  // Signed modular reduction
  //--------------------------------------------------------------------

  friend bignum operator%(bignum const & a, bignum const & b) {
    SST_ASSERT((!b.is_zero()));
    bignum r(sst::indeterminate);
    if (!BN_div(nullptr, r.p_, a.p_, b.p_, ctx())) {
      throw sst::bignum_error("BN_div() failed");
    }
    return r;
  }

  friend bignum operator%(bignum && a, bignum const & b) {
    SST_ASSERT((!b.is_zero()));
    if (!BN_div(nullptr, a.p_, a.p_, b.p_, ctx())) {
      throw sst::bignum_error("BN_div() failed");
    }
    return std::move(a);
  }

  friend bignum operator%(bignum const & a, bignum && b) {
    SST_ASSERT((!b.is_zero()));
    if (!BN_div(nullptr, b.p_, a.p_, b.p_, ctx())) {
      throw sst::bignum_error("BN_div() failed");
    }
    return std::move(b);
  }

  friend bignum operator%(bignum && a, bignum && b) {
    SST_ASSERT((!b.is_zero()));
    return std::move(a) % b;
  }

  //--------------------------------------------------------------------
  // Addition
  //--------------------------------------------------------------------

  friend bignum operator+(bignum const & a, bignum const & b) {
    bignum r(sst::indeterminate);
    if (BN_add(r.p_, a.p_, b.p_) != 1) {
      throw sst::bignum_error("BN_add() failed");
    }
    return r;
  }

  friend bignum operator+(bignum && a, bignum const & b) {
    if (BN_add(a.p_, a.p_, b.p_) != 1) {
      throw sst::bignum_error("BN_add() failed");
    }
    return std::move(a);
  }

  friend bignum operator+(bignum const & a, bignum && b) {
    return std::move(b) + a;
  }

  friend bignum operator+(bignum && a, bignum && b) {
    return std::move(a) + b;
  }

  //--------------------------------------------------------------------
  // Subtraction
  //--------------------------------------------------------------------

  friend bignum operator-(bignum const & a, bignum const & b) {
    bignum r(sst::indeterminate);
    if (BN_sub(r.p_, a.p_, b.p_) != 1) {
      throw sst::bignum_error("BN_sub() failed");
    }
    return r;
  }

  friend bignum operator-(bignum && a, bignum const & b) {
    if (BN_sub(a.p_, a.p_, b.p_) != 1) {
      throw sst::bignum_error("BN_sub() failed");
    }
    return std::move(a);
  }

  friend bignum operator-(bignum const & a, bignum && b) {
    if (BN_sub(b.p_, a.p_, b.p_) != 1) {
      throw sst::bignum_error("BN_sub() failed");
    }
    return std::move(b);
  }

  friend bignum operator-(bignum && a, bignum && b) {
    return std::move(a) - b;
  }

  //--------------------------------------------------------------------
  // Bitwise operators
  //--------------------------------------------------------------------

#define SST_DEFUN(op)                                                  \
                                                                       \
  bignum operator op(bignum const & c) const {                         \
    bignum const & b = *this;                                          \
    using size_type = guts::bignum::buffer_t::size_type;               \
    size_type const n =                                                \
        sst::max(b.num_bytes<size_type>(), c.num_bytes<size_type>());  \
    guts::bignum::buffer_t bbuf(n);                                    \
    guts::bignum::buffer_t cbuf(n);                                    \
    b.to_bytes(bbuf.begin(), n);                                       \
    c.to_bytes(cbuf.begin(), n);                                       \
    for (size_type i = 0; i != n; ++i) {                               \
      unsigned int const bx = bbuf[i];                                 \
      unsigned int const cx = cbuf[i];                                 \
      bbuf[i] = static_cast<unsigned char>(bx op cx);                  \
    }                                                                  \
    return bignum(bbuf);                                               \
  }                                                                    \
                                                                       \
  bignum & operator op##=(bignum const & b) {                          \
    bignum & a = *this;                                                \
    a = a op b;                                                        \
    return a;                                                          \
  }

  SST_DEFUN(&)
  SST_DEFUN(^)
  SST_DEFUN(|)

#undef SST_DEFUN

  bignum operator~() const {
    bignum const & b = *this;
    using size_type = guts::bignum::buffer_t::size_type;
    size_type const n = b.num_bytes<size_type>();
    guts::bignum::buffer_t bbuf(n);
    b.to_bytes(bbuf.begin(), n);
    for (size_type i = 0; i != n; ++i) {
      unsigned int const bx = bbuf[i];
      bbuf[i] = static_cast<unsigned char>(~bx);
    }
    return bignum(bbuf);
  }

  //--------------------------------------------------------------------
  // Shift operators
  //--------------------------------------------------------------------

private:

  static constexpr BN_ULONG max_shift_step() noexcept {
    return sst::unsigned_lt(sst::int_max_v, bn_ulong_max() - 1) ?
               static_cast<BN_ULONG>(sst::int_max_v) :
               static_cast<BN_ULONG>(bn_ulong_max() - 1);
  }

public:
#define SST_DEFUN(op, func)                                            \
                                                                       \
  template<class T,                                                    \
           typename sst::enable_if<                                    \
               sst::can_represent_all<int, T>::value>::type = 0>       \
  bignum & operator op##=(T const n) {                                 \
    SST_ASSERT((!is_negative()));                                      \
    SST_ASSERT((!sst::is_negative(n)));                                \
    if (func(p_, p_, static_cast<int>(n)) != 1) {                      \
      set_zero();                                                      \
      throw sst::bignum_error(#func "() failed");                      \
    }                                                                  \
    return *this;                                                      \
  }                                                                    \
                                                                       \
  template<class T,                                                    \
           typename sst::enable_if<                                    \
               !sst::can_represent_all<int, T>::value                  \
               && std::is_integral<T>::value>::type = 0>               \
  bignum & operator op##=(T n) {                                       \
    SST_ASSERT((!is_negative()));                                      \
    SST_ASSERT((!sst::is_negative(n)));                                \
    for (; sst::unsigned_gt(n, sst::int_max_v);                        \
         n -= static_cast<T>(sst::int_max_v)) {                        \
      *this op## = sst::int_max_v;                                     \
    }                                                                  \
    return *this op## = static_cast<int>(n);                           \
  }                                                                    \
                                                                       \
  template<class T,                                                    \
           typename std::enable_if<std::is_integral<T>::value,         \
                                   int>::type = 0>                     \
  bignum operator op(T const n) const {                                \
    SST_ASSERT((!is_negative()));                                      \
    SST_ASSERT((!sst::is_negative(n)));                                \
    bignum r;                                                          \
    if (sst::unsigned_gt(n, sst::int_max_v)) {                         \
      if (func(r.p_, p_, sst::int_max_v) != 1) {                       \
        throw sst::bignum_error(#func "() failed");                    \
      }                                                                \
      r op## = n - static_cast<T>(sst::int_max_v);                     \
    } else if (func(r.p_, p_, static_cast<int>(n)) != 1) {             \
      throw sst::bignum_error(#func "() failed");                      \
    }                                                                  \
    return r;                                                          \
  }                                                                    \
                                                                       \
  bignum & operator op##=(bignum const & n) {                          \
    SST_ASSERT((!is_negative()));                                      \
    SST_ASSERT((!n.is_negative()));                                    \
    BN_ULONG step = BN_get_word(n.p_);                                 \
    if (step > max_shift_step()) {                                     \
      bignum nn = n;                                                   \
      while (step > max_shift_step()) {                                \
        *this op## = static_cast<int>(max_shift_step());               \
        nn -= max_shift_step();                                        \
        step = BN_get_word(nn.p_);                                     \
      }                                                                \
    }                                                                  \
    *this op## = static_cast<int>(step);                               \
    return *this;                                                      \
  }                                                                    \
                                                                       \
  bignum & operator op##=(bignum && n) {                               \
    SST_ASSERT((!is_negative()));                                      \
    SST_ASSERT((!n.is_negative()));                                    \
    BN_ULONG step = BN_get_word(n.p_);                                 \
    if (step > max_shift_step()) {                                     \
      bignum && nn = std::move(n);                                     \
      while (step > max_shift_step()) {                                \
        *this op## = static_cast<int>(max_shift_step());               \
        nn -= max_shift_step();                                        \
        step = BN_get_word(nn.p_);                                     \
      }                                                                \
    }                                                                  \
    *this op## = static_cast<int>(step);                               \
    return *this;                                                      \
  }                                                                    \
                                                                       \
  bignum operator op(bignum const & n) const {                         \
    SST_ASSERT((!is_negative()));                                      \
    SST_ASSERT((!n.is_negative()));                                    \
    bignum r = *this;                                                  \
    r op## = n;                                                        \
    return r;                                                          \
  }                                                                    \
                                                                       \
  bignum operator op(bignum && n) const {                              \
    SST_ASSERT((!is_negative()));                                      \
    SST_ASSERT((!n.is_negative()));                                    \
    bignum r = *this;                                                  \
    r op## = std::move(n);                                             \
    return r;                                                          \
  }

  SST_DEFUN(<<, BN_lshift)
  SST_DEFUN(>>, BN_rshift)

#undef SST_DEFUN

  //--------------------------------------------------------------------
  // Comparison operators
  //--------------------------------------------------------------------

#define SST_DEFUN(op)                                                  \
                                                                       \
  friend bool operator op(bignum const & a,                            \
                          bignum const & b) noexcept {                 \
    return BN_cmp(a.p_, b.p_) op 0;                                    \
  }

  SST_DEFUN(<)
  SST_DEFUN(>)
  SST_DEFUN(<=)
  SST_DEFUN(>=)
  SST_DEFUN(==)
  SST_DEFUN(!=)

#undef SST_DEFUN

  //--------------------------------------------------------------------
  // Speed up the == and != operators for fundamental integer types
  //--------------------------------------------------------------------

  template<class T,
           sst::enable_if_t<
               std::is_integral<T>::value
               && sst::can_represent_all<BN_ULONG, T>::value> = 0>
  friend bool operator==(bignum const & a, T const b) noexcept {
    return BN_is_word(a.p_, static_cast<BN_ULONG>(b)) != 0;
  }

  template<class T,
           sst::enable_if_t<
               std::is_integral<T>::value
               && !sst::can_represent_all<BN_ULONG, T>::value> = 0>
  friend bool operator==(bignum const & a, T const b) {
    if (!sst::is_negative(b) && sst::unsigned_le(b, bn_ulong_max())) {
      return a == static_cast<BN_ULONG>(b);
    }
    return a == bignum(b);
  }

  template<class T, sst::enable_if_t<std::is_integral<T>::value> = 0>
  friend bool operator==(T const a,
                         bignum const & b) noexcept(noexcept(b == a)) {
    return b == a;
  }

  template<class T, sst::enable_if_t<std::is_integral<T>::value> = 0>
  friend bool operator!=(bignum const & a,
                         T const b) noexcept(noexcept(!(a == b))) {
    return !(a == b);
  }

  template<class T, sst::enable_if_t<std::is_integral<T>::value> = 0>
  friend bool
  operator!=(T const a,
             bignum const & b) noexcept(noexcept(!(a == b))) {
    return !(a == b);
  }

  //--------------------------------------------------------------------

  // Assignment from integer types subsumed by BN_ULONG.
  template<class IntType,
           typename std::enable_if<
               sst::can_represent_all<BN_ULONG, IntType>::value,
               int>::type = 0>
  bignum & operator=(IntType const a) {
    if (!BN_set_word(p_, static_cast<BN_ULONG>(a))) {
      set_zero();
      throw sst::bignum_error("BN_set_word() failed");
    }
    return *this;
  }

  // Assignment from integer types not subsumed by BN_ULONG.
  template<class IntType,
           typename std::enable_if<
               !sst::can_represent_all<BN_ULONG, IntType>::value
                   && std::is_integral<IntType>::value,
               int>::type = 0>
  bignum & operator=(IntType const a) {
    using V = decltype(+a);
    V v = static_cast<V>(a);
    bool const negative = sst::is_negative(v);
    if (negative) {
      // Two's complement prevents us from doing v = -v alone.
      ++v;
      v = -v;
    }
    V n = 1;
    using U = typename std::make_unsigned<V>::type;
    using I = decltype(U() + static_cast<BN_ULONG>(0));
    I const max = static_cast<I>(bn_ulong_max());
    int const w1 = sst::value_bits<BN_ULONG>::value;
    for (I i = static_cast<I>(v); i > max; i >>= w1 - 1, i >>= 1) {
      ++n;
    }
    V const w2 = static_cast<V>(w1);
    *this = static_cast<BN_ULONG>(v >> (--n * w2));
    while (n != 0) {
      *this <<= w1;
      *this += static_cast<BN_ULONG>(v >> (--n * w2));
    }
    if (negative) {
      set_neg();
      --*this;
    }
    return *this;
  }

  // Implicit construction from any integer type.
  template<class IntType,
           typename std::enable_if<std::is_integral<IntType>::value,
                                   int>::type = 0>
  bignum(IntType const a) : bignum() {
    *this = a;
  }

  //--------------------------------------------------------------------

  template<class T,
           typename std::enable_if<std::is_integral<T>::value,
                                   int>::type = 0>
  explicit operator T() const noexcept {
    bool const negative = BN_is_negative(p_);
    auto const n = +BN_num_bits(p_);
    typename std::conditional<std::is_signed<T>::value,
                              decltype(+T()),
                              decltype(sst::to_unsigned(T()))>::type x =
        0;
    for (decltype(+n) i = 0; i != n; ++i) {
      x *= 2;
      if (BN_is_bit_set(p_, n - 1 - i)) {
        if (negative) {
          --x;
        } else {
          ++x;
        }
      }
    }
    return static_cast<T>(x);
  }

  template<class T,
           typename std::enable_if<
               sst::can_represent_all<BN_ULONG, T>::value,
               int>::type = 0>
  T extract() const noexcept {
    return static_cast<T>(BN_get_word(p_));
  }

  template<class T,
           typename std::enable_if<
               !sst::can_represent_all<BN_ULONG, T>::value
                   && std::is_integral<T>::value,
               int>::type = 0>
  T extract() const noexcept {
    return static_cast<T>(*this);
  }

  //--------------------------------------------------------------------

  template<class InputIt>
  static bignum from_string(InputIt first, InputIt const last) {
    bignum r;
    using T = decltype(+*first);
    if (first == last) {
      throw sst::bignum_error("invalid string");
    }
    bool negative = false;
    if (*first == T('+') || *first == T('-')) {
      negative = (*first == T('-'));
      if (++first == last) {
        throw sst::bignum_error("invalid string");
      }
    }
    int base = 10;
    if (*first == T('0')) {
      if (++first == last) {
        return r;
      }
      if (*first == T('b') || *first == T('B')) {
        base = 2;
      } else if (*first == T('o') || *first == T('O')) {
        base = 8;
      } else if (*first == T('x') || *first == T('X')) {
        base = 16;
      } else {
        throw sst::bignum_error("invalid string");
      }
      if (++first == last) {
        throw sst::bignum_error("invalid string");
      }
    }
    bool first_digit = true;
    for (; first != last; ++first) {
      if (first_digit) {
        first_digit = false;
      } else if (*first == T('\'')) {
        if (++first == last) {
          throw sst::bignum_error("invalid string");
        }
      }
      BN_ULONG digit;
      if (*first >= T('0')
          && *first <= T('0') + T(std::min(base - 1, 9))) {
        digit = static_cast<BN_ULONG>(*first - T('0'));
      } else if (base > 10 && *first >= T('A')
                 && *first <= T('A') + T(base - 11)) {
        digit = static_cast<BN_ULONG>(*first - T('A')) + 10;
      } else if (base > 10 && *first >= T('a')
                 && *first <= T('a') + T(base - 11)) {
        digit = static_cast<BN_ULONG>(*first - T('a')) + 10;
      } else {
        throw sst::bignum_error("invalid string");
      }
      if (base == 2) {
        r <<= 1;
      } else if (base == 8) {
        r <<= 3;
      } else if (base == 16) {
        r <<= 4;
      } else {
        r *= static_cast<BN_ULONG>(base);
      }
      r += digit;
    }
    if (negative) {
      r.set_neg();
    }
    return r;
  }

  static bignum from_string(std::string const & s) {
    return from_string(s.begin(), s.end());
  }

  explicit bignum(std::string const & s) : bignum(from_string(s)) {
  }

  //--------------------------------------------------------------------
  // to_string
  //--------------------------------------------------------------------

private:
  template<class OutputIt>
  OutputIt foo_to_string(OutputIt out) const {
    bool const neg = is_negative();
    bignum x = *this;
    if (neg) {
      x.set_neg();
    }
    do {
      *out++ = static_cast<char>(
          '0' + static_cast<char>(BN_div_word(x.p_, 10)));
    } while (!BN_is_zero(x.p_));
    if (neg) {
      *out++ = '-';
    }
    return out;
  }

public:
  template<class = void>
  static std::string to_string(sst::bignum const & a) {
    std::string s;
    a.foo_to_string(std::back_inserter(s));
    std::reverse(s.begin(), s.end());
    return s;
  }

  template<class X = void>
  std::string to_string() const {
    return sst::bignum::to_string<X>(*this);
  }

  //--------------------------------------------------------------------

  bignum & operator*=(bignum const & a) {
    if (!BN_mul(p_, p_, a.p_, ctx())) {
      set_zero();
      throw sst::bignum_error("BN_mul() failed");
    }
    return *this;
  }

  template<class IntType,
           typename std::enable_if<
               sst::can_represent_all<BN_ULONG, IntType>::value,
               int>::type = 0>
  bignum & operator*=(IntType const a) {
    if (!BN_mul_word(p_, static_cast<BN_ULONG>(a))) {
      set_zero();
      throw sst::bignum_error("BN_mul_word() failed");
    }
    return *this;
  }

#define SST_DEFUN(op)                                                  \
                                                                       \
  template<class IntType,                                              \
           typename std::enable_if<                                    \
               !sst::can_represent_all<BN_ULONG, IntType>::value       \
                   && std::is_integral<IntType>::value,                \
               int>::type = 0>                                         \
  bignum & operator op(IntType const a) {                              \
    if (!sst::is_negative(a) && sst::unsigned_le(a, bn_ulong_max())) { \
      return *this op static_cast<BN_ULONG>(a);                        \
    }                                                                  \
    if (sst::is_negative(a)                                            \
        && sst::unsigned_lt(-(a + 1), bn_ulong_max())) {               \
      set_neg();                                                       \
      return *this op static_cast<BN_ULONG>(                           \
          static_cast<BN_ULONG>(-(a + 1)) + static_cast<BN_ULONG>(1)); \
    }                                                                  \
    return *this op bignum(a);                                         \
  }

  SST_DEFUN(*=)

  //--------------------------------------------------------------------

  bignum & operator/=(bignum const & a) {
    if (!BN_div(p_, nullptr, p_, a.p_, ctx())) {
      set_zero();
      throw sst::bignum_error("BN_div() failed");
    }
    return *this;
  }

  template<class IntType,
           typename std::enable_if<
               sst::can_represent_all<BN_ULONG, IntType>::value,
               int>::type = 0>
  bignum & operator/=(IntType const a) {
    BN_ULONG const r = BN_div_word(p_, static_cast<BN_ULONG>(a));
    if (r == bn_ulong_max()) {
      set_zero();
      throw sst::bignum_error("BN_div_word() failed");
    }
    return *this;
  }

  SST_DEFUN(/=)

  //--------------------------------------------------------------------

  bignum & operator%=(bignum const & a) {
    if (!BN_div(nullptr, p_, p_, a.p_, ctx())) {
      set_zero();
      throw sst::bignum_error("BN_div() failed");
    }
    return *this;
  }

  template<class IntType,
           typename std::enable_if<
               sst::can_represent_all<BN_ULONG, IntType>::value,
               int>::type = 0>
  bignum & operator%=(IntType const a) {
    BN_ULONG const r = BN_mod_word(p_, static_cast<BN_ULONG>(a));
    if (r == bn_ulong_max()) {
      set_zero();
      throw sst::bignum_error("BN_mod_word() failed");
    }
    return *this = r;
  }

  SST_DEFUN(%=)

#undef SST_DEFUN

  //--------------------------------------------------------------------

#define SST_DEFUN(bn_op, bn_op_word, op, reverse_op)                   \
                                                                       \
  bignum & operator op(bignum const & a) {                             \
    if (!bn_op(p_, p_, a.p_)) {                                        \
      set_zero();                                                      \
      throw sst::bignum_error(#bn_op "() failed");                     \
    }                                                                  \
    return *this;                                                      \
  }                                                                    \
                                                                       \
  template<class IntType,                                              \
           typename std::enable_if<                                    \
               sst::can_represent_all<BN_ULONG, IntType>::value,       \
               int>::type = 0>                                         \
  bignum & operator op(IntType const a) {                              \
    if (!bn_op_word(p_, static_cast<BN_ULONG>(a))) {                   \
      set_zero();                                                      \
      throw sst::bignum_error(#bn_op_word "() failed");                \
    }                                                                  \
    return *this;                                                      \
  }                                                                    \
                                                                       \
  template<class IntType,                                              \
           typename std::enable_if<                                    \
               !sst::can_represent_all<BN_ULONG, IntType>::value       \
                   && std::is_integral<IntType>::value,                \
               int>::type = 0>                                         \
  bignum & operator op(IntType const a) {                              \
    if (!sst::is_negative(a) && sst::unsigned_le(a, bn_ulong_max())) { \
      return *this op static_cast<BN_ULONG>(a);                        \
    }                                                                  \
    if (sst::is_negative(a)                                            \
        && sst::unsigned_lt(-(a + 1), bn_ulong_max())) {               \
      return *this reverse_op static_cast<BN_ULONG>(                   \
          static_cast<BN_ULONG>(-(a + 1)) + static_cast<BN_ULONG>(1)); \
    }                                                                  \
    return *this op bignum(a);                                         \
  }

  SST_DEFUN(BN_add, BN_add_word, +=, -=)
  SST_DEFUN(BN_sub, BN_sub_word, -=, +=)

#undef SST_DEFUN

  //--------------------------------------------------------------------
  // sst::bignum::abs
  //--------------------------------------------------------------------

  static sst::bignum abs(sst::bignum const & a) {
    sst::bignum r = a;
    r.set_abs();
    return r;
  }

  friend sst::bignum abs(sst::bignum const & a) {
    return sst::bignum::abs(a);
  }

  sst::bignum abs() const {
    return sst::bignum::abs(*this);
  }

  //--------------------------------------------------------------------
  // sst::bignum::add_mod
  //--------------------------------------------------------------------

  static sst::bignum add_mod(sst::bignum const & a,
                             sst::bignum const & b,
                             sst::bignum const & m) {
    SST_ASSERT(a >= 0);
    SST_ASSERT(b >= 0);
    SST_ASSERT(m > 0);
    sst::bignum r;
    auto const s = BN_mod_add(r.p_, a.p_, b.p_, m.p_, ctx());
    if (s != 1) {
      throw sst::bignum_error("BN_mod_add() returned "
                              + sst::to_string(s));
    }
    return r;
  }

  sst::bignum add_mod(sst::bignum const & b,
                      sst::bignum const & m) const {
    return sst::bignum::add_mod(*this, b, m);
  }

  friend sst::bignum add_mod(sst::bignum const & a,
                             sst::bignum const & b,
                             sst::bignum const & m) {
    return sst::bignum::add_mod(a, b, m);
  }

  //--------------------------------------------------------------------
  // from_bytes
  //--------------------------------------------------------------------

public:

  template<class... Args>
  SST_NODISCARD()
  static bignum from_bytes(Args &&... args) {
    bignum r;
    r.set_from_bytes(std::forward<Args>(args)...);
    return r;
  }

  //--------------------------------------------------------------------
  // sst::bignum::inv_mod
  //--------------------------------------------------------------------

  static sst::bignum inv_mod(sst::bignum const & a,
                             sst::bignum const & m) {
    SST_ASSERT(a >= 0);
    SST_ASSERT(m > 0);
    sst::bignum r;
    auto const s = BN_mod_inverse(r.p_, a.p_, m.p_, ctx());
    if (s == nullptr) {
      throw sst::bignum_error("BN_mod_inverse() returned null");
    }
    return r;
  }

  sst::bignum inv_mod(sst::bignum const & m) const {
    return sst::bignum::inv_mod(*this, m);
  }

  friend sst::bignum inv_mod(sst::bignum const & a,
                             sst::bignum const & m) {
    return sst::bignum::inv_mod(a, m);
  }

  //--------------------------------------------------------------------
  // sst::bignum::is_negative
  //--------------------------------------------------------------------

  static bool is_negative(sst::bignum const & a) noexcept {
    return BN_is_negative(a.p_) != 0;
  }

  friend bool is_negative(sst::bignum const & a) noexcept {
    return sst::bignum::is_negative(a);
  }

  bool is_negative() const noexcept {
    return sst::bignum::is_negative(*this);
  }

  //--------------------------------------------------------------------
  // sst::bignum::is_zero
  //--------------------------------------------------------------------

  static bool is_zero(sst::bignum const & a) noexcept {
    return BN_is_zero(a.p_) != 0;
  }

  friend bool is_zero(sst::bignum const & a) noexcept {
    return sst::bignum::is_zero(a);
  }

  bool is_zero() const noexcept {
    return sst::bignum::is_zero(*this);
  }

  //--------------------------------------------------------------------
  // sst::bignum::mul_mod
  //--------------------------------------------------------------------

  static sst::bignum mul_mod(sst::bignum const & a,
                             sst::bignum const & b,
                             sst::bignum const & m) {
    SST_ASSERT(a >= 0);
    SST_ASSERT(b >= 0);
    SST_ASSERT(m > 0);
    sst::bignum r;
    auto const s = BN_mod_mul(r.p_, a.p_, b.p_, m.p_, ctx());
    if (s != 1) {
      throw sst::bignum_error("BN_mod_mul() returned "
                              + sst::to_string(s));
    }
    return r;
  }

  sst::bignum mul_mod(sst::bignum const & b,
                      sst::bignum const & m) const {
    return sst::bignum::mul_mod(*this, b, m);
  }

  friend sst::bignum mul_mod(sst::bignum const & a,
                             sst::bignum const & b,
                             sst::bignum const & m) {
    return sst::bignum::mul_mod(a, b, m);
  }

  //--------------------------------------------------------------------
  // num_bits
  //--------------------------------------------------------------------

  template<class N_ = std::size_t, class N = sst::remove_cvref_t<N_>>
  N num_bits(sst::integer_rep const rep =
                 sst::integer_rep::twos_complement()) const {
    switch (rep) {
      case sst::integer_rep::twos_complement(): {
        return ((is_negative() ? -(*this + 1) : *this) << 1)
            .num_bits<N>(sst::integer_rep::pure_unsigned());
      } break;
      case sst::integer_rep::pure_unsigned(): {
        SST_ASSERT((!is_negative()));
        auto const n = BN_num_bits(p_);
        if (sst::is_negative(n)) {
          throw sst::bignum_error("BN_num_bits() returned "
                                  + sst::to_string(n));
        }
        if (sst::is_zero(n)) {
          return static_cast<N>(1);
        }
        return sst::checked_cast<N>(n);
      } break;
      default: {
        SST_THROW_UNIMPLEMENTED();
      } break;
    }
  }

  //--------------------------------------------------------------------
  // num_bytes
  //--------------------------------------------------------------------

  template<class N_ = std::size_t, class N = sst::remove_cvref_t<N_>>
  N num_bytes(sst::integer_rep const rep =
                  sst::integer_rep::twos_complement()) const {
    switch (rep) {
      case sst::integer_rep::twos_complement(): {
        return ((is_negative() ? -(*this + 1) : *this) << 1)
            .num_bytes<N>(sst::integer_rep::pure_unsigned());
      } break;
      case sst::integer_rep::pure_unsigned(): {
        SST_ASSERT((!is_negative()));
        auto const n = BN_num_bytes(p_);
        if (sst::is_negative(n)) {
          throw sst::bignum_error("BN_num_bytes() returned "
                                  + sst::to_string(n));
        }
        if (sst::is_zero(n)) {
          return static_cast<N>(1);
        }
        return sst::checked_cast<N>(n);
      } break;
      default: {
        SST_THROW_UNIMPLEMENTED();
      } break;
    }
  }

  //--------------------------------------------------------------------
  // sst::bignum::pow_mod
  //--------------------------------------------------------------------

  // TODO: Support a < 0 and b < 0. When b < 0, assert that m > 1 and
  // gcd(a%m, m) == 1.

  static sst::bignum pow_mod(sst::bignum const & a,
                             sst::bignum const & b,
                             sst::bignum const & m) {
    SST_ASSERT(!(a == 0 && b == 0));
    SST_ASSERT(a >= 0);
    SST_ASSERT(b >= 0);
    SST_ASSERT(m > 0);
    sst::bignum r;
    auto const s = BN_mod_exp(r.p_, a.p_, b.p_, m.p_, ctx());
    if (s != 1) {
      throw sst::bignum_error("BN_mod_exp() failed");
    }
    return r;
  }

  sst::bignum pow_mod(sst::bignum const & b,
                      sst::bignum const & m) const {
    return sst::bignum::pow_mod(*this, b, m);
  }

  friend sst::bignum pow_mod(sst::bignum const & a,
                             sst::bignum const & b,
                             sst::bignum const & m) {
    return sst::bignum::pow_mod(a, b, m);
  }

  //--------------------------------------------------------------------
  // sst::bignum::rand_range
  //--------------------------------------------------------------------

  static sst::bignum rand_range(sst::bignum const & m) {
    SST_ASSERT((m > 0));
    sst::bignum r;
    auto const s = BN_rand_range(r.p_, m.p_);
    if (s != 1) {
      throw sst::bignum_error("BN_rand_range() returned "
                              + sst::to_string(s));
    }
    SST_ASSERT((r >= 0));
    SST_ASSERT((r < m));
    return r;
  }

  friend sst::bignum rand_range(sst::bignum const & m) {
    return sst::bignum::rand_range(m);
  }

  sst::bignum rand_range() const {
    return sst::bignum::rand_range(*this);
  }

  //--------------------------------------------------------------------
  // sst::bignum::set_abs
  //--------------------------------------------------------------------

  static sst::bignum & set_abs(sst::bignum & a) {
    BN_set_negative(a.p_, 0);
    return a;
  }

  friend sst::bignum & set_abs(sst::bignum & a) {
    return sst::bignum::set_abs(a);
  }

  sst::bignum & set_abs() {
    return sst::bignum::set_abs(*this);
  }

  //--------------------------------------------------------------------
  // sst::bignum::set_from_ZZ
  //--------------------------------------------------------------------

#if SST_WITH_NTL

  bignum & set_from_ZZ(NTL::ZZ const & x) {
    if (sign(x) < 0) {
      return set_from_ZZ(-x).set_neg();
    }
    auto const n = NumBytes(x);
    if (n == 0) {
      return set_zero();
    }
    guts::bignum::buffer_t buf(
        sst::checked_cast<guts::bignum::buffer_t::size_type>(n));
    NTL::BytesFromZZ(buf.data(), x, n);
    set_from_bytes(buf.data(), n, sst::integer_rep::pure_unsigned());
    return *this;
  }

#endif

  //--------------------------------------------------------------------
  // sst::bignum::set_neg
  //--------------------------------------------------------------------

  static bignum & set_neg(sst::bignum & a) noexcept {
    BN_set_negative(a.p_, !a.is_negative());
    return a;
  }

  friend bignum & set_neg(sst::bignum & a) noexcept {
    return sst::bignum::set_neg(a);
  }

  bignum & set_neg() noexcept {
    return sst::bignum::set_neg(*this);
  }

  //--------------------------------------------------------------------
  // sst::bignum::set_zero
  //--------------------------------------------------------------------

  static bignum & set_zero(sst::bignum & a) noexcept {
    BN_zero(a.p_);
    return a;
  }

  friend bignum & set_zero(sst::bignum & a) noexcept {
    return sst::bignum::set_zero(a);
  }

  bignum & set_zero() noexcept {
    return sst::bignum::set_zero(*this);
  }

  //--------------------------------------------------------------------
  // sst::bignum::sub_mod
  //--------------------------------------------------------------------

  static sst::bignum sub_mod(sst::bignum const & a,
                             sst::bignum const & b,
                             sst::bignum const & m) {
    SST_ASSERT(a >= 0);
    SST_ASSERT(b >= 0);
    SST_ASSERT(m > 0);
    sst::bignum r;
    auto const s = BN_mod_sub(r.p_, a.p_, b.p_, m.p_, ctx());
    if (s != 1) {
      throw sst::bignum_error("BN_mod_sub() returned "
                              + sst::to_string(s));
    }
    return r;
  }

  sst::bignum sub_mod(sst::bignum const & b,
                      sst::bignum const & m) const {
    return sst::bignum::sub_mod(*this, b, m);
  }

  friend sst::bignum sub_mod(sst::bignum const & a,
                             sst::bignum const & b,
                             sst::bignum const & m) {
    return sst::bignum::sub_mod(a, b, m);
  }

  //--------------------------------------------------------------------
  // swap
  //--------------------------------------------------------------------

  friend void swap(sst::bignum & a, sst::bignum & b) {
    swap(a.p_, b.p_);
  }

  //--------------------------------------------------------------------
  // sst::bignum::to_ZZ
  //--------------------------------------------------------------------

#if SST_WITH_NTL

  NTL::ZZ to_ZZ() const {
    if (is_negative()) {
      return -(-*this).to_ZZ();
    }
    auto const n = num_bytes(sst::integer_rep::pure_unsigned());
    guts::bignum::buffer_t buf(
        sst::checked_cast<guts::bignum::buffer_t::size_type>(n));
    to_bytes(buf.data(), n, sst::integer_rep::pure_unsigned());
    return NTL::ZZFromBytes(buf.data(), sst::checked_cast<long>(n));
  }

#endif

  //--------------------------------------------------------------------
  // sst::bignum::to_bytes
  //--------------------------------------------------------------------

  // TODO: Support endianness selection.

private:
  template<class ByteIt, class SizeOrByteIt, class Function>
  ByteIt
  private_to_bytes(ByteIt dst,
                   SizeOrByteIt size_or_end,
                   Function && step,
                   sst::integer_rep const rep =
                       sst::integer_rep::twos_complement()) const {
    switch (rep) {
      case sst::integer_rep::pure_unsigned():
      case sst::integer_rep::twos_complement(): {
        bool const negative = rep == sst::integer_rep::pure_unsigned() ?
                                  (SST_ASSERT(!is_negative()), false) :
                                  is_negative();
        using size_type = guts::bignum::buffer_t::size_type;
        guts::bignum::buffer_t digits(num_bytes<size_type>());
        auto i = static_cast<size_type>(BN_bn2bin(p_, &digits[0]));
        unsigned int digit = 0;
        unsigned int carry = 1;
        while (step(dst, size_or_end)) {
          digit = i != 0 ? digits[--i] : 0;
          if (negative) {
            auto const flip = static_cast<unsigned char>(~digit);
            digit = static_cast<unsigned char>(flip + carry);
            carry = flip > digit;
          }
          *dst++ = static_cast<unsigned char>(digit);
        }
        if (i != 0
            || (rep == sst::integer_rep::twos_complement()
                && bool(digit & sst::uchar_msb_v) != negative)) {
          throw sst::buffer_overrun(
              "sst::bignum::to_bytes: buffer overrun");
        }
      } break;
      default: {
        SST_THROW_UNIMPLEMENTED();
      } break;
    }
    return dst;
  }

public:
  template<
      class ByteIt,
      class Size,
      typename sst::enable_if<std::is_integral<
          typename sst::remove_cvref<Size>::type>::value>::type = 0>
  ByteIt to_bytes(ByteIt const dst,
                  Size const size,
                  sst::integer_rep const rep =
                      sst::integer_rep::twos_complement()) const {
    SST_ASSERT(sst::perfect_gt(size, 0));
    return private_to_bytes(
        dst,
        size,
        [](ByteIt, Size & size) {
          return size != 0 ? (--size, true) : false;
        },
        rep);
  }

  template<
      class ByteIt,
      typename sst::enable_if<!std::is_integral<
          typename sst::remove_cvref<ByteIt>::type>::value>::type = 0>
  ByteIt to_bytes(ByteIt const dst,
                  ByteIt const end,
                  sst::integer_rep const rep =
                      sst::integer_rep::twos_complement()) const {
    SST_ASSERT(dst != end);
    return private_to_bytes(
        dst,
        end,
        [](ByteIt const dst, ByteIt const end) { return dst != end; },
        rep);
  }

  template<class ByteSequence = std::vector<unsigned char>>
  ByteSequence to_bytes(sst::integer_rep const rep =
                            sst::integer_rep::twos_complement()) const {
    using size_type = typename ByteSequence::size_type;
    ByteSequence dst(num_bytes<size_type>(rep), 0);
    to_bytes(dst.begin(), dst.end(), rep);
    return dst;
  }

  //--------------------------------------------------------------------
  // sst::bignum::set_from_bytes
  //--------------------------------------------------------------------

  // TODO: Support endianness selection.

private:
  template<class ByteIt, class SizeOrByteIt, class Function>
  ByteIt
  private_set_from_bytes(ByteIt src,
                         SizeOrByteIt size_or_end,
                         Function && step,
                         sst::integer_rep const rep =
                             sst::integer_rep::twos_complement()) {
    switch (rep) {
      case sst::integer_rep::pure_unsigned():
      case sst::integer_rep::twos_complement(): {
        set_zero();
        bignum v;
        sst::checked_t<int> k = -sst::char_bit_v;
        unsigned char digit = 0;
        while (step(src, size_or_end)) {
          digit = *src++;
          v = static_cast<BN_ULONG>(digit);
          v <<= (k += sst::char_bit_v).value();
          *this += v;
        }
        if (rep == sst::integer_rep::twos_complement()
            && digit >= sst::uchar_msb_v) {
          v = static_cast<BN_ULONG>(1);
          v <<= (k += sst::char_bit_v).value();
          *this -= v;
        }
      } break;
      default: {
        SST_THROW_UNIMPLEMENTED();
      } break;
    }
    return src;
  }

public:
  template<
      class ByteIt,
      class Size,
      typename sst::enable_if<std::is_integral<
          typename sst::remove_cvref<Size>::type>::value>::type = 0>
  ByteIt set_from_bytes(ByteIt const src,
                        Size const size,
                        sst::integer_rep const rep =
                            sst::integer_rep::twos_complement()) {
    SST_ASSERT(sst::perfect_gt(size, 0));
    return private_set_from_bytes(
        src,
        size,
        [](ByteIt, Size & size) {
          return size != 0 ? (--size, true) : false;
        },
        rep);
  }

  template<
      class ByteIt,
      class Size,
      class Avail,
      typename sst::enable_if<std::is_integral<
          typename sst::remove_cvref<Size>::type>::value>::type = 0>
  ByteIt set_from_bytes(ByteIt src,
                        Size const size,
                        Avail & avail,
                        sst::integer_rep const rep =
                            sst::integer_rep::twos_complement()) {
    SST_ASSERT(sst::perfect_gt(size, 0));
    SST_ASSERT(sst::perfect_ge(avail, 0));
    if (sst::unsigned_gt(size, avail)) {
      throw sst::buffer_underrun(
          "sst::bignum::set_from_bytes: buffer underrun");
    }
    src = set_from_bytes(src, size, rep);
    avail -= static_cast<Avail>(size);
    return src;
  }

  template<
      class ByteIt,
      typename sst::enable_if<!std::is_integral<
          typename sst::remove_cvref<ByteIt>::type>::value>::type = 0>
  ByteIt set_from_bytes(ByteIt const src,
                        ByteIt const end,
                        sst::integer_rep const rep =
                            sst::integer_rep::twos_complement()) {
    SST_ASSERT(src != end);
    return private_set_from_bytes(
        src,
        end,
        [](ByteIt const src, ByteIt const end) { return src != end; },
        rep);
  }

  template<class ByteSequence>
  bignum & set_from_bytes(ByteSequence const & src,
                          sst::integer_rep const rep =
                              sst::integer_rep::twos_complement()) {
    set_from_bytes(src.begin(), src.end(), rep);
    return *this;
  }

  template<
      class ByteSequence,
      typename sst::enable_if<
          std::is_same<typename sst::remove_cvref<
                           decltype(*std::declval<ByteSequence>()
                                         .begin())>::type,
                       unsigned char>::value
          && std::is_same<
              typename sst::remove_cvref<
                  decltype(*std::declval<ByteSequence>().end())>::type,
              unsigned char>::value>::type = 0>
  explicit bignum(
      ByteSequence const & src,
      sst::integer_rep const rep = sst::integer_rep::twos_complement())
      : bignum() {
    set_from_bytes(src, rep);
  }

  //--------------------------------------------------------------------
  // zero
  //--------------------------------------------------------------------

  static constexpr bignum const & zero() noexcept {
    return guts::bignum::zero;
  }

  //--------------------------------------------------------------------
};

} // namespace sst

//----------------------------------------------------------------------
// std::numeric_limits specialization (part 2 of 2)
//----------------------------------------------------------------------

namespace std {

constexpr sst::bignum const &
numeric_limits<sst::bignum>::min() noexcept {
  return sst::bignum::zero();
}

constexpr sst::bignum const &
numeric_limits<sst::bignum>::max() noexcept {
  return sst::bignum::zero();
}

constexpr sst::bignum const &
numeric_limits<sst::bignum>::lowest() noexcept {
  return sst::bignum::zero();
}

constexpr sst::bignum const &
numeric_limits<sst::bignum>::epsilon() noexcept {
  return sst::bignum::zero();
}

constexpr sst::bignum const &
numeric_limits<sst::bignum>::round_error() noexcept {
  return sst::bignum::zero();
}

constexpr sst::bignum const &
numeric_limits<sst::bignum>::infinity() noexcept {
  return sst::bignum::zero();
}

constexpr sst::bignum const &
numeric_limits<sst::bignum>::quiet_NaN() noexcept {
  return sst::bignum::zero();
}

constexpr sst::bignum const &
numeric_limits<sst::bignum>::signaling_NaN() noexcept {
  return sst::bignum::zero();
}

constexpr sst::bignum const &
numeric_limits<sst::bignum>::denorm_min() noexcept {
  return sst::bignum::zero();
}

} // namespace std

//----------------------------------------------------------------------

#endif // #if SST_WITH_OPENSSL_CRYPTO

#endif // SST_CATALOG_BIGNUM_HPP
