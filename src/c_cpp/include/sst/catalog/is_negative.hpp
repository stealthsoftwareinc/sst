//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_IS_NEGATIVE_HPP
#define SST_CATALOG_IS_NEGATIVE_HPP

#include <sst/language.h>
#include <sst/type.h>
#include <type_traits>

namespace sst {

template<class T,
         typename std::enable_if<sst::is_signed_integer<T>::value,
                                 int>::type = 0>
constexpr bool is_negative(T const x) noexcept {
  return x < 0;
}

template<class T,
         typename std::enable_if<!sst::is_signed_integer<T>::value,
                                 int>::type = 0>
constexpr bool is_negative(T) noexcept {
  SST_STATIC_ASSERT(sst::is_unsigned_integer<T>::value);
  return false;
}

} // namespace sst

#endif // SST_CATALOG_IS_NEGATIVE_HPP
