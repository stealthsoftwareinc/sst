//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_SST_STATIC_ASSERT_HPP
#define SST_CATALOG_SST_STATIC_ASSERT_HPP

#include <sst/catalog/SST_CPP_OR_LATER.hpp>

#if SST_CPP17_OR_LATER
#define SST_STATIC_ASSERT(x) static_assert(x)
#else
#define SST_STATIC_ASSERT(x) static_assert(x, #x)
#endif

#endif // SST_CATALOG_SST_STATIC_ASSERT_HPP