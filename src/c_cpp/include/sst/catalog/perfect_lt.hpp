//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_PERFECT_LT_HPP
#define SST_CATALOG_PERFECT_LT_HPP

#include <sst/catalog/integer_promote.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/unsigned_lt.hpp>
#include <sst/language.h>
#include <type_traits>

namespace sst {

template<class IntType1, class IntType2>
constexpr bool perfect_lt(IntType1 const a, IntType2 const b) noexcept {
  SST_STATIC_ASSERT(std::is_integral<IntType1>());
  SST_STATIC_ASSERT(std::is_integral<IntType2>());
  using P1 = typename sst::integer_promote<IntType1>::type;
  using P2 = typename sst::integer_promote<IntType2>::type;
  using S1 = typename std::make_signed<P1>::type;
  using S2 = typename std::make_signed<P2>::type;
  return sst::is_negative(a) ?
             !sst::is_negative(b)
                 || static_cast<S1>(a) < static_cast<S2>(b) :
             !sst::is_negative(b) && sst::unsigned_lt(a, b);
}

} // namespace sst

#endif // SST_CATALOG_PERFECT_LT_HPP
