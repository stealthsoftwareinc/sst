//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_PERFECT_GE_HPP
#define SST_CATALOG_PERFECT_GE_HPP

#include <sst/catalog/perfect_lt.hpp>

namespace sst {

template<class IntType1, class IntType2>
constexpr bool perfect_ge(IntType1 const a, IntType2 const b) noexcept {
  return !sst::perfect_lt(a, b);
}

} // namespace sst

#endif // SST_CATALOG_PERFECT_GE_HPP
