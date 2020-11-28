//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_UNSIGNED_NE_HPP
#define SST_CATALOG_UNSIGNED_NE_HPP

#include <sst/catalog/unsigned_eq.hpp>

namespace sst {

template<class IntType1, class IntType2>
constexpr bool unsigned_ne(IntType1 const a,
                           IntType2 const b) noexcept {
  return !sst::unsigned_eq(a, b);
}

} // namespace sst

#endif // SST_CATALOG_UNSIGNED_NE_HPP
