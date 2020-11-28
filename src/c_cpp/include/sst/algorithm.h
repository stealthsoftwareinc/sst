/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_ALGORITHM_H
#define SST_ALGORITHM_H

#include <sst/config.h>

/*----------------------------------------------------------------------
// C and C++
//--------------------------------------------------------------------*/

/*----------------------------------------------------------------------
// C only
//--------------------------------------------------------------------*/
#ifndef __cplusplus

/*----------------------------------------------------------------------
// C++ only
//--------------------------------------------------------------------*/
#elif SST_WITH_BUILD_GROUP_CPP_AUTOTOOLS

#include <sst/catalog/ceil_sqrt.hpp>
#include <sst/catalog/floor_sqrt.hpp>
#include <sst/catalog/max.hpp>
#include <sst/catalog/min.hpp>

/*--------------------------------------------------------------------*/
#endif

#endif /* SST_ALGORITHM_H */
