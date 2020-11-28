//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_TO_UNSIGNED_HPP
#define SST_CATALOG_TO_UNSIGNED_HPP

#include <sst/catalog/promote_unsigned.hpp>

namespace sst {

template<class T>
constexpr typename promote_unsigned<T>::type
to_unsigned(T const x) noexcept {
  return static_cast<typename promote_unsigned<T>::type>(x);
}

} // namespace sst

#endif // SST_CATALOG_TO_UNSIGNED_HPP
