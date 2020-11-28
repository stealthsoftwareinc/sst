/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_wall_time_CLOCK_MONOTONIC_live</code>
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

#ifndef SST_SST_WALL_TIME_CLOCK_MONOTONIC_LIVE_H
#define SST_SST_WALL_TIME_CLOCK_MONOTONIC_LIVE_H

#include <sst/SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC.h>
#if SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_OBJECT.h>

/* end_includes */

/**
 * Indicates that an object of type
 * <code>::sst_wall_time_CLOCK_MONOTONIC</code>
 * is probably valid.
 * <p>
 * The value of this variable is the least residue
 * of&nbsp;0xB15CB0A1
 * modulo&nbsp;<code>UINT_MAX</code>&nbsp;+&nbsp;1.
 * </p>
 *
 * @available
 * if and only if the
 * <code>::SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC</code>
 * macro is defined to the integer
 * constant&nbsp;<code>1</code>
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

SST_PUBLIC_C_OBJECT unsigned int const sst_wall_time_CLOCK_MONOTONIC_live;

#else

extern unsigned int const sst_wall_time_CLOCK_MONOTONIC_live;

#endif

#endif

#endif
