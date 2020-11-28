//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_BIT_HPP
#define SST_BIT_HPP

#include <cassert>
#include <limits>
#include <sst/catalog/ones_mask.hpp>
#include <sst/catalog/type_msb.hpp>
#include <sst/catalog/uchar_msb.hpp>
#include <sst/integer.h>
#include <sst/language.h>
#include <sst/limits.h>
#include <type_traits>

namespace sst {

//----------------------------------------------------------------------
// sst::get_bit
//----------------------------------------------------------------------

template<
    class X,
    class Q,
    class R,
    typename std::enable_if<std::is_integral<X>::value, int>::type = 0>
constexpr bool get_bit(X const x, Q const q, R const r) noexcept {
  SST_STATIC_ASSERT(std::is_integral<X>::value);
  SST_STATIC_ASSERT(std::is_integral<Q>::value);
  SST_STATIC_ASSERT(std::is_integral<R>::value);
  SST_CONSTEXPR_ASSERT(!is_negative(q));
  SST_CONSTEXPR_ASSERT(!is_negative(r));
  using UX = typename promote_unsigned<X>::type;
#define SST_X_is_signed (std::is_signed<X>::value)
#define SST_X_width (std::numeric_limits<X>::digits + SST_X_is_signed)
#define SST_char_bit (std::numeric_limits<unsigned char>::digits)
  SST_CONSTEXPR_ASSERT(unsigned_le(r, SST_X_width - 1));
  SST_CONSTEXPR_ASSERT(unsigned_le(
      q, (SST_X_width - 1 - static_cast<int>(r)) / SST_char_bit));
#define SST_i (static_cast<int>(q) * SST_char_bit + static_cast<int>(r))
#define SST_mask (static_cast<UX>(1) << SST_i)
  return SST_X_is_signed && SST_i == SST_X_width - 1 ?
      is_negative(x) :
      static_cast<bool>(static_cast<UX>(x) & SST_mask);
#undef SST_mask
#undef SST_i
#undef SST_char_bit
#undef SST_X_width
#undef SST_X_is_signed
}

template<
    class X,
    class R,
    typename std::enable_if<std::is_integral<X>::value, int>::type = 0>
constexpr bool get_bit(X const x, R const r) noexcept {
  return get_bit(x, 0, r);
}

template<class Q, class R>
bool get_bit(void const * const x, Q const q, R const r) noexcept {
  SST_STATIC_ASSERT(std::is_integral<Q>::value);
  SST_STATIC_ASSERT(std::is_integral<R>::value);
  assert(x != nullptr);
  assert(!is_negative(q));
  assert(!is_negative(r));
  auto const rq = r / std::numeric_limits<unsigned char>::digits;
  auto const rr = r % std::numeric_limits<unsigned char>::digits;
  return static_cast<bool>(
      *(static_cast<unsigned char const *>(x) + q + rq) &
      static_cast<unsigned char>(1U << rr));
}

template<class R>
bool get_bit(void const * const x, R const r) noexcept {
  return get_bit(x, 0, r);
}

//----------------------------------------------------------------------
// sst::set_bit
//----------------------------------------------------------------------

template<
    class X,
    class Q,
    class R,
    typename std::enable_if<std::is_integral<X>::value, int>::type = 0>
constexpr X
set_bit(X const x, Q const q, R const r, bool const b) noexcept {
  SST_STATIC_ASSERT(std::is_integral<X>::value);
  SST_STATIC_ASSERT(std::is_integral<Q>::value);
  SST_STATIC_ASSERT(std::is_integral<R>::value);
  SST_CONSTEXPR_ASSERT(!is_negative(q));
  SST_CONSTEXPR_ASSERT(!is_negative(r));
  using UX = typename promote_unsigned<X>::type;
#define SST_X_max (std::numeric_limits<X>::max())
#define SST_X_is_signed (std::is_signed<X>::value)
#define SST_X_width (std::numeric_limits<X>::digits + SST_X_is_signed)
#define SST_char_bit (std::numeric_limits<unsigned char>::digits)
  SST_CONSTEXPR_ASSERT(unsigned_le(r, SST_X_width - 1));
  SST_CONSTEXPR_ASSERT(unsigned_le(
      q, (SST_X_width - 1 - static_cast<int>(r)) / SST_char_bit));
#define SST_i (static_cast<int>(q) * SST_char_bit + static_cast<int>(r))
#define SST_mask (static_cast<UX>(1) << SST_i)
  return SST_X_is_signed && SST_i == SST_X_width - 1 ?
      (b == is_negative(x) ? x :
                             b ? x - SST_X_max - static_cast<X>(1) :
                                 x + SST_X_max + static_cast<X>(1)) :
      static_cast<X>(
          (b ? static_cast<UX>(x) | SST_mask :
               static_cast<UX>(x) & ~SST_mask) &
          static_cast<UX>(SST_X_max)) -
          (is_negative(x) ? SST_X_max : static_cast<X>(0)) -
          (is_negative(x) ? static_cast<X>(1) : static_cast<X>(0));
#undef SST_mask
#undef SST_i
#undef SST_char_bit
#undef SST_X_width
#undef SST_X_is_signed
#undef SST_X_max
}

template<
    class X,
    class R,
    typename std::enable_if<std::is_integral<X>::value, int>::type = 0>
constexpr X set_bit(X const x, R const r, bool const b) noexcept {
  return set_bit(x, 0, r, b);
}

template<class Q, class R>
void *
set_bit(void * const x, Q const q, R const r, bool const b) noexcept {
  SST_STATIC_ASSERT(std::is_integral<Q>::value);
  SST_STATIC_ASSERT(std::is_integral<R>::value);
  assert(x != nullptr);
  assert(!is_negative(q));
  assert(!is_negative(r));
  auto const rq = r / std::numeric_limits<unsigned char>::digits;
  auto const rr = r % std::numeric_limits<unsigned char>::digits;
  if (b) {
    *(static_cast<unsigned char *>(x) + q + rq) |=
        static_cast<unsigned char>(1U << rr);
  } else {
    *(static_cast<unsigned char *>(x) + q + rq) &=
        static_cast<unsigned char>(~(1U << rr));
  }
  return x;
}

template<class R>
void * set_bit(void * const x, R const r, bool const b) noexcept {
  return set_bit(x, 0, r, b);
}

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_BIT_HPP
