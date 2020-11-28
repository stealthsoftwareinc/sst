//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_SST_CPP_CONSTEXPR_HPP
#define SST_CATALOG_SST_CPP_CONSTEXPR_HPP

#include <sst/catalog/SST_CPP_OR_LATER.hpp>

#if SST_CPP14_OR_LATER
#define SST_CPP14_CONSTEXPR constexpr
#else
#define SST_CPP14_CONSTEXPR
#endif

#if SST_CPP17_OR_LATER
#define SST_CPP17_CONSTEXPR constexpr
#else
#define SST_CPP17_CONSTEXPR
#endif

#if SST_CPP20_OR_LATER
#define SST_CPP20_CONSTEXPR constexpr
#else
#define SST_CPP20_CONSTEXPR
#endif

#endif // SST_CATALOG_SST_CPP_CONSTEXPR_HPP
