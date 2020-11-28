//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_TYPE_MAX_HPP
#define SST_CATALOG_TYPE_MAX_HPP

#include <limits>
#include <sst/language.h>
#include <type_traits>

namespace sst {

template<class T>
struct type_max
    : std::integral_constant<T, std::numeric_limits<T>::max()> {
  SST_STATIC_ASSERT(std::is_integral<T>::value);
};

} // namespace sst

#endif // SST_CATALOG_TYPE_MAX_HPP
