//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_VALUE_BITS_HPP
#define SST_CATALOG_VALUE_BITS_HPP

#include <limits>
#include <type_traits>

namespace sst {

template<class IntType, class = void>
struct value_bits;

template<class IntType>
struct value_bits<
    IntType,
    typename std::enable_if<std::is_integral<IntType>::value>::type>
    : std::integral_constant<int,
                             std::numeric_limits<IntType>::digits> {};

} // namespace sst

#endif // SST_CATALOG_VALUE_BITS_HPP
