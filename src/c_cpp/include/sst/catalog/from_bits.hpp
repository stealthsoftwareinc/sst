//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_FROM_BITS_HPP
#define SST_CATALOG_FROM_BITS_HPP

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <sst/bit.h>
#include <sst/catalog/char_bit.hpp>
#include <sst/catalog/is_exact_width_integer.hpp>
#include <sst/catalog/is_little_endian.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/promote_unsigned.hpp>
#include <sst/catalog/unsigned_ne.hpp>
#include <sst/catalog/width_bits.hpp>
#include <sst/integer.h>
#include <sst/language.h>
#include <type_traits>

namespace sst {

template<
    class Y,
    bool SignExtend = std::is_signed<Y>::value,
    class Q,
    class R,
    class N,
    typename std::enable_if<std::is_integral<Y>::value, int>::type = 0>
Y from_bits(void const * const x,
            Q const q,
            R const r,
            N const n) noexcept {
  SST_STATIC_ASSERT(std::is_integral<Y>::value);
  SST_STATIC_ASSERT(std::is_integral<Q>::value);
  SST_STATIC_ASSERT(std::is_integral<R>::value);
  SST_STATIC_ASSERT(std::is_integral<N>::value);

  assert(x != nullptr);
  assert(!sst::is_negative(q));
  assert(!sst::is_negative(r));
  assert(n > 0);

  auto const xp = reinterpret_cast<unsigned char const *>(x);
  auto const qu = sst::to_unsigned(q);
  auto const ru = sst::to_unsigned(r);
  auto const nu = sst::to_unsigned(n);
  constexpr auto cbu = sst::to_unsigned(sst::char_bit_v);

  if (sst::is_exact_width_integer<Y>::value
      && sst::is_little_endian<Y>::value && ru % cbu == 0
      && nu / cbu >= sizeof(Y)) {
    Y y;
    auto const src = xp + qu + ru / cbu;
    auto const end = src + sizeof(Y);
    auto const dst = reinterpret_cast<unsigned char *>(&y);
    std::copy(src, end, dst);
    return y;
  }

  using sz = typename sst::promote_unsigned<std::size_t>::type;
  using UR = typename sst::promote_unsigned<R>::type;
  Y y = 0;
  constexpr int Y_width = sst::width_bits<Y>::value;
  constexpr sz char_bit = std::numeric_limits<unsigned char>::digits;
  constexpr sz size_max = std::numeric_limits<std::size_t>::max();
  sz i = static_cast<sz>(q)
         + static_cast<sz>(static_cast<UR>(r) / char_bit);
  sz j = static_cast<sz>(static_cast<UR>(r) % char_bit);
  int k = 0;
  bool b = false;
  for (; k != Y_width && sst::unsigned_ne(k, n); ++k) {
    b = get_bit(x, i, j);
    y = set_bit(y, k, b);
    if (j == size_max) {
      i += j / char_bit;
      j %= char_bit;
    }
    ++j;
  }
  if (SignExtend && b) {
    for (; k != Y_width; ++k) {
      y = set_bit(y, k, b);
    }
  }
  return y;
}

template<
    class Y,
    bool SignExtend = std::is_signed<Y>::value,
    class R,
    class N,
    typename std::enable_if<std::is_integral<Y>::value, int>::type = 0>
Y from_bits(void const * const x, R const r, N const n) noexcept {
  return from_bits<Y, SignExtend>(x, 0, r, n);
}

} // namespace sst

#endif // SST_CATALOG_FROM_BITS_HPP
