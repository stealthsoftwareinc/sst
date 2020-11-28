//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_REMOVE_CVREF_HPP
#define SST_CATALOG_REMOVE_CVREF_HPP

#include <type_traits>

namespace sst {

template<class T>
struct remove_cvref {
  using type = typename std::remove_cv<
      typename std::remove_reference<T>::type>::type;
};

} // namespace sst

#endif // SST_CATALOG_REMOVE_CVREF_HPP
