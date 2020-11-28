//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_IS_EXACT_WIDTH_INTEGER_HPP
#define SST_CATALOG_IS_EXACT_WIDTH_INTEGER_HPP

#include <cstdint>
#include <type_traits>

namespace sst {

template<class, class = void>
struct is_exact_width_integer : std::false_type {};

template<class T>
struct is_exact_width_integer<
    T,
    typename std::enable_if<
        false
#ifdef INT8_MAX
        || std::is_same<typename std::remove_cv<T>::type,
                        std::int8_t>::value
#endif
#ifdef UINT8_MAX
        || std::is_same<typename std::remove_cv<T>::type,
                        std::uint8_t>::value
#endif
#ifdef INT16_MAX
        || std::is_same<typename std::remove_cv<T>::type,
                        std::int16_t>::value
#endif
#ifdef UINT16_MAX
        || std::is_same<typename std::remove_cv<T>::type,
                        std::uint16_t>::value
#endif
#ifdef INT32_MAX
        || std::is_same<typename std::remove_cv<T>::type,
                        std::int32_t>::value
#endif
#ifdef UINT32_MAX
        || std::is_same<typename std::remove_cv<T>::type,
                        std::uint32_t>::value
#endif
#ifdef INT64_MAX
        || std::is_same<typename std::remove_cv<T>::type,
                        std::int64_t>::value
#endif
#ifdef UINT64_MAX
        || std::is_same<typename std::remove_cv<T>::type,
                        std::uint64_t>::value
#endif
        >::type> : std::true_type {
};

} // namespace sst

#endif // SST_CATALOG_IS_EXACT_WIDTH_INTEGER_HPP
