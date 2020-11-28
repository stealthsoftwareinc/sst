//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_UNSIGNED_LT_HPP
#define SST_CATALOG_UNSIGNED_LT_HPP

#include <sst/catalog/to_unsigned.hpp>

namespace sst {

template<class IntType1, class IntType2>
constexpr bool unsigned_lt(IntType1 const a,
                           IntType2 const b) noexcept {
  return sst::to_unsigned(a) < sst::to_unsigned(b);
}

} // namespace sst

#endif // SST_CATALOG_UNSIGNED_LT_HPP
