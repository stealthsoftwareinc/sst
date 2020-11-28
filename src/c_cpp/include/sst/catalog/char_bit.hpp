//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_CHAR_BIT_HPP
#define SST_CATALOG_CHAR_BIT_HPP

#include <sst/catalog/SST_CPP_INLINE.hpp>
#include <sst/catalog/width_bits.hpp>

namespace sst {

using char_bit = sst::width_bits<unsigned char>;

SST_CPP17_INLINE constexpr int char_bit_v = sst::char_bit::value;

} // namespace sst

#endif // SST_CATALOG_CHAR_BIT_HPP
