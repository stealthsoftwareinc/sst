/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_LIMITS_H
#define SST_LIMITS_H

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

#include <sst/catalog/char_bit.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/type_min.hpp>
#include <sst/catalog/uchar_max.hpp>
#include <sst/catalog/value_bits.hpp>
#include <sst/catalog/width_bits.hpp>

/*--------------------------------------------------------------------*/
#endif

#endif /* SST_LIMITS_H */
