/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_wall_time_CLOCK_MONOTONIC</code>
 * type.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_SST_WALL_TIME_CLOCK_MONOTONIC_H
#define SST_SST_WALL_TIME_CLOCK_MONOTONIC_H

#include <sst/SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC.h>
#if SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC

struct sst_wall_time_CLOCK_MONOTONIC_ut;

/**
 * A synonym for the
 * <code>::sst_wall_time_CLOCK_MONOTONIC_ut</code>
 * type.
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

typedef struct sst_wall_time_CLOCK_MONOTONIC_ut sst_wall_time_CLOCK_MONOTONIC;

#endif

#endif
