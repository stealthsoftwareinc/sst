//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_BIGNUM_HPP
#define SST_CATALOG_BIGNUM_HPP

#include <sst/config.h>

#if SST_HAVE_LIB_CRYPTO

#include <algorithm>
#include <cassert>
#include <iterator>
#include <openssl/bn.h>
#include <sst/catalog/SST_PUBLIC_CPP_CLASS.hpp>
#include <sst/catalog/SST_PUBLIC_CPP_FUNCTION.hpp>
#include <sst/catalog/bignum_error.hpp>
#include <sst/catalog/can_represent_all.hpp>
#include <sst/catalog/char_bit.hpp>
#include <sst/catalog/checked.hpp>
#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/integer_rep.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/to_unsigned.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/uchar_max.hpp>
#include <sst/catalog/unsigned_gt.hpp>
#include <sst/catalog/unsigned_le.hpp>
#include <sst/catalog/unsigned_lt.hpp>
#include <sst/catalog/value_bits.hpp>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace sst {

namespace detail {

//----------------------------------------------------------------------

//
// A BIGNUM that frees itself on destruction.
//

class bignum_ptr_t final {
  BIGNUM * p_ = nullptr;

public:
  bignum_ptr_t() noexcept = default;

  bignum_ptr_t(BIGNUM * const p) noexcept : p_(p) {
  }

  ~bignum_ptr_t() noexcept {
    if (p_ != nullptr) {
      BN_free(p_);
    }
  }

  bignum_ptr_t(bignum_ptr_t const &) = delete;
  bignum_ptr_t & operator=(bignum_ptr_t const &) = delete;

  bignum_ptr_t(bignum_ptr_t && other) noexcept : p_(other.p_) {
    other.p_ = nullptr;
  }

  bignum_ptr_t & operator=(bignum_ptr_t && other) noexcept {
    std::swap(p_, other.p_);
    return *this;
  }

  operator BIGNUM *() const noexcept {
    return p_;
  }

  BIGNUM * operator->() const noexcept {
    return p_;
  }
};

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
    return p_;
  }
};

//----------------------------------------------------------------------

SST_PUBLIC_CPP_FUNCTION
std::vector<detail::bignum_ptr_t> & bignum_pool() noexcept;

SST_PUBLIC_CPP_FUNCTION
detail::bignum_bn_ctx_t & bignum_bn_ctx() noexcept;

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

class SST_PUBLIC_CPP_CLASS buffer_t final {
  std::vector<unsigned char> buffer;

public:
  buffer_t();
  buffer_t(std::size_t const size) : buffer_t() {
    buffer.resize(size);
  }
  buffer_t(buffer_t const &) = delete;
  buffer_t(buffer_t &&) = delete;
  buffer_t & operator=(buffer_t const &) = delete;
  buffer_t & operator=(buffer_t &&) = delete;
  ~buffer_t() noexcept;
  std::vector<unsigned char> & get() noexcept {
    return buffer;
  }
};

} // namespace detail

//----------------------------------------------------------------------

class bignum {
  static constexpr BN_ULONG bn_ulong_max =
      sst::type_max<BN_ULONG>::value;

  // A fixed maximum number of BIGNUM's in the pool should be okay for
  // now. Let's not go crazy on designing the pooling system without
  // concrete experience motivating us.
  static constexpr std::size_t pool_max = 1000;

  detail::bignum_ptr_t p_;

public:
  //--------------------------------------------------------------------

  bignum() {
    // If the pool is empty, allocate a new BIGNUM. Otherwise, take one
    // from the pool.
    if (detail::bignum_pool().empty()) {
      p_ = BN_new();
      if (p_ == nullptr) {
        throw sst::bignum_error("BN_new() failed");
      }
    } else {
      // Note that p_'s destructor will free the BIGNUM if an exception
      // is thrown after we've taken it from the pool but before this
      // constructor is complete.
      p_ = std::move(detail::bignum_pool().back());
      detail::bignum_pool().pop_back();
      zero();
    }
  }

  ~bignum() noexcept {
    // p_ will be null if we're moved-from.
    if (p_ != nullptr) {
      // Note that p_'s destructor will free the BIGNUM if the pool is
      // full or an exception prevents us from moving it into the pool.
      try {
        if (detail::bignum_pool().size() < pool_max) {
          detail::bignum_pool().push_back(std::move(p_));
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
      zero();
      throw sst::bignum_error("BN_copy() failed");
    }
    return *this;
  }

  // For our move operations, it's important for performance that we
  // don't try to be friendly and reallocate or zero the other bignum.

  bignum(bignum && b) noexcept : p_(std::move(b.p_)) {
    // This leaves the other bignum valid for destruction or moving
    // into, but nothing else.
  }

  bignum & operator=(bignum && b) noexcept {
    // If this bignum is moved-from, this leaves the other bignum
    // moved-from. Otherwise, the other bignum is left with an
    // unspecified value, but valid for any operations.
    std::swap(p_, b.p_);
    return *this;
  }

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
    return detail::bignum_bn_ctx();
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
    r.negate();
    return r;
  }

  // Contextual conversion to bool.
  explicit operator bool() const noexcept {
    return !BN_is_zero(p_);
  }

  //--------------------------------------------------------------------

  bignum operator*(bignum const & b) const {
    bignum r;
    if (!BN_mul(r.p_, p_, b.p_, detail::bignum_bn_ctx())) {
      throw sst::bignum_error("BN_mul() failed");
    }
    return r;
  }

  bignum operator/(bignum const & b) const {
    bignum r;
    if (!BN_div(r.p_, nullptr, p_, b.p_, detail::bignum_bn_ctx())) {
      throw sst::bignum_error("BN_div() failed");
    }
    return r;
  }

  bignum operator%(bignum const & b) const {
    bignum r;
    if (!BN_div(nullptr, r.p_, p_, b.p_, detail::bignum_bn_ctx())) {
      throw sst::bignum_error("BN_div() failed");
    }
    return r;
  }

  bignum operator+(bignum const & b) const {
    bignum r;
    if (!BN_add(r.p_, p_, b.p_)) {
      throw sst::bignum_error("BN_add() failed");
    }
    return r;
  }

  bignum operator-(bignum const & b) const {
    bignum r;
    if (!BN_sub(r.p_, p_, b.p_)) {
      throw sst::bignum_error("BN_sub() failed");
    }
    return r;
  }

#define SST_DEFUN(op) \
  template<class IntType, \
           typename std::enable_if<std::is_integral<IntType>::value, \
                                   int>::type = 0> \
  bignum operator op(IntType const b) const { \
    bignum r = *this; \
    r op## = b; \
    return r; \
  }

  SST_DEFUN(*)
  SST_DEFUN(/)
  SST_DEFUN(%)
  SST_DEFUN(+)
  SST_DEFUN(-)

#undef SST_DEFUN

  //--------------------------------------------------------------------
  // Bitwise operators
  //--------------------------------------------------------------------

#define SST_DEFUN(op) \
\
  bignum operator op(bignum const & c) const { \
    bignum const & b = *this; \
    /* We need the most significant bit of our result buffer to always
     * be zero for two nonnegative inputs. Otherwise, from_bytes would
     * produce an incorrect result for certain values. For example,
     * sst::bignum(UCHAR_MAX) | 0 would produce -1. Furthermore, for
     * certain negative inputs, BN_num_bytes will return one byte short
     * of the correct number of bytes needed to guarantee the presence
     * of a sign bit. For example, BN_num_bytes(SCHAR_MIN - 1) will
     * return 1, but 2 bytes are needed (assuming two's complement,
     * i.e., SCHAR_MIN is a negative power of two). The +1 here solves
     * both of these problems by guaranteeing the presence of at least
     * one sign bit. */ \
    auto const n = sst::checked_cast<std::size_t>( \
        sst::checked<std::size_t>( \
            std::max(BN_num_bytes(b.p_), BN_num_bytes(c.p_))) \
        + 1); \
    detail::buffer_t bbuf(n); \
    detail::buffer_t cbuf(n); \
    b.foo_to_bytes(bbuf.get().begin(), bbuf.get().end()); \
    c.foo_to_bytes(cbuf.get().begin(), cbuf.get().end()); \
    for (decltype(+n) i = 0; i != n; ++i) { \
      unsigned int const bx = bbuf.get()[i]; \
      unsigned int const cx = cbuf.get()[i]; \
      bbuf.get()[i] = static_cast<unsigned char>(bx op cx); \
    } \
    return from_bytes(bbuf.get()); \
  } \
\
  bignum & operator op##=(bignum const & b) { \
    bignum & a = *this; \
    a = a op b; \
    return a; \
  }

  SST_DEFUN(&)
  SST_DEFUN(^)
  SST_DEFUN(|)

#undef SST_DEFUN

  bignum operator~() const {
    bignum const & b = *this;
    // The +1 here has the same reasoning as for operator& and friends.
    auto const n = sst::checked_cast<std::size_t>(
        sst::checked<std::size_t>(BN_num_bytes(b.p_)) + 1);
    detail::buffer_t bbuf(n);
    b.foo_to_bytes(bbuf.get().begin(), bbuf.get().end());
    for (decltype(+n) i = 0; i != n; ++i) {
      unsigned int const bx = bbuf.get()[i];
      bbuf.get()[i] = static_cast<unsigned char>(~bx);
    }
    return from_bytes(bbuf.get());
  }

#define SST_DEFUN(op, func) \
  template<class IntType, \
           typename std::enable_if<std::is_integral<IntType>::value, \
                                   int>::type = 0> \
  bignum operator op(IntType const b) const { \
    assert(!sst::is_negative(b)); \
    bignum r; \
    if (sst::unsigned_gt(b, sst::type_max<int>::value)) { \
      if (!func(r.p_, p_, sst::type_max<int>::value)) { \
        throw sst::bignum_error(#func "() failed"); \
      } \
      r op## = b - static_cast<IntType>(sst::type_max<int>::value); \
    } else if (!func(r.p_, p_, static_cast<int>(b))) { \
      throw sst::bignum_error(#func "() failed"); \
    } \
    return r; \
  }

  SST_DEFUN(<<, BN_lshift)
  SST_DEFUN(>>, BN_rshift)

#undef SST_DEFUN

#define SST_DEFUN(op, func) \
\
  template<class IntType, \
           typename std::enable_if< \
               +sst::can_represent_all<int, IntType>::value, \
               int>::type = 0> \
  bignum & operator op(IntType const b) { \
    assert(!sst::is_negative(b)); \
    if (!func(p_, p_, static_cast<int>(b))) { \
      zero(); \
      throw sst::bignum_error(#func "() failed"); \
    } \
    return *this; \
  } \
\
  template<class IntType, \
           typename std::enable_if< \
               !sst::can_represent_all<int, IntType>::value \
                   && std::is_integral<IntType>::value, \
               int>::type = 0> \
  bignum & operator op(IntType b) { \
    assert(!sst::is_negative(b)); \
    for (; sst::unsigned_gt(b, sst::type_max<int>::value); \
         b -= static_cast<IntType>(sst::type_max<int>::value)) { \
      *this op sst::type_max<int>::value; \
    } \
    return *this op static_cast<int>(b); \
  }

  SST_DEFUN(<<=, BN_lshift)
  SST_DEFUN(>>=, BN_rshift)

#undef SST_DEFUN

  // TODO: implement shift by bignum

  //--------------------------------------------------------------------

#define SST_DEFUN(op) \
  bool operator op(bignum const & b) const noexcept { \
    return BN_cmp(p_, b.p_) op 0; \
  }

  SST_DEFUN(<)
  SST_DEFUN(>)
  SST_DEFUN(<=)
  SST_DEFUN(>=)
  SST_DEFUN(==)
  SST_DEFUN(!=)

#undef SST_DEFUN

  // TODO: optimize with BN_is_word()

  //--------------------------------------------------------------------

  // Assignment from integer types subsumed by BN_ULONG.
  template<class IntType,
           typename std::enable_if<
               sst::can_represent_all<BN_ULONG, IntType>::value,
               int>::type = 0>
  bignum & operator=(IntType const a) {
    if (!BN_set_word(p_, static_cast<BN_ULONG>(a))) {
      zero();
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
    I const max = static_cast<I>(bn_ulong_max);
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
      negate();
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
      if (negative) {
        r -= digit;
      } else {
        r += digit;
      }
    }
    return r;
  }

  static bignum from_string(std::string const & s) {
    return from_string(s.begin(), s.end());
  }

  explicit bignum(std::string const & s) : bignum(from_string(s)) {
  }

  //--------------------------------------------------------------------

private:
  template<class OutputIt>
  OutputIt foo_to_string(OutputIt out) const {
    bool const neg = is_negative();
    bignum x = *this;
    if (neg) {
      x.negate();
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
  std::string to_string() const {
    std::string s;
    foo_to_string(std::back_inserter(s));
    std::reverse(s.begin(), s.end());
    return s;
  }

  //--------------------------------------------------------------------

  bignum & operator*=(bignum const & a) {
    if (!BN_mul(p_, p_, a.p_, detail::bignum_bn_ctx())) {
      zero();
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
      zero();
      throw sst::bignum_error("BN_mul_word() failed");
    }
    return *this;
  }

#define SST_DEFUN(op) \
\
  template<class IntType, \
           typename std::enable_if< \
               !sst::can_represent_all<BN_ULONG, IntType>::value \
                   && std::is_integral<IntType>::value, \
               int>::type = 0> \
  bignum & operator op(IntType const a) { \
    if (!sst::is_negative(a) && sst::unsigned_le(a, bn_ulong_max)) { \
      return *this op static_cast<BN_ULONG>(a); \
    } \
    if (sst::is_negative(a) \
        && sst::unsigned_lt(-(a + 1), bn_ulong_max)) { \
      negate(); \
      return *this op static_cast<BN_ULONG>( \
          static_cast<BN_ULONG>(-(a + 1)) + static_cast<BN_ULONG>(1)); \
    } \
    return *this op bignum(a); \
  }

  SST_DEFUN(*=)

  //--------------------------------------------------------------------

  bignum & operator/=(bignum const & a) {
    if (!BN_div(p_, nullptr, p_, a.p_, detail::bignum_bn_ctx())) {
      zero();
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
    if (r == bn_ulong_max) {
      zero();
      throw sst::bignum_error("BN_div_word() failed");
    }
    return *this;
  }

  SST_DEFUN(/=)

  //--------------------------------------------------------------------

  bignum & operator%=(bignum const & a) {
    if (!BN_div(nullptr, p_, p_, a.p_, detail::bignum_bn_ctx())) {
      zero();
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
    if (r == bn_ulong_max) {
      zero();
      throw sst::bignum_error("BN_mod_word() failed");
    }
    return *this = r;
  }

  SST_DEFUN(%=)

#undef SST_DEFUN

  //--------------------------------------------------------------------

#define SST_DEFUN(bn_op, bn_op_word, op, reverse_op) \
\
  bignum & operator op(bignum const & a) { \
    if (!bn_op(p_, p_, a.p_)) { \
      zero(); \
      throw sst::bignum_error(#bn_op "() failed"); \
    } \
    return *this; \
  } \
\
  template<class IntType, \
           typename std::enable_if< \
               sst::can_represent_all<BN_ULONG, IntType>::value, \
               int>::type = 0> \
  bignum & operator op(IntType const a) { \
    if (!bn_op_word(p_, static_cast<BN_ULONG>(a))) { \
      zero(); \
      throw sst::bignum_error(#bn_op_word "() failed"); \
    } \
    return *this; \
  } \
\
  template<class IntType, \
           typename std::enable_if< \
               !sst::can_represent_all<BN_ULONG, IntType>::value \
                   && std::is_integral<IntType>::value, \
               int>::type = 0> \
  bignum & operator op(IntType const a) { \
    if (!sst::is_negative(a) && sst::unsigned_le(a, bn_ulong_max)) { \
      return *this op static_cast<BN_ULONG>(a); \
    } \
    if (sst::is_negative(a) \
        && sst::unsigned_lt(-(a + 1), bn_ulong_max)) { \
      return *this reverse_op static_cast<BN_ULONG>( \
          static_cast<BN_ULONG>(-(a + 1)) + static_cast<BN_ULONG>(1)); \
    } \
    return *this op bignum(a); \
  }

  SST_DEFUN(BN_add, BN_add_word, +=, -=)
  SST_DEFUN(BN_sub, BN_sub_word, -=, +=)

#undef SST_DEFUN

  //--------------------------------------------------------------------

private:
  template<class ByteOutputIt>
  void foo_to_bytes(ByteOutputIt first, ByteOutputIt const last) const {
    bool const negative = is_negative();
    detail::buffer_t digits(
        sst::checked_cast<std::size_t>(BN_num_bytes(p_)));
    BN_bn2bin(p_, &digits.get()[0]);
    std::size_t i = digits.get().size();
    unsigned int carry = 1;
    for (; first != last; ++first) {
      unsigned int const digit = i > 0 ? digits.get()[--i] : 0;
      if (negative) {
        unsigned char const a = static_cast<unsigned char>(~digit);
        unsigned char const b = static_cast<unsigned char>(a + carry);
        *first = b;
        carry = a > b;
      } else {
        *first = static_cast<unsigned char>(digit);
      }
    }
  }

public:
  std::vector<unsigned char> to_bytes(std::size_t const width) const {
    std::vector<unsigned char> x(width);
    foo_to_bytes(x.begin(), x.end());
    return x;
  }

  //--------------------------------------------------------------------

  // TODO: endian for to_bytes and from_bytes

  template<class InputIt>
  static bignum from_bytes(
      InputIt first,
      InputIt last,
      sst::integer_rep const rep = sst::integer_rep::twos_complement) {
    assert(rep == sst::integer_rep::pure_unsigned
           || rep == sst::integer_rep::twos_complement);
    bignum r;
    bignum v;
    sst::checked<int> k = 0;
    unsigned char x = 0;
    for (; first != last; ++first) {
      x = *first;
      v = static_cast<BN_ULONG>(x);
      v <<= k.v();
      r += v;
      k += sst::char_bit_v;
    }
    if (rep == sst::integer_rep::twos_complement
        && x > (sst::uchar_max_v >> 1)) {
      v = static_cast<BN_ULONG>(1);
      v <<= k.v();
      r -= v;
    }
    return r;
  }

  template<class Container>
  static bignum from_bytes(
      Container const & c,
      sst::integer_rep const rep = sst::integer_rep::twos_complement) {
    return from_bytes(c.begin(), c.end(), rep);
  }

  explicit bignum(
      std::vector<unsigned char> const & c,
      sst::integer_rep const rep = sst::integer_rep::twos_complement)
      : bignum(from_bytes(c, rep)) {
  }

  //--------------------------------------------------------------------

private:
  bool is_negative() const noexcept {
    return BN_is_negative(p_) != 0;
  }

  bignum & negate() noexcept {
    BN_set_negative(p_, !is_negative());
    return *this;
  }

  bignum & zero() noexcept {
    BN_zero(p_);
    return *this;
  }
};

} // namespace sst

#endif // SST_HAVE_LIB_CRYPTO

#endif // SST_CATALOG_BIGNUM_HPP
