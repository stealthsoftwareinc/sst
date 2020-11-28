//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_UCHAR_MAX_HPP
#define SST_CATALOG_UCHAR_MAX_HPP

#include <sst/catalog/SST_CPP_INLINE.hpp>
#include <sst/catalog/type_max.hpp>

namespace sst {

using uchar_max = sst::type_max<unsigned char>;

SST_CPP17_INLINE constexpr unsigned char uchar_max_v =
    sst::uchar_max::value;

} // namespace sst

#endif // SST_CATALOG_UCHAR_MAX_HPP
