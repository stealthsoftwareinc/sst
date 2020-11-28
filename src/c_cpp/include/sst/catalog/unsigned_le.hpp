//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_UNSIGNED_LE_HPP
#define SST_CATALOG_UNSIGNED_LE_HPP

#include <sst/catalog/unsigned_gt.hpp>

namespace sst {

template<class IntType1, class IntType2>
constexpr bool unsigned_le(IntType1 const a,
                           IntType2 const b) noexcept {
  return !sst::unsigned_gt(a, b);
}

} // namespace sst

#endif // SST_CATALOG_UNSIGNED_LE_HPP
