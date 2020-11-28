//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_PERFECT_EQ_HPP
#define SST_CATALOG_PERFECT_EQ_HPP

#include <sst/catalog/perfect_le.hpp>

namespace sst {

template<class IntType1, class IntType2>
constexpr bool perfect_eq(IntType1 const a, IntType2 const b) noexcept {
  return sst::perfect_le(a, b) && sst::perfect_le(b, a);
}

} // namespace sst

#endif // SST_CATALOG_PERFECT_EQ_HPP
