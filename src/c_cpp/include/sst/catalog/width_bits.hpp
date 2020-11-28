//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_WIDTH_BITS_HPP
#define SST_CATALOG_WIDTH_BITS_HPP

#include <sst/catalog/value_bits.hpp>
#include <type_traits>

namespace sst {

template<class IntType, class = void>
struct width_bits;

template<class IntType>
struct width_bits<
    IntType,
    typename std::enable_if<std::is_integral<IntType>::value>::type>
    : std::integral_constant<int,
                             sst::value_bits<IntType>::value
                                 + static_cast<int>(
                                     std::is_signed<IntType>::value)> {
};

} // namespace sst

#endif // SST_CATALOG_WIDTH_BITS_HPP
