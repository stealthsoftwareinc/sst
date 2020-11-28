//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_CEIL_SQRT_HPP
#define SST_CATALOG_CEIL_SQRT_HPP

#include <cassert>
#include <sst/catalog/SST_CPP_CONSTEXPR.hpp>
#include <type_traits>

namespace sst {

template<
    class T,
    typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
SST_CPP14_CONSTEXPR T ceil_sqrt(T const x) noexcept {
  assert(x >= 0);
  if (x <= 1) {
    return x;
  }
  T a = 1;
  T b = x;
  while (a < b) {
    T const m = a / 2 + b / 2;
    if (m > x / m) {
      b = m;
    } else if (m * m < x) {
      a = m + 1;
    } else {
      return m;
    }
  }
  return a;
}

template<
    class T,
    typename std::enable_if<!std::is_integral<T>::value, int>::type = 0>
T ceil_sqrt(T const & x) {
  assert(x >= 0);
  if (x <= 1) {
    return x;
  }
  T a = 1;
  T b = x;
  while (a < b) {
    T const m = a / 2 + b / 2;
    if (m > x / m) {
      b = m;
    } else if (m * m < x) {
      a = m + 1;
    } else {
      return m;
    }
  }
  return a;
}

} // namespace sst

#endif // SST_CATALOG_CEIL_SQRT_HPP
