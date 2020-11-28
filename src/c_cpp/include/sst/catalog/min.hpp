//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_MIN_HPP
#define SST_CATALOG_MIN_HPP

namespace sst {

template<class T>
constexpr T const & min(T const & a, T const & b) {
  return a < b ? a : b;
}

} // namespace sst

#endif // SST_CATALOG_MIN_HPP
