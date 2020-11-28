/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_wall_time_null_live</code>
 * object.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_SST_WALL_TIME_NULL_LIVE_H
#define SST_SST_WALL_TIME_NULL_LIVE_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_OBJECT.h>

/* end_includes */

/**
 * Indicates that an object of type
 * <code>::sst_wall_time_null</code>
 * is probably valid.
 * <p>
 * The value of this variable is the least residue
 * of&nbsp;0x2CA392F8
 * modulo&nbsp;<code>UINT_MAX</code>&nbsp;+&nbsp;1.
 * </p>
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_DOXYGEN

SST_PUBLIC_C_OBJECT unsigned int const sst_wall_time_null_live;

#else

extern unsigned int const sst_wall_time_null_live;

#endif

#endif
