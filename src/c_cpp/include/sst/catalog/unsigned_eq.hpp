//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_UNSIGNED_EQ_HPP
#define SST_CATALOG_UNSIGNED_EQ_HPP

#include <sst/catalog/unsigned_le.hpp>

namespace sst {

template<class IntType1, class IntType2>
constexpr bool unsigned_eq(IntType1 const a,
                           IntType2 const b) noexcept {
  return sst::unsigned_le(a, b) && sst::unsigned_le(b, a);
}

} // namespace sst

#endif // SST_CATALOG_UNSIGNED_EQ_HPP
