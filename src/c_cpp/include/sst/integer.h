/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_INTEGER_H
#define SST_INTEGER_H

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

#include <sst/catalog/can_represent_all.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/perfect_eq.hpp>
#include <sst/catalog/perfect_ge.hpp>
#include <sst/catalog/perfect_gt.hpp>
#include <sst/catalog/perfect_le.hpp>
#include <sst/catalog/perfect_lt.hpp>
#include <sst/catalog/perfect_ne.hpp>
#include <sst/catalog/promote_unsigned.hpp>
#include <sst/catalog/promote_with_sign.hpp>
#include <sst/catalog/to_unsigned.hpp>
#include <sst/catalog/unsigned_eq.hpp>
#include <sst/catalog/unsigned_ge.hpp>
#include <sst/catalog/unsigned_gt.hpp>
#include <sst/catalog/unsigned_le.hpp>
#include <sst/catalog/unsigned_lt.hpp>
#include <sst/catalog/unsigned_ne.hpp>

/*--------------------------------------------------------------------*/
#endif

#endif /* SST_INTEGER_H */
