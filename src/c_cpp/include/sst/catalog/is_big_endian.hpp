//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_IS_BIG_ENDIAN_HPP
#define SST_CATALOG_IS_BIG_ENDIAN_HPP

#include <sst/catalog/SST_CPP_OR_LATER.hpp>
#include <sst/type.h>
#include <type_traits>

#if SST_CPP20_OR_LATER
#include <bit>
#endif

namespace sst {

template<class, class = void>
struct is_big_endian : std::false_type {};

template<class T>
struct is_big_endian<
    T,
    typename std::enable_if<
        false
        || (sst::is_non_bool_integer<T>::value
            && (sizeof(T) == 1
#if SST_CPP20_OR_LATER
                || std::endian::native == std::endian::big
#endif
#if defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__)
                || __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#endif
                ))>::type> : std::true_type {
};

} // namespace sst

#endif // SST_CATALOG_IS_BIG_ENDIAN_HPP
