/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_LANGUAGE_H
#define SST_LANGUAGE_H

#include <sst/config.h>

/*----------------------------------------------------------------------
// C and C++
//--------------------------------------------------------------------*/

/*----------------------------------------------------------------------
// C only
//--------------------------------------------------------------------*/
#ifndef __cplusplus

#include <sst/catalog/SST_C_OR_LATER.h>
#include <sst/catalog/SST_C_VALUE.h>
#include <sst/catalog/SST_STATIC_ASSERT.h>

/*----------------------------------------------------------------------
// C++ only
//--------------------------------------------------------------------*/
#elif SST_WITH_BUILD_GROUP_CPP_AUTOTOOLS

#include <sst/catalog/SST_CONSTEXPR_ASSERT.hpp>
#include <sst/catalog/SST_CPP_CONSTEXPR.hpp>
#include <sst/catalog/SST_CPP_INLINE.hpp>
#include <sst/catalog/SST_CPP_OR_LATER.hpp>
#include <sst/catalog/SST_CPP_VALUE.hpp>
#include <sst/catalog/SST_STATIC_ASSERT.hpp>

/*--------------------------------------------------------------------*/
#endif

#endif /* SST_LANGUAGE_H */
