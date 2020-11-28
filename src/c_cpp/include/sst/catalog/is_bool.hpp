//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_IS_BOOL_HPP
#define SST_CATALOG_IS_BOOL_HPP

#include <type_traits>

namespace sst {

template<class, class = void>
struct is_bool : std::false_type {};

template<class T>
struct is_bool<T,
               typename std::enable_if<
                   std::is_same<typename std::remove_cv<T>::type,
                                bool>::value>::type> : std::true_type {
};

} // namespace sst

#endif // SST_CATALOG_IS_BOOL_HPP
