/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_CATALOG_SST_STATIC_ASSERT_H
#define SST_CATALOG_SST_STATIC_ASSERT_H

#include <sst/catalog/SST_C_OR_LATER.h>

#if SST_C11_OR_LATER
#define SST_STATIC_ASSERT(x) _Static_assert(x, #x)
#else
#define SST_STATIC_ASSERT(x) extern int sst_static_assert[(x) ? 1 : -1]
#endif

#endif /* SST_CATALOG_SST_STATIC_ASSERT_H */
