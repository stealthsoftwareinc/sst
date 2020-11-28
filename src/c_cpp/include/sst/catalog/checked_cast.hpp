//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_CHECKED_CAST_HPP
#define SST_CATALOG_CHECKED_CAST_HPP

#include <sst/catalog/checked.hpp>
#include <sst/language.h>

namespace sst {

template<class T, class U>
SST_CPP14_CONSTEXPR T checked_cast(U const x) {
  return checked<T>(x).v();
}

} // namespace sst

#endif // SST_CATALOG_CHECKED_CAST_HPP
