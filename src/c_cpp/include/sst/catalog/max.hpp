//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_MAX_HPP
#define SST_CATALOG_MAX_HPP

namespace sst {

template<class T>
constexpr T const & max(T const & a, T const & b) {
  return a < b ? b : a;
}

} // namespace sst

#endif // SST_CATALOG_MAX_HPP
