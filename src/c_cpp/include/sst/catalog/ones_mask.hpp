//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_ONES_MASK_HPP
#define SST_CATALOG_ONES_MASK_HPP

#include <sst/catalog/SST_CONSTEXPR_ASSERT.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/unsigned_le.hpp>
#include <sst/catalog/value_bits.hpp>
#include <type_traits>

namespace sst {

template<class IntType1,
         class IntType2,
         typename std::enable_if<std::is_integral<IntType1>()
                                     && std::is_integral<IntType2>(),
                                 int>::type = 0>
constexpr IntType1 ones_mask(IntType2 const n) noexcept {
  SST_CONSTEXPR_ASSERT(!sst::is_negative(n));
  SST_CONSTEXPR_ASSERT(
      sst::unsigned_le(n, sst::value_bits<IntType1>::value));
  return n == 0 ? static_cast<IntType1>(0) :
                  static_cast<IntType1>(sst::type_max<IntType1>()
                                        >> (sst::value_bits<IntType1>()
                                            - static_cast<int>(n)));
}

template<class IntType1,
         class IntType2,
         class IntType3,
         typename std::enable_if<std::is_integral<IntType1>()
                                     && std::is_integral<IntType2>()
                                     && std::is_integral<IntType3>(),
                                 int>::type = 0>
constexpr IntType1 ones_mask(IntType2 const n,
                             IntType3 const k) noexcept {
  SST_CONSTEXPR_ASSERT(!sst::is_negative(n));
  SST_CONSTEXPR_ASSERT(!sst::is_negative(k));
  SST_CONSTEXPR_ASSERT(
      sst::unsigned_le(n, sst::value_bits<IntType1>::value));
  SST_CONSTEXPR_ASSERT(sst::unsigned_le(k,
                                        sst::value_bits<IntType1>()
                                            - static_cast<int>(n)));
  return static_cast<IntType1>(sst::ones_mask<IntType1>(n) << k);
}

} // namespace sst

#endif // SST_CATALOG_ONES_MASK_HPP
