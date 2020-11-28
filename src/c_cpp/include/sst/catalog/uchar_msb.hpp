//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_UCHAR_MSB_HPP
#define SST_CATALOG_UCHAR_MSB_HPP

#include <sst/catalog/SST_CPP_INLINE.hpp>
#include <sst/catalog/type_msb.hpp>

namespace sst {

using uchar_msb = sst::type_msb<unsigned char>;

SST_CPP17_INLINE constexpr unsigned char uchar_msb_v =
    sst::uchar_msb::value;

} // namespace sst

#endif // SST_CATALOG_UCHAR_MSB_HPP
