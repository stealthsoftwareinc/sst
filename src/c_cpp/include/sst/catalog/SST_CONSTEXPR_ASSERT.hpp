//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_SST_CONSTEXPR_ASSERT_HPP
#define SST_CATALOG_SST_CONSTEXPR_ASSERT_HPP

#include <cassert>
#include <sst/catalog/SST_CPP_OR_LATER.hpp>

#if SST_CPP14_OR_LATER
#define SST_CONSTEXPR_ASSERT(x) assert(x)
#else
#define SST_CONSTEXPR_ASSERT(x)
#endif

#endif // SST_CATALOG_SST_CONSTEXPR_ASSERT_HPP
