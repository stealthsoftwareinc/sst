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

#ifndef SST_CATALOG_CHECKED_CLASS_HPP
#define SST_CATALOG_CHECKED_CLASS_HPP

#include <iterator>
#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_CPP14_CONSTEXPR.hpp>
#include <sst/catalog/SST_DEBUG.h>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/can_represent_all.hpp>
#include <sst/catalog/checked_overflow.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/is_ones_complement.hpp>
#include <sst/catalog/is_sign_magnitude.hpp>
#include <sst/catalog/is_signed_integer.hpp>
#include <sst/catalog/is_twos_complement.hpp>
#include <sst/catalog/is_unsigned_integer.hpp>
#include <sst/catalog/perfect_ge.hpp>
#include <sst/catalog/perfect_le.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/type_min.hpp>
#include <sst/catalog/type_name.hpp>
#include <sst/catalog/unsigned_ge.hpp>
#include <sst/catalog/width_bits.hpp>
#include <sst/private/checked_class/decl.hpp>
#include <sst/private/to_string/from_integer.hpp>

//----------------------------------------------------------------------
// checked_class
//----------------------------------------------------------------------

namespace sst {

namespace guts {
namespace checked_class {

template<class R, class A>
sst::checked_overflow overflow(A const a) {
  std::string m;
  m += "A checked integer expression attempted to convert (";
  sst::type_name<A>(std::back_inserter(m));
  m += ")";
  sst::to_string(a, std::back_inserter(m));
  m += " to type ";
  sst::type_name<R>(std::back_inserter(m));
  m += ", in which it would not be representable.";
  return sst::checked_overflow(std::move(m));
}

template<class R, class A>
sst::checked_overflow overflow(char const * const op, A const a) {
  std::string m;
  m += "A checked integer expression attempted to evaluate ";
  m += op;
  m += "(";
  sst::type_name<A>(std::back_inserter(m));
  m += ")";
  sst::to_string(a, std::back_inserter(m));
  m += ", whose result would not be representable in the result type, ";
  sst::type_name<R>(std::back_inserter(m));
  m += ".";
  return sst::checked_overflow(std::move(m));
}

// Note that B2 = R except for the << operator, where B2 = B.
template<class A, class B, class R, class B2>
sst::checked_overflow
overflow(R const a, char const * const op, B2 const b) {
  std::string m;
  m += "A checked integer expression attempted to evaluate (";
  sst::type_name<A>(std::back_inserter(m));
  m += ")";
  sst::to_string(a, std::back_inserter(m));
  m += " ";
  m += op;
  m += " (";
  sst::type_name<B>(std::back_inserter(m));
  m += ")";
  sst::to_string(b, std::back_inserter(m));
  m += ", whose result would not be representable in the result type, ";
  sst::type_name<R>(std::back_inserter(m));
  m += ".";
  return sst::checked_overflow(std::move(m));
}

template<class A, class B, class R>
std::string
div_zero(R const a, char const * const op, R const b, bool const mod) {
  std::string m;
  m += "A checked integer expression attempted to evaluate (";
  sst::type_name<A>(std::back_inserter(m));
  m += ")";
  sst::to_string(a, std::back_inserter(m));
  m += " ";
  m += op;
  m += " (";
  sst::type_name<B>(std::back_inserter(m));
  m += ")";
  sst::to_string(b, std::back_inserter(m));
  m += ", which would cause ";
  m += mod ? "an implicit" : "a";
  m += " division by zero to occur.";
  return m;
}

template<class A, class B, class R>
std::string mod_overflow(R const a, R const b) {
  std::string m;
  m += "A checked integer expression attempted to evaluate (";
  sst::type_name<A>(std::back_inserter(m));
  m += ")";
  sst::to_string(a, std::back_inserter(m));
  m += " % (";
  sst::type_name<B>(std::back_inserter(m));
  m += ")";
  sst::to_string(b, std::back_inserter(m));
  m += ", whose implicit quotient would not ";
  m += "be representable in the result type, ";
  sst::type_name<R>(std::back_inserter(m));
  m += ".";
  return m;
}

template<class R, class A>
std::string neg_zero(A const a) {
  std::string m;
  m += "A checked integer expression attempted to evaluate ~(";
  sst::type_name<A>(std::back_inserter(m));
  m += ")";
  sst::to_string(a, std::back_inserter(m));
  m += ", whose result would be negative zero.";
  return m;
}

template<class A, class B, class R>
std::string neg_zero(R const a, char const * const op, R const b) {
  std::string m;
  m += "A checked integer expression attempted to evaluate (";
  sst::type_name<A>(std::back_inserter(m));
  m += ")";
  sst::to_string(a, std::back_inserter(m));
  m += " ";
  m += op;
  m += " (";
  sst::type_name<B>(std::back_inserter(m));
  m += ")";
  sst::to_string(b, std::back_inserter(m));
  m += ", whose result would be negative zero.";
  return m;
}

template<class A, class B, class R>
std::string
neg_shift(R const a, char const * const op, B const b, bool const lhs) {
  std::string m;
  m += "A checked integer expression attempted to evaluate (";
  sst::type_name<A>(std::back_inserter(m));
  m += ")";
  sst::to_string(a, std::back_inserter(m));
  m += " ";
  m += op;
  m += " (";
  sst::type_name<B>(std::back_inserter(m));
  m += ")";
  sst::to_string(b, std::back_inserter(m));
  m += ", whose shift ";
  m += lhs ? "subject" : "amount";
  m += " is negative.";
  return m;
}

template<class A, class B, class R>
std::string overshift(R const a, char const * const op, B const b) {
  std::string m;
  m += "A checked integer expression attempted to evaluate (";
  sst::type_name<A>(std::back_inserter(m));
  m += ")";
  sst::to_string(a, std::back_inserter(m));
  m += " ";
  m += op;
  m += " (";
  sst::type_name<B>(std::back_inserter(m));
  m += ")";
  sst::to_string(b, std::back_inserter(m));
  m += ", whose shift amount is greater than ";
  m += "or equal to the width of the result type, ";
  sst::type_name<R>(std::back_inserter(m));
  m += ".";
  return m;
}

} // namespace checked_class
} // namespace guts

#define SST_CHECKED_BARF(M) (SST_ASSERT(false, M), static_cast<R>(0))

//----------------------------------------------------------------------
// is_checked_class
//----------------------------------------------------------------------

template<class>
struct is_checked_class : std::false_type {};

template<class T>
struct is_checked_class<sst::checked_class<T>> : std::true_type {};

template<class T>
struct is_checked_class<sst::checked_class<T> const> : std::true_type {
};

template<class T>
struct is_checked_class<sst::checked_class<T> volatile>
    : std::true_type {};

template<class T>
struct is_checked_class<sst::checked_class<T> const volatile>
    : std::true_type {};

template<class T>
struct is_checked_class<sst::checked_class<T> const &>
    : std::true_type {};

template<class T>
struct is_checked_class<sst::checked_class<T> volatile &>
    : std::true_type {};

template<class T>
struct is_checked_class<sst::checked_class<T> const volatile &>
    : std::true_type {};

//----------------------------------------------------------------------

template<class T>
class checked_class<T,
                    sst::enable_if_t<sst::is_integer_ish<T>::value>> {

  SST_STATIC_ASSERT((!sst::is_checked_class<T>::value),
                    "sst::checked_class does not allow self-nesting. "
                    "You may want to use sst::checked_t instead of "
                    "using sst::checked_class directly.");

public:

  using value_type = sst::remove_cvref_t<T>;

private:

  value_type value_{};

public:

  //--------------------------------------------------------------------
  // Default operations
  //--------------------------------------------------------------------

  constexpr checked_class()
      SST_NOEXCEPT(noexcept(value_type())) = default;

  constexpr checked_class(checked_class const &) SST_NOEXCEPT(noexcept(
      value_type(std::declval<value_type const &>()))) = default;

  SST_CPP14_CONSTEXPR checked_class & operator=(checked_class const &)
      SST_NOEXCEPT(noexcept(std::declval<value_type &>() =
                                std::declval<value_type const &>())) =
          default;

  constexpr checked_class(checked_class &&) SST_NOEXCEPT(
      noexcept(value_type(std::declval<value_type &&>()))) = default;

  SST_CPP14_CONSTEXPR checked_class & operator=(checked_class &&)
      SST_NOEXCEPT(noexcept(std::declval<value_type &>() =
                                std::declval<value_type &&>())) =
          default;

  ~checked_class() noexcept = default;

  //--------------------------------------------------------------------
  // Value retrieval
  //--------------------------------------------------------------------

  constexpr value_type const & value() const noexcept {
    return value_;
  }

  //--------------------------------------------------------------------
  // Converting constructor
  //--------------------------------------------------------------------

private:

  struct converting_constructor_tag {};

  template<class R = value_type,
           class A,
           sst::enable_if_t<sst::can_represent_all<R, A>::value> = 0>
  constexpr checked_class(converting_constructor_tag, A const & a)
      SST_NOEXCEPT(noexcept(R(static_cast<R>(a))))
      : value_(static_cast<R>(a)) {
  }

  template<class R = value_type,
           class A,
           sst::enable_if_t<!sst::can_represent_all<R, A>::value> = 0>
  constexpr checked_class(converting_constructor_tag, A const & a)
      : value_(sst::perfect_ge(a, sst::type_min<R>::value)
                       && sst::perfect_le(a, sst::type_max<R>::value) ?
                   static_cast<R>(a) :
                   throw guts::checked_class::overflow<R>(a)) {
  }

public:

  template<class A,
           sst::enable_if_t<sst::is_checked_class<A>::value> = 0>
  constexpr checked_class(A const & a)
      SST_NOEXCEPT(noexcept(checked_class(converting_constructor_tag{},
                                          a.value())))
      : checked_class(converting_constructor_tag{}, a.value()) {
  }

  template<class A,
           sst::enable_if_t<!sst::is_checked_class<A>::value
                            && sst::is_integer_ish<A>::value> = 0>
  constexpr checked_class(A const & a)
      SST_NOEXCEPT(noexcept(checked_class(converting_constructor_tag{},
                                          a)))
      : checked_class(converting_constructor_tag{}, a) {
  }

  //--------------------------------------------------------------------
  // Explicit conversions
  //--------------------------------------------------------------------

  template<class R,
           sst::enable_if_t<sst::is_checked_class<R>::value> = 0>
  explicit constexpr operator R() const
      SST_NOEXCEPT(noexcept(R(value_type()))) {
    return R(value());
  }

  template<class R,
           sst::enable_if_t<!sst::is_checked_class<R>::value
                            && sst::is_integer_ish<R>::value> = 0>
  explicit constexpr operator R() const
      SST_NOEXCEPT(noexcept(checked_class<R>(value_type()).value())) {
    return checked_class<R>(value()).value();
  }

  //--------------------------------------------------------------------
  // Logical operators
  //--------------------------------------------------------------------

  constexpr checked_class<bool> operator!() const noexcept {
    return !value();
  }

  //--------------------------------------------------------------------
  // Increment and decrement operators
  //--------------------------------------------------------------------

  SST_CPP14_CONSTEXPR checked_class operator++(int) {
    checked_class x = *this;
    ++*this;
    return x;
  }

  SST_CPP14_CONSTEXPR checked_class operator--(int) {
    checked_class x = *this;
    --*this;
    return x;
  }

  SST_CPP14_CONSTEXPR checked_class operator++() {
    return *this += static_cast<value_type>(1);
  }

  SST_CPP14_CONSTEXPR checked_class operator--() {
    return *this -= static_cast<value_type>(1);
  }

  //--------------------------------------------------------------------
  // Unary arithmetic operators
  //--------------------------------------------------------------------

  template<class R = decltype(+value_type())>
  constexpr checked_class<R> operator+() const noexcept {
    return value();
  }

  template<class R = decltype(-value_type()),
           sst::enable_if_t<sst::is_signed_integer<R>::value
                            && sst::is_twos_complement<R>::value> = 0>
  constexpr checked_class<R> operator-() const {
    return static_cast<R>(value()) >= -sst::type_max<R>::value ?
               -static_cast<R>(value()) :
               throw guts::checked_class::overflow<R>("-", value());
  }

  template<class R = decltype(-value_type()),
           sst::enable_if_t<sst::is_signed_integer<R>::value
                            && !sst::is_twos_complement<R>::value> = 0>
  constexpr checked_class<R> operator-() const noexcept {
    return -static_cast<R>(value());
  }

  template<class R = decltype(-value_type()),
           sst::enable_if_t<sst::is_unsigned_integer<R>::value> = 0>
  constexpr checked_class<R> operator-() const {
    return value() == static_cast<value_type>(0) ?
               static_cast<R>(0) :
               throw guts::checked_class::overflow<R>("-", value());
  }

  //--------------------------------------------------------------------
  // Binary arithmetic operators
  //--------------------------------------------------------------------

private:

  template<class A,
           class B,
           class R,
           sst::enable_if_t<std::numeric_limits<R>::is_bounded> = 0>
  static constexpr R mul(R const & a, R const & b) {
    return a > static_cast<R>(0) && b > static_cast<R>(0) ?
               (a <= sst::type_max<R>::value / b ?
                    a * b :
                    throw guts::checked_class::overflow<A, B>(a,
                                                              "*",
                                                              b)) :
           a > static_cast<R>(0) && sst::is_negative(b) ?
               (b >= sst::type_min<R>::value / a ?
                    a * b :
                    throw guts::checked_class::overflow<A, B>(a,
                                                              "*",
                                                              b)) :
           sst::is_negative(a) && b > static_cast<R>(0) ?
               (a >= sst::type_min<R>::value / b ?
                    a * b :
                    throw guts::checked_class::overflow<A, B>(a,
                                                              "*",
                                                              b)) :
           sst::is_negative(a) && sst::is_negative(b) ?
               (a >= sst::type_max<R>::value / b ?
                    a * b :
                    throw guts::checked_class::overflow<A, B>(a,
                                                              "*",
                                                              b)) :
               static_cast<R>(0);
  }

  template<class,
           class,
           class R,
           sst::enable_if_t<!std::numeric_limits<R>::is_bounded> = 0>
  static constexpr R mul(R const & a, R const & b)
      SST_NOEXCEPT(noexcept(a * b)) {
    return a * b;
  }

  template<class A,
           class B,
           class R,
           sst::enable_if_t<std::numeric_limits<R>::is_bounded> = 0>
  static constexpr R div(R const & a, R const & b) {
    return
#if SST_DEBUG
        b == static_cast<R>(0) ?
            SST_CHECKED_BARF(
                (guts::checked_class::div_zero<A, B>(a,
                                                     "/",
                                                     b,
                                                     false))) :
#endif
        sst::is_signed_integer<R>::value
                && sst::is_twos_complement<R>::value
                && a == sst::type_min<R>::value
                && b == static_cast<R>(-1) ?
            throw guts::checked_class::overflow<A, B>(a, "/", b) :
            a / b;
  }

  template<class A,
           class B,
           class R,
           sst::enable_if_t<!std::numeric_limits<R>::is_bounded> = 0>
  static constexpr R div(R const & a, R const & b)
      SST_NOEXCEPT(noexcept(a / b)) {
    return
#if SST_DEBUG
        b == static_cast<R>(0) ? SST_CHECKED_BARF(
            (guts::checked_class::div_zero<A, B>(a, "/", b, false))) :
#endif
                                 a / b;
  }

  template<class A,
           class B,
           class R,
           sst::enable_if_t<std::numeric_limits<R>::is_bounded> = 0>
  static constexpr R mod(R const & a, R const & b) {
    return
#if SST_DEBUG
        b == static_cast<R>(0) ?
            SST_CHECKED_BARF((
                guts::checked_class::div_zero<A, B>(a, "%", b, true))) :
#endif
        sst::is_signed_integer<R>::value
                && sst::is_twos_complement<R>::value
                && a == sst::type_min<R>::value
                && b == static_cast<R>(-1) ?
            SST_CHECKED_BARF(
                (guts::checked_class::mod_overflow<A, B>(a, b))) :
            a % b;
  }

  template<class A,
           class B,
           class R,
           sst::enable_if_t<!std::numeric_limits<R>::is_bounded> = 0>
  static constexpr R mod(R const & a, R const & b)
      SST_NOEXCEPT(noexcept(a % b)) {
    return
#if SST_DEBUG
        b == static_cast<R>(0) ? SST_CHECKED_BARF(
            (guts::checked_class::div_zero<A, B>(a, "%", b, true))) :
#endif
                                 a % b;
  }

  template<class A,
           class B,
           class R,
           sst::enable_if_t<std::numeric_limits<R>::is_bounded> = 0>
  static constexpr R add(R const & a, R const & b) {
    return a > static_cast<R>(0) && b > static_cast<R>(0) ?
               (a <= sst::type_max<R>::value - b ?
                    a + b :
                    throw guts::checked_class::overflow<A, B>(a,
                                                              "+",
                                                              b)) :
           sst::is_negative(a) && sst::is_negative(b) ?
               (a >= sst::type_min<R>::value - b ?
                    a + b :
                    throw guts::checked_class::overflow<A, B>(a,
                                                              "+",
                                                              b)) :
               a + b;
  }

  template<class,
           class,
           class R,
           sst::enable_if_t<!std::numeric_limits<R>::is_bounded> = 0>
  static constexpr R add(R const & a, R const & b)
      SST_NOEXCEPT(noexcept(a + b)) {
    return a + b;
  }

  template<class A,
           class B,
           class R,
           sst::enable_if_t<std::numeric_limits<R>::is_bounded> = 0>
  static constexpr R sub(R const & a, R const & b) {
    return sst::is_unsigned_integer<R>::value ?
               (sst::unsigned_ge(a, b) ?
                    a - b :
                    throw guts::checked_class::overflow<A, B>(a,
                                                              "-",
                                                              b)) :
           !sst::is_negative(a) && sst::is_negative(b) ?
               (a <= sst::type_max<R>::value + b ?
                    a - b :
                    throw guts::checked_class::overflow<A, B>(a,
                                                              "-",
                                                              b)) :
           sst::is_negative(a) && b > static_cast<R>(0) ?
               (a >= sst::type_min<R>::value + b ?
                    a - b :
                    throw guts::checked_class::overflow<A, B>(a,
                                                              "-",
                                                              b)) :
               a - b;
  }

  template<class,
           class,
           class R,
           sst::enable_if_t<!std::numeric_limits<R>::is_bounded> = 0>
  static constexpr R sub(R const & a, R const & b)
      SST_NOEXCEPT(noexcept(a - b)) {
    return a - b;
  }

public:

#define SST_r(FN)                                                      \
  (FN<AV, BV>(checked_class<R>(a).value(), checked_class<R>(b).value()))

#define SST_F(OP, FN)                                                  \
  template<class B,                                                    \
           class A = T,                                                \
           class AV = typename checked_class<A>::value_type,           \
           class BV = typename checked_class<B>::value_type,           \
           class R = decltype(AV() OP BV())>                           \
  friend constexpr checked_class<R> operator OP(                       \
      checked_class const & a,                                         \
      checked_class<B> const & b) SST_NOEXCEPT(noexcept(SST_r(FN))) {  \
    return SST_r(FN);                                                  \
  }

  SST_F(*, mul)
  SST_F(/, div)
  SST_F(%, mod)
  SST_F(+, add)
  SST_F(-, sub)

#undef SST_F
#undef SST_r

  //--------------------------------------------------------------------
  // Bitwise operators
  //--------------------------------------------------------------------

private:

  template<class A, class R>
  static constexpr R bit_neg(R const a) noexcept {
    return sst::is_twos_complement<R>::value ?
               ~a :
           sst::is_ones_complement<R>::value ?
               (
#if SST_DEBUG
                   a == static_cast<R>(0) ? SST_CHECKED_BARF(
                       (guts::checked_class::neg_zero<A>(a))) :
#endif
                                            ~a) :
               (
#if SST_DEBUG
                   a == sst::type_max<R>::value ? SST_CHECKED_BARF(
                       (guts::checked_class::neg_zero<A>(a))) :
#endif
                                                  ~a);
  }

  template<class A, class B, class R>
  static constexpr R bit_and(R const a, R const b) noexcept {
    return
#if SST_DEBUG
        sst::is_sign_magnitude<R>::value
                && (sst::is_negative(a) && sst::is_negative(b))
                && ((a & sst::type_max<R>::value)
                    & (b & sst::type_max<R>::value))
                       == static_cast<R>(0) ?
            SST_CHECKED_BARF(
                (guts::checked_class::neg_zero<A, B>(a, "&", b))) :
#endif
            a & b;
  }

  template<class A, class B, class R>
  static constexpr R bit_or(R const a, R const b) noexcept {
    return
#if SST_DEBUG
        sst::is_ones_complement<R>::value
                && (sst::is_negative(a) || sst::is_negative(b))
                && ((a & sst::type_max<R>::value)
                    | (b & sst::type_max<R>::value))
                       == sst::type_max<R>::value ?
            SST_CHECKED_BARF(
                (guts::checked_class::neg_zero<A, B>(a, "|", b))) :
#endif
            a | b;
  }

  template<class A, class B, class R>
  static constexpr R bit_xor(R const a, R const b) noexcept {
    return
#if SST_DEBUG
        !sst::is_twos_complement<R>::value
                && sst::is_negative(a) != sst::is_negative(b)
                && ((sst::is_ones_complement<R>::value
                     && ((a & sst::type_max<R>::value)
                         ^ (b & sst::type_max<R>::value))
                            == sst::type_max<R>::value)
                    || (sst::is_sign_magnitude<R>::value
                        && ((a & sst::type_max<R>::value)
                            ^ (b & sst::type_max<R>::value))
                               == static_cast<R>(0))) ?
            SST_CHECKED_BARF(
                (guts::checked_class::neg_zero<A, B>(a, "^", b))) :
#endif
            a ^ b;
  }

  template<class A, class B, class R>
  static constexpr R bit_lsh(R const a, B const b) {
    return
#if SST_DEBUG
        sst::is_negative(a) ? SST_CHECKED_BARF(
            (guts::checked_class::neg_shift<A, B>(a, "<<", b, true))) :
        sst::is_negative(b) ? SST_CHECKED_BARF(
            (guts::checked_class::neg_shift<A, B>(a, "<<", b, false))) :
        sst::unsigned_ge(b, sst::width_bits<R>::value) ?
                              SST_CHECKED_BARF(
                                  (guts::checked_class::overshift<A, B>(
                                      a,
                                      "<<",
                                      b))) :
#endif
        a > (sst::type_max<R>::value >> b) ?
                              throw guts::checked_class::overflow<A, B>(
                                  a,
                                  "<<",
                                  b) :
                              a << b;
  }

  template<class A, class B, class R>
  static constexpr R bit_rsh(R const a, B const b) noexcept {
    return
#if SST_DEBUG
        sst::is_negative(a) ? SST_CHECKED_BARF(
            (guts::checked_class::neg_shift<A, B>(a, ">>", b, true))) :
        sst::is_negative(b) ? SST_CHECKED_BARF(
            (guts::checked_class::neg_shift<A, B>(a, ">>", b, false))) :
        sst::unsigned_ge(b, sst::width_bits<R>::value) ?
                              SST_CHECKED_BARF(
                                  (guts::checked_class::overshift<A, B>(
                                      a,
                                      ">>",
                                      b))) :
#endif
                              a >> b;
  }

public:

  template<class R = decltype(~value_type())>
  constexpr checked_class<R> operator~() const {
    return bit_neg<value_type>(checked_class<R>(*this).value());
  }

  template<class U,
           class R = decltype(value_type() &
                              typename checked_class<U>::value_type())>
  constexpr checked_class<R> operator&(checked_class<U> const b) const {
    return bit_and<value_type, typename checked_class<U>::value_type>(
        checked_class<R>(*this).value(),
        checked_class<R>(b).value());
  }

  template<class U,
           class R = decltype(value_type() |
                              typename checked_class<U>::value_type())>
  constexpr checked_class<R> operator|(checked_class<U> const b) const {
    return bit_or<value_type, typename checked_class<U>::value_type>(
        checked_class<R>(*this).value(),
        checked_class<R>(b).value());
  }

  template<class U,
           class R = decltype(value_type() ^
                              typename checked_class<U>::value_type())>
  constexpr checked_class<R> operator^(checked_class<U> const b) const {
    return bit_xor<value_type, typename checked_class<U>::value_type>(
        checked_class<R>(*this).value(),
        checked_class<R>(b).value());
  }

  template<class U,
           class R = decltype(value_type() <<
                              typename checked_class<U>::value_type())>
  constexpr checked_class<R>
  operator<<(checked_class<U> const b) const {
    return bit_lsh<value_type, typename checked_class<U>::value_type>(
        static_cast<R>(value()),
        b.value());
  }

  template<class U,
           class R = decltype(value_type() >>
                              typename checked_class<U>::value_type())>
  constexpr checked_class<R>
  operator>>(checked_class<U> const b) const {
    return bit_rsh<value_type, typename checked_class<U>::value_type>(
        static_cast<R>(value()),
        b.value());
  }

  //--------------------------------------------------------------------
  // Promoting and compound assignment operators
  //--------------------------------------------------------------------

#define SST_DEFINE_FUNCTIONS(op)                                       \
                                                                       \
  template<class B,                                                    \
           sst::enable_if_t<sst::is_integer_ish<B>::value              \
                            && !sst::is_checked_class<B>::value> = 0>  \
  friend constexpr auto operator op(checked_class const & a,           \
                                    B const & b)                       \
      SST_NOEXCEPT(noexcept(a op checked_class<B>(b)))                 \
          ->decltype(a op checked_class<B>(b)) {                       \
    return a op checked_class<B>(b);                                   \
  }                                                                    \
                                                                       \
  template<class A,                                                    \
           sst::enable_if_t<sst::is_integer_ish<A>::value              \
                            && !sst::is_checked_class<A>::value> = 0>  \
  friend constexpr auto operator op(A const & a,                       \
                                    checked_class const & b)           \
      SST_NOEXCEPT(noexcept(checked_class<A>(a) op b))                 \
          ->decltype(checked_class<A>(a) op b) {                       \
    return checked_class<A>(a) op b;                                   \
  }                                                                    \
                                                                       \
  template<class B>                                                    \
  SST_CPP14_CONSTEXPR checked_class & operator op##=(                  \
      checked_class<B> const & b)                                      \
      SST_NOEXCEPT(noexcept(std::declval<checked_class &>() =          \
                                checked_class() op b)) {               \
    return *this = *this op b;                                         \
  }                                                                    \
                                                                       \
  template<class B,                                                    \
           sst::enable_if_t<sst::is_integer_ish<B>::value              \
                            && !sst::is_checked_class<B>::value> = 0>  \
  SST_CPP14_CONSTEXPR checked_class & operator op##=(B const & b)      \
      SST_NOEXCEPT(noexcept(std::declval<checked_class &>() op## =     \
                                checked_class<B>(b))) {                \
    return *this op## = checked_class<B>(b);                           \
  }

  SST_DEFINE_FUNCTIONS(*)
  SST_DEFINE_FUNCTIONS(/)
  SST_DEFINE_FUNCTIONS(%)
  SST_DEFINE_FUNCTIONS(+)
  SST_DEFINE_FUNCTIONS(-)
  SST_DEFINE_FUNCTIONS(&)
  SST_DEFINE_FUNCTIONS(|)
  SST_DEFINE_FUNCTIONS(^)
  SST_DEFINE_FUNCTIONS(<<)
  SST_DEFINE_FUNCTIONS(>>)

#undef SST_DEFINE_FUNCTIONS

  //--------------------------------------------------------------------
  // Comparison operators
  //--------------------------------------------------------------------

#define SST_DEFINE_FUNCTIONS(op)                                       \
                                                                       \
  template<class A = T,                                                \
           class B,                                                    \
           class R =                                                   \
               decltype(value_type() +                                 \
                        typename checked_class<B>::value_type())>      \
  constexpr bool operator op(checked_class<B> const b)                 \
      const SST_NOEXCEPT(                                              \
          noexcept(checked_class<R>(value_type())                      \
                       .value() op checked_class<R>(b.value())         \
                       .value())) {                                    \
    return checked_class<R>(value())                                   \
        .value() op checked_class<R>(b.value())                        \
        .value();                                                      \
  }                                                                    \
                                                                       \
  template<class A = T,                                                \
           class B,                                                    \
           sst::enable_if_t<sst::is_integer<B>::value> = 0>            \
  constexpr bool operator op(B const b) const SST_NOEXCEPT(            \
      noexcept(checked_class<A>() op checked_class<B>(b))) {           \
    return *this op checked_class<B>(b);                               \
  }                                                                    \
                                                                       \
  template<class A, sst::enable_if_t<sst::is_integer<A>::value> = 0>   \
  friend constexpr bool operator op(A const a, checked_class const b)  \
      SST_NOEXCEPT(noexcept(checked_class<A>(a) op b)) {               \
    return checked_class<A>(a) op b;                                   \
  }

  SST_DEFINE_FUNCTIONS(<)
  SST_DEFINE_FUNCTIONS(>)
  SST_DEFINE_FUNCTIONS(<=)
  SST_DEFINE_FUNCTIONS(>=)
  SST_DEFINE_FUNCTIONS(==)
  SST_DEFINE_FUNCTIONS(!=)

#undef SST_DEFINE_FUNCTIONS

  //--------------------------------------------------------------------
};

} // namespace sst

//----------------------------------------------------------------------
// std::numeric_limits specialization
//----------------------------------------------------------------------

namespace std {

template<class T>
class numeric_limits<sst::checked_class<T>> {

  using value_type = typename sst::checked_class<T>::value_type;
  using base = std::numeric_limits<value_type>;

public:

  static constexpr bool is_specialized = true;

  static constexpr sst::checked_class<T> min() noexcept {
    return base::min();
  }

  static constexpr sst::checked_class<T> max() noexcept {
    return base::max();
  }

  static constexpr sst::checked_class<T> lowest() noexcept {
    return base::lowest();
  }

  static constexpr int digits = base::digits;

  static constexpr int digits10 = base::digits10;

  static constexpr int max_digits10 = base::max_digits10;

  static constexpr bool is_signed = base::is_signed;

  static constexpr bool is_integer = base::is_integer;

  static constexpr bool is_exact = base::is_exact;

  static constexpr int radix = base::radix;

  static constexpr sst::checked_class<T> epsilon() noexcept {
    return base::epsilon();
  }

  static constexpr sst::checked_class<T> round_error() noexcept {
    return base::round_error();
  }

  static constexpr int min_exponent = base::min_exponent;

  static constexpr int min_exponent10 = base::min_exponent10;

  static constexpr int max_exponent = base::max_exponent;

  static constexpr int max_exponent10 = base::max_exponent10;

  static constexpr bool has_infinity = base::has_infinity;

  static constexpr bool has_quiet_NaN = base::has_quiet_NaN;

  static constexpr bool has_signaling_NaN = base::has_signaling_NaN;

  static constexpr float_denorm_style has_denorm = base::has_denorm;

  static constexpr bool has_denorm_loss = base::has_denorm_loss;

  static constexpr sst::checked_class<T> infinity() noexcept {
    return base::infinity();
  }

  static constexpr sst::checked_class<T> quiet_NaN() noexcept {
    return base::quiet_NaN();
  }

  static constexpr sst::checked_class<T> signaling_NaN() noexcept {
    return base::signaling_NaN();
  }

  static constexpr sst::checked_class<T> denorm_min() noexcept {
    return base::denorm_min();
  }

  static constexpr bool is_iec559 = base::is_iec559;

  static constexpr bool is_bounded = base::is_bounded;

  static constexpr bool is_modulo = false;

  static constexpr bool traps = base::traps;

  static constexpr bool tinyness_before = base::tinyness_before;

  static constexpr float_round_style round_style = base::round_style;

}; //

template<class T>
constexpr bool numeric_limits<sst::checked_class<T>>::is_specialized;

template<class T>
constexpr int numeric_limits<sst::checked_class<T>>::digits;

template<class T>
constexpr int numeric_limits<sst::checked_class<T>>::digits10;

template<class T>
constexpr int numeric_limits<sst::checked_class<T>>::max_digits10;

template<class T>
constexpr bool numeric_limits<sst::checked_class<T>>::is_signed;

template<class T>
constexpr bool numeric_limits<sst::checked_class<T>>::is_integer;

template<class T>
constexpr bool numeric_limits<sst::checked_class<T>>::is_exact;

template<class T>
constexpr int numeric_limits<sst::checked_class<T>>::radix;

template<class T>
constexpr int numeric_limits<sst::checked_class<T>>::min_exponent;

template<class T>
constexpr int numeric_limits<sst::checked_class<T>>::min_exponent10;

template<class T>
constexpr int numeric_limits<sst::checked_class<T>>::max_exponent;

template<class T>
constexpr int numeric_limits<sst::checked_class<T>>::max_exponent10;

template<class T>
constexpr bool numeric_limits<sst::checked_class<T>>::has_infinity;

template<class T>
constexpr bool numeric_limits<sst::checked_class<T>>::has_quiet_NaN;

template<class T>
constexpr bool numeric_limits<sst::checked_class<T>>::has_signaling_NaN;

template<class T>
constexpr float_denorm_style
    numeric_limits<sst::checked_class<T>>::has_denorm;

template<class T>
constexpr bool numeric_limits<sst::checked_class<T>>::has_denorm_loss;

template<class T>
constexpr bool numeric_limits<sst::checked_class<T>>::is_iec559;

template<class T>
constexpr bool numeric_limits<sst::checked_class<T>>::is_bounded;

template<class T>
constexpr bool numeric_limits<sst::checked_class<T>>::is_modulo;

template<class T>
constexpr bool numeric_limits<sst::checked_class<T>>::traps;

template<class T>
constexpr bool numeric_limits<sst::checked_class<T>>::tinyness_before;

template<class T>
constexpr float_round_style
    numeric_limits<sst::checked_class<T>>::round_style;

template<class T>
class numeric_limits<sst::checked_class<T> const>
    : public numeric_limits<sst::checked_class<T>> {};

template<class T>
class numeric_limits<sst::checked_class<T> volatile>
    : public numeric_limits<sst::checked_class<T>> {};

template<class T>
class numeric_limits<sst::checked_class<T> const volatile>
    : public numeric_limits<sst::checked_class<T>> {};

} // namespace std

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/is_integer_like.hpp>

SST_STATIC_ASSERT(sst::is_integer_like<sst::checked_class<int>>::value);

#endif

//----------------------------------------------------------------------

#endif // SST_CATALOG_CHECKED_CLASS_HPP
