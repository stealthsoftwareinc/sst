//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_MAKE_CHECKED_HPP
#define SST_CATALOG_MAKE_CHECKED_HPP

#include <sst/catalog/checked.hpp>
#include <type_traits>

namespace sst {

template<class T,
         typename std::enable_if<+std::is_integral<T>(), int>::type = 0>
checked<T> make_checked(T const x) noexcept {
  return checked<T>(x);
}

} // namespace sst

#endif // SST_CATALOG_MAKE_CHECKED_HPP
