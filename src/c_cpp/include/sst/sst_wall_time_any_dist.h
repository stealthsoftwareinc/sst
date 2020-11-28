/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_wall_time_any_dist</code>
 * function.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_SST_WALL_TIME_ANY_DIST_H
#define SST_SST_WALL_TIME_ANY_DIST_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_wall_time_any.h>

/* end_includes */

/**
 *
 * @param t1
 *
 * @param t2
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

SST_PUBLIC_C_FUNCTION double (sst_wall_time_any_dist)(
  sst_wall_time_any const *,
  sst_wall_time_any const *
);

#else

double sst_wall_time_any_dist(
  sst_wall_time_any const * t1,
  sst_wall_time_any const * t2
);

#endif

#endif
