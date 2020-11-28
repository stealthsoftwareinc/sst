//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_TYPE_MSB_HPP
#define SST_CATALOG_TYPE_MSB_HPP

#include <sst/catalog/type_max.hpp>
#include <type_traits>

namespace sst {

template<class T, class = void>
struct type_msb;

template<class IntType>
struct type_msb<
    IntType,
    typename std::enable_if<std::is_integral<IntType>::value>::type>
    : std::integral_constant<IntType,
                             static_cast<IntType>(
                                 sst::type_max<IntType>::value
                                 ^ (sst::type_max<IntType>::value
                                    >> 1))> {};

} // namespace sst

#endif // SST_CATALOG_TYPE_MSB_HPP
