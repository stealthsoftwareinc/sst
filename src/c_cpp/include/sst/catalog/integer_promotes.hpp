//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_PROMOTES_HPP
#define SST_CATALOG_PROMOTES_HPP

#include <sst/catalog/integer_promote.hpp>
#include <sst/language.h>
#include <type_traits>

namespace sst {

template<class T, class = void>
struct integer_promotes : std::false_type {
  SST_STATIC_ASSERT(std::is_integral<T>());
};

template<class T>
struct integer_promotes<
    T,
    typename std::enable_if<
        !std::is_same<T, typename integer_promote<T>::type>()>::type>
    : std::true_type {};

} // namespace sst

#endif // SST_CATALOG_PROMOTES_HPP
